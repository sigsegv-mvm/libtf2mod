#include "all.h"


PATCH(currencypack_torture);
/* make credits fly toward the scout but never let him actually collect them */


// CTFPowerup::ValidTouch:
//   always return false
// CTFPlayerShared::RadiusCurrencyCollectionCheck:
//   not sure if changes needed


PATCH_CHECK
{
	return false;
}


PATCH_APPLY
{
	/* always return false */
	size_t data1_base = 0x0000;
	uint8_t data1[] = {
		0x31, 0xc0, // +0000  xor eax,eax
		0xc3,       // +0002  ret
	};
	
	func_write(CTFPowerup_ValidTouch,
		data1_base, sizeof(data1), data1);
}
