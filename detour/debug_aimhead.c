#include "all.h"


DETOUR(debug_aimhead);
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


static void detour_IBody_AimHeadTowards_ent(IBody* this, CBaseEntity* ent, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	pr_info("IBody::AimHeadTowards(ent, %s, %.1f, '%s')\n",
		pri_strs[priority], duration, reason);
	BACKTRACE();
	
	trampoline_IBody_AimHeadTowards_ent(this, ent, priority, duration, reply, reason);
}

static void detour_IBody_AimHeadTowards_vec(IBody* this, Vector const* vec, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	pr_info("IBody::AimHeadTowards(vec, %s, %.1f, '%s')\n",
		pri_strs[priority], duration, reason);
	BACKTRACE();
	
	trampoline_IBody_AimHeadTowards_vec(this, vec, priority, duration, reply, reason);
}


static void detour_PlayerBody_AimHeadTowards_ent(PlayerBody* this, CBaseEntity* ent, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	pr_info("PlayerBody::AimHeadTowards(ent, %s, %.1f, '%s')\n",
		pri_strs[priority], duration, reason);
	BACKTRACE();
	
	trampoline_PlayerBody_AimHeadTowards_ent(this, ent, priority, duration, reply, reason);
}

static void detour_PlayerBody_AimHeadTowards_vec(PlayerBody* this, Vector const* vec, IBody_LookAtPriorityType priority, float duration, INextBotReply* reply, char const* reason)
{
	pr_info("PlayerBody::AimHeadTowards(vec, %s, %.1f, '%s')\n",
		pri_strs[priority], duration, reason);
	BACKTRACE();
	
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
