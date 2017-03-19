#ifndef _LIBTF2MOD_VTABLE_H
#define _LIBTF2MOD_VTABLE_H


int vtable_find_offset(const char *sym_name, void *pfunc);

void vtable_init(void);

CBaseEntity* vcall_IServerUnknown_GetBaseEntity(IServerUnknown* this);

bool vcall_CBaseEntity_IsAlive(CBaseEntity* this);
bool vcall_CBaseEntity_IsPlayer(CBaseEntity* this);

void vcall_CBasePlayer_CommitSuicide(CBasePlayer* this, bool bExplode, bool bForce);
bool vcall_CBasePlayer_IsBot(CBasePlayer* this);

bool vcall_CBaseMultiplayerPlayer_SpeakConceptIfAllowed(CBaseMultiplayerPlayer* this, int iConcept, const char *modifiers, char *pszOutResponseChosen, size_t bufsize, IRecipientFilter* filter);

int vcall_CTFWeaponBase_GetWeaponID(CTFWeaponBase* this);

void vcall_CBaseCombatWeapon_SetWeaponVisible(CBaseCombatWeapon* this, bool visible);

INextBot* vcall_INextBotComponent_GetBot(INextBotComponent* this);

char const* vcall_Action_CTFBot_GetName(Action_CTFBot* this);


#endif
