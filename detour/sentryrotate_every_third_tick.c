#include "all.h"


DETOUR(sentryrotate_every_third_tick);
/* only let CObjectSentrygun::SentryRotate run every third tick to compensate
 * for the sentrygun_think_every_tick patch */


static void (*trampoline_CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);


static void detour_CObjectSentrygun_SentryRotate(CObjectSentrygun* this)
{
	static uint8_t counts[2048];
	
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	/* only run the function every third time */
	if (counts[entindex] == 0) {
		trampoline_CObjectSentrygun_SentryRotate(this);
	}
	if (++counts[entindex] == 3) {
		counts[entindex] = 0;
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectSentrygun_SentryRotate);
}
