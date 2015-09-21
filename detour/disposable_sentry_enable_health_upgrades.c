#include "all.h"


DETOUR(disposable_sentry_enable_health_upgrades);
/* fix disposable sentry's hard-coded 100 starting and max health */


static void (*trampoline_CObjectSentrygun_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);


static void detour_CObjectSentrygun_MakeDisposableBuilding(CBaseObject* this, CTFPlayer* player)
{
	trampoline_CObjectSentrygun_MakeDisposableBuilding(this, player);
	
	int *m_iMaxHealth = prop_CBaseObject_m_iMaxHealth(this);
	bool *m_bDisposableBuilding = prop_CBaseObject_m_bDisposableBuilding(this);
	
	/* check if it's a disposable sentry */
	if (CBaseObject_GetType(this) == 2 && *m_bDisposableBuilding) {
		//pr_debug("%s: is a disposable sentry\n",
		//	__func__);
		
		int health = CObjectSentrygun_GetMaxHealthForCurrentLevel(this);
		
		if (*m_iMaxHealth != health) {
			*m_iMaxHealth = health;
			//CBaseEntity_NetworkStateChanged_m_iMaxHealth(this, maxhealth);
		}
		
		CBaseObject_SetHealth(this, (float)health);
	} else {
		//pr_debug("%s: not a disposable sentry\n",
		//	__func__);
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectSentrygun_MakeDisposableBuilding);
	
	return true;
}
