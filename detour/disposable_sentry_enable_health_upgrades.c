#include "all.h"


DETOUR(disposable_sentry_enable_health_upgrades);
/* fix disposable sentry's hard-coded 100 starting and max health */


static void (*trampoline_CObjectSentrygun_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);

static uintptr_t off_CObjectSentrygun_m_iMaxHealth;


static void detour_CObjectSentrygun_MakeDisposableBuilding(CBaseObject* this, CTFPlayer* player)
{
	trampoline_CObjectSentrygun_MakeDisposableBuilding(this, player);
	
	/* check if it's a disposable sentry */
	if (CBaseObject_GetType(this) == 2 &&
		((uint8_t *)this)[0xa0f] != 0) {
		//pr_debug("%s: is a disposable sentry\n",
		//	__func__);
		
		int health = CObjectSentrygun_GetMaxHealthForCurrentLevel(this);
		
		int *maxhealth = (int *)((uintptr_t)this +
			off_CObjectSentrygun_m_iMaxHealth);
		if (*maxhealth != health) {
			*maxhealth = health;
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
		off_CObjectSentrygun_m_iMaxHealth = datamap_findoffset(
			CObjectSentrygun_GetDataDescMap(), "m_iMaxHealth");
		
		if (off_CObjectSentrygun_m_iMaxHealth == 0) {
			pr_warn("%s: off_CObjectSentrygun_m_iMaxHealth = 0\n", __func__);
			return;
		}
	}
	
	
	DETOUR_CREATE(CObjectSentrygun_MakeDisposableBuilding);
}
