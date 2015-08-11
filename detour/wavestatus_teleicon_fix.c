#include "all.h"


DETOUR(wavestatus_teleicon_fix);
/* fix RTR making the teleporter icon stay active on the wave status panel
 * (this detour relies on a patch) */


static void (*trampoline_CObjectTeleporter_FinishedBuilding)(CObjectTeleporter* this);


static void detour_CObjectTeleporter_FinishedBuilding(CObjectTeleporter* this)
{
	bool is_rtr =
		(CBaseObject_GetReversesBuildingConstructionSpeed(this) != 0.0f);
	
	
	trampoline_CObjectTeleporter_FinishedBuilding(this);
	
	
	/* don't increment the teleporter count if we're under the effects of the
	 * Red-Tape Recorder */
	if (!is_rtr) {
		CTFObjectiveResource_IncrementTeleporterCount(*g_pObjectiveResource);
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectTeleporter_FinishedBuilding);
}
