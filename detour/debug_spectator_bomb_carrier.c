#include "all.h"


DETOUR(debug_spectator_bomb_carrier);
/*  */


static unknown_t (*trampoline_CCaptureFlag_AddFollower)(void* this, void*);
static unknown_t (*trampoline_CCaptureFlag_RemoveFollower)(void* this, void*);
static unknown_t (*trampoline_CCaptureFlag_PickUp)(void* this, void*, bool);
static unknown_t (*trampoline_CCaptureFlag_Drop)(void* this, void*, bool, bool, bool);
static unknown_t (*trampoline_CTFBot_SetFlagTarget)(void* this, void*);
static unknown_t (*trampoline_CTFBot_Event_Killed)(void* this, CTakeDamageInfo*);
static unknown_t (*trampoline_CTFBot_ChangeTeam)(void* this, int, bool, bool);
static unknown_t (*trampoline_CTFPlayer_ForceChangeTeam)(void* this, int, bool);


// 1: enable
// 2: backtrace
static ConVar cvar_CCaptureFlag_AddFollower;
static ConVar cvar_CCaptureFlag_RemoveFollower;
static ConVar cvar_CCaptureFlag_PickUp;
static ConVar cvar_CCaptureFlag_Drop;
static ConVar cvar_CTFBot_SetFlagTarget;
static ConVar cvar_CTFBot_Event_Killed;
static ConVar cvar_CTFBot_ChangeTeam;
static ConVar cvar_CTFPlayer_ForceChangeTeam;


static const char *_get_team_name(int team)
{
	static const char *const team_names[] = {
		"UNASSIGNED",
		"SPEC",
		"RED",
		"BLUE",
	};
	
	if (team >= 4) {
		return "???";
	}
	
	return team_names[team];
}

static void _get_ent_info(CBaseEntity* ent, char *dst, size_t len)
{
	if (ent == NULL) {
		strlcpy(dst, "nullptr", len);
	} else {
		const char *m_iClassname = *prop_CBaseEntity_m_iClassname(ent);
		const char *m_iName = *prop_CBaseEntity_m_iName(ent);
		
		snprintf(dst, len,
			"0x%08x[#%d class:\"%s\" name:\"%s\"]",
			(uintptr_t)ent,
			ENTINDEX(ent),
			(m_iClassname != NULL ? m_iClassname : ""),
			(m_iName != NULL ? m_iName : ""));
	}
}

static void _get_player_info(CTFPlayer* player, char *dst, size_t len)
{
	if (player == NULL) {
		strlcpy(dst, "nullptr", len);
	} else {
		char *netname = prop_CTFPlayer_m_szNetname(player);
		
		snprintf(dst, len,
			"0x%08x[#%d name:\"%s\" team:%d<%s> alive:%d]",
			(uintptr_t)player,
			ENTINDEX(player),
			(netname != NULL ? netname : ""),
			CBaseEntity_GetTeamNumber(player),
			_get_team_name(CBaseEntity_GetTeamNumber(player)),
			vcall_CBaseEntity_IsAlive(player));
	}
}


static unknown_t detour_CCaptureFlag_AddFollower(void* this, CTFBot* bot)
{
	int cvar = ConVar_GetInt(&cvar_CCaptureFlag_AddFollower);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_ent_info(this, str_this, sizeof(str_this));
	char str_bot[4096];
	_get_player_info(bot, str_bot, sizeof(str_bot));
	cl_con_printf("[%8.3f] CCaptureFlag::AddFollower(%s, %s)\n",
		(*gpGlobals)->curtime, str_this, str_bot);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CCaptureFlag_AddFollower(this, bot);
}

static unknown_t detour_CCaptureFlag_RemoveFollower(void* this, CTFBot* bot)
{
	int cvar = ConVar_GetInt(&cvar_CCaptureFlag_RemoveFollower);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_ent_info(this, str_this, sizeof(str_this));
	char str_bot[4096];
	_get_player_info(bot, str_bot, sizeof(str_bot));
	cl_con_printf("[%8.3f] CCaptureFlag::RemoveFollower(%s, %s)\n",
		(*gpGlobals)->curtime, str_this, str_bot);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CCaptureFlag_RemoveFollower(this, bot);
}

static unknown_t detour_CCaptureFlag_PickUp(void* this, CTFPlayer* player, bool b1)
{
	int cvar = ConVar_GetInt(&cvar_CCaptureFlag_PickUp);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_ent_info(this, str_this, sizeof(str_this));
	char str_player[4096];
	_get_player_info(player, str_player, sizeof(str_player));
	cl_con_printf("[%8.3f] CCaptureFlag::PickUp(%s, %s, %s)\n",
		(*gpGlobals)->curtime, str_this, str_player,
		(b1 ? "true" : "false"));
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CCaptureFlag_PickUp(this, player, b1);
}

static unknown_t detour_CCaptureFlag_Drop(void* this, CTFPlayer* player, bool b1, bool b2, bool b3)
{
	int cvar = ConVar_GetInt(&cvar_CCaptureFlag_Drop);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_ent_info(this, str_this, sizeof(str_this));
	char str_player[4096];
	_get_player_info(player, str_player, sizeof(str_player));
	cl_con_printf("[%8.3f] CCaptureFlag::Drop(%s, %s, %s, %s, %s)\n",
		(*gpGlobals)->curtime, str_this, str_player,
		(b1 ? "true" : "false"),
		(b2 ? "true" : "false"),
		(b3 ? "true" : "false"));
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CCaptureFlag_Drop(this, player, b1, b2, b3);
}

