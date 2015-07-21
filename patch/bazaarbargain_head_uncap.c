#include "all.h"


PATCH(bazaarbargain_head_uncap);
/* remove the 6-head cap on the Bazaar Bargain */


PATCH_CHECK
{
	size_t check1_base = 0x001a;
	uint8_t check1[] = {
		0x83, 0xf8, 0x05, // +001A  cmp eax,0x5
		0x7f, 0x2d,       // +001D  jg +0x4c
	};
	
	
	bool result = true;
	if (!func_verify(CTFSniperRifleDecap_SniperRifleChargeRateMod,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the jump instruction for heads > 5 */
	func_write_nop(CTFSniperRifleDecap_SniperRifleChargeRateMod,
		0x001d, 2);
}
