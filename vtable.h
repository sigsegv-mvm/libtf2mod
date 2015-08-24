#ifndef _LIBTF2MOD_VTABLE_H
#define _LIBTF2MOD_VTABLE_H


void vtable_init(void);

int vtable_find_offset(const char *sym_name, void *pfunc);

bool vcall_CBasePlayer_IsBot(CBasePlayer* this);
int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this);


#endif
