#include "all.h"


PATCH(redcredits_unrestrict_weaponid);
/* allow red credits to drop from revolver headshots */


static bool WeaponID_IsSniperRifleOrBowOrRevolver(int id)
{
	if (id == TF_WEAPON_REVOLVER) {
		return true;
	}
	
	return WeaponID_IsSniperRifleOrBow(id);
}


PATCH_CHECK
{
	uintptr_t off1 = CALC_RELJMP(CTFPlayer_Event_Killed, 0x08c9,
		WeaponID_IsSniperRifleOrBow);
	
	size_t check1_base = 0x08c4;
	uint8_t check1[] = {
		0xe8, CONV_LE(off1) // +08C4  call WeaponID_IsSniperRifleOrBow
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_Event_Killed,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	uintptr_t off1 = CALC_RELJMP(CTFPlayer_Event_Killed, 0x08c9,
		WeaponID_IsSniperRifleOrBowOrRevolver);
	
	
	size_t data1_base = 0x08c4;
	uint8_t data1[] = {
		0xe8, CONV_LE(off1) // +08C4  call WeaponID_IsSniperRifleOrBowOrRevolver
	};
	
	
	/* instead of calling WeaponID_IsSniperRifleOrBow, call our custom function,
	 * WeaponID_IsSniperRifleOrBowOrRevolver */
	func_write(CTFPlayer_Event_Killed,
		data1_base, sizeof(data1), data1);
}
