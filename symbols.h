#ifndef _LIBTF2MOD_SYMBOLS_H
#define _LIBTF2MOD_SYMBOLS_H


#ifdef _LIBTF2MOD_SYMBOLS_C
#define extern
#endif


void symbols_init(void);


/* enums */

typedef enum {
	FIELD_VOID = 0,			// No type or value
	FIELD_FLOAT,			// Any floating point value
	FIELD_STRING,			// A string ID (return from ALLOC_STRING)
	FIELD_VECTOR,			// Any vector, QAngle, or AngularImpulse
	FIELD_QUATERNION,		// A quaternion
	FIELD_INTEGER,			// Any integer or enum
	FIELD_BOOLEAN,			// boolean, implemented as an int, I may use this as a hint for compression
	FIELD_SHORT,			// 2 byte integer
	FIELD_CHARACTER,		// a byte
	FIELD_COLOR32,			// 8-bit per channel r,g,b,a (32bit color)
	FIELD_EMBEDDED,			// an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
	FIELD_CUSTOM,			// special type that contains function pointers to it's read/write/parse functions
	
	FIELD_CLASSPTR,			// CBaseEntity *
	FIELD_EHANDLE,			// Entity handle
	FIELD_EDICT,			// edict_t *
	
	FIELD_POSITION_VECTOR,	// A world coordinate (these are fixed up across level transitions automagically)
	FIELD_TIME,				// a floating point time (these are fixed up automatically too!)
	FIELD_TICK,				// an integer tick count( fixed up similarly to time)
	FIELD_MODELNAME,		// Engine string that is a model name (needs precache)
	FIELD_SOUNDNAME,		// Engine string that is a sound name (needs precache)
	
	FIELD_INPUT,			// a list of inputed data fields (all derived from CMultiInputVar)
	FIELD_FUNCTION,			// A class function pointer (Think, Use, etc)
	
	FIELD_VMATRIX,			// a vmatrix (output coords are NOT worldspace)
	
	// NOTE: Use float arrays for local transformations that don't need to be fixed up.
	FIELD_VMATRIX_WORLDSPACE,// A VMatrix that maps some local space to world space (translation is fixed up on level transitions)
	FIELD_MATRIX3X4_WORLDSPACE,	// matrix3x4_t that maps some local space to world space (translation is fixed up on level transitions)
	
	FIELD_INTERVAL,			// a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
	FIELD_MODELINDEX,		// a model index
	FIELD_MATERIALINDEX,	// a material index (using the material precache string table)
	
	FIELD_VECTOR2D,			// 2 floats
	
	FIELD_TYPECOUNT,		// MUST BE LAST
} fieldtype_t;

enum {
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,
	
	// Must be last
	TD_OFFSET_COUNT,
};

typedef enum {
	// ...
	TFCOND_UBERCHARGED       = 5,
	// ...
	TFCOND_UBERCHARGEFADING  = 8,
	// ...
	TFCOND_UBERCHARGEDHIDDEN = 51,
	// ...
} ETFCond;

enum {
	TFTEAM_UNASSIGNED = 0,
	TFTEAM_SPECTATOR  = 1,
	TFTEAM_RED        = 2,
	TFTEAM_BLUE       = 3,
};

enum {
	TFCLASS_UNKNOWN  = 0,
	TFCLASS_SCOUT    = 1,
	TFCLASS_SNIPER   = 2,
	TFCLASS_SOLDIER  = 3,
	TFCLASS_DEMOMAN  = 4,
	TFCLASS_MEDIC    = 5,
	TFCLASS_HEAVY    = 6,
	TFCLASS_PYRO     = 7,
	TFCLASS_SPY      = 8,
	TFCLASS_ENGINEER = 9,
};

