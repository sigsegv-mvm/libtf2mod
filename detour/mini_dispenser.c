#include "all.h"


DETOUR(mini_dispenser);
/* replaces the dispenser with a cute mini-dispenser;
 * also unconditionally makes sentries be mini-sentries */


static bool (*trampoline_CBaseObject_ShouldBeMiniBuilding)(CBaseObject* this, CTFPlayer*);
static bool (*trampoline_CObjectDispenser_ShouldBeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
static void (*trampoline_CObjectDispenser_MakeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);


static bool detour_CBaseObject_ShouldBeMiniBuilding(CBaseObject* this, CTFPlayer* player)
{
	pr_debug("%s: returning true\n", __func__);
	return true;
}


static bool detour_CObjectDispenser_ShouldBeMiniBuilding(CBaseObject* this, CTFPlayer* player)
{
	pr_debug("%s: returning true\n", __func__);
	return true;
}


static void detour_CObjectDispenser_MakeMiniBuilding(CBaseObject* this, CTFPlayer* player)
{
	trampoline_CObjectDispenser_MakeMiniBuilding(this, player);
	
	pr_debug("%s: setting model scale to 0.75\n", __func__);
	CBaseAnimating_SetModelScale(this, 0.75f, 0.0f);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CBaseObject_ShouldBeMiniBuilding);
	DETOUR_CREATE(CObjectDispenser_ShouldBeMiniBuilding);
	DETOUR_CREATE(CObjectDispenser_MakeMiniBuilding);
}
