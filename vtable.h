#ifndef _LIBTF2MOD_VTABLE_H
#define _LIBTF2MOD_VTABLE_H


int vtable_find_offset(const char *sym_name, void *pfunc);

void vtable_init(void);

bool vcall_CBasePlayer_IsBot(CBasePlayer* this);
int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this);


#endif
