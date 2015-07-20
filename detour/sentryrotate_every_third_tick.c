#include "all.h"


DETOUR(sentryrotate_every_third_tick);
/* only let CObjectSentrygun::SentryRotate run every third tick to compensate
 * for the sentrygun_think_every_tick patch */


static void (*trampoline_CObjectSentrygun_SentryRotate)(void*);


void detour_CObjectSentrygun_SentryRotate(void* this)
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
	func_t *func1 = func_register(
		"_ZN16CObjectSentrygun12SentryRotateEv");
	
	
	/* CObjectSentrygun::SentryRotate() */
	trampoline_CObjectSentrygun_SentryRotate =
		(void *)(func1->trampoline_addr);
	
	
	func_detour_enable(func1,
		&detour_CObjectSentrygun_SentryRotate);
}
