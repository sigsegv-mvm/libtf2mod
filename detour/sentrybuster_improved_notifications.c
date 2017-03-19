#include "all.h"


DETOUR(sentrybuster_improved_notifications);
/*  */


#if 0
#error comment
#error register detour


static void (*trampoline_CTFPlayerClassShared_SetCustomModel)(CTFPlayerClassShared* this, char const*, bool);

static void (*trampoline_CMultiplayGameRules_HaveAllPlayersSpeakConceptIfAllowed)(CMultiplayGameRules* this, int, int, char const*);


static func_t *func_CMissionPopulator_UpdateMissionDestroySentries;
static func_t *func_CTFBotMissionSuicideBomber_Detonate;


static void detour_CTFPlayerClassShared_SetCustomModel(CTFPlayerClassShared* this, char const* model, bool b1)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (model == *g_szBotBossSentryBusterModel &&
		func_owns_addr(caller1,
		func_CMissionPopulator_UpdateMissionDestroySentries)) {
		if (this == NULL) {
			pr_warn("%s: this == NULL", __func__);
			goto bail_out;
		}
		
		ptrdiff_t off_m_PlayerClass = prop_CTFPlayer_m_PlayerClass(NULL);
		CTFPlayer* player = ((uintptr_t)this - off_m_PlayerClass);
		
		CTFBot* bot = DYNAMIC_CAST(player, CTFPlayer, CTFBot);
		if (bot == NULL) {
			pr_warn("%s: bot == NULL", __func__);
			goto bail_out;
		}
		
		EHANDLE m_hSBTarget = *prop_CTFBot_m_hSBTarget(bot);
		if (m_hSBTarget == -1) {
			pr_warn("%s: m_hSBTarget == NULL", __func__);
			goto bail_out;
		}
		
		CBaseEntity* target = INDEXENT(m_hSBTarget);
		if (target == NULL) {
			pr_warn("%s: target == NULL", __func__);
			goto bail_out;
		}
		
		CBaseObject* sentry = DYNAMIC_CAST(CBaseEntity, CBaseObject);
		if (sentry == NULL) {
			pr_warn("%s: sentry == NULL", __func__);
			goto bail_out;
		}
		
		CBaseEntity* owner = CBaseObject_GetOwner(sentry);
		if (owner == NULL) {
			pr_warn("%s: owner == NULL", __func__);
			goto bail_out;
		}
		if (!vcall_CBaseEntity_IsPlayer(owner)) {
			pr_warn("%s: !owner->IsPlayer()", __func__);
			goto bail_out;
		}
		
		CTFPlayer* engie = DYNAMIC_CAST(CBaseEntity, CTFPlayer);
		if (engie == NULL) {
			pr_warn("%s: engie == NULL", __func__);
			goto bail_out;
		}
		
		CTFPlayer_SpeakConceptIfAllowed(engie, TLK_MVM_SENTRY_BUSTER,
			NULL, NULL, 0, NULL);
	}
	
bail_out:
	trampoline_CTFPlayerClassShared_SetCustomModel(this, model, b1);
}


static void detour_CMultiplayGameRules_HaveAllPlayersSpeakConceptIfAllowed(CMultiplayGameRules* this, int iConcept, int iTeam, char const* modifiers)
{
	if (iConcept == TLK_MVM_SENTRY_BUSTER) {
		return;
	}
	
	if (iConcept == TLK_MVM_SENTRY_BUSTER_DOWN) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1,
			func_CTFBotMissionSuicideBomber_Detonate)) {
			uintptr_t caller1_frame = (uintptr_t)__builtin_frame_address(1);
			CTFBot* bot = *(CTFBot **)(caller1_frame + 0xc);
			if (bot == NULL) {
				pr_warn("%s: bot == NULL", __func__);
				return;
			}
			
			EHANDLE m_hSBTarget = *prop_CTFBot_m_hSBTarget(bot);
			if (m_hSBTarget == -1) {
				pr_warn("%s: m_hSBTarget == NULL", __func__);
				return;
			}
			
			CBaseEntity* target = INDEXENT(m_hSBTarget);
			if (target == NULL) {
				pr_warn("%s: target == NULL", __func__);
				return;
			}
			
			CBaseObject* sentry = DYNAMIC_CAST(CBaseEntity, CBaseObject);
			if (sentry == NULL) {
				pr_warn("%s: sentry == NULL", __func__);
				return;
			}
			
			CBaseEntity* owner = CBaseObject_GetOwner(sentry);
			if (owner == NULL) {
				pr_warn("%s: owner == NULL", __func__);
				return;
			}
			if (!vcall_CBaseEntity_IsPlayer(owner)) {
				pr_warn("%s: !owner->IsPlayer()", __func__);
				return;
			}
			
			CTFPlayer* engie = DYNAMIC_CAST(CBaseEntity, CTFPlayer);
			if (engie == NULL) {
				pr_warn("%s: engie == NULL", __func__);
				return;
			}
			
			CTFPlayer_SpeakConceptIfAllowed(engie, TLK_MVM_SENTRY_BUSTER_DOWN,
				NULL, NULL, 0, NULL);
			return;
		}
	}
	
	trampoline_CMultiplayGameRules_HaveAllPlayersSpeakConceptIfAllowed(this, iConcept, iTeam, modifiers);
}


// need to do this for announcer lines:
// - detour CTeamplayRoundBasedRules::BroadcastSound
//   - filter out "Announcer.MvM_Sentry_Buster_Alert"
//   - filter out "Announcer.MVM_Sentry_Buster_Alert_Another"
// - figure out the best way for us to send these sounds just to the appropriate engineer

// ALSO:
// on sentry buster spawn, print a message to the engie's chat saying that a sentry buster
// has spawned for them;
// maybe do this too when their buster is destroyed
// (try to mimic the style of the 'canteen used' and/or 'buyback' chat msgs)

#endif

DETOUR_SETUP
{
	/*func_CMissionPopulator_UpdateMissionDestroySentries =
		func_register(CMissionPopulator_UpdateMissionDestroySentries);
	func_CTFBotMissionSuicideBomber_Detonate =
		func_register(CTFBotMissionSuicideBomber_Detonate);
	
	DETOUR_CREATE(CTFPlayerClassShared_SetCustomModel);
	
	DETOUR_CREATE(CMultiplayGameRules_HaveAllPlayersSpeakConceptIfAllowed);*/
	
	return true;
}