enum {
	DMG_GENERIC               = 0,
	DMG_CRUSH                 = (1 << 0),
	DMG_BULLET                = (1 << 1),
	DMG_SLASH                 = (1 << 2),
	DMG_BURN                  = (1 << 3),
	DMG_VEHICLE               = (1 << 4),
	DMG_FALL                  = (1 << 5),
	DMG_BLAST                 = (1 << 6),
	DMG_CLUB                  = (1 << 7),
	DMG_SHOCK                 = (1 << 8),
	DMG_SONIC                 = (1 << 9),
	DMG_ENERGYBEAM            = (1 << 10),
	DMG_PREVENT_PHYSICS_FORCE = (1 << 11),
	DMG_NEVERGIB              = (1 << 12),
	DMG_ALWAYSGIB             = (1 << 13),
	DMG_DROWN                 = (1 << 14),
	DMG_PARALYZE              = (1 << 15),
	DMG_NERVEGAS              = (1 << 16),
	DMG_POISON                = (1 << 17),
	DMG_RADIATION             = (1 << 18),
	DMG_DROWNRECOVER          = (1 << 19),
	DMG_ACID                  = (1 << 20),
	DMG_SLOWBURN              = (1 << 21),
	DMG_REMOVENORAGDOLL       = (1 << 22),
	DMG_PHYSGUN               = (1 << 23),
	DMG_PLASMA                = (1 << 24),
	DMG_AIRBLAST              = (1 << 25),
	DMG_DISSOLVE              = (1 << 26),
	DMG_BLAST_SURFACE         = (1 << 27),
	DMG_DIRECT                = (1 << 28),
	DMG_BUCKSHOT              = (1 << 29),
	
	DMG_CRIT = DMG_ACID,
};

enum {
	TF_CUSTOM_HEADSHOT = 1,
	TF_CUSTOM_BACKSTAB,
	TF_CUSTOM_BURNING,
	TF_CUSTOM_WRENCH_FIX,
	TF_CUSTOM_MINIGUN,
	TF_CUSTOM_SUICIDE,
	TF_CUSTOM_TAUNT_HADOUKEN,
	TF_CUSTOM_BURNING_FLARE,
	TF_CUSTOM_TAUNT_HIGH_NOON,
	TF_CUSTOM_TAUNT_GRAND_SLAM,
	TF_CUSTOM_PENETRATE_MY_TEAM,
	TF_CUSTOM_PENETRATE_ALL_PLAYERS,
	TF_CUSTOM_TAUNT_FENCING,
	TF_CUSTOM_PENETRATE_HEADSHOT,
	TF_CUSTOM_TAUNT_ARROW_STAB,
	TF_CUSTOM_TELEFRAG,
	TF_CUSTOM_BURNING_ARROW,
	TF_CUSTOM_FLYINGBURN,
	TF_CUSTOM_PUMPKIN_BOMB,
	TF_CUSTOM_DECAPITATION,
	TF_CUSTOM_TAUNT_GRENADE,
	TF_CUSTOM_BASEBALL,
	TF_CUSTOM_CHARGE_IMPACT,
	TF_CUSTOM_TAUNT_BARBARIAN_SWING,
	TF_CUSTOM_AIR_STICKY_BURST,
	TF_CUSTOM_DEFENSIVE_STICKY,
	TF_CUSTOM_PICKAXE,
	TF_CUSTOM_ROCKET_DIRECTHIT,
	TF_CUSTOM_TAUNT_UBERSLICE,
	TF_CUSTOM_PLAYER_SENTRY,
	TF_CUSTOM_STANDARD_STICKY,
	TF_CUSTOM_SHOTGUN_REVENGE_CRIT,
	TF_CUSTOM_TAUNT_ENGINEER_SMASH,
	TF_CUSTOM_BLEEDING,
	TF_CUSTOM_GOLD_WRENCH,
	TF_CUSTOM_CARRIED_BUILDING,
	TF_CUSTOM_COMBO_PUNCH,
	TF_CUSTOM_TAUNT_ENGINEER_ARM,
	TF_CUSTOM_FISH_KILL,
	TF_CUSTOM_TRIGGER_HURT,
	TF_CUSTOM_DECAPITATION_BOSS,
	TF_CUSTOM_STICKBOMB_EXPLOSION,
	TF_CUSTOM_AEGIS_ROUND,
	TF_CUSTOM_FLARE_EXPLOSION,
	TF_CUSTOM_BOOTS_STOMP,
	TF_CUSTOM_PLASMA,
	TF_CUSTOM_PLASMA_CHARGED,
	TF_CUSTOM_PLASMA_GIB,
	TF_CUSTOM_PRACTICE_STICKY,
	TF_CUSTOM_EYEBALL_ROCKET,
	TF_CUSTOM_HEADSHOT_DECAPITATION,
	TF_CUSTOM_TAUNT_ARMAGEDDON,
	TF_CUSTOM_FLARE_PELLET,
	TF_CUSTOM_CLEAVER,
	TF_CUSTOM_CLEAVER_CRIT,
	TF_CUSTOM_SAPPER_RECORDER_DEATH,
	TF_CUSTOM_MERASMUS_PLAYER_BOMB,
	TF_CUSTOM_MERASMUS_GRENADE,
	TF_CUSTOM_MERASMUS_ZAP,
	TF_CUSTOM_MERASMUS_DECAPITATION,
	TF_CUSTOM_CANNONBALL_PUSH,
	TF_CUSTOM_TAUNT_ALLCLASS_GUITAR_RIFF,
};

