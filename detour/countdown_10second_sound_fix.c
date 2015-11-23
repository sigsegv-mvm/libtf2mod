#include "all.h"


DETOUR(countdown_10second_sound_fix);
/*  */


#if 0
static bool (*trampoline_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady)(CTeamplayRoundBasedRules* this, int);


static func_t *func_CTFGameRules_BetweenRounds_Think;


static bool detour_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady(CTeamplayRoundBasedRules* this, int teamnum)
{
	bool result = trampoline_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady(this, teamnum);
	
	pr_info("%s", __func__);
	pr_debug("(%d): %s\n",
		teamnum,
		(result ? "TRUE" : "FALSE"));
	
	if (result) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1,
			func_CTFGameRules_BetweenRounds_Think)) {
			bool *m_bAwaitingReadyRestart = prop_CTFGameRules_m_bAwaitingReadyRestart(this);
			pr_debug("  this->m_bAwaitingReadyRestart: %s\n",
				(*m_bAwaitingReadyRestart ? "TRUE" : "FALSE"));
			if (!*m_bAwaitingReadyRestart) {
				pr_debug("  setting m_bAwaitingReadyRestart to TRUE\n");
				CGameRulesProxy_NotifyNetworkStateChanged();
				*m_bAwaitingReadyRestart = true;
			}
		}
	}
	
	return result;
}


DETOUR_SETUP
{
	func_CTFGameRules_BetweenRounds_Think =
		func_register(CTFGameRules_BetweenRounds_Think);
	
	DETOUR_CREATE(CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady);
	
	return true;
}
#endif


#if 0
static void (*trampoline_CTFGameRules_BetweenRounds_Think)(CTFGameRules* this);


static void detour_CTFGameRules_BetweenRounds_Think(CTFGameRules* this)
{
	pr_info("CTFGameRules::BetweenRounds_Think");
	pr_debug(" @ %.3f\n", (*gpGlobals)->curtime);
	
	bool  *m_bInWaitingForPlayers  = prop_CTFGameRules_m_bInWaitingForPlayers(this);
	bool  *m_bAwaitingReadyRestart = prop_CTFGameRules_m_bAwaitingReadyRestart(this);
	float *m_flRestartRoundTime    = prop_CTFGameRules_m_flRestartRoundTime(this);
	
	static const char c_red[] = "\e[91m";
	static const char c_grn[] = "\e[92m";
	static const char c_rst[] = "\e[0m";
	
	pr_debug(
		"  m_bInWaitingForPlayers  %s%s%s\n"
		"  m_bAwaitingReadyRestart %s%s%s\n"
		"  m_flRestartRoundTime    %s%.3f%s\n",
		(*m_bInWaitingForPlayers ? c_grn : c_red),
		(*m_bInWaitingForPlayers ? "TRUE" : "FALSE"),
		c_rst,
		(*m_bAwaitingReadyRestart ? c_red : c_grn),
		(*m_bAwaitingReadyRestart ? "TRUE" : "FALSE"),
		c_rst,
		(*m_flRestartRoundTime >= 0.0f ? c_grn : c_red),
		*m_flRestartRoundTime,
		c_rst);
	
	trampoline_CTFGameRules_BetweenRounds_Think(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFGameRules_BetweenRounds_Think);
	
	return true;
}
#endif


static void (*trampoline_ConVar_SetValue_int)(ConVar* this, int);


static func_t *func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState;


static void detour_ConVar_SetValue_int(ConVar* this, int val)
{
	trampoline_ConVar_SetValue_int(this, val);
	
	pr_debug("%s(%08x, %d)\n", "ConVar::SetValue", (uintptr_t)this, val);
	if (this == CONVAR_mp_restartgame && val != 0) {
		pr_debug("  this and val are good\n");
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1,
			func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState)) {
			pr_debug("%s: firing event 'tournament_enablecountdown'\n",
				__func__);
			
			IGameEvent* event = CGameEventManager_CreateEvent(*gameeventmanager,
				"tournament_enablecountdown", false);
			if (event != NULL) {
				CGameEventManager_FireEvent(*gameeventmanager,
					event, false);
			}
		}
	}
}


DETOUR_SETUP
{
	func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState =
		func_register(CTFGameRules_PlayerReadyStatus_UpdatePlayerState);
	
	DETOUR_CREATE(ConVar_SetValue_int);
	
	return true;
}
