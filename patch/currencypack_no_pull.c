#include "all.h"


PATCH(currencypack_no_pull);
/* disable the scout class's credit attraction force */


static func_t *func1;


PATCH_INIT
{
	/* CTFPlayerShared::RadiusCurrencyCollectionCheck() */
	func1 = func_register(
		"_ZN15CTFPlayerShared29RadiusCurrencyCollectionCheckEv");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_ZN11CBaseEntity23ApplyAbsVelocityImpulseERK6Vector");
	uintptr_t off1 = calc_relative_jump(func1, 0x04a0, dl_baseaddr + sym1.addr);
	
	
	size_t check1_base = 0x04a0;
	uint8_t check1[] = {
		0xe8, CONV_LE(off1) // +04A0  call CBaseEntity::ApplyAbsVelocityImpulse
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* remove call to ApplyAbsVelocityImpulse */
	func_write_nop(func1, 0x04a0, 5);
}
