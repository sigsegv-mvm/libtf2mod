#ifndef _LIBTF2MOD_SYMBOLS_H
#define _LIBTF2MOD_SYMBOLS_H


#ifdef _LIBTF2MOD_SYMBOLS_C
#define extern
#endif


void symbols_init(void);


/* RTTI */

extern void *typeinfo_for_CBaseEntity;
extern void *typeinfo_for_CBaseObject;
extern void *typeinfo_for_CTFWeaponBase;


/* globals */

extern CGlobalVars **gpGlobals;

extern CTFGameRules **g_pGameRules;

extern CTFGameStats *CTF_GameStats;

extern CTFObjectiveResource **g_pObjectiveResource;


/* functions: global */

extern ServerClass* (*SV_FindServerClass)(char const*);

extern int (*ENTINDEX)(CBaseEntity*);

extern unknown_t (*UserMessageBegin)(IRecipientFilter*, char const*);
extern unknown_t (*MessageEnd)(void);
extern unknown_t (*MessageWriteAngle)(float);
extern unknown_t (*MessageWriteAngles)(QAngle const*);
extern unknown_t (*MessageWriteBits)(void const*, int);
extern unknown_t (*MessageWriteBool)(bool);
extern unknown_t (*MessageWriteByte)(int);
extern unknown_t (*MessageWriteChar)(int);
extern unknown_t (*MessageWriteCoord)(float);
extern unknown_t (*MessageWriteEHandle)(CBaseEntity*);
extern unknown_t (*MessageWriteEntity)(int);
extern unknown_t (*MessageWriteFloat)(float);
extern unknown_t (*MessageWriteLong)(int);
extern unknown_t (*MessageWriteSBitLong)(int, int);
extern unknown_t (*MessageWriteShort)(int);
extern unknown_t (*MessageWriteString)(char const*);
extern unknown_t (*MessageWriteUBitLong)(unsigned int, int);
extern unknown_t (*MessageWriteVec3Coord)(Vector const*);
extern unknown_t (*MessageWriteVec3Normal)(Vector const*);
extern unknown_t (*MessageWriteWord)(int);


extern CBaseEntity* (*UTIL_EntityByIndex)(int);
extern unknown_t (*UTIL_LogPrintf)(char const*, ...);
extern CBasePlayer* (*UTIL_PlayerByIndex)(int);
extern void (*UTIL_ScreenShake)(Vector const*, float, float, float, float, ShakeCommand_t, bool);

extern bool (*WeaponID_IsSniperRifle)(int);
extern bool (*WeaponID_IsSniperRifleOrBow)(int);


/* functions: static */

extern void (*CBaseEntity_PrecacheScriptSound)(char const*);

extern datamap_t* (*CBaseObject_GetDataDescMap)(void);
extern datamap_t* (*CObjectSentrygun_GetDataDescMap)(void);

extern int (*CAttributeManager_AttribHookValue_int)(int, char const*, CBaseEntity const*, CUtlVector*, bool);


/* functions: member */

extern unknown_t (*CServerGameDLL_DLLInit)(CServerGameDLL* this, void* (*)(char const*, int*), void* (*)(char const*, int*), void* (*)(char const*, int*), CGlobalVars*);

extern void (*ConCommand_ctor)(ConCommand* this, char const*, void (*)(CCommand const*), char const*, int, int (*)(char const*, char (*) [64]));

extern void (*CBaseEntity_ApplyAbsVelocityImpulse)(CBaseEntity* this, Vector const*);
extern int (*CBaseEntity_GetMaxHealth)(CBaseEntity* this);
extern int (*CBaseEntity_GetTeamNumber)(CBaseEntity* this);
extern bool (*CBaseEntity_IsBaseObject)(CBaseEntity* this);
extern unknown_t (*CBaseEntity_NetworkStateChanged)(CBaseEntity* this, void*);

extern void (*CBaseAnimating_SetModelScale)(CBaseAnimating* this, float, float);

extern bool (*CBasePlayer_IsBot)(CBasePlayer* this);

