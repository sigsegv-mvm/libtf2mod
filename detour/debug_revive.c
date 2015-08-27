#include "all.h"


DETOUR(debug_revive);
/*  */


static unknown_t (*trampoline_CTFReviveMarker_AddMarkerHealth)(CTFReviveMarker* this, float);


static unknown_t detour_CTFReviveMarker_AddMarkerHealth(CTFReviveMarker* this, float amount)
{
	pr_debug("CTFReviveMarker::AddMarkerHealth(%.3f)\n", amount);
	return trampoline_CTFReviveMarker_AddMarkerHealth(this, amount);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFReviveMarker_AddMarkerHealth);
}
