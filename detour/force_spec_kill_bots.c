#include "all.h"


DETOUR(force_spec_kill_bots);
/* make sure that bots which are forced to team spectator are properly killed
 * first */


static void (*trampoline_CTFPlayer_ForceChangeTeam)(CTFPlayer* this, int, bool);
static void (*trampoline_CTFBot_ChangeTeam)(CTFBot* this, int, bool, bool);


static ConVar cvar_all;
static ConVar cvar_sentrybuster;
static ConVar cvar_forcefinish;
static ConVar cvar_firegameevent;
static ConVar cvar_squad;


static func_t *func_CTFBotMissionSuicideBomber_Detonate;
static func_t *func_CWaveSpawnPopulator_ForceFinish;
static func_t *func_CTFGameRules_FireGameEvent;
static func_t *func_CSquadSpawner_Spawn;


static void detour_CTFPlayer_ForceChangeTeam(CTFPlayer* this, int i1, bool b1)
{
	if (i1 == TEAM_SPECTATOR) {
		uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(__builtin_return_address(0));
		if (ConVar_GetInt(&cvar_sentrybuster) != 0 &&
			func_owns_addr(caller, func_CTFBotMissionSuicideBomber_Detonate)) {
			pr_debug("CTFPlayer::ForceChangeTeam [from CTFBotMissionSuicideBomber::Detonate]\n"
				"  calling CommitSuicide before switching to spectator\n");
			vcall_CBasePlayer_CommitSuicide(this, false, true);
		}
	}
	
	trampoline_CTFPlayer_ForceChangeTeam(this, i1, b1);
}

static void detour_CTFBot_ChangeTeam(CTFBot* this, int i1, bool b1, bool b2)
{
	if (i1 == TEAM_SPECTATOR) {
		uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(__builtin_return_address(0));
		if (ConVar_GetInt(&cvar_forcefinish) != 0 &&
			func_owns_addr(caller, func_CWaveSpawnPopulator_ForceFinish)) {
			pr_debug("CTFBot::ChangeTeam [from CWaveSpawnPopulator::ForceFinish]\n"
				"  calling CommitSuicide before switching to spectator\n");
			vcall_CBasePlayer_CommitSuicide(this, false, true);
		}
		
		if (ConVar_GetInt(&cvar_firegameevent) != 0 &&
			func_owns_addr(caller, func_CTFGameRules_FireGameEvent)) {
			pr_debug("CTFBot::ChangeTeam [from CTFGameRules::FireGameEvent]\n"
				"  calling CommitSuicide before switching to spectator\n");
			vcall_CBasePlayer_CommitSuicide(this, false, true);
		}
		
		if (ConVar_GetInt(&cvar_squad) != 0 &&
			func_owns_addr(caller, func_CSquadSpawner_Spawn)) {
			pr_debug("CTFBot::ChangeTeam [from CSquadSpawner::Spawn]\n"
				"  calling CommitSuicide before switching to spectator\n");
			vcall_CBasePlayer_CommitSuicide(this, false, true);
		}
	}
	
	trampoline_CTFBot_ChangeTeam(this, i1, b1, b2);
}


void cvar_change_all(IConVar* var, const char *pOldValue, float flOldValue)
{
	int val = ConVar_GetInt(&cvar_all);
	
	ConVar_SetValue_int(&cvar_sentrybuster, val);
	ConVar_SetValue_int(&cvar_forcefinish, val);
	ConVar_SetValue_int(&cvar_firegameevent, val);
	ConVar_SetValue_int(&cvar_squad, val);
}


DETOUR_SETUP
{
	ConVar_ctor_callback(&cvar_all,
		"sigsegv_suicide_all", "0", FCVAR_NOTIFY,
		"Detour: set suicide-before-spectator for all cases",
		cvar_change_all);
	ConVar_ctor(&cvar_sentrybuster,
		"sigsegv_suicide_sentrybuster", "0", FCVAR_NOTIFY,
		"Detour: set suicide-before-spectator for CTFBotMissionSuicideBomber::Detonate");
	ConVar_ctor(&cvar_forcefinish,
		"sigsegv_suicide_forcefinish", "0", FCVAR_NOTIFY,
		"Detour: set suicide-before-spectator for CWaveSpawnPopulator::ForceFinish");
	ConVar_ctor(&cvar_firegameevent,
		"sigsegv_suicide_firegameevent", "0", FCVAR_NOTIFY,
		"Detour: set suicide-before-spectator for CTFGameRules::FireGameEvent");
	ConVar_ctor(&cvar_squad,
		"sigsegv_suicide_squad", "0", FCVAR_NOTIFY,
		"Detour: set suicide-before-spectator for CSquadSpawner::Spawn");
	
	func_CTFBotMissionSuicideBomber_Detonate =
		func_register(CTFBotMissionSuicideBomber_Detonate);
	func_CWaveSpawnPopulator_ForceFinish =
		func_register(CWaveSpawnPopulator_ForceFinish);
	func_CTFGameRules_FireGameEvent =
		func_register(CTFGameRules_FireGameEvent);
	func_CSquadSpawner_Spawn =
		func_register(CSquadSpawner_Spawn);
	
	DETOUR_CREATE(CTFPlayer_ForceChangeTeam);
	DETOUR_CREATE(CTFBot_ChangeTeam);
	
	return true;
}
