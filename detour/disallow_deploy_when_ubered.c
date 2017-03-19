#include "all.h"


DETOUR(disallow_deploy_when_ubered);
/*  */


static unknown_t (*trampoline_CTFPlayer_GetClosestCaptureZone)(CTFPlayer* this);


static unknown_t detour_CTFPlayer_GetClosestCaptureZone(CTFPlayer* this)
{
	if (CTFPlayerShared_IsInvulnerable(prop_CTFPlayer_m_Shared(this))) {
		return 0;
	}
	
	return trampoline_CTFPlayer_GetClosestCaptureZone(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_GetClosestCaptureZone);
	
	return true;
}
