#include "all.h"


DETOUR(debug_gametype);
/*  */


static void (*trampoline_CTFGameRulesProxy_Activate)(CTFGameRulesProxy* this);


static uintptr_t off_m_nHudType;
static uintptr_t off_m_nGameType;
static uintptr_t off_m_nMapHolidayType;
static uintptr_t off_m_nStopWatchState;
static uintptr_t off_m_bIsInItemTestingMode;
static uintptr_t off_m_bPlayingKoth;
static uintptr_t off_m_bPlayingMedieval;
static uintptr_t off_m_bPlayingHybrid_CTF_CP;
static uintptr_t off_m_bPlayingSpecialDeliveryMode;
static uintptr_t off_m_bPlayingMannVsMachine;
static uintptr_t off_m_bPlayingRobotDestructionMode;
static uintptr_t off_m_bCompetitiveMode;
static uintptr_t off_m_bPowerupMode;
static uintptr_t off_m_bHaveMinPlayersToEnableReady;


static void detour_CTFGameRulesProxy_Activate(CTFGameRulesProxy* this)
{
	int *m_nHudType = (int *)((uintptr_t)(*g_pGameRules) + off_m_nHudType);
	int *m_nGameType = (int *)((uintptr_t)(*g_pGameRules) + off_m_nGameType);
	int *m_nMapHolidayType = (int *)((uintptr_t)(*g_pGameRules) + off_m_nMapHolidayType);
	int *m_nStopWatchState = (int *)((uintptr_t)(*g_pGameRules) + off_m_nStopWatchState);
	bool *m_bIsInItemTestingMode = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bIsInItemTestingMode);
	bool *m_bPlayingKoth = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingKoth);
	bool *m_bPlayingMedieval = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingMedieval);
	bool *m_bPlayingHybrid_CTF_CP = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingHybrid_CTF_CP);
	bool *m_bPlayingSpecialDeliveryMode = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingSpecialDeliveryMode);
	bool *m_bPlayingMannVsMachine = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingMannVsMachine);
	bool *m_bPlayingRobotDestructionMode = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPlayingRobotDestructionMode);
	bool *m_bCompetitiveMode = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bCompetitiveMode);
	bool *m_bPowerupMode = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bPowerupMode);
	bool *m_bHaveMinPlayersToEnableReady = (bool *)((uintptr_t)(*g_pGameRules) + off_m_bHaveMinPlayersToEnableReady);
	
	
	pr_info("[PRE]  CTFGameRulesProxy::Activate\n");
	pr_debug(
		"m_nHudType = %d\n"
		"m_nGameType = %d\n"
		"m_nMapHolidayType = %d\n"
		"m_nStopWatchState = %d\n"
		"m_bIsInItemTestingMode = %s\n"
		"m_bPlayingKoth = %s\n"
		"m_bPlayingMedieval = %s\n"
		"m_bPlayingHybrid_CTF_CP = %s\n"
		"m_bPlayingSpecialDeliveryMode = %s\n"
		"m_bPlayingMannVsMachine = %s\n"
		"m_bPlayingRobotDestructionMode = %s\n"
		"m_bCompetitiveMode = %s\n"
		"m_bPowerupMode = %s\n"
		"m_bHaveMinPlayersToEnableReady = %s\n",
		*m_nHudType,
		*m_nGameType,
		*m_nMapHolidayType,
		*m_nStopWatchState,
		(*m_bIsInItemTestingMode ? "TRUE" : "FALSE"),
		(*m_bPlayingKoth ? "TRUE" : "FALSE"),
		(*m_bPlayingMedieval ? "TRUE" : "FALSE"),
		(*m_bPlayingHybrid_CTF_CP ? "TRUE" : "FALSE"),
		(*m_bPlayingSpecialDeliveryMode ? "TRUE" : "FALSE"),
		(*m_bPlayingMannVsMachine ? "TRUE" : "FALSE"),
		(*m_bPlayingRobotDestructionMode ? "TRUE" : "FALSE"),
		(*m_bCompetitiveMode ? "TRUE" : "FALSE"),
		(*m_bPowerupMode ? "TRUE" : "FALSE"),
		(*m_bHaveMinPlayersToEnableReady ? "TRUE" : "FALSE"));
	
	
	/*pr_info("before: manually calling CTFGameRules::Activate\n");
	CTFGameRules_Activate(*g_pGameRules);
	pr_info(" after: manually calling CTFGameRules::Activate\n");
	
	
	pr_info("[MID]  CTFGameRulesProxy::Activate\n");
	pr_debug(
		"m_nHudType = %d\n"
		"m_nGameType = %d\n"
		"m_nMapHolidayType = %d\n"
		"m_nStopWatchState = %d\n"
		"m_bIsInItemTestingMode = %s\n"
		"m_bPlayingKoth = %s\n"
		"m_bPlayingMedieval = %s\n"
		"m_bPlayingHybrid_CTF_CP = %s\n"
		"m_bPlayingSpecialDeliveryMode = %s\n"
		"m_bPlayingMannVsMachine = %s\n"
		"m_bPlayingRobotDestructionMode = %s\n"
		"m_bCompetitiveMode = %s\n"
		"m_bPowerupMode = %s\n"
		"m_bHaveMinPlayersToEnableReady = %s\n",
		*m_nHudType,
		*m_nGameType,
		*m_nMapHolidayType,
		*m_nStopWatchState,
		(*m_bIsInItemTestingMode ? "TRUE" : "FALSE"),
		(*m_bPlayingKoth ? "TRUE" : "FALSE"),
		(*m_bPlayingMedieval ? "TRUE" : "FALSE"),
		(*m_bPlayingHybrid_CTF_CP ? "TRUE" : "FALSE"),
		(*m_bPlayingSpecialDeliveryMode ? "TRUE" : "FALSE"),
		(*m_bPlayingMannVsMachine ? "TRUE" : "FALSE"),
		(*m_bPlayingRobotDestructionMode ? "TRUE" : "FALSE"),
		(*m_bCompetitiveMode ? "TRUE" : "FALSE"),
		(*m_bPowerupMode ? "TRUE" : "FALSE"),
		(*m_bHaveMinPlayersToEnableReady ? "TRUE" : "FALSE"));*/
	
	
	pr_info("entering trampoline: CTFGameRulesProxy::Activate\n");
	trampoline_CTFGameRulesProxy_Activate(this);
	pr_info(" exiting trampoline: CTFGameRulesProxy::Activate\n");
	
	
	pr_info("[POST] CTFGameRulesProxy::Activate\n");
	pr_debug(
		"m_nHudType = %d\n"
		"m_nGameType = %d\n"
		"m_nMapHolidayType = %d\n"
		"m_nStopWatchState = %d\n"
		"m_bIsInItemTestingMode = %s\n"
		"m_bPlayingKoth = %s\n"
		"m_bPlayingMedieval = %s\n"
		"m_bPlayingHybrid_CTF_CP = %s\n"
		"m_bPlayingSpecialDeliveryMode = %s\n"
		"m_bPlayingMannVsMachine = %s\n"
		"m_bPlayingRobotDestructionMode = %s\n"
		"m_bCompetitiveMode = %s\n"
		"m_bPowerupMode = %s\n"
		"m_bHaveMinPlayersToEnableReady = %s\n",
		*m_nHudType,
		*m_nGameType,
		*m_nMapHolidayType,
		*m_nStopWatchState,
		(*m_bIsInItemTestingMode ? "TRUE" : "FALSE"),
		(*m_bPlayingKoth ? "TRUE" : "FALSE"),
		(*m_bPlayingMedieval ? "TRUE" : "FALSE"),
		(*m_bPlayingHybrid_CTF_CP ? "TRUE" : "FALSE"),
		(*m_bPlayingSpecialDeliveryMode ? "TRUE" : "FALSE"),
		(*m_bPlayingMannVsMachine ? "TRUE" : "FALSE"),
		(*m_bPlayingRobotDestructionMode ? "TRUE" : "FALSE"),
		(*m_bCompetitiveMode ? "TRUE" : "FALSE"),
		(*m_bPowerupMode ? "TRUE" : "FALSE"),
		(*m_bHaveMinPlayersToEnableReady ? "TRUE" : "FALSE"));
}


