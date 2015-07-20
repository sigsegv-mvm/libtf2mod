#include "all.h"


DETOUR(disposable_dispenser_part5);
/* add functionality for creating disposable dispensers */


static int (*trampoline_CBaseObject_MakeDisposableBuilding)(void*, void*) = NULL; // may be void, dunno
static int (*func_CBaseObject_GetType)(void*)                             = NULL;


int detour_CBaseObject_MakeDisposableBuilding(void* this, void* player)
{
	/*if (func_CBaseObject_GetType(this) == 0 &&
		func_CTFPlayer_GetNumObjects(player, 0, 0) != 0 &&
		func_CTFPlayer_CanBuild(player, 0, 0) == 0) {
		func_CBaseAnimating_SetModelScale(this, 0.65f, 0.0f);
	}*/
	
	return trampoline_CBaseObject_MakeDisposableBuilding(this, player);
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN11CBaseObject22MakeDisposableBuildingEP9CTFPlayer");
	
	
	/* CBaseObject::MakeDisposableBuilding(CTFPlayer*) */
	trampoline_CBaseObject_MakeDisposableBuilding =
		(void *)(func1->trampoline_addr);
	
	/* CBaseObject::GetType() */
	func_CBaseObject_GetType =
		(void *)(func_register(
		"_ZNK11CBaseObject7GetTypeEv")
		->func_addr);
	
	
	/*func_detour_enable(func1,
		&detour_CBaseObject_MakeDisposableBuilding);*/
}
