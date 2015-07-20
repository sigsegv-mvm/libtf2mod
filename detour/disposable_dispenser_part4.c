#include "all.h"


DETOUR(disposable_dispenser_part4);
/* determine whether a dispenser should be a mini-dispenser */


static bool (*trampoline_CObjectDispenser_ShouldBeMiniBuilding)(void*, void*) = NULL;


bool detour_CObjectDispenser_ShouldBeMiniBuilding(void* this, void* player)
{
	// TEMPORARY HACK!
	//return true;
	return false;
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN16CObjectDispenser20ShouldBeMiniBuildingEP9CTFPlayer");
	
	
	/* CObjectDispenser::ShouldBeMiniBuilding(CTFPlayer*) */
	trampoline_CObjectDispenser_ShouldBeMiniBuilding =
		(void *)(func1->trampoline_addr);
	
	
	func_detour_enable(func1,
		&detour_CObjectDispenser_ShouldBeMiniBuilding);
}