static unknown_t detour_CTFBot_SetFlagTarget(void* this, void* flag)
{
	int cvar = ConVar_GetInt(&cvar_CTFBot_SetFlagTarget);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_player_info(this, str_this, sizeof(str_this));
	char str_flag[4096];
	_get_ent_info(flag, str_flag, sizeof(str_flag));
	cl_con_printf("[%8.3f] CTFBot::SetFlagTarget(%s, %s)\n",
		(*gpGlobals)->curtime, str_this, str_flag);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFBot_SetFlagTarget(this, flag);
}

static unknown_t detour_CTFBot_Event_Killed(void* this, CTakeDamageInfo* info)
{
	int cvar = ConVar_GetInt(&cvar_CTFBot_Event_Killed);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_player_info(this, str_this, sizeof(str_this));
	cl_con_printf("[%8.3f] CTFBot::Event_Killed(%s, <info>)\n",
		(*gpGlobals)->curtime, str_this);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFBot_Event_Killed(this, info);
}

static unknown_t detour_CTFBot_ChangeTeam(void* this, int team, bool b1, bool b2)
{
	int cvar = ConVar_GetInt(&cvar_CTFBot_ChangeTeam);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_player_info(this, str_this, sizeof(str_this));
	cl_con_printf("[%8.3f] CTFBot::ChangeTeam(%s, %d<%s>, %s, %s)\n",
		(*gpGlobals)->curtime, str_this, team,
		_get_team_name(team),
		(b1 ? "true" : "false"),
		(b2 ? "true" : "false"));
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFBot_ChangeTeam(this, team, b1, b2);
}

static unknown_t detour_CTFPlayer_ForceChangeTeam(void* this, int team, bool b1)
{
	int cvar = ConVar_GetInt(&cvar_CTFPlayer_ForceChangeTeam);
	if ((cvar & 1) == 0) goto done;
	
	char str_this[4096];
	_get_player_info(this, str_this, sizeof(str_this));
	cl_con_printf("[%8.3f] CTFPlayer::ForceChangeTeam(%s, %d<%s>, %s)\n",
		(*gpGlobals)->curtime, str_this, team,
		_get_team_name(team),
		(b1 ? "true" : "false"));
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFPlayer_ForceChangeTeam(this, team, b1);
}


#define SYM_AND_DETOUR(_var, _mangled) \
	void *_var; \
	symtab_func_absolute(_mangled, (void **)&_var, NULL); \
	DETOUR_CREATE(_var)


DETOUR_SETUP
{
	ConVar_ctor(&cvar_CCaptureFlag_AddFollower,
		"sigsegv_debug_CCaptureFlag_AddFollower", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CCaptureFlag::AddFollower");
	ConVar_ctor(&cvar_CCaptureFlag_RemoveFollower,
		"sigsegv_debug_CCaptureFlag_RemoveFollower", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CCaptureFlag::RemoveFollower");
	ConVar_ctor(&cvar_CCaptureFlag_PickUp,
		"sigsegv_debug_CCaptureFlag_PickUp", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CCaptureFlag::PickUp");
	ConVar_ctor(&cvar_CCaptureFlag_Drop,
		"sigsegv_debug_CCaptureFlag_Drop", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CCaptureFlag::Drop");
	ConVar_ctor(&cvar_CTFBot_SetFlagTarget,
		"sigsegv_debug_CTFBot_SetFlagTarget", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CTFBot::SetFlagTarget");
	ConVar_ctor(&cvar_CTFBot_Event_Killed,
		"sigsegv_debug_CTFBot_Event_Killed", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CTFBot::Event_Killed");
	ConVar_ctor(&cvar_CTFBot_ChangeTeam,
		"sigsegv_debug_CTFBot_ChangeTeam", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CTFBot::ChangeTeam");
	ConVar_ctor(&cvar_CTFPlayer_ForceChangeTeam,
		"sigsegv_debug_CTFPlayer_ForceChangeTeam", "1", FCVAR_NOTIFY,
		"Debug: trace calls to CTFPlayer::ForceChangeTeam");
	
	SYM_AND_DETOUR(CCaptureFlag_AddFollower, "_ZN12CCaptureFlag11AddFollowerEP6CTFBot");
	SYM_AND_DETOUR(CCaptureFlag_RemoveFollower, "_ZN12CCaptureFlag14RemoveFollowerEP6CTFBot");
	SYM_AND_DETOUR(CCaptureFlag_PickUp, "_ZN12CCaptureFlag6PickUpEP9CTFPlayerb");
	SYM_AND_DETOUR(CCaptureFlag_Drop, "_ZN12CCaptureFlag4DropEP9CTFPlayerbbb");
	SYM_AND_DETOUR(CTFBot_SetFlagTarget, "_ZN6CTFBot13SetFlagTargetEP12CCaptureFlag");
	SYM_AND_DETOUR(CTFBot_Event_Killed, "_ZN6CTFBot12Event_KilledERK15CTakeDamageInfo");
	SYM_AND_DETOUR(CTFBot_ChangeTeam, "_ZN6CTFBot10ChangeTeamEibb");
	SYM_AND_DETOUR(CTFPlayer_ForceChangeTeam, "_ZN9CTFPlayer15ForceChangeTeamEib");
	
	return true;
}
