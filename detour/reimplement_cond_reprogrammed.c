#include "all.h"


DETOUR(reimplement_cond_reprogrammed);
/* reimplement TF_COND_REPROGRAMMED */


static void (*trampoline_CTFPlayerShared_OnConditionAdded)(CTFPlayerShared* this, ETFCond);
static void (*trampoline_CTFPlayerShared_OnConditionRemoved)(CTFPlayerShared* this, ETFCond);


static void reimpl_CTFPlayerShared_OnAddReprogrammed(CTFPlayerShared* this)
{
	CTFPlayerShared_StunPlayer(this, 5.0f, 0.65f,
		TF_STUNFLAG_NOSOUNDOREFFECT | TF_STUNFLAG_SLOWDOWN, NULL);
	
	CTFPlayer* *m_pOuter = prop_CTFPlayerShared_m_pOuter(this);
	if (*m_pOuter != NULL) {
		CTFPlayer_ForceChangeTeam(*m_pOuter, TFTEAM_RED, false);
	}
}

static void reimpl_CTFPlayerShared_OnRemoveReprogrammed(CTFPlayerShared* this)
{
	CTFPlayer* *m_pOuter = prop_CTFPlayerShared_m_pOuter(this);
	if (*m_pOuter != NULL) {
		CTFPlayer_ForceChangeTeam(*m_pOuter, TFTEAM_BLUE, false);
	}
}


static void detour_CTFPlayerShared_OnConditionAdded(CTFPlayerShared* this, ETFCond cond)
{
	if (cond == TF_COND_REPROGRAMMED) {
		reimpl_CTFPlayerShared_OnAddReprogrammed(this);
	} else {
		trampoline_CTFPlayerShared_OnConditionAdded(this, cond);
	}
}

static void detour_CTFPlayerShared_OnConditionRemoved(CTFPlayerShared* this, ETFCond cond)
{
	if (cond == TF_COND_REPROGRAMMED) {
		reimpl_CTFPlayerShared_OnRemoveReprogrammed(this);
	} else {
		trampoline_CTFPlayerShared_OnConditionRemoved(this, cond);
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayerShared_OnConditionAdded);
	DETOUR_CREATE(CTFPlayerShared_OnConditionRemoved);
	
	return true;
}
