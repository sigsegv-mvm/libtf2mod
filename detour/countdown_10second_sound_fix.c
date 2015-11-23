#include "all.h"


DETOUR(countdown_10second_sound_fix);
/* fix a bug created in Gun Mettle where the 10-second countdown announcer lines
 * and music don't play if everyone isn't readied up, due to the
 * "tournament_enablecountdown" event not being fired by the server in that
 * particular case */


static void (*trampoline_ConVar_SetValue_int)(ConVar* this, int);


static func_t *func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState;


static void detour_ConVar_SetValue_int(ConVar* this, int val)
{
	trampoline_ConVar_SetValue_int(this, val);
	
	pr_debug("%s(%08x, %d)\n", "ConVar::SetValue", (uintptr_t)this, val);
	if (this == CONVAR_mp_restartgame && val != 0) {
		pr_debug("  this and val are good\n");
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1,
			func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState)) {
			pr_debug("%s: firing event 'tournament_enablecountdown'\n",
				__func__);
			
			IGameEvent* event = CGameEventManager_CreateEvent(*gameeventmanager,
				"tournament_enablecountdown", false);
			if (event != NULL) {
				CGameEventManager_FireEvent(*gameeventmanager,
					event, false);
			}
		}
	}
}


DETOUR_SETUP
{
	func_CTFGameRules_PlayerReadyStatus_UpdatePlayerState =
		func_register(CTFGameRules_PlayerReadyStatus_UpdatePlayerState);
	
	DETOUR_CREATE(ConVar_SetValue_int);
	
	return true;
}
