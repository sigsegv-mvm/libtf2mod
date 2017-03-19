#include "all.h"


DETOUR(debug_onkilled);
/*  */


static nextbot_event_response_t (*trampoline_Action_CTFBot_OnKilled)(void* this, CTFBot*, CTakeDamageInfo *const);


static void _get_player_info(CTFPlayer* player, char *dst, size_t len)
{
	if (player == NULL) {
		strlcpy(dst, "nullptr", len);
	} else {
		char *netname = prop_CTFPlayer_m_szNetname(player);
		
		snprintf(dst, len,
			"0x%08x[#%d name:\"%s\" team:%d alive:%d]",
			(uintptr_t)player,
			ENTINDEX(player),
			(netname != NULL ? netname : ""),
			CBaseEntity_GetTeamNumber(player),
			vcall_CBaseEntity_IsAlive(player));
	}
}


static nextbot_event_response_t detour_Action_CTFBot_OnKilled(void* this, CTFBot* actor, const CTakeDamageInfo *info)
{
	char actor_info[4096];
	_get_player_info(actor, actor_info, sizeof(actor_info));
	
	pr_info("Action<CTFBot>::OnKilled\n");
	pr_debug("  bot:    %s\n", actor_info);
	pr_debug("  action: %s\n", vcall_Action_CTFBot_GetName(this));
	
	if (strcmp(vcall_Action_CTFBot_GetName(this), "MainAction") == 0) {
		pr_warn("  forcing CHANGE_TO CTFBotDead!\n");
		
		struct {
			uint32_t vtable1;
			uint32_t vtable2;
			uint32_t m_Behavior;
			uint32_t m_ActionParent;
			uint32_t m_ActionChild;
			uint32_t m_ActionWeSuspended;
			uint32_t m_ActionSuspendedUs;
			uint32_t m_Actor;
			struct {
				uint32_t transition;
				uint32_t action;
				uint32_t reason;
				uint32_t severity;
			} m_Result;
			bool m_bStarted;
			bool m_bSuspended;
			float m_itTimeSinceDeath;
		} *CTFBotDead = OPERATOR_NEW(0x38);
		SIZE_CHECK(*CTFBotDead, 0x38);
		
		uintptr_t vtable;
		symtab_obj_absolute("_ZTV10CTFBotDead", (void **)&vtable, NULL);
		assert(vtable != 0);
		
		CTFBotDead->vtable1             = vtable + 0x8;
		CTFBotDead->vtable2             = vtable + 0x180;
		CTFBotDead->m_Behavior          = 0;
		CTFBotDead->m_ActionParent      = 0;
		CTFBotDead->m_ActionChild       = 0;
		CTFBotDead->m_ActionWeSuspended = 0;
		CTFBotDead->m_ActionSuspendedUs = 0;
		CTFBotDead->m_Actor             = 0;
		CTFBotDead->m_Result.transition = 0;
		CTFBotDead->m_Result.action     = 0;
		CTFBotDead->m_Result.reason     = 0;
		CTFBotDead->m_Result.severity   = 0;
		CTFBotDead->m_bStarted          = 0;
		CTFBotDead->m_bSuspended        = 0;
		CTFBotDead->m_itTimeSinceDeath  = -1.0f;
		
		return (nextbot_event_response_t){
			1,
			CTFBotDead,
			"I'm dead! (event handler)",
			1,
		};
	}
	
	return (nextbot_event_response_t){ 0, NULL, NULL, 1 };
}


#define SYM_AND_DETOUR(_var, _mangled) \
	void *_var; \
	symtab_func_absolute(_mangled, (void **)&_var, NULL); \
	DETOUR_CREATE(_var)


DETOUR_SETUP
{
	SYM_AND_DETOUR(Action_CTFBot_OnKilled, "_ZN6ActionI6CTFBotE8OnKilledEPS0_RK15CTakeDamageInfo");
	
	return true;
}
