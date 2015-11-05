#include "all.h"


DETOUR(mvm_enable_dropped_weapons);
/*  */


static bool (*trampoline_CTFPlayer_ShouldDropAmmoPack)(CTFPlayer* this);
static void (*trampoline_CTFPlayer_Regenerate)(CTFPlayer* this, bool);


static func_t *func_CUpgrades_PlayerPurchasingUpgrade;


static bool detour_CTFPlayer_ShouldDropAmmoPack(CTFPlayer* this)
{
	return true;
}

static void detour_CTFPlayer_Regenerate(CTFPlayer* this, bool b1)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	/* don't regen every time players purchase an upgrade, because it messes
	 * with their loadout and causes havoc */
	if (func_owns_addr(caller,
		func_CUpgrades_PlayerPurchasingUpgrade)) {
		return;
	}
	
	trampoline_CTFPlayer_Regenerate(this, b1);
}


DETOUR_SETUP
{
	func_CUpgrades_PlayerPurchasingUpgrade =
		func_register(CUpgrades_PlayerPurchasingUpgrade);
	
	DETOUR_CREATE(CTFPlayer_ShouldDropAmmoPack);
	DETOUR_CREATE(CTFPlayer_Regenerate);
	
	return true;
}
