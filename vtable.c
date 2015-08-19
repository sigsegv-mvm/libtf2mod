#include "all.h"


int vtable_find_offset(const char *sym_name, void *pfunc)
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


bool vcall_CBasePlayer_IsBot(CBasePlayer* this)
{
	static int vidx = -1;
	if (vidx == -1) {
		vidx = vtable_find_offset("_ZTV11CBasePlayer",
			CBasePlayer_IsBot);
	}
	assert(vidx != -1);
	
	
	void **vtable = *((void ***)this);
	int (*vfunc)(void*) = vtable[vidx];
	
	return vfunc(this);
}


int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this)
{
	static int vidx = -1;
	if (vidx == -1) {
		vidx = vtable_find_offset("_ZTV13CTFWeaponBase",
			CTFWeaponBase_GetWeaponID);
	}
	assert(vidx != -1);
	
	
	void **vtable = *((void ***)this);
	int (*vfunc)(void*) = vtable[vidx];
	
	return vfunc(this);
}
