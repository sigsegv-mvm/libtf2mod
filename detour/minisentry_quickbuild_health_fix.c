#include "all.h"


DETOUR(minisentry_quickbuild_health_fix);
/* fix Gunslinger mini-sentries starting at 50% health during pre-wave time */


static void     (*trampoline_CBaseObject_DoQuickBuild)(void*)               = NULL;
static uint32_t (*func_CBaseObject_GetType)(void*)                          = NULL;
static uint32_t (*func_CObjectSentrygun_GetMaxHealthForCurrentLevel)(void*) = NULL;
static void     (*func_CBaseObject_SetHealth)(void*, float)                 = NULL;


void detour_CBaseObject_DoQuickBuild(void* this)
{
	trampoline_CBaseObject_DoQuickBuild(this);
	
	/* check if it's a mini sentry */
	if (func_CBaseObject_GetType(this) == 2 &&
		((uint8_t *)this)[0xa0e] != 0) {
		//pr_debug("%s: is a mini sentry\n",
		//	__func__);
		uint32_t health = func_CObjectSentrygun_GetMaxHealthForCurrentLevel(this);
		func_CBaseObject_SetHealth(this, (float)health);
	} else {
		//pr_debug("%s: not a mini sentry\n",
		//	__func__);
	}
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN11CBaseObject12DoQuickBuildEb");
	
	
	/* CBaseObject::DoQuickBuild() */
	trampoline_CBaseObject_DoQuickBuild =
		(void *)(func1->trampoline_addr);
	
	/* CBaseObject::GetType() */
	func_CBaseObject_GetType =
		(void *)(func_register(
		"_ZNK11CBaseObject7GetTypeEv")
		->func_addr);
	
	/* CObjectSentrygun::GetMaxHealthForCurrentLevel() */
	func_CObjectSentrygun_GetMaxHealthForCurrentLevel =
		(void *)(func_register(
		"_ZN16CObjectSentrygun27GetMaxHealthForCurrentLevelEv")
		->func_addr);
	
	/* CBaseObject::SetHealth(float) */
	func_CBaseObject_SetHealth =
		(void *)(func_register(
		"_ZN11CBaseObject9SetHealthEf")
		->func_addr);
	
	
	func_detour_enable(func1,
		&detour_CBaseObject_DoQuickBuild);
}
