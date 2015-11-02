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
	TF_COND_AIMING                           =   0,
	TF_COND_ZOOMED                           =   1,
	TF_COND_DISGUISING                       =   2,
	TF_COND_DISGUISED                        =   3,
	TF_COND_STEALTHED                        =   4,
	TF_COND_INVULNERABLE                     =   5,
	TF_COND_TELEPORTED                       =   6,
	TF_COND_TAUNTING                         =   7,
	TF_COND_INVULNERABLE_WEARINGOFF          =   8,
	TF_COND_STEALTHED_BLINK                  =   9,
	TF_COND_SELECTED_TO_TELEPORT             =  10,
	TF_COND_CRITBOOSTED                      =  11,
	TF_COND_TMPDAMAGEBONUS                   =  12,
	TF_COND_FEIGN_DEATH                      =  13,
	TF_COND_PHASE                            =  14,
	TF_COND_STUNNED                          =  15,
	TF_COND_OFFENSEBUFF                      =  16,
	TF_COND_SHIELD_CHARGE                    =  17,
	TF_COND_DEMO_BUFF                        =  18,
	TF_COND_ENERGY_BUFF                      =  19,
	TF_COND_RADIUSHEAL                       =  20,
	TF_COND_HEALTH_BUFF                      =  21,
	TF_COND_BURNING                          =  22,
	TF_COND_HEALTH_OVERHEALED                =  23,
	TF_COND_URINE                            =  24,
	TF_COND_BLEEDING                         =  25,
	TF_COND_DEFENSEBUFF                      =  26,
	TF_COND_MAD_MILK                         =  27,
	TF_COND_MEGAHEAL                         =  28,
	TF_COND_REGENONDAMAGEBUFF                =  29,
	TF_COND_MARKEDFORDEATH                   =  30,
	TF_COND_NOHEALINGDAMAGEBUFF              =  31,
	TF_COND_SPEED_BOOST                      =  32,
	TF_COND_CRITBOOSTED_PUMPKIN              =  33,
	TF_COND_CRITBOOSTED_USER_BUFF            =  34,
	TF_COND_CRITBOOSTED_DEMO_CHARGE          =  35,
	TF_COND_SODAPOPPER_HYPE                  =  36,
	TF_COND_CRITBOOSTED_FIRST_BLOOD          =  37,
	TF_COND_CRITBOOSTED_BONUS_TIME           =  38,
	TF_COND_CRITBOOSTED_CTF_CAPTURE          =  39,
	TF_COND_CRITBOOSTED_ON_KILL              =  40,
	TF_COND_CANNOT_SWITCH_FROM_MELEE         =  41,
	TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK        =  42,
	TF_COND_REPROGRAMMED                     =  43,
	TF_COND_CRITBOOSTED_RAGE_BUFF            =  44,
	TF_COND_DEFENSEBUFF_HIGH                 =  45,
	TF_COND_SNIPERCHARGE_RAGE_BUFF           =  46,
	TF_COND_DISGUISE_WEARINGOFF              =  47,
	TF_COND_MARKEDFORDEATH_SILENT            =  48,
	TF_COND_DISGUISED_AS_DISPENSER           =  49,
	TF_COND_SAPPED                           =  50,
	TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGED =  51,
	TF_COND_INVULNERABLE_USER_BUFF           =  52,
	TF_COND_HALLOWEEN_BOMB_HEAD              =  53,
	TF_COND_HALLOWEEN_THRILLER               =  54,
	TF_COND_RADIUSHEAL_ON_DAMAGE             =  55,
	TF_COND_CRITBOOSTED_CARD_EFFECT          =  56,
	TF_COND_INVULNERABLE_CARD_EFFECT         =  57,
	TF_COND_MEDIGUN_UBER_BULLET_RESIST       =  58,
	TF_COND_MEDIGUN_UBER_BLAST_RESIST        =  59,
	TF_COND_MEDIGUN_UBER_FIRE_RESIST         =  60,
	TF_COND_MEDIGUN_SMALL_BULLET_RESIST      =  61,
	TF_COND_MEDIGUN_SMALL_BLAST_RESIST       =  62,
	TF_COND_MEDIGUN_SMALL_FIRE_RESIST        =  63,
	TF_COND_STEALTHED_USER_BUFF              =  64,
	TF_COND_MEDIGUN_DEBUFF                   =  65,
	TF_COND_STEALTHED_USER_BUFF_FADING       =  66,
	TF_COND_BULLET_IMMUNE                    =  67,
	TF_COND_BLAST_IMMUNE                     =  68,
	TF_COND_FIRE_IMMUNE                      =  69,
	TF_COND_PREVENT_DEATH                    =  70,
	TF_COND_MVM_BOT_STUN_RADIOWAVE           =  71,
	TF_COND_HALLOWEEN_SPEED_BOOST            =  72,
	TF_COND_HALLOWEEN_QUICK_HEAL             =  73,
	TF_COND_HALLOWEEN_GIANT                  =  74,
	TF_COND_HALLOWEEN_TINY                   =  75,
	TF_COND_HALLOWEEN_IN_HELL                =  76,
	TF_COND_HALLOWEEN_GHOST_MODE             =  77,
	TF_COND_MINICRITBOOSTED_ON_KILL          =  78,
	TF_COND_OBSCURED_SMOKE                   =  79,
	TF_COND_PARACHUTE_DEPLOYED               =  80,
	TF_COND_BLASTJUMPING                     =  81,
	TF_COND_HALLOWEEN_KART                   =  82,
	TF_COND_HALLOWEEN_KART_DASH              =  83,
	TF_COND_BALLOON_HEAD                     =  84,
	TF_COND_MELEE_ONLY                       =  85,
	TF_COND_SWIMMING_CURSE                   =  86,
	TF_COND_FREEZE_INPUT                     =  87,
	TF_COND_HALLOWEEN_KART_CAGE              =  88,
	TF_COND_DONOTUSE_0                       =  89,
	TF_COND_RUNE_STRENGTH                    =  90,
	TF_COND_RUNE_HASTE                       =  91,
	TF_COND_RUNE_REGEN                       =  92,
	TF_COND_RUNE_RESIST                      =  93,
	TF_COND_RUNE_VAMPIRE                     =  94,
	TF_COND_RUNE_WARLOCK                     =  95,
	TF_COND_RUNE_PRECISION                   =  96,
	TF_COND_RUNE_AGILITY                     =  97,
	TF_COND_GRAPPLINGHOOK                    =  98,
	TF_COND_GRAPPLINGHOOK_SAFEFALL           =  99,
	TF_COND_GRAPPLINGHOOK_LATCHED            = 100,
	TF_COND_GRAPPLINGHOOK_BLEEDING           = 101,
	TF_COND_AFTERBURN_IMMUNE                 = 102,
	TF_COND_RUNE_KNOCKOUT                    = 103,
	TF_COND_RUNE_IMBALANCE                   = 104,
	TF_COND_CRITBOOSTED_RUNE_TEMP            = 105,
	TF_COND_PASSTIME_INTERCEPTION            = 106,
	TF_COND_SWIMMING_NO_EFFECTS              = 107,
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
	TLK_FIREWEAPON = 0,
	TLK_HURT,
	TLK_PLAYER_EXPRESSION,
	TLK_WINDMINIGUN,
	TLK_FIREMINIGUN,
	TLK_PLAYER_MEDIC,
	TLK_DETONATED_OBJECT,
	TLK_KILLED_PLAYER,
	TLK_KILLED_OBJECT,
	TLK_PLAYER_PAIN,
	TLK_PLAYER_ATTACKER_PAIN,
	TLK_PLAYER_TAUNT,
	TLK_PLAYER_HELP,
	TLK_PLAYER_GO,
	TLK_PLAYER_MOVEUP,
	TLK_PLAYER_LEFT,
	TLK_PLAYER_RIGHT,
	TLK_PLAYER_YES,
	TLK_PLAYER_NO,
	TLK_PLAYER_INCOMING,
	TLK_PLAYER_CLOAKEDSPY,
	TLK_PLAYER_SENTRYAHEAD,
	TLK_PLAYER_TELEPORTERHERE,
	TLK_PLAYER_DISPENSERHERE,
	TLK_PLAYER_SENTRYHERE,
	TLK_PLAYER_ACTIVATECHARGE,
	TLK_PLAYER_CHARGEREADY,
	TLK_PLAYER_TAUNTS,
	TLK_PLAYER_BATTLECRY,
	TLK_PLAYER_CHEERS,
	TLK_PLAYER_JEERS,
	TLK_PLAYER_POSITIVE,
	TLK_PLAYER_NEGATIVE,
	TLK_PLAYER_NICESHOT,
	TLK_PLAYER_GOODJOB,
	TLK_MEDIC_STARTEDHEALING,
	TLK_MEDIC_CHARGEREADY,
	TLK_MEDIC_STOPPEDHEALING,
	TLK_MEDIC_CHARGEDEPLOYED,
	TLK_FLAGPICKUP,
	TLK_FLAGCAPTURED,
	TLK_ROUND_START,
	TLK_SUDDENDEATH_START,
	TLK_ONFIRE,
	TLK_STALEMATE,
	TLK_BUILDING_OBJECT,
	TLK_LOST_OBJECT,
	TLK_SPY_SAPPER,
	TLK_TELEPORTED,
	TLK_LOST_CONTROL_POINT,
	TLK_CAPTURED_POINT,
	TLK_CAPTURE_BLOCKED,
	TLK_HEALTARGET_STARTEDHEALING,
	TLK_HEALTARGET_CHARGEREADY,
	TLK_HEALTARGET_STOPPEDHEALING,
	TLK_HEALTARGET_CHARGEDEPLOYED,
	TLK_MINIGUN_FIREWEAPON,
	TLK_DIED,
	TLK_PLAYER_THANKS,
	TLK_CART_MOVING_FORWARD,
	TLK_CART_MOVING_BACKWARD,
	TLK_CART_STOP,
	TLK_ATE_FOOD,
	TLK_DOUBLE_JUMP,
	TLK_DODGING,
	TLK_DODGE_SHOT,
	TLK_GRAB_BALL,
	TLK_REGEN_BALL,
	TLK_DEFLECTED,
	TLK_BALL_MISSED,
	TLK_STUNNED,
	TLK_STUNNED_TARGET,
	TLK_TIRED,
	TLK_BAT_BALL,
	TLK_ACHIEVEMENT_AWARD,
	TLK_JARATE_HIT,
	TLK_JARATE_LAUNCH,
	TLK_HIGHFIVE_SUCCESS,
	TLK_HIGHFIVE_SUCCESS_FULL,
	TLK_HIGHFIVE_FAILURE,
	TLK_HIGHFIVE_FAILURE_FULL,
	TLK_PLAYER_TAUNT2,
	TLK_PICKUP_BUILDING,
	TLK_REDEPLOY_BUILDING,
	TLK_CARRYING_BUILDING,
	TLK_REQUEST_DUEL,
	TLK_REJECT_DUEL,
	TLK_DUEL_WAS_REJECTED,
	TLK_ACCEPT_DUEL,
	TLK_DUEL_WAS_ACCEPTED,
	TLK_PLAYER_SHOW_ITEM_TAUNT,
	TLK_TAUNT_REPLAY,
	TLK_TAUNT_LAUGH,
	TLK_TAUNT_HEROIC_POSE,
	TLK_PARTNER_TAUNT_READY,
	TLK_PLAYER_HOLDTAUNT,
	TLK_TAUNT_PYRO_ARMAGEDDON,
	TLK_ROCKET_DESTOYED,
	TLK_MVM_BOMB_DROPPED,
	TLK_MVM_BOMB_CARRIER_UPGRADE1,
	TLK_MVM_BOMB_CARRIER_UPGRADE2,
	TLK_MVM_BOMB_CARRIER_UPGRADE3,
	TLK_MVM_DEFENDER_DIED,
	TLK_MVM_FIRST_BOMB_PICKUP,
	TLK_MVM_BOMB_PICKUP,
	TLK_MVM_SENTRY_BUSTER,
	TLK_MVM_SENTRY_BUSTER_DOWN,
	TLK_MVM_SNIPER_CALLOUT,
	TLK_MVM_LAST_MAN_STANDING,
	TLK_MVM_ENCOURAGE_MONEY,
	TLK_MVM_MONEY_PICKUP,
	TLK_MVM_ENCOURAGE_UPGRADE,
	TLK_MVM_UPGRADE_COMPLETE,
	TLK_MVM_GIANT_CALLOUT,
	TLK_MVM_GIANT_HAS_BOMB,
	TLK_MVM_GIANT_KILLED,
	TLK_MVM_GIANT_KILLED_TEAMMATE,
	TLK_MVM_SAPPED_ROBOT,
	TLK_MVM_CLOSE_CALL,
	TLK_MVM_TANK_CALLOUT,
	TLK_MVM_TANK_DEAD,
	TLK_MVM_TANK_DEPLOYING,
	TLK_MVM_ATTACK_THE_TANK,
	TLK_MVM_TAUNT,
	TLK_MVM_WAVE_START,
	TLK_MVM_WAVE_WIN,
	TLK_MVM_WAVE_LOSE,
	TLK_MVM_DEPLOY_RAGE,
	TLK_MAGIC_BIGHEAD,
	TLK_MAGIC_SMALLHEAD,
	TLK_MAGIC_GRAVITY,
	TLK_MAGIC_GOOD,
	TLK_MAGIC_DANCE,
	TLK_HALLOWEEN_LONG_FALL,
	TLK_TAUNT_GUITAR_RIFF,
	TLK_PLAYER_CAST_FIREBALL,
	TLK_PLAYER_CAST_MERASMUS_ZAP,
	TLK_PLAYER_CAST_SELF_HEAL,
	TLK_PLAYER_CAST_MIRV,
	TLK_PLAYER_CAST_BLAST_JUMP,
	TLK_PLAYER_CAST_STEALTH,
	TLK_PLAYER_CAST_TELEPORT,
	TLK_PLAYER_CAST_LIGHTNING_BALL,
	TLK_PLAYER_CAST_MOVEMENT_BUFF,
	TLK_PLAYER_CAST_MONOCULOUS,
	TLK_PLAYER_CAST_METEOR_SWARM,
	TLK_PLAYER_CAST_SKELETON_HORDE,
	TLK_PLAYER_CAST_BOMB_HEAD_CURSE,
	TLK_PLAYER_SPELL_FIREBALL,
	TLK_PLAYER_SPELL_MERASMUS_ZAP,
	TLK_PLAYER_SPELL_SELF_HEAL,
	TLK_PLAYER_SPELL_MIRV,
	TLK_PLAYER_SPELL_BLAST_JUMP,
	TLK_PLAYER_SPELL_STEALTH,
	TLK_PLAYER_SPELL_TELEPORT,
	TLK_PLAYER_SPELL_LIGHTNING_BALL,
	TLK_PLAYER_SPELL_MOVEMENT_BUFF,
	TLK_PLAYER_SPELL_MONOCULOUS,
	TLK_PLAYER_SPELL_METEOR_SWARM,
	TLK_PLAYER_SPELL_SKELETON_HORDE,
	TLK_PLAYER_SPELL_BOMB_HEAD_CURSE,
	TLK_PLAYER_SPELL_PICKUP_COMMON,
	TLK_PLAYER_SPELL_PICKUP_RARE,
	TLK_PLAYER_HELLTOWER_MIDNIGHT,
	TLK_PLAYER_SKELETON_KING_APPEAR,
	TLK_MANNHATTAN_GATE_ATK,
	TLK_MANNHATTAN_GATE_TAKE,
	TLK_RESURRECTED,
	TLK_MVM_LOOT_COMMON,
	TLK_MVM_LOOT_RARE,
	TLK_MVM_LOOT_ULTRARARE,
	TLK_MEDIC_HEAL_SHIELD,
	TLK_TAUNT_EUREKA_EFFECT,
	TLK_COMBO_KILLED,
	TLK_PLAYER_ASK_FOR_BALL,
};

