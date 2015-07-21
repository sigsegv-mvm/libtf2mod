#include "all.h"


DETOUR(robot_tickle_enable);
/* allow robots to be tickled by the Holiday Punch */


static bool (*trampoline_CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);


static bool detour_CTFPlayer_CanBeForcedToLaugh(CTFPlayer* this)
{
	/* always return true */
	return true;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CanBeForcedToLaugh);
}
