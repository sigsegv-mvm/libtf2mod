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

DEFINE_ENTPROP(float, CBaseAnimating, m_flModelScale);
DEFINE_ENTPROP(int, CBaseAnimating, m_nSkin);

DEFINE_ENTPROP(unsigned int, CBasePlayer, m_nButtons);

DEFINE_ENTPROP(int, CTFPlayer, m_iClass);

DEFINE_ENTPROP(bool, CBaseObject, m_bBuilding);
DEFINE_ENTPROP(bool, CBaseObject, m_bDisposableBuilding);
DEFINE_ENTPROP(bool, CBaseObject, m_bMiniBuilding);
DEFINE_ENTPROP(int, CBaseObject, m_iMaxHealth);

DEFINE_ENTPROP(bool, CTFGameRules, m_bPlayingMedieval);

DEFINE_ENTPROP(bool, CCurrencyPack, m_bDistributed);


/* extracted entprops */

DEFINE_EXTRACTED(int, CTFBot, m_nMission);


void entprop_init(void)
{
	INIT_SENDPROP(CBaseAnimating_m_flModelScale,
		CBaseAnimating, m_flModelScale);
	INIT_SENDPROP(CBaseAnimating_m_nSkin,
		CBaseAnimating, m_nSkin);
	
	INIT_DATAMAP(CBasePlayer_m_nButtons,
		CBasePlayer, m_nButtons);
	
	INIT_SENDPROP2(CTFPlayer_m_iClass,
		CTFPlayer, m_PlayerClass, m_iClass);
	
	INIT_SENDPROP(CBaseObject_m_bBuilding,
		CBaseObject, m_bBuilding);
	INIT_SENDPROP(CBaseObject_m_bDisposableBuilding,
		CBaseObject, m_bDisposableBuilding);
	INIT_SENDPROP(CBaseObject_m_bMiniBuilding,
		CBaseObject, m_bMiniBuilding);
	INIT_DATAMAP(CBaseObject_m_iMaxHealth,
		CBaseObject, m_iMaxHealth);
	
	INIT_SENDPROP(CTFGameRules_m_bPlayingMedieval,
		CTFGameRulesProxy, m_bPlayingMedieval);
	
	INIT_SENDPROP(CCurrencyPack_m_bDistributed,
		CCurrencyPack, m_bDistributed);
	
	
	INIT_EXTRACTED(CTFBot_m_nMission);
}
