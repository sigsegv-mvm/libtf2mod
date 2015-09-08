#include "all.h"


DETOUR(redcredits_doublecollect_fix);
/* if red credits land in an auto-collection zone, don't distribute the currency
 * value because they have already been collected  */


static unknown_t (*trampoline_CTFGameRules_DistributeCurrencyAmount)(CTFGameRules* this, int, CTFPlayer*, bool, bool, bool);


static func_t *func_CCurrencyPack_ComeToRest;


static unknown_t detour_CTFGameRules_DistributeCurrencyAmount(CTFGameRules* this, int i1, CTFPlayer* player, bool b1, bool b2, bool b3)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	//pr_info("DistributeCurrencyAmount: i1:%d player:%d b1:%s b2:%s b3:%s\n",
	//	i1, ENTINDEX(player),
	//	(b1 ? "TRUE" : "FALSE"),
	//	(b2 ? "TRUE" : "FALSE"),
	//	(b3 ? "TRUE" : "FALSE"));
	
	if (func_owns_addr(caller,
		func_CCurrencyPack_ComeToRest)) {
		CCurrencyPack* cpack = *(CCurrencyPack **)(caller_frame + 0x8);
		bool *m_bDistributed = prop_CCurrencyPack_m_bDistributed(cpack);
		
		//pr_info("cpack->m_bDistributed = %02x\n",
		//	*((uint8_t*)m_bDistributed));
		//pr_info("auto-collect credits: %s\n",
		//	(*m_bDistributed ? "RED" : "GREEN"));
		
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
	func_CCurrencyPack_ComeToRest =
		func_register(CCurrencyPack_ComeToRest);
	
	
	DETOUR_CREATE(CTFGameRules_DistributeCurrencyAmount);
}
