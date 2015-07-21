#include "all.h"


DETOUR(disposable_dispenser_part4);
/* determine whether a dispenser should be a mini-dispenser */


static bool (*trampoline_CObjectDispenser_ShouldBeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);


static bool detour_CObjectDispenser_ShouldBeMiniBuilding(CObjectDispenser* this, CTFPlayer* player)
{
	// TEMPORARY HACK!
	//return true;
	return false;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectDispenser_ShouldBeMiniBuilding);
}
