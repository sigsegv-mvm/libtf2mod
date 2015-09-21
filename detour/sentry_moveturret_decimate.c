#include "all.h"


DETOUR(sentry_moveturret_decimate);
/* only let CObjectSentrygun::MoveTurret run every third tick to compensate for
 * the sentrygun_think_every_tick patch */


static void (*trampoline_CObjectSentrygun_SentryThink)(CObjectSentrygun* this);
static bool (*trampoline_CObjectSentrygun_MoveTurret)(CObjectSentrygun* this);


static void detour_CObjectSentrygun_SentryThink(CObjectSentrygun* this)
{
	pr_info("SentryThink\n");
	pr_debug("- curtime           = %f\n", (*gpGlobals)->curtime);
	pr_debug("- framecount        = %d\n", (*gpGlobals)->framecount);
	pr_debug("- tickcount         = %d\n", (*gpGlobals)->tickcount);
	pr_debug("- interval_per_tick = %f\n", (*gpGlobals)->interval_per_tick);
	pr_debug("- simTicksThisFrame = %d\n", (*gpGlobals)->simTicksThisFrame);
	
	trampoline_CObjectSentrygun_SentryThink(this);
}


static bool detour_CObjectSentrygun_MoveTurret(CObjectSentrygun* this)
{
	static uint8_t counts[2048];
	
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	//pr_debug("MoveTurret: %s\n",
	//	(counts[entindex] == 0 ? "YES" : "NO"));
	
	/* only run the function every third tick */
	bool should_call = (counts[entindex] == 0);
	if (++counts[entindex] == 3) {
		counts[entindex] = 0;
	}
	
	if (should_call) {
		return trampoline_CObjectSentrygun_MoveTurret(this);
	} else {
		/* CObjectSentrygun::SentryRotate (during sentry's idle state) will make
		 * the sentry switch directions if we return false, so don't do that */
		return true;
	}
}


DETOUR_SETUP
{
	//DETOUR_CREATE(CObjectSentrygun_SentryThink);
	
	DETOUR_CREATE(CObjectSentrygun_MoveTurret);
	
	return true;
}
