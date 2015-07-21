#include "all.h"


DETOUR(robot_gib_normal);
/* make robots gib under the same conditions as normal players */


static bool (*trampoline_CTFBot_ShouldGib)(CTFBot* this);


static bool detour_CTFBot_ShouldGib(CTFBot* this, CTakeDamageInfo const* info)
{
	/* defer to CTFPlayer::ShouldGib */
	return CTFPlayer_ShouldGib(this, info);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFBot_ShouldGib);
}
