#include "all.h"


DETOUR(mvm_extended_waveloss_time);
/* increases the length of humiliation time after losing a wave from 5 seconds
 * to some really long time period */


static int (*trampoline_CTFGameRules_GetBonusRoundTime)(CTFGameRules* this, bool);


static int detour_CTFGameRules_GetBonusRoundTime(CTFGameRules* this, bool b1)
{
	/* make the MvM post-wave-loss timer 10 minutes long */
	if (CTFGameRules_IsPVEModeActive(this)) {
		return 600;
	}
	
	
	return trampoline_CTFGameRules_GetBonusRoundTime(this, b1);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFGameRules_GetBonusRoundTime);
}
