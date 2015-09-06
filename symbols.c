#define _LIBTF2MOD_SYMBOLS_C
#include "all.h"


#define SYMBOL_OBJ(_var, _mangled) \
	symtab_obj_absolute(_mangled, (void **)&_var, NULL)
#define SYMBOL_FUNC(_var, _mangled) \
	symtab_func_absolute(_mangled, (void **)&_var, NULL)


void symbols_init(void)
{
	/* RTTI */
	
	SYMBOL_OBJ(typeinfo_for_CBaseEntity,
		"_ZTI11CBaseEntity");
	SYMBOL_OBJ(typeinfo_for_CBaseObject,
		"_ZTI11CBaseObject");
	SYMBOL_OBJ(typeinfo_for_CTFWeaponBase,
		"_ZTI13CTFWeaponBase");
	
	
	/* globals */
	
	SYMBOL_OBJ(gpGlobals,
		"gpGlobals");
	
	SYMBOL_OBJ(gameeventmanager,
		"gameeventmanager");
	
	SYMBOL_OBJ(g_pGameRules,
		"g_pGameRules");
	
	SYMBOL_OBJ(CTF_GameStats,
		"CTF_GameStats");
	
	SYMBOL_OBJ(g_pObjectiveResource,
		"g_pObjectiveResource");
	
	SYMBOL_OBJ(CONVAR_mp_restartgame,
		"mp_restartgame");
	
	
	/* functions: global */
	
	SYMBOL_FUNC(SV_FindServerClass,
		"_Z18SV_FindServerClassPKc");
	
	SYMBOL_FUNC(ENTINDEX,
		"_Z8ENTINDEXP11CBaseEntity");
	
	SYMBOL_FUNC(UserMessageBegin,
		"_Z16UserMessageBeginR16IRecipientFilterPKc");
	SYMBOL_FUNC(MessageEnd,
		"_Z10MessageEndv");
	SYMBOL_FUNC(MessageWriteAngle,
		"_Z17MessageWriteAnglef");
	SYMBOL_FUNC(MessageWriteAngles,
		"_Z18MessageWriteAnglesRK6QAngle");
	SYMBOL_FUNC(MessageWriteBits,
		"_Z16MessageWriteBitsPKvi");
	SYMBOL_FUNC(MessageWriteBool,
		"_Z16MessageWriteBoolb");
	SYMBOL_FUNC(MessageWriteByte,
		"_Z16MessageWriteBytei");
	SYMBOL_FUNC(MessageWriteChar,
		"_Z16MessageWriteChari");
	SYMBOL_FUNC(MessageWriteCoord,
		"_Z17MessageWriteCoordf");
	SYMBOL_FUNC(MessageWriteEHandle,
		"_Z19MessageWriteEHandleP11CBaseEntity");
	SYMBOL_FUNC(MessageWriteEntity,
		"_Z18MessageWriteEntityi");
	SYMBOL_FUNC(MessageWriteFloat,
		"_Z17MessageWriteFloatf");
	SYMBOL_FUNC(MessageWriteLong,
		"_Z16MessageWriteLongi");
	SYMBOL_FUNC(MessageWriteSBitLong,
		"_Z20MessageWriteSBitLongii");
	SYMBOL_FUNC(MessageWriteShort,
		"_Z17MessageWriteShorti");
	SYMBOL_FUNC(MessageWriteString,
		"_Z18MessageWriteStringPKc");
	SYMBOL_FUNC(MessageWriteUBitLong,
		"_Z20MessageWriteUBitLongji");
	SYMBOL_FUNC(MessageWriteVec3Coord,
		"_Z21MessageWriteVec3CoordRK6Vector");
	SYMBOL_FUNC(MessageWriteVec3Normal,
		"_Z22MessageWriteVec3NormalRK6Vector");
	SYMBOL_FUNC(MessageWriteWord,
		"_Z16MessageWriteWordi");
	
	SYMBOL_FUNC(CreateEntityByName,
		"_Z18CreateEntityByNamePKci");
	
	SYMBOL_FUNC(UTIL_EntityByIndex,
		"_Z18UTIL_EntityByIndexi");
	SYMBOL_FUNC(UTIL_LogPrintf,
		"_Z14UTIL_LogPrintfPKcz");
	SYMBOL_FUNC(UTIL_PlayerByIndex,
		"_Z18UTIL_PlayerByIndexi");
	SYMBOL_FUNC(UTIL_ScreenShake,
		"_Z16UTIL_ScreenShakeRK6Vectorffff14ShakeCommand_tb");
	
	SYMBOL_FUNC(TranslateWeaponEntForClass,
		"_Z26TranslateWeaponEntForClassPKci");
	
	SYMBOL_FUNC(WeaponID_IsSniperRifle,
		"_Z22WeaponID_IsSniperRiflei");
	SYMBOL_FUNC(WeaponID_IsSniperRifleOrBow,
		"_Z27WeaponID_IsSniperRifleOrBowi");
	
	SYMBOL_FUNC(FX_FireBullets,
		"_Z14FX_FireBulletsP13CTFWeaponBaseiRK6VectorRK6QAngleiiiffb");
	
	
	/* functions: static */
	
	SYMBOL_FUNC(CBaseEntity_PrecacheScriptSound,
		"_ZN11CBaseEntity19PrecacheScriptSoundEPKc");
	
	SYMBOL_FUNC(CBaseObject_GetDataDescMap,
		"_ZN11CBaseObject14GetDataDescMapEv");
	SYMBOL_FUNC(CObjectSentrygun_GetDataDescMap,
		"_ZN16CObjectSentrygun14GetDataDescMapEv");
	
	SYMBOL_FUNC(CTFMedigunShield_Create,
		"_ZN16CTFMedigunShield6CreateEP9CTFPlayer");
	
	SYMBOL_FUNC(CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot,
		"_ZN20CTFPlayerSharedUtils28GetEconItemViewByLoadoutSlotEP9CTFPlayeriPP11CEconEntity");
	
	SYMBOL_FUNC(CAttributeManager_AttribHookValue_int,
		"_ZN17CAttributeManager15AttribHookValueIiEET_S1_PKcPK11CBaseEntityP10CUtlVectorIPS4_10CUtlMemoryIS8_iEEb");
	
	
	/* functions: member */
	
	SYMBOL_FUNC(CServerGameDLL_DLLInit,
		"_ZN14CServerGameDLL7DLLInitEPFPvPKcPiES5_S5_P11CGlobalVars");
	
	SYMBOL_FUNC(ConVar_SetValue_int,
		"_ZN6ConVar8SetValueEi");
	
	SYMBOL_FUNC(ConCommand_ctor,
		"_ZN10ConCommandC1EPKcPFvRK8CCommandES1_iPFiS1_PA64_cE");
	
	SYMBOL_FUNC(CGameEventManager_CreateEvent,
		"_ZN17CGameEventManager11CreateEventEPKcb");
	SYMBOL_FUNC(CGameEventManager_FireEvent,
		"_ZN17CGameEventManager9FireEventEP10IGameEventb");
	
	SYMBOL_FUNC(CBaseEntity_ApplyAbsVelocityImpulse,
		"_ZN11CBaseEntity23ApplyAbsVelocityImpulseERK6Vector");
	SYMBOL_FUNC(CBaseEntity_GetMaxHealth,
		"_ZNK11CBaseEntity12GetMaxHealthEv");
	SYMBOL_FUNC(CBaseEntity_GetTeamNumber,
		"_ZNK11CBaseEntity13GetTeamNumberEv");
	SYMBOL_FUNC(CBaseEntity_IsBaseObject,
		"_ZNK11CBaseEntity12IsBaseObjectEv");
	SYMBOL_FUNC(CBaseEntity_NetworkStateChanged,
		"_ZN11CBaseEntity19NetworkStateChangedEPv");
	
	SYMBOL_FUNC(CBaseAnimating_SetModelScale,
		"_ZN14CBaseAnimating13SetModelScaleEff");
	
	SYMBOL_FUNC(CBasePlayer_GiveNamedItem,
		"_ZN11CBasePlayer13GiveNamedItemEPKci");
	SYMBOL_FUNC(CBasePlayer_IsBot,
		"_ZNK11CBasePlayer5IsBotEv");
	
	SYMBOL_FUNC(CTFPlayerShared_AddCond,
		"_ZN15CTFPlayerShared7AddCondE7ETFCondfP11CBaseEntity");
	SYMBOL_FUNC(CTFPlayerShared_IsInvulnerable,
		"_ZNK15CTFPlayerShared14IsInvulnerableEv");
	SYMBOL_FUNC(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		"_ZN15CTFPlayerShared29RadiusCurrencyCollectionCheckEv");
	
	SYMBOL_FUNC(CTFPlayer_ApplyAbsVelocityImpulse,
		"_ZN9CTFPlayer23ApplyAbsVelocityImpulseERK6Vector");
	SYMBOL_FUNC(CTFPlayer_ApplyAirBlastImpulse,
		"_ZN9CTFPlayer20ApplyAirBlastImpulseERK6Vector");
	SYMBOL_FUNC(CTFPlayer_CanBeForcedToLaugh,
		"_ZN9CTFPlayer18CanBeForcedToLaughEv");
	SYMBOL_FUNC(CTFPlayer_CanBuild,
		"_ZN9CTFPlayer8CanBuildEii");
	SYMBOL_FUNC(CTFPlayer_CanPickupBuilding,
		"_ZN9CTFPlayer17CanPickupBuildingEP11CBaseObject");
	SYMBOL_FUNC(CTFPlayer_CreateRagdollEntity,
		"_ZN9CTFPlayer19CreateRagdollEntityEbbbbbbbbib");
	SYMBOL_FUNC(CTFPlayer_DeathSound,
		"_ZN9CTFPlayer10DeathSoundERK15CTakeDamageInfo");
	SYMBOL_FUNC(CTFPlayer_Event_Killed,
		"_ZN9CTFPlayer12Event_KilledERK15CTakeDamageInfo");
	SYMBOL_FUNC(CTFPlayer_FireBullet,
		"_ZN9CTFPlayer10FireBulletEP13CTFWeaponBaseRK17FireBulletsInfo_tbii");
	SYMBOL_FUNC(CTFPlayer_GiveNamedItem,
		"_ZN9CTFPlayer13GiveNamedItemEPKciPK13CEconItemViewb");
	SYMBOL_FUNC(CTFPlayer_IsMiniBoss,
		"_ZNK9CTFPlayer10IsMiniBossEv");
	SYMBOL_FUNC(CTFPlayer_IsPlayerClass,
		"_ZNK9CTFPlayer13IsPlayerClassEi");
	SYMBOL_FUNC(CTFPlayer_OnTakeDamage_Alive,
		"_ZN9CTFPlayer18OnTakeDamage_AliveERK15CTakeDamageInfo");
	SYMBOL_FUNC(CTFPlayer_Regenerate,
		"_ZN9CTFPlayer10RegenerateEb");
	SYMBOL_FUNC(CTFPlayer_RememberUpgrade,
		"_ZN9CTFPlayer15RememberUpgradeEiP13CEconItemViewiib");
	SYMBOL_FUNC(CTFPlayer_RemoveCurrency,
		"_ZN9CTFPlayer14RemoveCurrencyEi");
	SYMBOL_FUNC(CTFPlayer_RemoveDisguise,
		"_ZN9CTFPlayer14RemoveDisguiseEv");
	SYMBOL_FUNC(CTFPlayer_ShouldGib,
		"_ZN9CTFPlayer9ShouldGibERK15CTakeDamageInfo");
	SYMBOL_FUNC(CTFPlayer_TFPlayerThink,
		"_ZN9CTFPlayer13TFPlayerThinkEv");
	SYMBOL_FUNC(CTFPlayer_TraceAttack,
		"_ZN9CTFPlayer11TraceAttackERK15CTakeDamageInfoRK6VectorP10CGameTraceP15CDmgAccumulator");
	
	SYMBOL_FUNC(CTFBot_AddItem,
		"_ZN6CTFBot7AddItemEPKc");
	SYMBOL_FUNC(CTFBot_EquipRequiredWeapon,
		"_ZN6CTFBot19EquipRequiredWeaponEv");
	SYMBOL_FUNC(CTFBot_ShouldGib,
		"_ZN6CTFBot9ShouldGibERK15CTakeDamageInfo");
	
	SYMBOL_FUNC(NextBotPlayer_CTFPlayer_IsBot,
		"_ZNK13NextBotPlayerI9CTFPlayerE5IsBotEv");
	
	SYMBOL_FUNC(CTFTankBoss_TankBossThink,
		"_ZN11CTFTankBoss13TankBossThinkEv");
	
	SYMBOL_FUNC(CEconItemSchema_GetAttributeDefinitionByName,
		"_ZN15CEconItemSchema28GetAttributeDefinitionByNameEPKc");
	
	SYMBOL_FUNC(CEconItemView_GetItemDefIndex,
		"_ZNK13CEconItemView15GetItemDefIndexEv");
	
	SYMBOL_FUNC(CSchemaFieldHandle_CEconItemDefinition_ctor,
		"_ZN18CSchemaFieldHandleI19CEconItemDefinitionEC1EPKc");
	
	SYMBOL_FUNC(CItemGeneration_GenerateRandomItem,
		"_ZN15CItemGeneration18GenerateRandomItemEP22CItemSelectionCriteriaRK6VectorRK6QAngle");
	SYMBOL_FUNC(CItemGeneration_SpawnItem,
		"_ZN15CItemGeneration9SpawnItemEiRK6VectorRK6QAngleiiPKc");
	
	SYMBOL_FUNC(CTFWeaponBase_AreRandomCritsEnabled,
		"_ZN13CTFWeaponBase21AreRandomCritsEnabledEv");
	SYMBOL_FUNC(CTFWeaponBase_CalcIsAttackCritical,
		"_ZN13CTFWeaponBase20CalcIsAttackCriticalEv");
	SYMBOL_FUNC(CTFWeaponBase_CalcIsAttackCriticalHelper,
		"_ZN13CTFWeaponBase26CalcIsAttackCriticalHelperEv");
	SYMBOL_FUNC(CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits,
		"_ZN13CTFWeaponBase33CalcIsAttackCriticalHelperNoCritsEv");
	SYMBOL_FUNC(CTFWeaponBase_CanBeCritBoosted,
		"_ZN13CTFWeaponBase16CanBeCritBoostedEv");
	SYMBOL_FUNC(CTFWeaponBase_CanFireCriticalShot,
		"_ZN13CTFWeaponBase19CanFireCriticalShotEb");
	SYMBOL_FUNC(CTFWeaponBase_CanFireRandomCriticalShot,
		"_ZN13CTFWeaponBase25CanFireRandomCriticalShotEf");
	SYMBOL_FUNC(CTFWeaponBase_GetWeaponID,
		"_ZNK13CTFWeaponBase11GetWeaponIDEv");
	
	SYMBOL_FUNC(CTFWeaponBaseGun_GetWeaponProjectileType,
		"_ZNK16CTFWeaponBaseGun23GetWeaponProjectileTypeEv");
	SYMBOL_FUNC(CTFWeaponBaseGun_PrimaryAttack,
		"_ZN16CTFWeaponBaseGun13PrimaryAttackEv");
	
	SYMBOL_FUNC(CTFRocketLauncher_Precache,
		"_ZN17CTFRocketLauncher8PrecacheEv");
	
	SYMBOL_FUNC(CTFSniperRifle_CanFireCriticalShot,
		"_ZN14CTFSniperRifle19CanFireCriticalShotEb");
	SYMBOL_FUNC(CTFSniperRifle_ExplosiveHeadShot,
		"_ZN14CTFSniperRifle17ExplosiveHeadShotEP9CTFPlayerS1_");
	SYMBOL_FUNC(CTFSniperRifle_ItemPostFrame,
		"_ZN14CTFSniperRifle13ItemPostFrameEv");
	SYMBOL_FUNC(CTFSniperRifleClassic_ItemPostFrame,
		"_ZN21CTFSniperRifleClassic13ItemPostFrameEv");
	SYMBOL_FUNC(CTFSniperRifleDecap_SniperRifleChargeRateMod,
		"_ZN19CTFSniperRifleDecap24SniperRifleChargeRateModEv");
	
	SYMBOL_FUNC(CTFKnife_DisguiseOnKill,
		"_ZN8CTFKnife14DisguiseOnKillEv");
	SYMBOL_FUNC(CTFKnife_PrimaryAttack,
		"_ZN8CTFKnife13PrimaryAttackEv");
	
	SYMBOL_FUNC(CTFProjectile_Arrow_StrikeTarget_clone321,
		"_ZN19CTFProjectile_Arrow12StrikeTargetEP13mstudiobbox_tP11CBaseEntity.part.321");
	SYMBOL_FUNC(CTFProjectile_Flare_Explode,
		"_ZN19CTFProjectile_Flare7ExplodeEP10CGameTraceP11CBaseEntity");
	
	SYMBOL_FUNC(CBaseObject_DoQuickBuild,
		"_ZN11CBaseObject12DoQuickBuildEb");
	SYMBOL_FUNC(CBaseObject_GetMaxHealthForCurrentLevel,
		"_ZN11CBaseObject27GetMaxHealthForCurrentLevelEv");
	SYMBOL_FUNC(CBaseObject_GetReversesBuildingConstructionSpeed,
		"_ZN11CBaseObject36GetReversesBuildingConstructionSpeedEv");
	SYMBOL_FUNC(CBaseObject_GetSapper,
		"_ZN11CBaseObject9GetSapperEv");
	SYMBOL_FUNC(CBaseObject_GetType,
		"_ZNK11CBaseObject7GetTypeEv");
	SYMBOL_FUNC(CBaseObject_MakeDisposableBuilding,
		"_ZN11CBaseObject22MakeDisposableBuildingEP9CTFPlayer");
	SYMBOL_FUNC(CBaseObject_SetHealth,
		"_ZN11CBaseObject9SetHealthEf");
	SYMBOL_FUNC(CBaseObject_ShouldBeMiniBuilding,
		"_ZN11CBaseObject20ShouldBeMiniBuildingEP9CTFPlayer");
	
	SYMBOL_FUNC(CObjectDispenser_MakeMiniBuilding,
		"_ZN16CObjectDispenser16MakeMiniBuildingEP9CTFPlayer");
	SYMBOL_FUNC(CObjectDispenser_ShouldBeMiniBuilding,
		"_ZN16CObjectDispenser20ShouldBeMiniBuildingEP9CTFPlayer");
	SYMBOL_FUNC(CObjectDispenser_StartPlacement,
		"_ZN16CObjectDispenser14StartPlacementEP9CTFPlayer");
	
	SYMBOL_FUNC(CObjectSentrygun_GetBaseTurnRate,
		"_ZN16CObjectSentrygun15GetBaseTurnRateEv");
	SYMBOL_FUNC(CObjectSentrygun_GetMaxHealthForCurrentLevel,
		"_ZN16CObjectSentrygun27GetMaxHealthForCurrentLevelEv");
	SYMBOL_FUNC(CObjectSentrygun_MakeDisposableBuilding,
		"_ZN16CObjectSentrygun22MakeDisposableBuildingEP9CTFPlayer");
	SYMBOL_FUNC(CObjectSentrygun_MoveTurret,
		"_ZN16CObjectSentrygun10MoveTurretEv");
	SYMBOL_FUNC(CObjectSentrygun_SentryRotate,
		"_ZN16CObjectSentrygun12SentryRotateEv");
	SYMBOL_FUNC(CObjectSentrygun_SentryThink,
		"_ZN16CObjectSentrygun11SentryThinkEv");
	SYMBOL_FUNC(CObjectSentrygun_Spawn,
		"_ZN16CObjectSentrygun5SpawnEv");
	
	SYMBOL_FUNC(CObjectTeleporter_FinishedBuilding,
		"_ZN17CObjectTeleporter16FinishedBuildingEv");
	
	SYMBOL_FUNC(CTFGameRules_BetweenRounds_Think,
		"_ZN12CTFGameRules19BetweenRounds_ThinkEv");
	SYMBOL_FUNC(CTFGameRules_CanUpgradeWithAttrib,
		"_ZN12CTFGameRules20CanUpgradeWithAttribEP9CTFPlayeritP22CMannVsMachineUpgrades");
	SYMBOL_FUNC(CTFGameRules_DistributeCurrencyAmount,
		"_ZN12CTFGameRules24DistributeCurrencyAmountEiP9CTFPlayerbbb");
	SYMBOL_FUNC(CTFGameRules_GameModeUsesUpgrades,
		"_ZN12CTFGameRules20GameModeUsesUpgradesEv");
	SYMBOL_FUNC(CTFGameRules_GetCostForUpgrade,
		"_ZN12CTFGameRules17GetCostForUpgradeEP22CMannVsMachineUpgradesiiP9CTFPlayer");
	SYMBOL_FUNC(CTFGameRules_GetUpgradeTier,
		"_ZN12CTFGameRules14GetUpgradeTierEi");
	SYMBOL_FUNC(CTFGameRules_IsPVEModeActive,
		"_ZNK12CTFGameRules15IsPVEModeActiveEv");
	SYMBOL_FUNC(CTFGameRules_IsPVEModeControlled,
		"_ZNK12CTFGameRules19IsPVEModeControlledEP11CBaseEntity");
	SYMBOL_FUNC(CTFGameRules_IsUpgradeTierEnabled,
		"_ZN12CTFGameRules20IsUpgradeTierEnabledEP9CTFPlayerii");
	SYMBOL_FUNC(CTFGameRules_PlayerReadyStatus_HaveMinPlayersToEnable,
		"_ZN12CTFGameRules40PlayerReadyStatus_HaveMinPlayersToEnableEv");
	SYMBOL_FUNC(CTFGameRules_PlayerReadyStatus_ShouldStartCountdown,
		"_ZN12CTFGameRules38PlayerReadyStatus_ShouldStartCountdownEv");
	SYMBOL_FUNC(CTFGameRules_PushAllPlayersAway,
		"_ZN12CTFGameRules18PushAllPlayersAwayERK6VectorffiP10CUtlVectorIP9CTFPlayer10CUtlMemoryIS5_iEE");
	SYMBOL_FUNC(CTFGameRules_UsePlayerReadyStatusMode,
		"_ZN12CTFGameRules24UsePlayerReadyStatusModeEv");
	
	SYMBOL_FUNC(CTeamplayRoundBasedRules_AreLobbyPlayersOnTeamReady,
		"_ZN24CTeamplayRoundBasedRules26AreLobbyPlayersOnTeamReadyEi");
	SYMBOL_FUNC(CTeamplayRoundBasedRules_CheckReadyRestart,
		"_ZN24CTeamplayRoundBasedRules17CheckReadyRestartEv");
	
	SYMBOL_FUNC(CTFGameStats_IncrementStat,
		"_ZN12CTFGameStats13IncrementStatEP9CTFPlayer12TFStatType_ti");
	SYMBOL_FUNC(CTFGameStats_ResetPlayerStats,
		"_ZN12CTFGameStats16ResetPlayerStatsEP9CTFPlayer");
	
	SYMBOL_FUNC(CMannVsMachineStats_ResetPlayerEvents,
		"_ZN19CMannVsMachineStats17ResetPlayerEventsEP9CTFPlayer");
	SYMBOL_FUNC(CMannVsMachineStats_ResetStats,
		"_ZN19CMannVsMachineStats10ResetStatsEv");
	
	SYMBOL_FUNC(CTFObjectiveResource_AddMannVsMachineWaveClassFlags,
		"_ZN20CTFObjectiveResource30AddMannVsMachineWaveClassFlagsEij");
	SYMBOL_FUNC(CTFObjectiveResource_ClearMannVsMachineWaveClassFlags,
		"_ZN20CTFObjectiveResource32ClearMannVsMachineWaveClassFlagsEv");
	SYMBOL_FUNC(CTFObjectiveResource_DecrementMannVsMachineWaveClassCount,
		"_ZN20CTFObjectiveResource36DecrementMannVsMachineWaveClassCountE8string_tj");
	SYMBOL_FUNC(CTFObjectiveResource_DecrementTeleporterCount,
		"_ZN20CTFObjectiveResource24DecrementTeleporterCountEv");
	SYMBOL_FUNC(CTFObjectiveResource_GetMannVsMachineWaveClassCount,
		"_ZN20CTFObjectiveResource30GetMannVsMachineWaveClassCountEi");
	SYMBOL_FUNC(CTFObjectiveResource_IncrementMannVsMachineWaveClassCount,
		"_ZN20CTFObjectiveResource36IncrementMannVsMachineWaveClassCountE8string_tj");
	SYMBOL_FUNC(CTFObjectiveResource_IncrementTeleporterCount,
		"_ZN20CTFObjectiveResource24IncrementTeleporterCountEv");
	SYMBOL_FUNC(CTFObjectiveResource_SetMannVsMachineWaveClassActive,
		"_ZN20CTFObjectiveResource31SetMannVsMachineWaveClassActiveE8string_tb");
	SYMBOL_FUNC(CTFObjectiveResource_SetMannVsMachineWaveClassCount,
		"_ZN20CTFObjectiveResource30SetMannVsMachineWaveClassCountEii");
	SYMBOL_FUNC(CTFObjectiveResource_SetMannVsMachineWaveClassName,
		"_ZN20CTFObjectiveResource29SetMannVsMachineWaveClassNameEi8string_t");
	
	SYMBOL_FUNC(CUpgrades_ApplyUpgradeAttributeBlock,
		"_ZN9CUpgrades26ApplyUpgradeAttributeBlockEP20UpgradeAttribBlock_tiP9CTFPlayerb");
	SYMBOL_FUNC(CUpgrades_ApplyUpgradeToItem,
		"_ZN9CUpgrades18ApplyUpgradeToItemEP9CTFPlayerP13CEconItemViewiibb");
	SYMBOL_FUNC(CUpgrades_EndTouch,
		"_ZN9CUpgrades8EndTouchEP11CBaseEntity");
	SYMBOL_FUNC(CUpgrades_FireGameEvent,
		"_ZN9CUpgrades13FireGameEventEP10IGameEvent");
	SYMBOL_FUNC(CUpgrades_GetUpgradeAttributeName,
		"_ZNK9CUpgrades23GetUpgradeAttributeNameEi");
	SYMBOL_FUNC(CUpgrades_GrantOrRemoveAllUpgrades,
		"_ZN9CUpgrades24GrantOrRemoveAllUpgradesEP9CTFPlayerbb");
	SYMBOL_FUNC(CUpgrades_InputDisable,
		"_ZN9CUpgrades12InputDisableER11inputdata_t");
	SYMBOL_FUNC(CUpgrades_InputEnable,
		"_ZN9CUpgrades11InputEnableER11inputdata_t");
	SYMBOL_FUNC(CUpgrades_InputReset,
		"_ZN9CUpgrades10InputResetER11inputdata_t");
	SYMBOL_FUNC(CUpgrades_NotifyItemOnUpgrade,
		"_ZN9CUpgrades19NotifyItemOnUpgradeEP9CTFPlayertb");
	SYMBOL_FUNC(CUpgrades_PlayerPurchasingUpgrade,
		"_ZN9CUpgrades23PlayerPurchasingUpgradeEP9CTFPlayeriibbb");
	SYMBOL_FUNC(CUpgrades_ReportUpgrade,
		"_ZN9CUpgrades13ReportUpgradeEP9CTFPlayeriiiibbb");
	SYMBOL_FUNC(CUpgrades_RestoreItemAttributeToBaseValue,
		"_ZN9CUpgrades31RestoreItemAttributeToBaseValueEP28CEconItemAttributeDefinitionP13CEconItemView");
	SYMBOL_FUNC(CUpgrades_RestorePlayerAttributeToBaseValue,
		"_ZN9CUpgrades33RestorePlayerAttributeToBaseValueEP28CEconItemAttributeDefinitionP9CTFPlayer");
	SYMBOL_FUNC(CUpgrades_UpgradeTouch,
		"_ZN9CUpgrades12UpgradeTouchEP11CBaseEntity");
	
	SYMBOL_FUNC(CTFBotMainAction_OnContact,
		"_ZN16CTFBotMainAction9OnContactEP6CTFBotP11CBaseEntityP10CGameTrace");
	SYMBOL_FUNC(CTFBotMainAction_Update,
		"_ZN16CTFBotMainAction6UpdateEP6CTFBotf");
	
	SYMBOL_FUNC(CTFBotMvMEngineerIdle_Update,
		"_ZN21CTFBotMvMEngineerIdle6UpdateEP6CTFBotf");
	
	SYMBOL_FUNC(CTFReviveMarker_AddMarkerHealth,
		"_ZN15CTFReviveMarker15AddMarkerHealthEf");
	
	SYMBOL_FUNC(CCurrencyPack_ComeToRest,
		"_ZN13CCurrencyPack10ComeToRestEv");
	
	SYMBOL_FUNC(Action_CTFBot_OnContact,
		"_ZN6ActionI6CTFBotE9OnContactEP11CBaseEntityP10CGameTrace");
	
	
#warning TODO: symbols for these upgrade related functions
	// CTFPlayer::*
	// CMannVsMachineStats::*
	// CPopulationManager::*
	// CEconEntity::*
	// CTFPowerupBottle::*
	// CTFWeaponBase::*
	// CTFWearable::*
	// CTFGameRules::*
}
