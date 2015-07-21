#include "all.h"


DETOUR(disposable_dispenser_part2);
/* force dispenser to try making a mini/disposable version when placed */


static unknown_t (*trampoline_CObjectDispenser_StartPlacement)(CObjectDispenser* this, CTFPlayer*);


static unknown_t detour_CObjectDispenser_StartPlacement(CObjectDispenser* this, CTFPlayer* player)
{
	CObjectDispenser_MakeMiniBuilding(this, player);
	CBaseObject_MakeDisposableBuilding(this, player);
	
	return trampoline_CObjectDispenser_StartPlacement(this, player);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectDispenser_StartPlacement);
}
