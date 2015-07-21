#include "all.h"


DETOUR(sentryrotate_every_third_tick);
/* only let CObjectSentrygun::SentryRotate run every third tick to compensate
 * for the sentrygun_think_every_tick patch */


static void (*trampoline_CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);


static void detour_CObjectSentrygun_SentryRotate(CObjectSentrygun* this)
{
	/* only run the function every third time */
	static int c = 0;
	if (c == 0) {
		trampoline_CObjectSentrygun_SentryRotate(this);
	}
	if (++c == 3) {
		c = 0;
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectSentrygun_SentryRotate);
}