enum {
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BAT_WOOD,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_GRENADE_STUNBALL,
	TF_WEAPON_GRENADE_JAR,
	TF_WEAPON_GRENADE_JAR_MILK,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_JAR,
	TF_WEAPON_COMPOUND_BOW,
	TF_WEAPON_BUFF_ITEM,
	TF_WEAPON_PUMPKIN_BOMB,
	TF_WEAPON_SWORD,
	TF_WEAPON_DIRECTHIT,
	TF_WEAPON_LIFELINE,
	TF_WEAPON_LASER_POINTER,
	TF_WEAPON_DISPENSER_GUN,
	TF_WEAPON_SENTRY_REVENGE,
	TF_WEAPON_JAR_MILK,
	TF_WEAPON_HANDGUN_SCOUT_PRIMARY,
	TF_WEAPON_BAT_FISH,
	TF_WEAPON_CROSSBOW,
	TF_WEAPON_STICKBOMB,
	TF_WEAPON_HANDGUN_SCOUT_SEC,
	TF_WEAPON_SODA_POPPER,
	TF_WEAPON_SNIPERRIFLE_DECAP,
	TF_WEAPON_RAYGUN,
	TF_WEAPON_PARTICLE_CANNON,
	TF_WEAPON_MECHANICAL_ARM,
	TF_WEAPON_DRG_POMSON,
	TF_WEAPON_BAT_GIFTWRAP,
	TF_WEAPON_GRENADE_ORNAMENT,
	TF_WEAPON_RAYGUN_REVENGE,
	TF_WEAPON_PEP_BRAWLER_BLASTER,
	TF_WEAPON_CLEAVER,
	TF_WEAPON_GRENADE_CLEAVER,
	TF_WEAPON_STICKY_BALL_LAUNCHER,
	TF_WEAPON_GRENADE_STICKY_BALL,
	TF_WEAPON_SHOTGUN_BUILDING_RESCUE,
	TF_WEAPON_CANNON,
	TF_WEAPON_THROWABLE,
	TF_WEAPON_GRENADE_THROWABLE,
	TF_WEAPON_PDA_SPY_BUILD,
	TF_WEAPON_GRENADE_WATERBALLOON,
	TF_WEAPON_HARVESTER_SAW,
	TF_WEAPON_SPELLBOOK,
	TF_WEAPON_SPELLBOOK_PROJECTILE,
	TF_WEAPON_SNIPERRIFLE_CLASSIC,
	TF_WEAPON_PARACHUTE,
};


