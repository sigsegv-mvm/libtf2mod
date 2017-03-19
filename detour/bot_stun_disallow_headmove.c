#include "all.h"


DETOUR(bot_stun_disallow_headmove);
/*  */


static void (*trampoline_IBody_AimHeadTowards_ent)(IBody* this, CBaseEntity*, IBody_LookAtPriorityType, float, INextBotReply*, char const*);
static void (*trampoline_IBody_AimHeadTowards_vec)(IBody* this, Vector const*, IBody_LookAtPriorityType, float, INextBotReply*, char const*);

static void (*trampoline_PlayerBody_AimHeadTowards_ent)(PlayerBody* this, CBaseEntity*, IBody_LookAtPriorityType, float, INextBotReply*, char const*);
static void (*trampoline_PlayerBody_AimHeadTowards_vec)(PlayerBody* this, Vector const*, IBody_LookAtPriorityType, float, INextBotReply*, char const*);


static const char *pri_strs[] = {
	"BORING",
	"INTERESTING",
	"IMPORTANT",
	"CRITICAL",
};


// TODO:
// also check InCond(7)


static void detour_IBody_AimHeadTowards_ent(IBody* this, CBaseEntity* ent, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	INextBot* nextbot = vcall_INextBotComponent_GetBot(this);
	CTFBot* bot = DYNAMIC_CAST(nextbot, INextBot, CTFBot);
	if (bot != NULL) {
		CTFPlayerShared* m_Shared = prop_CTFPlayer_m_Shared(bot);
		
		if (CTFPlayerShared_IsControlStunned(m_Shared)) {
			/* TODO: deal with reply if it's non-NULL */
			return;
		}
	}
	
	trampoline_IBody_AimHeadTowards_ent(this, ent, priority, duration, reply, reason);
}

static void detour_IBody_AimHeadTowards_vec(IBody* this, Vector const* vec, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	INextBot* nextbot = vcall_INextBotComponent_GetBot(this);
	CTFBot* bot = DYNAMIC_CAST(nextbot, INextBot, CTFBot);
	if (bot != NULL) {
		CTFPlayerShared* m_Shared = prop_CTFPlayer_m_Shared(bot);
		
		if (CTFPlayerShared_IsControlStunned(m_Shared)) {
			/* TODO: deal with reply if it's non-NULL */
			return;
		}
	}
	
	trampoline_IBody_AimHeadTowards_vec(this, vec, priority, duration, reply, reason);
}


static void detour_PlayerBody_AimHeadTowards_ent(PlayerBody* this, CBaseEntity* ent, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	INextBot* nextbot = vcall_INextBotComponent_GetBot(this);
	CTFBot* bot = DYNAMIC_CAST(nextbot, INextBot, CTFBot);
	if (bot != NULL) {
		CTFPlayerShared* m_Shared = prop_CTFPlayer_m_Shared(bot);
		
		if (CTFPlayerShared_IsControlStunned(m_Shared)) {
			/* TODO: deal with reply if it's non-NULL */
			return;
		}
	}
	
	trampoline_PlayerBody_AimHeadTowards_ent(this, ent, priority, duration, reply, reason);
}

static void detour_PlayerBody_AimHeadTowards_vec(PlayerBody* this, Vector const* vec, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	INextBot* nextbot = vcall_INextBotComponent_GetBot(this);
	CTFBot* bot = DYNAMIC_CAST(nextbot, INextBot, CTFBot);
	if (bot != NULL) {
		CTFPlayerShared* m_Shared = prop_CTFPlayer_m_Shared(bot);
		
		if (CTFPlayerShared_IsControlStunned(m_Shared)) {
			/* TODO: deal with reply if it's non-NULL */
			return;
		}
	}
	
	trampoline_PlayerBody_AimHeadTowards_vec(this, vec, priority, duration, reply, reason);
}


DETOUR_SETUP
{
	DETOUR_CREATE(IBody_AimHeadTowards_ent);
	DETOUR_CREATE(IBody_AimHeadTowards_vec);
	
	DETOUR_CREATE(PlayerBody_AimHeadTowards_ent);
	DETOUR_CREATE(PlayerBody_AimHeadTowards_vec);
	
	return true;
}
