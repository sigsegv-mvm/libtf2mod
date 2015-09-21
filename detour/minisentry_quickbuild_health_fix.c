#include "all.h"


DETOUR(minisentry_quickbuild_health_fix);
/* fix Gunslinger mini-sentries starting at 50% health during pre-wave time */


static void (*trampoline_CBaseObject_DoQuickBuild)(CBaseObject* this);


static void detour_CBaseObject_DoQuickBuild(CBaseObject* this)
{
	trampoline_CBaseObject_DoQuickBuild(this);
	
	bool *m_bMiniBuilding = prop_CBaseObject_m_bMiniBuilding(this);
	
	/* check if it's a mini sentry */
	if (CBaseObject_GetType(this) == 2 && *m_bMiniBuilding) {
		//pr_debug("%s: is a mini sentry\n",
		//	__func__);
		int health = CObjectSentrygun_GetMaxHealthForCurrentLevel(this);
		CBaseObject_SetHealth(this, (float)health);
	} else {
		//pr_debug("%s: not a mini sentry\n",
		//	__func__);
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CBaseObject_DoQuickBuild);
	
	return true;
}
