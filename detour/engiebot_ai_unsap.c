#include "all.h"


DETOUR(engiebot_ai_unsap);
/* trick the engiebot AI into thinking that sapped buildings are damaged so that
 * he'll actually get up and unsap it */


static int (*trampoline_CBaseEntity_GetMaxHealth)(CBaseEntity* this);


static func_t *func_CTFBotMvMEngineerIdle_Update;


static int detour_CBaseEntity_GetMaxHealth(CBaseEntity* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	//pr_info("CBaseEntity::GetMaxHealth\n");
	//pr_debug("caller: %08x\n", caller);
	//pr_debug("caller is CTFBotMvmEngineerIdle_Update: %s\n",
	//	(func_owns_addr(caller,
	//	func_CTFBotMvMEngineerIdle_Update) ? "YES" : "NO"));
	
	CBaseObject *obj = DYNAMIC_CAST(this, CBaseEntity, CBaseObject);
	//pr_debug("DYNAMIC_CAST this -> CBaseObject: %s\n",
	//	(obj != NULL ? "YES" : "NO"));
	
	if (func_owns_addr(caller,
		func_CTFBotMvMEngineerIdle_Update) &&
		obj != NULL) {
		CObjectSapper* sapper = CBaseObject_GetSapper(obj);
		
		//pr_debug("building: %s\n",
		//	(sapper == NULL ? "okay" : "SAPPED"));
		
		bool *m_bBuilding = prop_CBaseObject_m_bBuilding(obj);
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
	func_CTFBotMvMEngineerIdle_Update =
		func_register(CTFBotMvMEngineerIdle_Update);
	
	DETOUR_CREATE(CBaseEntity_GetMaxHealth);
	
	return true;
}
