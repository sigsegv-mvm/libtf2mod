#include "all.h"


DETOUR(wave_reset_countdown_fix);
/* fix tf_mvm_jump_to_wave and the restart game vote causing the wave start
 * countdown timer to silently continue in the background if it was already
 * in the process of counting down when the wave was reset */


static void (*trampoline_CWave_ForceFinish)(CWave* this);


static func_t *func_CPopulationManager_JumpToWave;


static void detour_CWave_ForceFinish(CWave* this)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	if (func_owns_addr(caller1,
		func_CPopulationManager_JumpToWave)) {
		float *m_flRestartRoundTime =
			prop_CTFGameRules_m_flRestartRoundTime(*g_pGameRules);
		
		if (*m_flRestartRoundTime != -1.0f) {
			CGameRulesProxy_NotifyNetworkStateChanged();
			*m_flRestartRoundTime = -1.0f;
		}
	}
	
	
	trampoline_CWave_ForceFinish(this);
}


DETOUR_SETUP
{
	func_CPopulationManager_JumpToWave =
		func_register(CPopulationManager_JumpToWave);
	
	DETOUR_CREATE(CWave_ForceFinish);
	
	return true;
}
