#include "all.h"


PATCH(sniperrifle_chargerate_uncap_stock);
/* remove the 200% maximum charge rate cap */


PATCH_CHECK
{
	size_t check1_base = 0x026a;
	uint8_t check1[] = {
		0xf3, 0x0f, 0x10, 0x45, 0xa4, // +026A  movss xmm0,DWORD PTR [ebp-0x5c]
		0xf3, 0x0f, 0x58, 0x45, 0xe0, // +026F  addss xmm0,DWORD PTR [ebp-0x20]
		0xf3, 0x0f, 0x10, 0xc8,       // +0274  movss xmm1,xmm0
		0x0f, 0x28, 0xc1,             // +0278  movaps xmm0,xmm1
		0x0f, 0x57, 0xc9,             // +027B  xorps xmm1,xmm1
		0xf3, 0x0f, 0x5f, 0xc1,       // +027E  maxss xmm0,xmm1
		0xf3, 0x0f, 0x5d, 0x05,       // +0282  minss xmm0,DWORD PTR [xxxxxxxx]
	};
	
	size_t check2_base = 0x028a;
	uint8_t check2[] = {
		0xf3, 0x0f, 0x11, 0x45, 0xe0, // +028A  movss DWORD PTR [ebp-0x20],xmm0
		0xf3, 0x0f, 0x59, 0x40, 0x10, // +028F  mulss xmm0,DWORD PTR [eax+0x10]
	};
	
	
	bool result = true;
	if (!func_verify(CTFSniperRifle_ItemPostFrame,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFSniperRifle_ItemPostFrame,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the MIN operation */
	func_write_nop(CTFSniperRifle_ItemPostFrame,
		0x0282, 8);
}