extern void (*CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
extern bool (*CTFPlayerShared_IsInvulnerable)(CTFPlayerShared* this);
extern void (*CTFPlayerShared_RadiusCurrencyCollectionCheck)(CTFPlayerShared* this);

extern unknown_t (*CTFPlayer_ApplyAbsVelocityImpulse)(CTFPlayer* this, Vector const*);
extern unknown_t (*CTFPlayer_ApplyAirBlastImpulse)(CTFPlayer* this, Vector const*);
extern bool (*CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);
extern int (*CTFPlayer_CanBuild)(CTFPlayer* this, int, int);
extern bool (*CTFPlayer_CanPickupBuilding)(CTFPlayer* this, CBaseObject*);
extern void (*CTFPlayer_CreateRagdollEntity)(CTFPlayer* this, bool, bool, bool, bool, bool, bool, bool, bool, int, bool);
extern void (*CTFPlayer_DeathSound)(CTFPlayer* this, CTakeDamageInfo const*);
extern void (*CTFPlayer_Event_Killed)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_IsMiniBoss)(CTFPlayer* this);
extern bool (*CTFPlayer_IsPlayerClass)(CTFPlayer* this, int);
extern unknown_t (*CTFPlayer_OnTakeDamage_Alive)(CTFPlayer* this, CTakeDamageInfo const*);
extern void (*CTFPlayer_RemoveDisguise)(CTFPlayer* this);
extern bool (*CTFPlayer_ShouldGib)(CTFPlayer* this, CTakeDamageInfo const*);
extern unknown_t (*CTFPlayer_TFPlayerThink)(CTFPlayer* this);

extern bool (*CTFBot_ShouldGib)(CTFBot* this, CTakeDamageInfo const*);

extern bool (*NextBotPlayer_CTFPlayer_IsBot)(NextBotPlayer_CTFPlayer* this);

extern void (*CTFTankBoss_TankBossThink)(CTFTankBoss* this);

extern bool (*CTFWeaponBase_AreRandomCritsEnabled)(CTFWeaponBase* this);
extern bool (*CTFWeaponBase_CalcIsAttackCritical)(CTFWeaponBase* this);
extern bool (*CTFWeaponBase_CalcIsAttackCriticalHelper)(CTFWeaponBase* this);
extern bool (*CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits)(CTFWeaponBase* this);
extern bool (*CTFWeaponBase_CanBeCritBoosted)(CTFWeaponBase* this);
extern bool (*CTFWeaponBase_CanFireCriticalShot)(CTFWeaponBase* this, bool);
extern bool (*CTFWeaponBase_CanFireRandomCriticalShot)(CTFWeaponBase* this, float);
extern int (*CTFWeaponBase_GetWeaponID)(CTFWeaponBase* this);

extern int (*CTFWeaponBaseGun_GetWeaponProjectileType)(CTFWeaponBaseGun* this);
extern void (*CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);

extern void (*CTFRocketLauncher_Precache)(CTFRocketLauncher* this);

extern bool (*CTFSniperRifle_CanFireCriticalShot)(CTFSniperRifle*, bool);
extern void (*CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);
extern void (*CTFSniperRifle_ItemPostFrame)(CTFSniperRifle* this);
extern void (*CTFSniperRifleClassic_ItemPostFrame)(CTFSniperRifleClassic* this);
extern float (*CTFSniperRifleDecap_SniperRifleChargeRateMod)(CTFSniperRifleDecap* this);

extern void (*CTFKnife_DisguiseOnKill)(CTFKnife* this);
extern void (*CTFKnife_PrimaryAttack)(CTFKnife* this);

extern unknown_t (*CTFProjectile_Arrow_StrikeTarget_clone323)(CTFProjectile_Arrow* this, mstudiobbox_t*, CBaseEntity*);
extern unknown_t (*CTFProjectile_Flare_Explode)(CTFProjectile_Flare* this, CGameTrace*, CBaseEntity*);

extern void (*CBaseObject_DoQuickBuild)(CBaseObject* this);
extern int (*CBaseObject_GetMaxHealthForCurrentLevel)(CBaseObject* this);
extern float (*CBaseObject_GetReversesBuildingConstructionSpeed)(CBaseObject* this);
extern CObjectSapper* (*CBaseObject_GetSapper)(CBaseObject* this);
extern int (*CBaseObject_GetType)(CBaseObject* this);
extern void (*CBaseObject_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);
extern void (*CBaseObject_SetHealth)(CBaseObject* this, float);
extern bool (*CBaseObject_ShouldBeMiniBuilding)(CBaseObject* this, CTFPlayer*);

