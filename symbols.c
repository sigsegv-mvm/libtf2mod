#define _LIBTF2MOD_SYMBOLS_C
#include "all.h"


static void *_sym_obj(const char *name)
{
	pr_debug("obj:  %s\n", name);
	
	symbol_t sym;
	if (!symtab_obj_name(&sym, name)) {
		pr_warn("could not get address for object symbol '%s'\n", name);
		return NULL;
	}
	
	uintptr_t addr = dl_baseaddr + sym.addr;
	return (void *)addr;
}

static void *_sym_func(const char *name)
{
	pr_debug("func: %s\n", name);
	
	symbol_t sym;
	if (!symtab_func_name(&sym, name)) {
		pr_warn("could not get address for function symbol '%s'\n", name);
		return NULL;
	}
	
	uintptr_t addr = dl_baseaddr + sym.addr;
	return (void *)addr;
}


void symbols_init(void)
{
	g_pGameRules = _sym_obj("g_pGameRules");
	
	
	ENTINDEX = _sym_func("_Z8ENTINDEXP11CBaseEntity");
	
	UTIL_ScreenShake = _sym_func("_Z16UTIL_ScreenShakeRK6Vectorffff14ShakeCommand_tb");
	
	WeaponID_IsSniperRifle = _sym_func("_Z22WeaponID_IsSniperRiflei");
	WeaponID_IsSniperRifleOrBow = _sym_func("_Z27WeaponID_IsSniperRifleOrBowi");
	
	
	CBaseEntity_PrecacheScriptSound = _sym_func("_ZN11CBaseEntity19PrecacheScriptSoundEPKc");
	
	CAttributeManager_AttribHookValue_int = _sym_func("_ZN17CAttributeManager15AttribHookValueIiEET_S1_PKcPK11CBaseEntityP10CUtlVectorIPS4_10CUtlMemoryIS8_iEEb");
	
	
	CBaseEntity_ApplyAbsVelocityImpulse = _sym_func("_ZN11CBaseEntity23ApplyAbsVelocityImpulseERK6Vector");
	
	CBaseAnimating_SetModelScale = _sym_func("_ZN14CBaseAnimating13SetModelScaleEff");
	
	CTFPlayerShared_AddCond = _sym_func("_ZN15CTFPlayerShared7AddCondE7ETFCondfP11CBaseEntity");
	CTFPlayerShared_RadiusCurrencyCollectionCheck = _sym_func("_ZN15CTFPlayerShared29RadiusCurrencyCollectionCheckEv");
	
	CTFPlayer_CanBeForcedToLaugh = _sym_func("_ZN9CTFPlayer18CanBeForcedToLaughEv");
	CTFPlayer_CanBuild = _sym_func("_ZN9CTFPlayer8CanBuildEii");
	CTFPlayer_DeathSound = _sym_func("_ZN9CTFPlayer10DeathSoundERK15CTakeDamageInfo");
	CTFPlayer_Event_Killed = _sym_func("_ZN9CTFPlayer12Event_KilledERK15CTakeDamageInfo");
	CTFPlayer_IsMiniBoss = _sym_func("_ZNK9CTFPlayer10IsMiniBossEv");
	CTFPlayer_IsPlayerClass = _sym_func("_ZNK9CTFPlayer13IsPlayerClassEi");
	CTFPlayer_OnTakeDamage_Alive = _sym_func("_ZN9CTFPlayer18OnTakeDamage_AliveERK15CTakeDamageInfo");
	CTFPlayer_ShouldGib = _sym_func("_ZN9CTFPlayer9ShouldGibERK15CTakeDamageInfo");
	
	CTFBot_ShouldGib = _sym_func("_ZN6CTFBot9ShouldGibERK15CTakeDamageInfo");
	
	CTFTankBoss_TankBossThink = _sym_func("_ZN11CTFTankBoss13TankBossThinkEv");
	
	CTFWeaponBaseGun_PrimaryAttack = _sym_func("_ZN16CTFWeaponBaseGun13PrimaryAttackEv");
	
	CTFRocketLauncher_Precache = _sym_func("_ZN17CTFRocketLauncher8PrecacheEv");
	
	CTFSniperRifle_ExplosiveHeadShot = _sym_func("_ZN14CTFSniperRifle17ExplosiveHeadShotEP9CTFPlayerS1_");
	CTFSniperRifle_ItemPostFrame = _sym_func("_ZN14CTFSniperRifle13ItemPostFrameEv");
	CTFSniperRifleClassic_ItemPostFrame = _sym_func("_ZN21CTFSniperRifleClassic13ItemPostFrameEv");
	CTFSniperRifleDecap_SniperRifleChargeRateMod = _sym_func("_ZN19CTFSniperRifleDecap24SniperRifleChargeRateModEv");
	
	CTFProjectile_Arrow_StrikeTarget_clone323 = _sym_func("_ZN19CTFProjectile_Arrow12StrikeTargetEP13mstudiobbox_tP11CBaseEntity.part.323");
	
	CBaseObject_DoQuickBuild = _sym_func("_ZN11CBaseObject12DoQuickBuildEb");
	CBaseObject_GetMaxHealthForCurrentLevel = _sym_func("_ZN11CBaseObject27GetMaxHealthForCurrentLevelEv");
	CBaseObject_GetType = _sym_func("_ZNK11CBaseObject7GetTypeEv");
	CBaseObject_MakeDisposableBuilding = _sym_func("_ZN11CBaseObject22MakeDisposableBuildingEP9CTFPlayer");
	CBaseObject_SetHealth = _sym_func("_ZN11CBaseObject9SetHealthEf");
	CBaseObject_ShouldBeMiniBuilding = _sym_func("_ZN11CBaseObject20ShouldBeMiniBuildingEP9CTFPlayer");
	
	CObjectDispenser_MakeMiniBuilding = _sym_func("_ZN16CObjectDispenser16MakeMiniBuildingEP9CTFPlayer");
	CObjectDispenser_ShouldBeMiniBuilding = _sym_func("_ZN16CObjectDispenser20ShouldBeMiniBuildingEP9CTFPlayer");
	CObjectDispenser_StartPlacement = _sym_func("_ZN16CObjectDispenser14StartPlacementEP9CTFPlayer");
	
	CObjectSentrygun_GetMaxHealthForCurrentLevel = _sym_func("_ZN16CObjectSentrygun27GetMaxHealthForCurrentLevelEv");
	CObjectSentrygun_SentryRotate = _sym_func("_ZN16CObjectSentrygun12SentryRotateEv");
	CObjectSentrygun_SentryThink = _sym_func("_ZN16CObjectSentrygun11SentryThinkEv");
	
	CTFGameRules_CanUpgradeWithAttrib = _sym_func("_ZN12CTFGameRules20CanUpgradeWithAttribEP9CTFPlayeritP22CMannVsMachineUpgrades");
	CTFGameRules_GameModeUsesUpgrades = _sym_func("_ZN12CTFGameRules20GameModeUsesUpgradesEv");
	CTFGameRules_PushAllPlayersAway = _sym_func("_ZN12CTFGameRules18PushAllPlayersAwayERK6VectorffiP10CUtlVectorIP9CTFPlayer10CUtlMemoryIS5_iEE");
	
	CTFBotMainAction_OnContact = _sym_func("_ZN16CTFBotMainAction9OnContactEP6CTFBotP11CBaseEntityP10CGameTrace");
	CTFBotMainAction_Update = _sym_func("_ZN16CTFBotMainAction6UpdateEP6CTFBotf");
}
