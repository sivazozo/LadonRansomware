#include "ladon.h"
#ifdef __cplusplus
extern "C" {
#endif
	int _fltused = 0;
#ifdef __cplusplus
}
#endif
#define PUT(x,y) (PVOID)((ULONG) x + y)

void *_memcpy(void* dest, const void* src, SIZE_T count) {
	char* dest1 = (char*)dest;
	char* src1 = (char*)src;

	while (count--) {
		*dest1++ = *src1++;
	}
	return dest;
}

BOOL
LadonIsWindowOpen(LPWSTR *lpszClassName, DWORD dwNumDebug)
{
	
	BOOL bOpen = TRUE;
	/*
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snap = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap) {
		for (DWORD i = 0; i < dwNumDebug; i++) {
			if (_Process32FirstW(snap, &entry) == TRUE) {
				while (_Process32NextW(snap, &entry)) {
					if (_lstrcmpW(entry.szExeFile, lpszClassName[i])) {
						HANDLE hp = _OpenProcess(PROCESS_TERMINATE, 0, entry.th32ProcessID);
						if (hp) {
							_TerminateProcess(hp, 0);
							Junk(1, 4);
						}
						break;
					}
				}
			}
		}
		CloseHandle(snap);
	}
	*/
	return bOpen;
}

INT
Junk(INT a, INT b)
{
	
	_Sleep(a);

	return (a*(b));

}

BOOL
LadonCheckHWBreakpoints()
{
	CONTEXT cContext;

	LadonZeroMemory(&cContext, sizeof(cContext));

	cContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	return (_GetThreadContext(GetCurrentThread(), &cContext)
		&& (cContext.Dr0 || cContext.Dr1 || cContext.Dr2
			|| cContext.Dr3));
}

BOOL
LadonIsBeingDebugged()
{
	if (_IsDebuggerPresent() || LadonCheckHWBreakpoints()) {
	wtf:
		_ExitProcess(0);
		goto wtf;

		return TRUE;
	}
	return FALSE;
}