DETOUR_SETUP
{
	assert((off_m_nHudType = sendprop_offset("CTFGameRulesProxy", "m_nHudType")) != 0);
	assert((off_m_nGameType = sendprop_offset("CTFGameRulesProxy", "m_nGameType")) != 0);
	assert((off_m_bIsInItemTestingMode = sendprop_offset("CTFGameRulesProxy", "m_bIsInItemTestingMode")) != 0);
	assert((off_m_bPlayingKoth = sendprop_offset("CTFGameRulesProxy", "m_bPlayingKoth")) != 0);
	assert((off_m_bPlayingMedieval = sendprop_offset("CTFGameRulesProxy", "m_bPlayingMedieval")) != 0);
	assert((off_m_bPlayingHybrid_CTF_CP = sendprop_offset("CTFGameRulesProxy", "m_bPlayingHybrid_CTF_CP")) != 0);
	assert((off_m_bPlayingSpecialDeliveryMode = sendprop_offset("CTFGameRulesProxy", "m_bPlayingSpecialDeliveryMode")) != 0);
	assert((off_m_bPlayingMannVsMachine = sendprop_offset("CTFGameRulesProxy", "m_bPlayingMannVsMachine")) != 0);
	assert((off_m_bPlayingRobotDestructionMode = sendprop_offset("CTFGameRulesProxy", "m_bPlayingRobotDestructionMode")) != 0);
	assert((off_m_bCompetitiveMode = sendprop_offset("CTFGameRulesProxy", "m_bCompetitiveMode")) != 0);
	assert((off_m_bPowerupMode = sendprop_offset("CTFGameRulesProxy", "m_bPowerupMode")) != 0);
	assert((off_m_nMapHolidayType = sendprop_offset("CTFGameRulesProxy", "m_nMapHolidayType")) != 0);
	assert((off_m_bHaveMinPlayersToEnableReady = sendprop_offset("CTFGameRulesProxy", "m_bHaveMinPlayersToEnableReady")) != 0);
	assert((off_m_nStopWatchState = sendprop_offset("CTFGameRulesProxy", "m_nStopWatchState")) != 0);
	
	DETOUR_CREATE(CTFGameRulesProxy_Activate);
	
	return true;
}
