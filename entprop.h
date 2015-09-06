#ifndef _LIBTF2MOD_ENTPROP_H
#define _LIBTF2MOD_ENTPROP_H


float *prop_CBaseAnimating_m_flModelScale(CBaseAnimating* ent);
int *prop_CBaseAnimating_m_nSkin(CBaseAnimating* ent);

int *prop_CTFPlayer_m_iClass(CTFPlayer* ent);

bool *prop_CBaseObject_m_bBuilding(CBaseObject* ent);
bool *prop_CBaseObject_m_bDisposableBuilding(CBaseObject* ent);
bool *prop_CBaseObject_m_bMiniBuilding(CBaseObject* ent);
int *prop_CBaseObject_m_iMaxHealth(CBaseObject* ent);

bool *prop_CTFGameRules_m_bPlayingMedieval(CTFGameRules* ent);

bool *prop_CCurrencyPack_m_bDistributed(CCurrencyPack* ent);


void entprop_init(void);


#endif