enum {
	TF_AMMO_DUMMY = 0,
	TF_AMMO_PRIMARY,
	TF_AMMO_SECONDARY,
	TF_AMMO_METAL,
	TF_AMMO_GRENADES1,
	TF_AMMO_GRENADES2,
	TF_AMMO_GRENADES3,
};

enum
{
	PROJECTILE_INVALID = 0,
	PROJECTILE_BULLET,
	PROJECTILE_ROCKET,
	PROJECTILE_PIPE,
	PROJECTILE_PIPE_REMOTE,
	PROJECTILE_SYRINGE,
	PROJECTILE_FLARE,
	PROJECTILE_JAR,
	PROJECTILE_ARROW,
	PROJECTILE_FLAME_ROCKET,
	PROJECTILE_JAR_MILK,
	PROJECTILE_HEALING_BOLT,
	PROJECTILE_ENERGY_BALL,
	PROJECTILE_ENERGY_RING,
	PROJECTILE_PIPE_REMOTE_PRACTICE,
	PROJECTILE_CLEAVER,
	PROJECTILE_STICKY_BALL,
	PROJECTILE_CANNONBALL,
	PROJECTILE_BUILDING_REPAIR_BOLT,
	PROJECTILE_FESTIVE_ARROW,
	PROJECTILE_THROWABLE,
	PROJECTILE_SPELLFIREBALL,
	PROJECTILE_FESTIVE_URINE,
	PROJECTILE_FESTIVE_HEALING_BOLT,
	PROJECTILE_BREADMONSTER_JARATE,
	PROJECTILE_BREADMONSTER_MADMILK,
	PROJECTILE_GRAPPLINGHOOK,
	PROJECTILE_SENTRY_ROCKET,
	PROJECTILE_BREAD_MONSTER,
};

