#include "all.h"


DETOUR(disposable_dispenser_part5);
/* add functionality for creating disposable dispensers */


static unknown_t (*trampoline_CBaseObject_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);


static unknown_t detour_CBaseObject_MakeDisposableBuilding(CBaseObject* this, CTFPlayer* player)
{
	/*if (CBaseObject_GetType(this) == 0 &&
		CTFPlayer_GetNumObjects(player, 0, 0) != 0 &&
		CTFPlayer_CanBuild(player, 0, 0) == 0) {
		CBaseAnimating_SetModelScale(this, 0.65f, 0.0f);
	}*/
	
	return trampoline_CBaseObject_MakeDisposableBuilding(this, player);
}


DETOUR_SETUP
{
	//DETOUR_CREATE(CBaseObject_MakeDisposableBuilding);
}
