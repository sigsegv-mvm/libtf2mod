#include "all.h"


DETOUR(mvm_chat_unrestrict);
/* allow players with any teamnum or life state to chat with each other in MvM
 * mode (but hide chat messages coming from actual bots) */


static bool (*trampoline_CTFPlayer_CanHearAndReadChatFrom)(CTFPlayer* this, CBasePlayer*);


static bool detour_CTFPlayer_CanHearAndReadChatFrom(CTFPlayer* this, CBasePlayer* them)
{
	/* non-MvM: defer to the regular logic */
	if (!CTFGameRules_IsPVEModeActive(*g_pGameRules)) {
		return trampoline_CTFPlayer_CanHearAndReadChatFrom(this, them);
	}
	
	
	/* MvM: allow chat from all players, but block chat from actual bots */
	if (them != NULL && vcall_CBasePlayer_IsBot(them)) {
		return false;
	} else {
		return true;
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CanHearAndReadChatFrom);
	
	return true;
}