enum {
	TFOBJECT_DISPENSER  = 0,
	TFOBJECT_TELEPORTER = 1,
	TFOBJECT_SENTRYGUN  = 2,
	TFOBJECT_SAPPER     = 3,
};

enum {
	TF_STUNFLAG_SLOWDOWN        = (1 << 0),	/**< activates slowdown modifier */
	TF_STUNFLAG_BONKSTUCK       = (1 << 1),	/**< bonk sound, stuck */
	TF_STUNFLAG_LIMITMOVEMENT   = (1 << 2),	/**< disable forward/backward movement */
	TF_STUNFLAG_CHEERSOUND      = (1 << 3),	/**< cheering sound */
	TF_STUNFLAG_NOSOUNDOREFFECT = (1 << 5),	/**< no sound or particle */
	TF_STUNFLAG_THIRDPERSON     = (1 << 6),	/**< panic animation */
	TF_STUNFLAG_GHOSTEFFECT     = (1 << 7),	/**< ghost particles */
	
	TF_STUNFLAGS_LOSERSTATE     = TF_STUNFLAG_SLOWDOWN | TF_STUNFLAG_NOSOUNDOREFFECT | TF_STUNFLAG_THIRDPERSON,
	TF_STUNFLAGS_GHOSTSCARE     = TF_STUNFLAG_GHOSTEFFECT | TF_STUNFLAG_THIRDPERSON,
	TF_STUNFLAGS_SMALLBONK      = TF_STUNFLAG_THIRDPERSON | TF_STUNFLAG_SLOWDOWN,
	TF_STUNFLAGS_NORMALBONK     = TF_STUNFLAG_BONKSTUCK,
	TF_STUNFLAGS_BIGBONK        = TF_STUNFLAG_CHEERSOUND | TF_STUNFLAG_BONKSTUCK,
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

typedef enum {
	// 0: ???
	// 1: ???
	TFBOT_MISSION_SENTRY_BUSTER = 2,
	TFBOT_MISSION_SNIPER        = 3,
	TFBOT_MISSION_SPY           = 4,
	// 5: ???
	// 6: ???
} CTFBot_MissionType;

typedef enum {
	ROUNDSTATE_INIT          = 0,
	ROUNDSTATE_PREGAME       = 1,
	ROUNDSTATE_STARTGAME     = 2,
	ROUNDSTATE_PREROUND      = 3,
	ROUNDSTATE_ROUNDRUNNING  = 4,
	ROUNDSTATE_TEAMWIN       = 5,
	ROUNDSTATE_RESTART       = 6,
	ROUNDSTATE_STALEMATE     = 7,
	ROUNDSTATE_GAMEOVER      = 8,
	ROUNDSTATE_BONUS         = 9,
	ROUNDSTATE_BETWEENROUNDS = 10,
} gamerules_roundstate_t;

typedef enum {
	SLOT_PRIMARY   = 0,
	SLOT_SECONDARY = 1,
	SLOT_MELEE     = 2,
	SLOT_UTILITY   = 3,
	SLOT_BUILDING  = 4, // sapper
	SLOT_PDA       = 5, // engie build pda, disguise kit
	SLOT_PDA2      = 6, // engie destroy pda, invis watch
	SLOT_HEAD      = 7,
	SLOT_MISC      = 8,
	SLOT_ACTION    = 9, // canteens
	/* slot 10 unknown */
	SLOT_TAUNT     = 11,
} LoadoutSlot;

typedef enum {
	TAUNTATK_NONE                          = 0,
	TAUNTATK_PYRO_HADOUKEN                 = 1,
	TAUNTATK_HEAVY_EAT                     = 2,
	TAUNTATK_HEAVY_RADIAL_BUFF             = 3,
	TAUNTATK_HEAVY_HIGH_NOON               = 4,
	TAUNTATK_SCOUT_DRINK                   = 5,
	TAUNTATK_SCOUT_GRAND_SLAM              = 6,
	TAUNTATK_MEDIC_INHALE                  = 7,
	TAUNTATK_SPY_FENCING_SLASH_A           = 8,
	TAUNTATK_SPY_FENCING_SLASH_B           = 9,
	TAUNTATK_SPY_FENCING_STAB              = 10,
	TAUNTATK_RPS_KILL                      = 11,
	TAUNTATK_SNIPER_ARROW_STAB_IMPALE      = 12,
	TAUNTATK_SNIPER_ARROW_STAB_KILL        = 13,
	TAUNTATK_SOLDIER_GRENADE_KILL          = 14,
	TAUNTATK_DEMOMAN_BARBARIAN_SWING       = 15,
	TAUNTATK_MEDIC_UBERSLICE_IMPALE        = 16,
	TAUNTATK_MEDIC_UBERSLICE_KILL          = 17,
	TAUNTATK_FLIP_LAND_PARTICLE            = 18,
	TAUNTATK_RPS_PARTICLE                  = 19,
	TAUNTATK_HIGHFIVE_PARTICLE             = 20,
	TAUNTATK_ENGINEER_GUITAR_SMASH         = 21,
	TAUNTATK_ENGINEER_ARM_IMPALE           = 22,
	TAUNTATK_ENGINEER_ARM_KILL             = 23,
	TAUNTATK_ENGINEER_ARM_BLEND            = 24,
	TAUNTATK_SOLDIER_GRENADE_KILL_WORMSIGN = 25,
	TAUNTATK_SHOW_ITEM                     = 26,
	TAUNTATK_MEDIC_RELEASE_DOVES           = 27,
	TAUNTATK_PYRO_ARMAGEDDON               = 28,
	TAUNTATK_PYRO_SCORCHSHOT               = 29,
	TAUNTATK_ALLCLASS_GUITAR_RIFF          = 30,
	TAUNTATK_MEDIC_HEROIC_TAUNT            = 31,
} TauntAttack;

typedef enum {
	HOLIDAY_NOHOLIDAY                       = 0,
	HOLIDAY_TF2BIRTHDAY                     = 1,
	HOLIDAY_HALLOWEEN                       = 2,
	HOLIDAY_CHRISTMAS                       = 3,
	HOLIDAY_ENDOFTHELINE                    = 4,
	HOLIDAY_VALENTINESDAY                   = 5,
	HOLIDAY_MEETTHEPYRO                     = 6,
	HOLIDAY_SPYVSENGYWAR                    = 7,
	HOLIDAY_FULLMOON                        = 8,
	HOLIDAY_HALLOWEENORFULLMOON             = 9,
	HOLIDAY_HALLOWEENORFULLMOONORVALENTINES = 10,
	HOLIDAY_APRILFOOLS                      = 11,
} TFHoliday;

typedef enum {
	LOOKPRI_BORING      = 0,
	LOOKPRI_INTERESTING = 1,
	LOOKPRI_IMPORTANT   = 2,
	LOOKPRI_CRITICAL    = 3,
} IBody_LookAtPriorityType;


/* opaque types */

typedef uint32_t unknown_t;

typedef void IServerNetworkable;
typedef void IHandleEntity;
typedef void IServerUnknown;

typedef void CServerGameDLL;
typedef void CVEngineServer;

typedef void CGameEventManager;
typedef void IGameEvent;

typedef void CGlobalEntityList;

typedef void CBaseEntity;
typedef void CBaseAnimating;

typedef void CBaseCombatCharacter;
typedef void CBasePlayer;
typedef void CBaseMultiplayerPlayer;
typedef void CTFPlayer;
typedef void CTFBot;
typedef void NextBotPlayer_CTFPlayer;

typedef void CTFPlayerShared;

typedef void CTFTankBoss;

typedef void CEconEntity;
typedef void CEconItemAttributeDefinition;
typedef void CEconItemDefinition;
typedef void CEconItemSchema;
typedef void CEconItemView;

typedef void CSchemaFieldHandle_CEconItemDefinition;

typedef void CItemGeneration;
typedef void CItemSelectionCriteria;

typedef void CAttribute_String;
typedef void CAttributeList;

typedef void CTFWeaponBase;
typedef void CTFWeaponBaseGun;
typedef void CWeaponMedigun;
typedef void CTFMinigun;
typedef void CTFRocketLauncher;
typedef void CTFSniperRifle;
typedef void CTFSniperRifleDecap;
typedef void CTFSniperRifleClassic;
typedef void CTFKnife;
typedef void CTFWearableDemoShield;
typedef void CTFStickBomb;
typedef void CTFSword;
typedef void CTFWeaponBuilder;

typedef void CTFBaseRocket;
typedef void CTFWeaponBaseGrenadeProj;
typedef void CTFProjectile_Arrow;
typedef void CTFProjectile_Flare;

typedef void CBaseObject;
typedef void CObjectDispenser;
typedef void CObjectSentrygun;
typedef void CObjectTeleporter;
typedef void CObjectSapper;

typedef void CTFMedigunShield;

typedef void CTFGameRules;
typedef void CTeamplayRoundBasedRules;

typedef void CTFGameStats;

typedef void CMannVsMachineStats;

typedef void CTFObjectiveResource;

typedef void CPopulationManager;

typedef void CMissionPopulator;

typedef void CWave;

typedef void CUpgrades;
typedef void CMannVsMachineUpgrades;
typedef void* UpgradeAttribBlock_t;
typedef void CMannVsMachineUpgradeManager;

typedef void CTFBotLocomotion;
typedef void CTFBotMainAction;
typedef void CTFBotScenarioMonitor;
typedef void CTFBotTacticalMonitor;
typedef void CTFBotMedicHeal;
typedef void CTFBotMvMEngineerIdle;
typedef void CTFBotMissionSuicideBomber;

typedef void INextBot;

typedef void INextBotComponent;

typedef void IVision;

typedef void IBody;
typedef void PlayerBody;

typedef void ILocomotion;
typedef void PlayerLocomotion;

typedef void CTFReviveMarker;

typedef void CCurrencyPack;

typedef void CTFDroppedWeapon;

typedef void CFuncNavCost;

typedef void CUtlVector;
typedef void CUtlConstStringBase;

typedef void Action_CTFBot;

typedef void IRecipientFilter;

typedef void CDmgAccumulator;

typedef void mstudiobbox_t;

typedef unknown_t ShakeCommand_t;

typedef void CTraceFilterObject;

typedef void inputdata_t;

typedef void CSoundEmitterSystemBase;

typedef void IEntityFindFilter;

typedef void INextBotReply;

typedef uint32_t EHANDLE;


/* defined types */

typedef struct {
	
} unknown_struct_t;

typedef struct {
	const char *pszValue;
} string_t;

typedef struct {
	int         status;
	void       *p_newbehavior;
	const char *p_comment;
	int         unknown1;
} nextbot_event_response_t;

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

typedef struct {
	int m_fStateFlags;
	short m_NetworkSerialNumber;
	short m_EdictIndex;
	IServerNetworkable *m_pNetworkable;
	IServerUnknown *m_pUnk;
} CBaseEdict;
SIZE_CHECK(CBaseEdict, 0x10);

typedef struct {
	CBaseEdict base;
	float freetime;
} edict_t;
SIZE_CHECK(edict_t, 0x14);


#endif
