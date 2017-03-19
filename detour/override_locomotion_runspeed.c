#include "all.h"


DETOUR(override_locomotion_runspeed);
/*  */


static float (*trampoline_CTFBotLocomotion_GetRunSpeed)(CTFBotLocomotion* this);


static float detour_CTFBotLocomotion_GetRunSpeed(CTFBotLocomotion* this)
{
	return 3200.0f;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFBotLocomotion_GetRunSpeed);
	
	return true;
}
