#include "all.h"


DETOUR(tank_minigun_resistance_disable);
/* remove CTFTankBoss's 75% minigun damage resistance */


static void (*trampoline_CTFTankBoss_ModifyDamage)(CTFTankBoss* this, CTakeDamageInfo*);


static void detour_CTFTankBoss_ModifyDamage(CTFTankBoss* this, CTakeDamageInfo* info)
{
	/* don't modify the damage at all */
	return;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFTankBoss_ModifyDamage);
	
	return true;
}
