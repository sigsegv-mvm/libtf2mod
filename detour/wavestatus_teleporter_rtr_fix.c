#include "all.h"


DETOUR(wavestatus_teleporter_rtr_fix);
/* fix two bugs related to the teleporter wave status icon and the RTR:
 * 1. At the completion of an RTR sap, CObjectTeleporter::FinishedBuilding
 *    increments the icon count right after it's already been decremented by
 *    CObjectTeleporter::UpdateOnRemove
 * 2. When an engiebot unsaps an RTR'd active teleporter, it goes active again,
 *    and CObjectTeleporter::FinishedBuilding increments the icon count */


static bool is_rtr_sapped;
static bool tele_active[2048];


static void (*trampoline_CObjectTeleporter_FinishedBuilding)(CObjectTeleporter* this);
static unknown_t (*trampoline_CTFObjectiveResource_IncrementTeleporterCount)(CTFObjectiveResource* this);
static unknown_t (*trampoline_CTFObjectiveResource_DecrementTeleporterCount)(CTFObjectiveResource* this);


static void detour_CObjectTeleporter_FinishedBuilding(CObjectTeleporter* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	/* we have to get the RTR sapped status in here because it gets wiped
	 * before CObjectTeleporter::FinishedBuilding finally gets around to
	 * calling CTFObjectiveResource::IncrementTeleporterCount */
	is_rtr_sapped =
		(CBaseObject_GetReversesBuildingConstructionSpeed(this) != 0.0f);
	
	
	trampoline_CObjectTeleporter_FinishedBuilding(this);
}

static unknown_t detour_CTFObjectiveResource_IncrementTeleporterCount(CTFObjectiveResource* this)
{
	/* this is always called by CObjectTeleporter::FinishedBuilding */
	
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	//if (tele_active[entindex]) {
	//	pr_info("IncrementTele: %d already active\n", entindex);
	//}
	//if (is_rtr_sapped) {
	//	pr_info("IncrementTele: %d is RTR-sapped\n", entindex);
	//}
	
	/* if this tele has already gone active, or was just destroyed by the
	 * completion of an RTR sap, then don't increment its wave status count */
	if (tele_active[entindex] || is_rtr_sapped) {
		return 0;
	}
	
	tele_active[entindex] = true;
	//pr_info("IncrementTele: %d active -> TRUE\n", entindex);
	
	
	return trampoline_CTFObjectiveResource_IncrementTeleporterCount(this);
}

static unknown_t detour_CTFObjectiveResource_DecrementTeleporterCount(CTFObjectiveResource* this)
{
	/* this is always called by CObjectTeleporter::UpdateOnRemove */
	
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	tele_active[entindex] = false;
	//pr_info("DecrementTele: %d active -> FALSE\n", entindex);
	
	
	return trampoline_CTFObjectiveResource_DecrementTeleporterCount(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectTeleporter_FinishedBuilding);
	DETOUR_CREATE(CTFObjectiveResource_IncrementTeleporterCount);
	DETOUR_CREATE(CTFObjectiveResource_DecrementTeleporterCount);
}
