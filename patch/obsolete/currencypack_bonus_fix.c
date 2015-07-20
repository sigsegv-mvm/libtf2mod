#include "all.h"


void patch_currencypack_bonus_fix(void)
{
	pr_special("PATCH: %s\n", __func__);
	
	/* CTFPopulationManager::OnCurrencyPackFade() */
	func_t *func = func_register(
		"_ZN18CPopulationManager18OnCurrencyPackFadeEv");
	
	
	pr_warn("TODO: checks\n");
	uint8_t check[] = {
		
	};
	
	
	/* don't set this[0x280] to zero */
	func_write_nop(func, 0x0030, 7);
}
