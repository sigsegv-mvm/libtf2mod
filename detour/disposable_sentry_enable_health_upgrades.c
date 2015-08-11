#include "all.h"


DETOUR(disposable_sentry_enable_health_upgrades);
/* fix disposable sentry's hard-coded 100 starting and max health */


static void (*trampoline_CObjectSentrygun_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);

static uintptr_t off_CObjectSentrygun_m_iMaxHealth;
static uintptr_t off_CObjectSentrygun_m_bDisposableBuilding;


static void detour_CObjectSentrygun_MakeDisposableBuilding(CBaseObject* this, CTFPlayer* player)
{
	trampoline_CObjectSentrygun_MakeDisposableBuilding(this, player);
	
	int *m_iMaxHealth = (int *)((uintptr_t)this +
		off_CObjectSentrygun_m_iMaxHealth);
	bool *m_bDisposableBuilding = (bool *)((uintptr_t)this +
		off_CObjectSentrygun_m_bDisposableBuilding);
	
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
	if (off_CObjectSentrygun_m_iMaxHealth == 0) {
		off_CObjectSentrygun_m_iMaxHealth = datamap_offset(
			CObjectSentrygun_GetDataDescMap(), "m_iMaxHealth");
		
		if (off_CObjectSentrygun_m_iMaxHealth == 0) {
			pr_warn("%s: off_CObjectSentrygun_m_iMaxHealth = 0\n", __func__);
			return;
		}
	}
	
	if (off_CObjectSentrygun_m_bDisposableBuilding == 0) {
		off_CObjectSentrygun_m_bDisposableBuilding = sendprop_offset(
			"CBaseObject", "m_bDisposableBuilding");
		
		if (off_CObjectSentrygun_m_bDisposableBuilding == 0) {
			pr_warn("%s: off_CObjectSentrygun_m_bDisposableBuilding = 0\n",
				__func__);
			return;
		}
	}
	
	
	DETOUR_CREATE(CObjectSentrygun_MakeDisposableBuilding);
}
