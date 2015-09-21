#include "all.h"


DETOUR(debug_rescueranger_pickup_range);
/*  */


static bool (*trampoline_CTFPlayer_CanPickupBuilding)(CTFPlayer* this, CBaseObject*);


static bool detour_CTFPlayer_CanPickupBuilding(CTFPlayer* this, CBaseObject* bldg)
{
	bool result = trampoline_CTFPlayer_CanPickupBuilding(this, bldg);
	pr_debug("CanPickupBuilding: %s\n", (result ? "YES" : "NO"));
	
	return result;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CanPickupBuilding);
	
	return true;
}
