#include "all.h"
#if 0


DETOUR(mini_dispenser);
/* replaces the dispenser with a cute mini-dispenser;
 * also unconditionally makes sentries be mini-sentries */


static bool (*trampoline_CBaseObject_ShouldBeMiniBuilding)(void*, void*)      = NULL;
static bool (*trampoline_CObjectDispenser_ShouldBeMiniBuilding)(void*, void*) = NULL;
static bool (*trampoline_CObjectDispenser_MakeMiniBuilding)(void*, void*)     = NULL;
static void (*func_CBaseAnimating_SetModelScale)(void*, float, float)         = NULL;


bool detour_CBaseObject_ShouldBeMiniBuilding(void* this, void* player)
{
	pr_debug("%s: returning true\n", __func__);
	return true;
}


bool detour_CObjectDispenser_ShouldBeMiniBuilding(void* this, void* player)
{
	pr_debug("%s: returning true\n", __func__);
	return true;
}


void detour_CObjectDispenser_MakeMiniBuilding(void* this, void* player)
{
	trampoline_CObjectDispenser_MakeMiniBuilding(this, player);
	
	pr_debug("%s: setting model scale to 0.75\n", __func__);
	func_CBaseAnimating_SetModelScale(this, 0.75f, 0.0f);
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN16CObjectDispenser20ShouldBeMiniBuildingEP9CTFPlayer");
	
	func_t *func2 = func_register(
		"_ZN11CBaseObject20ShouldBeMiniBuildingEP9CTFPlayer");
	
	func_t *func3 = func_register(
		"_ZN16CObjectDispenser16MakeMiniBuildingEP9CTFPlayer");
	
	
	/* CBaseObject::ShouldBeMiniBuilding(CTFPlayer*) */
	trampoline_CBaseObject_ShouldBeMiniBuilding =
		(void *)(func1->trampoline_addr);
	
	/* CObjectDispenser::ShouldBeMiniBuilding(CTFPlayer*) */
	trampoline_CObjectDispenser_ShouldBeMiniBuilding =
		(void *)(func2->trampoline_addr);
	
	/* CObjectDispenser::MakeMiniBuilding(CTFPlayer*) */
	trampoline_CObjectDispenser_MakeMiniBuilding =
		(void *)(func3->trampoline_addr);
	
	/* CBaseAnimating::SetModelScale(float, float) */
	func_CBaseAnimating_SetModelScale =
		(void *)(func_register(
		"_ZN14CBaseAnimating13SetModelScaleEff")
		->func_addr);
	
	
	func_detour_enable(func1,
		&detour_CBaseObject_ShouldBeMiniBuilding);
	
	func_detour_enable(func2,
		&detour_CObjectDispenser_ShouldBeMiniBuilding);
	
	func_detour_enable(func3,
		&detour_CObjectDispenser_MakeMiniBuilding);
}
#endif
