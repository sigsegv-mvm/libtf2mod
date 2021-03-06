#include "all.h"


#define DEFINE_ENTPROP(_type, _class, _prop) \
	static uintptr_t off_ ## _class ## _ ## _prop; \
	_type *prop_ ## _class ## _ ## _prop(_class* ent) { \
		assert(off_ ## _class ## _ ## _prop != 0); \
		return (_type *)((uintptr_t)ent + off_ ## _class ## _ ## _prop); \
	}
#define INIT_SENDPROP(_name, _class, _prop) \
	off_ ## _name = sendprop_offset(#_class, #_prop); \
	assert(off_ ## _name != 0); \
	pr_debug("[netprop] %04x off_" #_name "\n", off_ ## _name);
#define INIT_SENDPROP2(_name, _class, _prop1, _prop2) \
	{ \
		uintptr_t off1 = sendprop_offset(#_class, #_prop1); \
		uintptr_t off2 = sendprop_offset(#_class, #_prop2); \
		off_ ## _name = off1 + off2; \
		assert(off1 != 0); \
		assert(off2 != 0); \
		pr_debug("[netprop] %04x off_" #_name "\n", off_ ## _name); \
	}
#define INIT_DATAMAP(_name, _class, _prop) \
	off_ ## _name = datamap_offset(_class ## _GetDataDescMap(), #_prop); \
	assert(off_ ## _name != 0); \
	pr_debug("[datamap] %04x off_" #_name "\n", off_ ## _name);


#define DEFINE_EXTRACTED(_type, _class, _prop) \
	DEFINE_ENTPROP(_type, _class, _prop) \
	extern uintptr_t entprop_extract_ ## _class ## _ ## _prop(void);
#define INIT_EXTRACTED(_name) \
	off_ ## _name = entprop_extract_ ## _name(); \
	assert(off_ ## _name != 0); \
	pr_debug("[extract] %04x off_" #_name "\n", off_ ## _name);


/* known entprops */

DEFINE_ENTPROP(CCollisionProperty, CBaseEntity, m_Collision);
DEFINE_ENTPROP(char*, CBaseEntity, m_iClassname);
DEFINE_ENTPROP(char*, CBaseEntity, m_iName);

DEFINE_ENTPROP(float, CBaseAnimating, m_flModelScale);
DEFINE_ENTPROP(int, CBaseAnimating, m_nSkin);

DEFINE_ENTPROP(unsigned int, CBasePlayer, m_nButtons);

DEFINE_ENTPROP(CAttributeList, CTFPlayer, m_AttributeList);
DEFINE_ENTPROP(int, CTFPlayer, m_iClass);
DEFINE_ENTPROP(CTFPlayerShared, CTFPlayer, m_Shared);
DEFINE_ENTPROP(char, CTFPlayer, m_szNetname);

DEFINE_ENTPROP(int, CTFPlayerShared, m_iStunFlags);
DEFINE_ENTPROP(int, CTFPlayerShared, m_iStunIndex);

DEFINE_ENTPROP(float, CTFWeaponBaseGun, m_flNextPrimaryAttack);

DEFINE_ENTPROP(bool, CBaseObject, m_bBuilding);
DEFINE_ENTPROP(bool, CBaseObject, m_bDisposableBuilding);
DEFINE_ENTPROP(bool, CBaseObject, m_bMiniBuilding);
DEFINE_ENTPROP(int, CBaseObject, m_iMaxHealth);

DEFINE_ENTPROP(bool, CTFGameRules, m_bAwaitingReadyRestart);
DEFINE_ENTPROP(bool, CTFGameRules, m_bInWaitingForPlayers);
DEFINE_ENTPROP(bool, CTFGameRules, m_bPlayingMedieval);
DEFINE_ENTPROP(float, CTFGameRules, m_flRestartRoundTime);
DEFINE_ENTPROP(int, CTFGameRules, m_iRoundState);
DEFINE_ENTPROP(int, CTFGameRules, m_nGameType);

DEFINE_ENTPROP(bool, CCurrencyPack, m_bDistributed);


/* extracted entprops */

DEFINE_EXTRACTED(CTFPlayer*, CTFPlayerShared, m_pOuter);
DEFINE_EXTRACTED(int, CTFBot, m_nMission);
DEFINE_EXTRACTED(EHANDLE, CTFBot, m_hSBTarget);


void entprop_init(void)
{
	INIT_SENDPROP(CBaseEntity_m_Collision,
		CBaseEntity, m_Collision);
	INIT_DATAMAP(CBaseEntity_m_iClassname,
		CBaseEntity, m_iClassname);
	INIT_DATAMAP(CBaseEntity_m_iName,
		CBaseEntity, m_iName);
	
	INIT_SENDPROP(CBaseAnimating_m_flModelScale,
		CBaseAnimating, m_flModelScale);
	INIT_SENDPROP(CBaseAnimating_m_nSkin,
		CBaseAnimating, m_nSkin);
	
	INIT_DATAMAP(CBasePlayer_m_nButtons,
		CBasePlayer, m_nButtons);
	
	INIT_SENDPROP(CTFPlayer_m_AttributeList,
		CTFPlayer, m_AttributeList);
	INIT_SENDPROP2(CTFPlayer_m_iClass,
		CTFPlayer, m_PlayerClass, m_iClass);
	INIT_SENDPROP(CTFPlayer_m_Shared,
		CTFPlayer, m_Shared);
	INIT_DATAMAP(CTFPlayer_m_szNetname,
		CTFPlayer, m_szNetname);
	
	INIT_SENDPROP(CTFPlayerShared_m_iStunFlags,
		CTFPlayer, m_iStunFlags);
	INIT_SENDPROP(CTFPlayerShared_m_iStunIndex,
		CTFPlayer, m_iStunIndex);
	
	INIT_SENDPROP(CTFWeaponBaseGun_m_flNextPrimaryAttack,
		CTFWeaponBaseGun, m_flNextPrimaryAttack);
	
	INIT_SENDPROP(CBaseObject_m_bBuilding,
		CBaseObject, m_bBuilding);
	INIT_SENDPROP(CBaseObject_m_bDisposableBuilding,
		CBaseObject, m_bDisposableBuilding);
	INIT_SENDPROP(CBaseObject_m_bMiniBuilding,
		CBaseObject, m_bMiniBuilding);
	INIT_DATAMAP(CBaseObject_m_iMaxHealth,
		CBaseObject, m_iMaxHealth);
	
	INIT_SENDPROP(CTFGameRules_m_bAwaitingReadyRestart,
		CTFGameRulesProxy, m_bAwaitingReadyRestart);
	INIT_SENDPROP(CTFGameRules_m_bInWaitingForPlayers,
		CTFGameRulesProxy, m_bInWaitingForPlayers);
	INIT_SENDPROP(CTFGameRules_m_bPlayingMedieval,
		CTFGameRulesProxy, m_bPlayingMedieval);
	INIT_SENDPROP(CTFGameRules_m_flRestartRoundTime,
		CTFGameRulesProxy, m_flRestartRoundTime);
	INIT_SENDPROP(CTFGameRules_m_iRoundState,
		CTFGameRulesProxy, m_iRoundState);
	INIT_SENDPROP(CTFGameRules_m_nGameType,
		CTFGameRulesProxy, m_nGameType);
	
	INIT_SENDPROP(CCurrencyPack_m_bDistributed,
		CCurrencyPack, m_bDistributed);
	
	
	INIT_EXTRACTED(CTFPlayerShared_m_pOuter);
	
	INIT_EXTRACTED(CTFBot_m_nMission);
	INIT_EXTRACTED(CTFBot_m_hSBTarget);
}


bool entprop_extract_verify_runs(void *func,
	size_t check_base, uint8_t check[],
	int num_runs, size_t runs[][2])
{
	bool result = true;
	
	for (int i = 0; i < num_runs; ++i) {
		size_t run_off = runs[i][0];
		size_t run_len = runs[i][1];
		
		assert(run_off >= check_base);
		
		if (!func_verify_quiet(func,
			run_off, run_len, check + (run_off - check_base))) {
			result = false;
			/* don't break so we don't skip any warnings */
		}
	}
	
	return result;
}


bool entprop_extract_ensure_match(const char *caller,
	int num_offs, size_t offs[])
{
	bool mismatch = false;
	for (int i = 1; i < num_offs; ++i) {
		if (offs[i] != offs[i - 1]) {
			mismatch = true;
			break;
		}
	}
	
	if (mismatch) {
		pr_warn("%s: mismatch\n", caller);
		for (int i = 0; i < num_offs; ++i) {
			pr_debug("  %d: %04x\n", i, offs[i]);
		}
	}
	
	return !mismatch;
}
