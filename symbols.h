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

enum
{
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,
	
	// Must be last
	TD_OFFSET_COUNT,
};


/* defined types */

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
	struct datamap         *baseMap;
};
typedef struct datamap datamap_t;

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

extern datamap_t* (*CBaseObject_GetDataDescMap)(void);
extern datamap_t* (*CObjectSentrygun_GetDataDescMap)(void);

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
extern void (*CObjectSentrygun_MakeDisposableBuilding)(CObjectSentrygun* this, CTFPlayer*);
extern void (*CObjectSentrygun_SentryRotate)(CObjectSentrygun* this);
extern void (*CObjectSentrygun_SentryThink)(CObjectSentrygun* this);

extern bool (*CTFGameRules_CanUpgradeWithAttrib)(CTFGameRules* this, CTFPlayer*, int, unsigned short, CMannVsMachineUpgrades*);
extern bool (*CTFGameRules_GameModeUsesUpgrades)(CTFGameRules* this);
extern void (*CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);

extern unknown_t (*CTFBotMainAction_OnContact)(CTFBotMainAction* this, CTFBot*, CBaseEntity*, CGameTrace*);
extern unknown_t (*CTFBotMainAction_Update)(CTFBotMainAction* this, CTFBot*, float);


#undef extern


#endif
