#include "all.h"


PATCH(currencypack_no_pull);
/* disable the scout class's credit attraction force */


PATCH_CHECK
{
	uintptr_t off1 = CALC_RELJMP(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		0x04a5, CBaseEntity_ApplyAbsVelocityImpulse);
	
	
	size_t check1_base = 0x04a0;
	uint8_t check1[] = {
		0xe8, CONV_LE(off1) // +04A0  call CBaseEntity::ApplyAbsVelocityImpulse
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* remove call to ApplyAbsVelocityImpulse */
	func_write_nop(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		0x04a0, 5);
}
