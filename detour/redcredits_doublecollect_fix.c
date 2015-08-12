#include "all.h"


DETOUR(redcredits_doublecollect_fix);
/* if red credits land in an auto-collection zone, don't distribute the currency
 * value because they have already been collected  */


static unknown_t (*trampoline_CTFGameRules_DistributeCurrencyAmount)(CTFGameRules* this, int, CTFPlayer*, bool, bool, bool);

static uintptr_t off_CCurrencyPack_m_bDistributed;


static unknown_t detour_CTFGameRules_DistributeCurrencyAmount(CTFGameRules* this, int i1, CTFPlayer* player, bool b1, bool b2, bool b3)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	if (func_owns_addr(CCurrencyPack_ComeToRest, caller)) {
		uintptr_t cpack = caller_frame + 0x8;
		bool *m_bDistributed = (bool *)(cpack +
			off_CCurrencyPack_m_bDistributed);
		
		/* if the credits that landed in a trigger_hurt are red credits, then
		 * don't distribute their value to the players */
		if (*m_bDistributed) {
			return 0;
		}
	}
	
	return trampoline_CTFGameRules_DistributeCurrencyAmount(this, i1, player, b1, b2, b3);
}


DETOUR_SETUP
{
	if (off_CCurrencyPack_m_bDistributed == 0) {
		off_CCurrencyPack_m_bDistributed = sendprop_offset(
			"CCurrencyPack", "m_bDistributed");
		
		if (off_CCurrencyPack_m_bDistributed == 0) {
			pr_warn("%s: off_CCurrencyPack_m_bDistributed = 0\n", __func__);
			return;
		}
	}
	
	
	DETOUR_CREATE(CTFGameRules_DistributeCurrencyAmount);
}
