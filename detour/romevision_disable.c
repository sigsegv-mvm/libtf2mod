#include "all.h"


#if 0
DETOUR(romevision_disable);
/* don't allow bots to equip Romevision items; also don't precache them */


static  (*trampoline_)(* this);


static  detour_(* this)
{
	
}


DETOUR_SETUP
{
	DETOUR_CREATE();
	
	return true;
}
#endif

// CBaseEntity::PrecacheModel
// models/bots/tw2/*

// CTFBot::AddItem
// tw_*

// CBaseEntity::SetModelIndexOverride(int, int)
// if caller is a CTFTankBoss and the first param is 3, skip it
//
// OR, maybe just overwrite s_TankModelRome with s_TankModel?

// tank stuff is trickier to remove
