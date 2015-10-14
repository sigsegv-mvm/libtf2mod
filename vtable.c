#include "all.h"


static int vidx_CBaseEntity_GetBaseEntity          = -1;
static int vidx_CBasePlayer_IsBot                  = -1;
static int vidx_CTFWeaponBase_GetWeaponID          = -1;
static int vidx_INextBotComponent_GetBot           = -1;


static int vtable_find_index_mem(void **vtable, size_t size, void *pfunc)
{
	vtable += 2;
	size -= 2 * sizeof(*vtable);
	
	pr_info("%s\n", __func__);
	pr_debug(
		"  vtable @ %08x\n"
		"  size: %04x\n"
		"  (%d entries)\n",
		(uintptr_t)vtable,
		size,
		size / 4);
	
	
	int count = size / 4;
	for (int i = 0; i < count; ++i) {
		if (vtable[i] == pfunc) {
			return i;
		}
	}
	
	return -1;
}

static int vtable_find_index_sym(const char *sym_name, void *pfunc)
{
	void **vtable;
	size_t size;
	symtab_obj_absolute(sym_name, (void **)&vtable, &size);
	
	return vtable_find_index_mem(vtable, size, pfunc);
}


int vtable_find_offset(const char *sym_name, void *pfunc)
{
	int idx = vtable_find_index_sym(sym_name, pfunc);
	
	if (idx != -1) {
		return 4 * idx;
	} else {
		return idx;
	}
}


void vtable_init(void)
{
	assert((vidx_CBaseEntity_GetBaseEntity =
		vtable_find_index_sym("_ZTV11CBaseEntity",
		CBaseEntity_GetBaseEntity)) != -1);
	
	assert((vidx_CBasePlayer_IsBot =
		vtable_find_index_sym("_ZTV11CBasePlayer",
		CBasePlayer_IsBot)) != -1);
	
	assert((vidx_CTFWeaponBase_GetWeaponID =
		vtable_find_index_sym("_ZTV13CTFWeaponBase",
		CTFWeaponBase_GetWeaponID)) != -1);
	
	assert((vidx_INextBotComponent_GetBot =
		vtable_find_index_sym("_ZTV17INextBotComponent",
		INextBotComponent_GetBot)) != -1);
}


CBaseEntity* vcall_IServerUnknown_GetBaseEntity(IServerUnknown* this)
{
	void **vtable = *((void ***)this);
	int vidx = vidx_CBaseEntity_GetBaseEntity;
	assert(vidx != -1);
	
	CBaseEntity* (*vfunc)(IServerUnknown*) = vtable[vidx];
	return vfunc(this);
}


bool vcall_CBasePlayer_IsBot(CBasePlayer* this)
{
	void **vtable = *((void ***)this);
	int vidx = vidx_CBasePlayer_IsBot;
	assert(vidx != -1);
	
	bool (*vfunc)(CBasePlayer*) = vtable[vidx];
	return vfunc(this);
}


int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this)
{
	void **vtable = *((void ***)this);
	int vidx = vidx_CTFWeaponBase_GetWeaponID;
	assert(vidx != -1);
	
	int (*vfunc)(CTFWeaponBase*) = vtable[vidx];
	return vfunc(this);
}


INextBot* vcall_INextBotComponent_GetBot(INextBotComponent* this)
{
	void **vtable = *((void ***)this);
	int vidx = vidx_INextBotComponent_GetBot;
	assert(vidx != -1);
	
	INextBot* (*vfunc)(INextBotComponent*) = vtable[vidx];
	return vfunc(this);
}