extern void (*CObjectDispenser_MakeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern bool (*CObjectDispenser_ShouldBeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern void (*CObjectDispenser_StartPlacement)(CObjectDispenser* this, CTFPlayer*);

extern int (*CObjectSentrygun_GetBaseTurnRate)(CObjectSentrygun* this);
extern int (*CObjectSentrygun_GetMaxHealthForCurrentLevel)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_MakeDisposableBuilding)(CObjectSentrygun* this, CTFPlayer*);
extern bool (*CObjectSentrygun_MoveTurret)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_SentryThink)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_Spawn)(CObjectSentrygun* this);

extern void (*CObjectTeleporter_FinishedBuilding)(CObjectTeleporter* this);

extern bool (*CTFGameRules_CanUpgradeWithAttrib)(CTFGameRules* this, CTFPlayer*, int, unsigned short, CMannVsMachineUpgrades*);
extern unknown_t (*CTFGameRules_DistributeCurrencyAmount)(CTFGameRules* this, int, CTFPlayer*, bool, bool, bool);
extern bool (*CTFGameRules_GameModeUsesUpgrades)(CTFGameRules* this);
extern bool (*CTFGameRules_IsPVEModeActive)(CTFGameRules* this);
extern bool (*CTFGameRules_IsPVEModeControlled)(CTFGameRules* this, CBaseEntity*);
extern void (*CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);

extern unknown_t (*CTFGameStats_IncrementStat)(CTFGameStats* this, CTFPlayer*, TFStatType_t, int);
extern unknown_t (*CTFGameStats_ResetPlayerStats)(CTFGameStats* this, CTFPlayer*);

extern unknown_t (*CMannVsMachineStats_ResetPlayerEvents)(CMannVsMachineStats* this, CTFPlayer*);
extern unknown_t (*CMannVsMachineStats_ResetStats)(CMannVsMachineStats* this);

extern unknown_t (*CTFObjectiveResource_AddMannVsMachineWaveClassFlags)(CTFObjectiveResource* this, int, unsigned int);
extern unknown_t (*CTFObjectiveResource_ClearMannVsMachineWaveClassFlags)(CTFObjectiveResource* this);
extern unknown_t (*CTFObjectiveResource_DecrementMannVsMachineWaveClassCount)(CTFObjectiveResource* this, string_t, unsigned int);
extern unknown_t (*CTFObjectiveResource_DecrementTeleporterCount)(CTFObjectiveResource* this);
extern int (*CTFObjectiveResource_GetMannVsMachineWaveClassCount)(CTFObjectiveResource* this, int);
extern unknown_t (*CTFObjectiveResource_IncrementMannVsMachineWaveClassCount)(CTFObjectiveResource* this, string_t, unsigned int);
extern unknown_t (*CTFObjectiveResource_IncrementTeleporterCount)(CTFObjectiveResource* this);
extern unknown_t (*CTFObjectiveResource_SetMannVsMachineWaveClassActive)(CTFObjectiveResource* this, string_t, bool);
extern unknown_t (*CTFObjectiveResource_SetMannVsMachineWaveClassCount)(CTFObjectiveResource* this, int, int);
extern unknown_t (*CTFObjectiveResource_SetMannVsMachineWaveClassName)(CTFObjectiveResource* this, int, string_t);

extern unknown_t (*CTFBotMainAction_OnContact)(CTFBotMainAction* this, CTFBot*, CBaseEntity*, CGameTrace*);
extern unknown_t (*CTFBotMainAction_Update)(CTFBotMainAction* this, CTFBot*, float);

extern unknown_t (*CTFBotMvMEngineerIdle_Update)(CTFBotMvMEngineerIdle* this, CTFBot*, float);

extern unknown_t (*CTFReviveMarker_AddMarkerHealth)(CTFReviveMarker* this, float);

extern unknown_t (*CCurrencyPack_ComeToRest)(CCurrencyPack* this);

extern unknown_t (*Action_CTFBot_OnContact)(Action_CTFBot* this, CBaseEntity*, CGameTrace*);


#undef extern


#endif