/* opaque types */

typedef uint32_t unknown_t;

typedef void CServerGameDLL;

typedef void ConCommand;
typedef void CCommand;

typedef void CBaseEntity;
typedef void CBaseAnimating;

typedef void CBasePlayer;
typedef void CTFPlayerShared;
typedef void CTFPlayer;
typedef void CTFBot;

typedef void CTFTankBoss;

typedef void CTFWeaponBase;
typedef void CTFWeaponBaseGun;
typedef void CTFRocketLauncher;
typedef void CTFSniperRifle;
typedef void CTFSniperRifleDecap;
typedef void CTFSniperRifleClassic;

typedef void CTFProjectile_Arrow;

typedef void CBaseObject;
typedef void CObjectDispenser;
typedef void CObjectSentrygun;
typedef void CObjectTeleporter;
typedef void CObjectSapper;

typedef void CTFGameRules;

typedef void CTFGameStats;

typedef void CMannVsMachineStats;

typedef void CMannVsMachineUpgrades;

typedef void CTFObjectiveResource;

typedef void CTFBotMainAction;
typedef void CTFBotMvMEngineerIdle;

typedef void CTFReviveMarker;

typedef void CCurrencyPack;

typedef void CUtlVector;

typedef void CGameTrace;

typedef void Action_CTFBot;

typedef void IRecipientFilter;

typedef void mstudiobbox_t;

typedef unknown_t ShakeCommand_t;

typedef char const* string_t;

typedef uint32_t EHANDLE;


/* defined types */

typedef struct {
	float realtime;          // absolute time
	int framecount;          // absolute frame counter
	float absoluteframetime; // non-paused frametime
	float curtime;           // current time
	float frametime;         // time spent on last frame
	int maxClients;          // maxplayers
	int tickcount;           // simulation ticks
	float interval_per_tick; // simulation tick interval
	
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	void *pSaveData;
	
	bool m_bClient;
	int nTimestampNetworkingBase;
	int nTimestampRandomizeWindow;
	
	string_t mapname;
	int mapversion;
	string_t startspot;
	/*MapLoadType_t*/int eLoadType;
	bool bMapLoadFailed;
	
	bool deathmatch;
	bool coop;
	bool teamplay;
	
	int maxEntities;
	int serverCount;
} CGlobalVars;

typedef struct {
	uint8_t pad1[0x30];
	
	const char *m_pVarName; // +30
	
	uint8_t pad2[0x10];
	
	void* m_pDataTable; // +44
	int   m_Offset;     // +48
	
	uint8_t pad3[0x4];
} SendProp;
_Static_assert(sizeof(SendProp) == 0x50, "bad size: SendProp");

typedef struct {
	SendProp* m_pProps; // +00
	int m_nProps;       // +04
} SendTable;

typedef struct {
	uint8_t pad1[0x4];
	
	SendTable* m_pTable; // +04
} ServerClass;

struct datamap;

typedef struct {
	fieldtype_t			fieldType;
	const char			*fieldName;
	int					fieldOffset[ TD_OFFSET_COUNT ]; // 0 == normal, 1 == packed offset
	unsigned short		fieldSize;
	short				flags;
	// the name of the variable in the map/fgd data, or the name of the action
	const char			*externalName;	
	// pointer to the function set for save/restoring of custom data types
	void/*ISaveRestoreOps*/		*pSaveRestoreOps; 
	// for associating function with string names
	uint64_t/*inputfunc_t*/			inputFunc; 
	// For embedding additional datatables inside this one
	struct datamap			*td;
	
	// Stores the actual member variable size in bytes
	int					fieldSizeInBytes;
	
	// FTYPEDESC_OVERRIDE point to first baseclass instance if chains_validated has occurred
	void/*struct typedescription_t*/ *override_field;
	
	// Used to track exclusion of baseclass fields
	int					override_count;
  	
	// Tolerance for field errors for float fields
	float				fieldTolerance;
} typedescription_t;

