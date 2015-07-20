#include "all.h"


DETOUR(disposable_dispenser_part2);
/* force dispenser to try making a mini/disposable version when placed */


static int  (*trampoline_CObjectDispenser_StartPlacement)(void*, void*) = NULL; // may be void, dunno
static void (*func_CObjectDispenser_MakeMiniBuilding)(void*, void*)     = NULL;
static void (*func_CBaseObject_MakeDisposableBuilding)(void*, void*)    = NULL;


int detour_CObjectDispenser_StartPlacement(void* this, void* player)
{
	func_CObjectDispenser_MakeMiniBuilding(this, player);
	func_CBaseObject_MakeDisposableBuilding(this, player);
	
	return trampoline_CObjectDispenser_StartPlacement(this, player);
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN16CObjectDispenser14StartPlacementEP9CTFPlayer");
	
	
	/* CObjectDispenser::StartPlacement(CTFPlayer*) */
	trampoline_CObjectDispenser_StartPlacement =
		(void *)(func1->trampoline_addr);
	
	/* CObjectDispenser::MakeMiniBuilding(CTFPlayer*) */
	func_CObjectDispenser_MakeMiniBuilding =
		(void *)(func_register(
		"_ZN16CObjectDispenser16MakeMiniBuildingEP9CTFPlayer")
		->func_addr);
	
	/* CBaseObject::MakeDisposableBuilding(CTFPlayer*) */
	func_CBaseObject_MakeDisposableBuilding =
		(void *)(func_register(
		"_ZN11CBaseObject22MakeDisposableBuildingEP9CTFPlayer")
		->func_addr);
	
	
	func_detour_enable(func1,
		&detour_CObjectDispenser_StartPlacement);
}
