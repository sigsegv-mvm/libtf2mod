#include "all.h"


DETOUR(mvm_enable_dropped_weapons);
/*  */


static bool (*trampoline_CTFPlayer_ShouldDropAmmoPack)(CTFPlayer* this);


static bool detour_CTFPlayer_ShouldDropAmmoPack(CTFPlayer* this)
{
	return true;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_ShouldDropAmmoPack);
	
	return true;
}
