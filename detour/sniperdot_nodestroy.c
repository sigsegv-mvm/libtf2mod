#include "all.h"


DETOUR(sniperdot_nodestroy);
/*  */


static void (*trampoline_CTFSniperRifle_DestroySniperDot)(CTFSniperRifle* this);


static void detour_CTFSniperRifle_DestroySniperDot(CTFSniperRifle* this)
{
	/* do nothing */
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFSniperRifle_DestroySniperDot);
	
	return true;
}
