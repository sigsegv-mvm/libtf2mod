#ifndef _LIBTF2MOD_ENTPROP_H
#define _LIBTF2MOD_ENTPROP_H


/* known entprops */

float *prop_CBaseAnimating_m_flModelScale(CBaseAnimating* ent);
int *prop_CBaseAnimating_m_nSkin(CBaseAnimating* ent);

unsigned int *prop_CBasePlayer_m_nButtons(CBasePlayer* ent);

int *prop_CTFPlayer_m_iClass(CTFPlayer* ent);
CTFPlayerShared *prop_CTFPlayer_m_Shared(CTFPlayer* ent);

int *prop_CTFPlayerShared_m_iStunFlags(CTFPlayerShared* ent);
int *prop_CTFPlayerShared_m_iStunIndex(CTFPlayerShared* ent);

float *prop_CTFWeaponBaseGun_m_flNextPrimaryAttack(CTFWeaponBaseGun* ent);

bool *prop_CBaseObject_m_bBuilding(CBaseObject* ent);
bool *prop_CBaseObject_m_bDisposableBuilding(CBaseObject* ent);
bool *prop_CBaseObject_m_bMiniBuilding(CBaseObject* ent);
int *prop_CBaseObject_m_iMaxHealth(CBaseObject* ent);

bool *prop_CTFGameRules_m_bPlayingMedieval(CTFGameRules* ent);
float *prop_CTFGameRules_m_flRestartRoundTime(CTFGameRules* ent);
int *prop_CTFGameRules_m_iRoundState(CTFGameRules* ent);
int *prop_CTFGameRules_m_nGameType(CTFGameRules* ent);

bool *prop_CCurrencyPack_m_bDistributed(CCurrencyPack* ent);


/* extracted entprops */

CTFPlayer* *prop_CTFPlayerShared_m_pOuter(CTFPlayerShared* ent);

int *prop_CTFBot_m_nMission(CTFBot* ent);
EHANDLE *prop_CTFBot_m_hSBTarget(CTFBot* ent);


void entprop_init(void);


/* useful stuff for extracting entprop offsets from code */

#define ANY_BYTE  0x00,
#define ANY_WORD  0x00, 0x00,
#define ANY_DWORD 0x00, 0x00, 0x00, 0x00,

#define NOP_1BYTE 0x00,
#define NOP_3BYTE 0x00, 0x00, 0x00,
#define NOP_7BYTE 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,


#define EXTRACT_CHECK(_name) \
	if (_name != 0) { \
		if (off == 0) { \
			off = _name; \
			pr_debug("%s: %s OK\n", __func__, #_name); \
		} else if (_name != off) { \
			pr_err("%s: %s MISMATCH: %04x vs %04x\n", __func__, #_name, off, _name); \
			fail = true; \
		} else { \
			pr_debug("%s: %s OK\n", __func__, #_name); \
		} \
	} else { \
		pr_warn("%s: %s FAIL\n", __func__, #_name); \
	}


bool entprop_extract_verify_runs(void *func,
	size_t check_base, uint8_t check[],
	int num_runs, size_t runs[][2]);
bool entprop_extract_ensure_match(const char *caller,
	int num_offs, size_t offs[]);


#endif
