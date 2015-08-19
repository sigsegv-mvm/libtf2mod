#ifndef _LIBTF2MOD_TYPES_H
#define _LIBTF2MOD_TYPES_H


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

enum {
	FIRE_BULLETS_FIRST_SHOT_ACCURATE         = 0x1,
	FIRE_BULLETS_DONT_HIT_UNDERWATER         = 0x2,
	FIRE_BULLETS_ALLOW_WATER_SURFACE_IMPACTS = 0x4,
	FIRE_BULLETS_TEMPORARY_DANGER_SOUND      = 0x8,
};

typedef enum {
	TFSTAT_UNDEFINED = 0,
	
	// TODO
} TFStatType_t;


/* opaque types */

typedef uint32_t unknown_t;

typedef void CServerGameDLL;

typedef void CBaseEntity;
typedef void CBaseAnimating;

typedef void CBasePlayer;
typedef void CTFPlayerShared;
typedef void CTFPlayer;
typedef void CTFBot;
typedef void NextBotPlayer_CTFPlayer;

typedef void CTFTankBoss;

typedef void CTFWeaponBase;
typedef void CTFWeaponBaseGun;
typedef void CTFRocketLauncher;
typedef void CTFSniperRifle;
typedef void CTFSniperRifleDecap;
typedef void CTFSniperRifleClassic;
typedef void CTFKnife;

typedef void CTFProjectile_Arrow;
typedef void CTFProjectile_Flare;

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

typedef void Action_CTFBot;

typedef void IRecipientFilter;

typedef void CDmgAccumulator;

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
	float x;
	float y;
	float z;
} Vector;
SIZE_CHECK(Vector, 0xc);

typedef struct {
	float x;
	float y;
	float z;
} QAngle;
SIZE_CHECK(QAngle, 0xc);

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
SIZE_CHECK(CTakeDamageInfo, 0x60);

typedef struct {
	int m_iShots;
	Vector m_vecSrc;
	Vector m_vecDirShooting;
	Vector m_vecSpread;
	float m_flDistance;
	int m_iAmmoType;
	int m_iTracerFreq;
	float m_flDamage;
	int m_iPlayerDamage;
	int m_nFlags;
	float m_flDamageForceScale;
	CBaseEntity *m_pAttacker;
	CBaseEntity *m_pAdditionalIgnoreEnt;
	bool m_bPrimaryAttack;
} FireBulletsInfo_t;
SIZE_CHECK(FireBulletsInfo_t, 0x50);

typedef struct {
	Vector normal;
	float dist;
	uint8_t type;
	uint8_t signbits;
	uint8_t pad[2];
} cplane_t;
SIZE_CHECK(cplane_t, 0x14);

typedef struct {
	const char *name;
	short surfaceProps;
	unsigned short flags;
} csurface_t;
SIZE_CHECK(csurface_t, 0x8);

typedef struct {
	Vector startpos;
	Vector endpos;
	cplane_t plane;
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startsolid;
} CBaseTrace;
SIZE_CHECK(CBaseTrace, 0x38);

typedef struct {
	CBaseTrace base;
	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	CBaseEntity *m_pEnt;
	int hitbox;
} CGameTrace;
SIZE_CHECK(CGameTrace, 0x54);


#endif
