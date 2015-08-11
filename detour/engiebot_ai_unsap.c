#include "all.h"


DETOUR(engiebot_ai_unsap);
/* fix RTR making the teleporter icon stay active on the wave status panel */


static int (*trampoline_CBaseEntity_GetMaxHealth)(CBaseEntity* this);


static int detour_CBaseEntity_GetMaxHealth(CBaseEntity* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	//pr_info("CBaseEntity::GetMaxHealth\n");
	//pr_debug("caller: %08x\n", caller);
	//pr_debug("caller is CTFBotMvmEngineerIdle_Update: %s\n",
	//	(func_owns_addr(CTFBotMvMEngineerIdle_Update, caller) ? "YES" : "NO"));
	
	CBaseObject *obj = DYNAMIC_CAST(this, CBaseEntity, CBaseObject);
	//pr_debug("DYNAMIC_CAST this -> CBaseObject: %s\n",
	//	(obj != NULL ? "YES" : "NO"));
	
	if (func_owns_addr(CTFBotMvMEngineerIdle_Update, caller) &&
		obj != NULL) {
		CObjectSapper* sapper = CBaseObject_GetSapper(obj);
		
		//pr_debug("building: %s\n",
		//	(sapper == NULL ? "okay" : "SAPPED"));
		
		bool *m_bBuilding = (bool *)((uintptr_t)obj + 0x9fe);
		//pr_debug("m_bBuilding (@ 0x9fe): %s\n",
		//	(*m_bBuilding ? "TRUE" : "FALSE"));
		
		/* if the building is currently sapped, then report an erroneously
		 * high max health value so the engiebot will try to repair it */ 
		if (sapper != NULL) {
			return 100 + trampoline_CBaseEntity_GetMaxHealth(this);
		}
	}
	
	return trampoline_CBaseEntity_GetMaxHealth(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CBaseEntity_GetMaxHealth);
}
