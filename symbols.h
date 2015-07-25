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
typedef void CTFRocketLauncher;
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

typedef void CGameTrace;

typedef void mstudiobbox_t;

typedef unknown_t ETFCond;
typedef unknown_t ShakeCommand_t;


/* globals */

extern void **gpGlobals;

extern CTFGameRules **g_pGameRules;


/* functions: global */

extern int (*ENTINDEX)(CBaseEntity*);

extern void (*UTIL_ScreenShake)(Vector const*, float, float, float, float, ShakeCommand_t, bool);

extern bool (*WeaponID_IsSniperRifle)(int);
extern bool (*WeaponID_IsSniperRifleOrBow)(int);


/* functions: static */

extern void (*CBaseEntity_PrecacheScriptSound)(char const*);

extern int (*CAttributeManager_AttribHookValue_int)(int, char const*, CBaseEntity const*, CUtlVector*, bool);


/* functions: member */

extern void (*CBaseEntity_ApplyAbsVelocityImpulse)(CBaseEntity* this, Vector const*);

extern void (*CBaseAnimating_SetModelScale)(CBaseAnimating* this, float, float);

extern void (*CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
extern void (*CTFPlayerShared_RadiusCurrencyCollectionCheck)(CTFPlayerShared* this);

extern bool (*CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);
extern int (*CTFPlayer_CanBuild)(CTFPlayer* this, int, int);
extern void (*CTFPlayer_DeathSound)(CTFPlayer* this, CTakeDamageInfo const*);
extern void (*CTFPlayer_Event_Killed)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_IsMiniBoss)(CTFPlayer* this);
extern bool (*CTFPlayer_IsPlayerClass)(CTFPlayer* this, int);
extern unknown_t (*CTFPlayer_OnTakeDamage_Alive)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_ShouldGib)(CTFPlayer* this, CTakeDamageInfo const*);

extern bool (*CTFBot_ShouldGib)(CTFBot* this, CTakeDamageInfo const*);

extern void (*CTFTankBoss_TankBossThink)(CTFTankBoss* this);

extern void (*CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);

extern void (*CTFRocketLauncher_Precache)(CTFRocketLauncher* this);

extern void (*CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);
extern void (*CTFSniperRifle_ItemPostFrame)(CTFSniperRifle* this);
extern void (*CTFSniperRifleClassic_ItemPostFrame)(CTFSniperRifleClassic* this);
extern float (*CTFSniperRifleDecap_SniperRifleChargeRateMod)(CTFSniperRifleDecap* this);

extern unknown_t (*CTFProjectile_Arrow_StrikeTarget_clone323)(CTFProjectile_Arrow* this, mstudiobbox_t*, CBaseEntity*);

extern void (*CBaseObject_DoQuickBuild)(CBaseObject* this);
extern int (*CBaseObject_GetMaxHealthForCurrentLevel)(CBaseObject* this);
extern int (*CBaseObject_GetType)(CBaseObject* this);
extern void (*CBaseObject_MakeDisposableBuilding)(CBaseObject* this, CTFPlayer*);
extern void (*CBaseObject_SetHealth)(CBaseObject* this, float);
extern bool (*CBaseObject_ShouldBeMiniBuilding)(CBaseObject* this, CTFPlayer*);

extern void (*CObjectDispenser_MakeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern bool (*CObjectDispenser_ShouldBeMiniBuilding)(CObjectDispenser* this, CTFPlayer*);
extern void (*CObjectDispenser_StartPlacement)(CObjectDispenser* this, CTFPlayer*);

extern int (*CObjectSentrygun_GetMaxHealthForCurrentLevel)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_SentryThink)(CObjectSentrygun* this);

extern bool (*CTFGameRules_CanUpgradeWithAttrib)(CTFGameRules* this, CTFPlayer*, int, unsigned short, CMannVsMachineUpgrades*);
extern bool (*CTFGameRules_GameModeUsesUpgrades)(CTFGameRules* this);
extern void (*CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);

extern unknown_t (*CTFBotMainAction_OnContact)(CTFBotMainAction* this, CTFBot*, CBaseEntity*, CGameTrace*);
extern unknown_t (*CTFBotMainAction_Update)(CTFBotMainAction* this, CTFBot*, float);


#undef extern


#endif
