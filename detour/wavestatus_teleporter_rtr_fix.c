#include "all.h"


DETOUR(wavestatus_teleporter_rtr_fix);
/* fix RTR making the teleporter icon stay active on the wave status panel */


static bool is_rtr_sapped;


static void (*trampoline_CObjectTeleporter_FinishedBuilding)(CObjectTeleporter* this);
static unknown_t (*trampoline_CTFObjectiveResource_IncrementTeleporterCount)(CTFObjectiveResource* this);


static void detour_CObjectTeleporter_FinishedBuilding(CObjectTeleporter* this)
{
	is_rtr_sapped = (CBaseObject_GetReversesBuildingConstructionSpeed(this) != 0.0f);
	
	trampoline_CObjectTeleporter_FinishedBuilding(this);
}

static unknown_t detour_CTFObjectiveResource_IncrementTeleporterCount(CTFObjectiveResource* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	
	/*pr_info("CTFObjectiveResource:\n");
	pr_debug("  caller: %08x\n"
		"  caller_frame: %08x\n"
		"  CObjectTeleporter::FinishedBuilding is at %08x\n",
		caller, caller_frame, CObjectTeleporter_FinishedBuilding);*/
	
	bool owns_addr = func_owns_addr(CObjectTeleporter_FinishedBuilding, caller);
	/*pr_debug("  func_owns_addr: %s\n", (owns_addr ? "YES" : "NO"));*/
	
	if (owns_addr) {
		uintptr_t caller_this = *(uintptr_t *)(caller_frame + 8);
		
		/*pr_debug("  caller_this: %08x\n", caller_this);
		pr_debug("  is_rtr_sapped: %s\n", (is_rtr_sapped ? "YES" : "NO"));*/
		
		/* if teleporter is sapped with RTR, then don't increment tele count */
		if (is_rtr_sapped) {
			return 0;
		}
	}
	
	return trampoline_CTFObjectiveResource_IncrementTeleporterCount(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectTeleporter_FinishedBuilding);
	DETOUR_CREATE(CTFObjectiveResource_IncrementTeleporterCount);
}
