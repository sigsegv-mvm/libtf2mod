#include "all.h"


DETOUR(sapper_extended_duration);
/* make the robosapper last for an extremely long time */


static void (*trampoline_CObjectSapper_ApplyRoboSapper)(CObjectSapper* this, CTFPlayer*, float, int);


static void detour_CObjectSapper_ApplyRoboSapper(CObjectSapper* this, CTFPlayer* player, float duration, int radius)
{
	trampoline_CObjectSapper_ApplyRoboSapper(this, player, 3600.0f, radius);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectSapper_ApplyRoboSapper);
	
	return true;
}
