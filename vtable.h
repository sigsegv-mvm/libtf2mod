#ifndef _LIBTF2MOD_VTABLE_H
#define _LIBTF2MOD_VTABLE_H


int vtable_find_offset(const char *sym_name, void *pfunc);

void vtable_init(void);

CBaseEntity* vcall_IServerUnknown_GetBaseEntity(IServerUnknown* this);
bool vcall_CBaseEntity_IsPlayer(CBaseEntity* this);
bool vcall_CBasePlayer_IsBot(CBasePlayer* this);
int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this);
INextBot* vcall_INextBotComponent_GetBot(INextBotComponent* this);


#endif
