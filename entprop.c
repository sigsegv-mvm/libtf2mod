#include "all.h"


static uintptr_t off_CBaseAnimating_m_flModelScale;
static uintptr_t off_CBaseAnimating_m_nSkin;

static uintptr_t off_CBaseObject_m_bBuilding;
static uintptr_t off_CBaseObject_m_bDisposableBuilding;
static uintptr_t off_CBaseObject_m_bMiniBuilding;
static uintptr_t off_CBaseObject_m_iMaxHealth;

static uintptr_t off_CCurrencyPack_m_bDistributed;


void entprop_init(void)
{
	assert((off_CBaseAnimating_m_flModelScale =
		sendprop_offset("CBaseAnimating",
			"m_flModelScale")) != 0);
	assert((off_CBaseAnimating_m_nSkin =
		sendprop_offset("CBaseAnimating",
			"m_nSkin")) != 0);
	
	assert((off_CBaseObject_m_bBuilding =
		sendprop_offset("CBaseObject",
			"m_bBuilding")) != 0);
	assert((off_CBaseObject_m_bDisposableBuilding =
		sendprop_offset("CBaseObject",
			"m_bDisposableBuilding")) != 0);
	assert((off_CBaseObject_m_bMiniBuilding =
		sendprop_offset("CBaseObject",
			"m_bMiniBuilding")) != 0);
	assert((off_CBaseObject_m_iMaxHealth =
		datamap_offset(CBaseObject_GetDataDescMap(),
			"m_iMaxHealth")) != 0);
	
	assert((off_CCurrencyPack_m_bDistributed =
		sendprop_offset("CCurrencyPack",
			"m_bDistributed")) != 0);
}


float *prop_CBaseAnimating_m_flModelScale(CBaseAnimating* ent)
{
	assert(off_CBaseAnimating_m_flModelScale != 0);
	return (float *)((uintptr_t)ent + off_CBaseAnimating_m_flModelScale);
}

int *prop_CBaseAnimating_m_nSkin(CBaseAnimating* ent)
{
	assert(off_CBaseAnimating_m_nSkin != 0);
	return (int *)((uintptr_t)ent + off_CBaseAnimating_m_nSkin);
}


bool *prop_CBaseObject_m_bBuilding(CBaseObject* ent)
{
	assert(off_CBaseObject_m_bBuilding != 0);
	return (bool *)((uintptr_t)ent + off_CBaseObject_m_bBuilding);
}

bool *prop_CBaseObject_m_bDisposableBuilding(CBaseObject* ent)
{
	assert(off_CBaseObject_m_bDisposableBuilding != 0);
	return (bool *)((uintptr_t)ent + off_CBaseObject_m_bDisposableBuilding);
}

bool *prop_CBaseObject_m_bMiniBuilding(CBaseObject* ent)
{
	assert(off_CBaseObject_m_bMiniBuilding != 0);
	return (bool *)((uintptr_t)ent + off_CBaseObject_m_bMiniBuilding);
}

int *prop_CBaseObject_m_iMaxHealth(CBaseObject* ent)
{
	assert(off_CBaseObject_m_iMaxHealth != 0);
	return (int *)((uintptr_t)ent + off_CBaseObject_m_iMaxHealth);
}


bool *prop_CCurrencyPack_m_bDistributed(CCurrencyPack* ent)
{
	assert(off_CCurrencyPack_m_bDistributed != 0);
	return (bool *)((uintptr_t)ent + off_CCurrencyPack_m_bDistributed);
}

