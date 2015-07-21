#include "all.h"


PATCH(sniperrifle_chargerate_uncap_classic);
/* remove the 200% maximum charge rate cap */


PATCH_INIT
{
	
}


PATCH_CHECK
{
	size_t check1_base = 0x0146;
	uint8_t check1[] = {
		0xf3, 0x0f, 0x10, 0x45, 0xc4, // +0146  movss xmm0,DWORD PTR [ebp-0x3c]
		0xf3, 0x0f, 0x58, 0x45, 0xe0, // +014B  addss xmm0,DWORD PTR [ebp-0x20]
		0xf3, 0x0f, 0x10, 0xc8,       // +0150  movss xmm1,xmm0
		0x0f, 0x28, 0xc1,             // +0154  movaps xmm0,xmm1
		0x0f, 0x57, 0xc9,             // +0157  xorps xmm1,xmm1
		0xf3, 0x0f, 0x5f, 0xc1,       // +015A  maxss xmm0,xmm1
		0xf3, 0x0f, 0x5d, 0x05,       // +015E  minss xmm0,DWORD PTR [xxxxxxxx]
	};
	
	size_t check2_base = 0x0166;
	uint8_t check2[] = {
		0xf3, 0x0f, 0x11, 0x45, 0xe0, // +0166  movss DWORD PTR [ebp-0x20],xmm0
		0xf3, 0x0f, 0x59, 0x40, 0x10, // +016B  mulss xmm0,DWORD PTR [eax+0x10]
	};
	
	
	bool result = true;
	if (!func_verify(CTFSniperRifleClassic_ItemPostFrame,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFSniperRifleClassic_ItemPostFrame,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the MIN operation */
	func_write_nop(CTFSniperRifleClassic_ItemPostFrame,
		0x015e, 8);
}
