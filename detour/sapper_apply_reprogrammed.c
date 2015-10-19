#include "all.h"


DETOUR(sapper_apply_reprogrammed);
/* make the robo sapper apply condition TF_COND_REPROGRAMMED instead of
 * TF_COND_SAPPED */


static bool (*trampoline_CObjectSapper_IsValidRoboSapperTarget)(CObjectSapper* this, CTFPlayer*);
static bool (*trampoline_CObjectSapper_ApplyRoboSapperEffects)(CObjectSapper* this, CTFPlayer*, float);


static bool detour_CObjectSapper_IsValidRoboSapperTarget(CObjectSapper* this, CTFPlayer* victim)
{
	bool result = trampoline_CObjectSapper_IsValidRoboSapperTarget(this, victim);
	
	//if (result && CTFPlayer_IsMiniBoss(victim)) {
	//	return false;
	//}
	
	return result;
}

static bool detour_CObjectSapper_ApplyRoboSapperEffects(CObjectSapper* this, CTFPlayer* victim, float duration)
{
	if (victim == NULL) {
		return false;
	}
	
	//if (CTFPlayer_IsMiniBoss(victim)) {
	//	return false;
	//}
	
	
	CTFPlayer* builder = CBaseObject_GetBuilder(this);
	if (builder == NULL || !vcall_CBaseEntity_IsPlayer(builder)) {
		return false;
	}
	
	int attr = CAttributeManager_AttribHookValue_int(0, "robo_sapper",
		builder, NULL, true);
	if (attr == 0) {
		duration = 5.0f;
	} else {
		duration = 15.0f * attr;
	}
	
	CTFPlayerShared* shared = prop_CTFPlayer_m_Shared(victim);
	CTFPlayerShared_AddCond(shared, TF_COND_REPROGRAMMED, duration, builder);
	
	return true;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CObjectSapper_IsValidRoboSapperTarget);
	DETOUR_CREATE(CObjectSapper_ApplyRoboSapperEffects);
	
	return true;
}
