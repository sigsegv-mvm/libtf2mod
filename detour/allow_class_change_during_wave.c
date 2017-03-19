#include "all.h"


DETOUR(allow_class_change_during_wave);
/*  */


static bool (*trampoline_CPopulationManager_IsInEndlessWaves)(CPopulationManager* this);


static func_t *func_CTFPlayer_HandleCommand_JoinClass;


static bool detour_CPopulationManager_IsInEndlessWaves(CPopulationManager* this)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (func_owns_addr(caller1, func_CTFPlayer_HandleCommand_JoinClass)) {
		return true;
	}
	
	return trampoline_CPopulationManager_IsInEndlessWaves(this);
}


DETOUR_SETUP
{
	func_CTFPlayer_HandleCommand_JoinClass =
		func_register(CTFPlayer_HandleCommand_JoinClass);
	
	DETOUR_CREATE(CPopulationManager_IsInEndlessWaves);
	
	return true;
}
