#include "all.h"


DETOUR(loadout_allow_holiday_items);
/* allow holiday-restricted items to be equipped at any time without having to
 * use heavy-handed measures like tf_forced_holiday */


static int (*trampoline_UTIL_GetHolidayForString)(char const*);


static int detour_UTIL_GetHolidayForString(char const* holiday)
{
	/* all the callers of this function will assume that an item is
	 * un-holiday-restricted if zero (HOLIDAY_NOHOLIDAY) is returned */
	return HOLIDAY_NOHOLIDAY;
}


DETOUR_SETUP
{
	DETOUR_CREATE(UTIL_GetHolidayForString);
	
	return true;
}
