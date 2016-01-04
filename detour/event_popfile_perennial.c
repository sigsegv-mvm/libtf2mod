#include "all.h"


DETOUR(event_popfile_perennial);
/* make EventPopfile Halloween work regardless of the holiday state */


static bool (*trampoline_UTIL_IsHolidayActive)(int);


static func_t *func_CTFBotSpawner_Spawn;


static bool detour_UTIL_IsHolidayActive(int holiday)
{
	if (holiday == HOLIDAY_HALLOWEENORFULLMOONORVALENTINES) {
		uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(__builtin_return_address(0));
		if (func_owns_addr(caller, func_CTFBotSpawner_Spawn)) {
			return true;
		}
	}
	
	return trampoline_UTIL_IsHolidayActive(holiday);
}


DETOUR_SETUP
{
	func_CTFBotSpawner_Spawn =
		func_register(CTFBotSpawner_Spawn);
	
	DETOUR_CREATE(UTIL_IsHolidayActive);
	
	return true;
}
