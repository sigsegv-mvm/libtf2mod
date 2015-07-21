#ifndef _LIBTF2MOD_SYMBOLS_H
#define _LIBTF2MOD_SYMBOLS_H


#ifdef _LIBTF2MOD_SYMBOLS_C
#define extern
#endif


void symbols_init(void);


/* defined types */

typedef struct {
	// TODO
} Vector;

typedef struct {
	// TODO
} CTakeDamageInfo;

typedef uint32_t unknown_t;


/* opaque types */

typedef void CBaseEntity;
typedef void CBaseAnimating;

typedef void CTFPlayerShared;
typedef void CTFPlayer;
typedef void CTFBot;

typedef void CTFTankBoss;

typedef void CTFWeaponBaseGun;
typedef void CTFSniperRifle;
typedef void CTFSniperRifleDecap;
typedef void CTFSniperRifleClassic;

typedef void CTFProjectile_Arrow;

typedef void CBaseObject;
typedef void CObjectDispenser;
typedef void CObjectSentrygun;

typedef void CTFGameRules;
typedef void CMannVsMachineUpgrades;

typedef void CTFBotMainAction;

typedef void CUtlVector;

typedef void mstudiobbox_t;

typedef unknown_t ETFCond;
typedef unknown_t ShakeCommand_t;


/* globals */

extern void **gpGlobals;

extern CTFGameRules **g_pGameRules;


/* functions: global */

extern bool (*WeaponID_IsSniperRifle)(int);
extern bool (*WeaponID_IsSniperRifleOrBow)(int);

extern unknown_t (*UTIL_ScreenShake)(Vector const*, float, float, float, float, ShakeCommand_t, bool);


/* functions: static */

extern int (*CAttributeManager_AttribHookValue_int)(int, char const*, CBaseEntity const*, CUtlVector*, bool);


/* functions: member */

extern unknown_t (*CBaseEntity_ApplyAbsVelocityImpulse)(CBaseEntity* this, Vector const*);

extern unknown_t (*CBaseAnimating_SetModelScale)(CBaseAnimating* this, float, float);

extern unknown_t (*CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
extern unknown_t (*CTFPlayerShared_RadiusCurrencyCollectionCheck)(CTFPlayerShared* this);

extern bool (*CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);
extern unknown_t (*CTFPlayer_CanBuild)(CTFPlayer* this, int, int);
extern unknown_t (*CTFPlayer_DeathSound)(CTFPlayer* this, CTakeDamageInfo const*);
extern unknown_t (*CTFPlayer_Event_Killed)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_IsMiniBoss)(CTFPlayer* this);
extern bool (*CTFPlayer_IsPlayerClass)(CTFPlayer* this, int);
extern unknown_t (*CTFPlayer_OnTakeDamage_Alive)(CTFPlayer* this, CTakeDamageInfo const*);
extern unknown_t (*CTFPlayer_ShouldGib)(CTFPlayer* this, CTakeDamageInfo const*);

extern unknown_t (*CTFBot_ShouldGib)(CTFBot* this, CTakeDamageInfo const*);

extern unknown_t (*CTFTankBoss_TankBossThink)(CTFTankBoss* this);

extern unknown_t (*CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);

extern unknown_t (*CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);
extern unknown_t (*CTFSniperRifle_ItemPostFrame)(CTFSniperRifle* this);
extern unknown_t (*CTFSniperRifleClassic_ItemPostFrame)(CTFSniperRifleClassic* this);
extern unknown_t (*CTFSniperRifleDecap_SniperRifleChargeRateMod)(CTFSniperRifleDecap* this);

extern unknown_t (*CTFProjectile_Arrow_StrikeTarget_clone323)(CTFProjectile_Arrow* this, mstudiobbox_t*, CBaseEntity*);

extern unknown_t (*CBaseObject_DoQuickBuild)(CBaseObject* this);
extern unknown_t (*CBaseObject_GetMaxHealthForCurrentLevel)(CBaseObject* this);
extern unknown_t (*CBaseObject_GetType)(CBaseObject* this);
extern unknown_t (*CBaseObject_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);
extern unknown_t (*CBaseObject_SetHealth)(CBaseObject* this, float);
extern unknown_t (*CBaseObject_ShouldBeMiniBuilding)(CBaseObject* this, CTFPlayer*);

extern unknown_t (*CObjectDispenser_MakeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern unknown_t (*CObjectDispenser_ShouldBeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern unknown_t (*CObjectDispenser_StartPlacement)(CObjectDispenser* this, CTFPlayer*);

extern unknown_t (*CObjectSentrygun_GetMaxHealthForCurrentLevel)(CObjectSentrygun* this);
extern unknown_t (*CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);
extern unknown_t (*CObjectSentrygun_SentryThink)(CObjectSentrygun* this);

extern unknown_t (*CTFGameRules_CanUpgradeWithAttrib)(CTFGameRules* this, CTFPlayer*, int, unsigned short, CMannVsMachineUpgrades*);
extern unknown_t (*CTFGameRules_GameModeUsesUpgrades)(CTFGameRules* this);
extern unknown_t (*CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);

extern unknown_t (*CTFBotMainAction_Update)(CTFBotMainAction* this, CTFBot*, float);


#undef extern


#endif
