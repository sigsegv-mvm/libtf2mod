#include "all.h"


DETOUR(debug_readyup_missing_sounds);
/*  */


static void (*trampoline_ConVar_SetValue_int)(ConVar* this, int);
static IGameEvent* (*trampoline_CGameEventManager_CreateEvent)(CGameEventManager* this, char const*, bool);
static bool (*trampoline_CGameEventManager_FireEvent)(CGameEventManager* this, IGameEvent*, bool);
static void (*trampoline_CTFGameRules_BetweenRounds_Think)(CTFGameRules* this);
static bool (*trampoline_CTFGameRules_PlayerReadyStatus_HaveMinPlayersToEnable)(CTFGameRules* this);
static bool (*trampoline_CTFGameRules_PlayerReadyStatus_ShouldStartCountdown)(CTFGameRules* this);
static bool (*trampoline_CTFGameRules_UsePlayerReadyStatusMode)(CTFGameRules* this);
static bool (*trampoline_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady)(CTeamplayRoundBasedRules* this, int);
static void (*trampoline_CTeamplayRoundBasedRules_CheckReadyRestart)(CTeamplayRoundBasedRules* this);


static func_t *func_CTFGameRules_BetweenRounds_Think;


static void detour_ConVar_SetValue_int(ConVar* this, int val)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think) &&
		this == *CONVAR_mp_restartgame) {
		pr_info(" ConVar::SetValue(mp_restartgame): ");
		pr_debug(" was:%d now:%d\n",
			this->m_nValue,
			val);
	}
	
	trampoline_ConVar_SetValue_int(this, val);
}

static IGameEvent* detour_CGameEventManager_CreateEvent(CGameEventManager* this, char const* s1, bool b1)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	IGameEvent* result = trampoline_CGameEventManager_CreateEvent(this, s1, b1);
	
	/*if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {*/
		pr_info(" CGameEventManager::CreateEvent");
		pr_debug("('%s', %s) = %08x\n",
			s1,
			(b1 ? "TRUE" : "FALSE"),
			(uintptr_t)result);
	/*}*/
	
	return result;
}

static bool detour_CGameEventManager_FireEvent(CGameEventManager* this, IGameEvent* e1, bool b1)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(1));
	
	bool result = trampoline_CGameEventManager_FireEvent(this, e1, b1);
	
	/*if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think) ||
		func_owns_addr(caller1,
		func_CTFGameRules_BetweenRounds_Think)) {*/
		pr_info(" CGameEventManager::FireEvent");
		pr_debug("(%08x, %s) = %s\n",
			(uintptr_t)e1,
			(b1 ? "TRUE" : "FALSE"),
			(result ? "TRUE" : "FALSE"));
	/*}*/
	
	return result;
}

static void detour_CTFGameRules_BetweenRounds_Think(CTFGameRules* this)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	pr_info("CTFGameRules::BetweenRounds_Think @ tick %d / time %5.3f\n",
		(*gpGlobals)->tickcount, (*gpGlobals)->curtime);
	
	trampoline_CTFGameRules_BetweenRounds_Think(this);
}

static bool detour_CTFGameRules_PlayerReadyStatus_HaveMinPlayersToEnable(CTFGameRules* this)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	bool result = trampoline_CTFGameRules_PlayerReadyStatus_HaveMinPlayersToEnable(this);
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {
		pr_info(" CTFGameRules::PlayerReadyStatus_HaveMinPlayersToEnable");
		pr_debug(" = %s\n",
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static bool detour_CTFGameRules_PlayerReadyStatus_ShouldStartCountdown(CTFGameRules* this)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	bool result = trampoline_CTFGameRules_PlayerReadyStatus_ShouldStartCountdown(this);
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {
		pr_info(" CTFGameRules::PlayerReadyStatus_ShouldStartCountdown");
		pr_debug(" = %s\n",
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static bool detour_CTFGameRules_UsePlayerReadyStatusMode(CTFGameRules* this)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	bool result = trampoline_CTFGameRules_UsePlayerReadyStatusMode(this);
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {
		pr_info(" CTFGameRules::UsePlayerReadyStatusMode");
		pr_debug(" = %s\n",
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static bool detour_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady(CTeamplayRoundBasedRules* this, int i1)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	bool result = trampoline_CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady(this, i1);
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {
		pr_info(" CTeamplayRoundBasedRules::AreLobbyPlayersOnTeamReady");
		pr_debug("(%d) = %s\n",
			i1,
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static void detour_CTeamplayRoundBasedRules_CheckReadyRestart(CTeamplayRoundBasedRules* this)
{
	uintptr_t caller0 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	if (func_owns_addr(caller0,
		func_CTFGameRules_BetweenRounds_Think)) {
		pr_info(" CTeamplayRoundBasedRules::CheckReadyRestart\n");
	}
	
	trampoline_CTeamplayRoundBasedRules_CheckReadyRestart(this);
}


DETOUR_SETUP
{
	func_CTFGameRules_BetweenRounds_Think =
		func_register(CTFGameRules_BetweenRounds_Think);
	
	DETOUR_CREATE(ConVar_SetValue_int);
	DETOUR_CREATE(CGameEventManager_CreateEvent);
	DETOUR_CREATE(CGameEventManager_FireEvent);
	DETOUR_CREATE(CTFGameRules_BetweenRounds_Think);
	DETOUR_CREATE(CTFGameRules_PlayerReadyStatus_HaveMinPlayersToEnable);
	DETOUR_CREATE(CTFGameRules_PlayerReadyStatus_ShouldStartCountdown);
	DETOUR_CREATE(CTFGameRules_UsePlayerReadyStatusMode);
	DETOUR_CREATE(CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady);
	DETOUR_CREATE(CTeamplayRoundBasedRules_CheckReadyRestart);
	
	return true;
}