struct datamap {
	typedescription_t *dataDesc;
	int                dataNumFields;
	char const        *dataClassName;
	struct datamap    *baseMap;
};
typedef struct datamap datamap_t;

typedef struct {
	float x;
	float y;
	float z;
} Vector;
_Static_assert(sizeof(Vector) == 12, "bad size: Vector");

typedef struct {
	float x;
	float y;
	float z;
} QAngle;
_Static_assert(sizeof(QAngle) == 12, "bad size: QAngle");

typedef struct {
	Vector m_vecDamageForce;
	Vector m_vecDamagePosition;
	Vector m_vecReportedPosition;
	EHANDLE m_hInflictor;
	EHANDLE m_hAttacker;
	EHANDLE m_hWeapon;
	float m_flDamage;
	float m_flMaxDamage;
	float m_flBaseDamage;
	int m_bitsDamageType;
	int m_iDamageCustom;
	int m_iDamageStats;
	int m_iAmmoType;
	int m_iDamagedOtherPlayers;
	int m_iPlayerPenetrationCount;
	float m_flDamageBonus;
	EHANDLE m_hDamageBonusProvider;
	bool m_bForceFriendlyFire;
} CTakeDamageInfo;
_Static_assert(sizeof(CTakeDamageInfo) == 0x60, "bad size: CTakeDamageInfo");

typedef enum {
	TFSTAT_UNDEFINED = 0,
	
	// TODO
} TFStatType_t;


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

extern void (*CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
extern void (*CTFPlayerShared_RadiusCurrencyCollectionCheck)(CTFPlayerShared* this);

extern unknown_t (*CTFPlayer_ApplyAbsVelocityImpulse)(CTFPlayer* this, Vector const*);
extern bool (*CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);
extern int (*CTFPlayer_CanBuild)(CTFPlayer* this, int, int);
extern bool (*CTFPlayer_CanPickupBuilding)(CTFPlayer* this, CBaseObject*);
extern void (*CTFPlayer_CreateRagdollEntity)(CTFPlayer* this, bool, bool, bool, bool, bool, bool, bool, bool, int, bool);
extern void (*CTFPlayer_DeathSound)(CTFPlayer* this, CTakeDamageInfo const*);
extern void (*CTFPlayer_Event_Killed)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_IsMiniBoss)(CTFPlayer* this);
extern bool (*CTFPlayer_IsPlayerClass)(CTFPlayer* this, int);
extern unknown_t (*CTFPlayer_OnTakeDamage_Alive)(CTFPlayer* this, CTakeDamageInfo const*);
extern bool (*CTFPlayer_ShouldGib)(CTFPlayer* this, CTakeDamageInfo const*);
extern unknown_t (*CTFPlayer_TFPlayerThink)(CTFPlayer* this);

extern bool (*CTFBot_ShouldGib)(CTFBot* this, CTakeDamageInfo const*);

extern void (*CTFTankBoss_TankBossThink)(CTFTankBoss* this);

extern int (*CTFWeaponBase_GetWeaponID)(CTFWeaponBase* this);

extern void (*CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);

extern void (*CTFRocketLauncher_Precache)(CTFRocketLauncher* this);

extern void (*CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);
extern void (*CTFSniperRifle_ItemPostFrame)(CTFSniperRifle* this);
extern void (*CTFSniperRifleClassic_ItemPostFrame)(CTFSniperRifleClassic* this);
extern float (*CTFSniperRifleDecap_SniperRifleChargeRateMod)(CTFSniperRifleDecap* this);

extern unknown_t (*CTFProjectile_Arrow_StrikeTarget_clone323)(CTFProjectile_Arrow* this, mstudiobbox_t*, CBaseEntity*);

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
