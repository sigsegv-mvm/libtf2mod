#include "all.h"


static int vidx_CBasePlayer_IsBot         = -1;
static int vidx_CTFWeaponBase_GetWeaponID = -1;


static int vtable_find_index(const char *sym_name, void *pfunc)
{
	void **vtable;
	size_t size;
	
	symtab_obj_absolute(sym_name, (void **)&vtable, &size);
	
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


int vtable_find_offset(const char *sym_name, void *pfunc)
{
	int idx = vtable_find_index(sym_name, pfunc);
	
	if (idx != -1) {
		return 4 * idx;
	} else {
		return idx;
	}
}


void vtable_init(void)
{
	assert((vidx_CBasePlayer_IsBot =
		vtable_find_index("_ZTV11CBasePlayer",
		CBasePlayer_IsBot)) != -1);
	
	assert((vidx_CTFWeaponBase_GetWeaponID =
		vtable_find_index("_ZTV13CTFWeaponBase",
		CBasePlayer_IsBot)) != -1);
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
