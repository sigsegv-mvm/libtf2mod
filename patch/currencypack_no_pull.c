#include "all.h"


PATCH(currencypack_no_pull);
/* disable the scout class's credit attraction force and make him instantly
 * collect credits like the other classes; keep his bigger radius though */


PATCH_CHECK
{
	uintptr_t off_m_iClass = sendprop_offset("CTFPlayer", "m_PlayerClass") +
		sendprop_offset("CTFPlayer", "m_iClass");
	
	uintptr_t off_gpGlobals = (uintptr_t)gpGlobals;
	
	/* non-public offset in CTFPlayerShared */
	uintptr_t off_nextcheck = 0x0a50;
	
	
	size_t check1_base = 0x0066;
	uint8_t check1[] = {
		0x83, 0xbe, CONV_LE(off_m_iClass) 0x01, // +0066  cmp DWORD PTR [esi+m_PlayerClass+m_iClass],TFCLASS_SCOUT
		0x0f, 0x94, 0x45, 0xcb,                 // +006D  sete BYTE PTR [ebp-0x35]
	};
	
	size_t check2_base = 0x01cc;
	uint8_t check2[] = {
		0x80, 0x7d, 0xcb, 0x00,             // +01CC  cmp BYTE PTR [ebp-0x35],0x0
		0x0f, 0x84, 0x6c, 0x03, 0x00, 0x00, // +01D0  je +0x36c
	};
	
	size_t check3a_base = 0x0329;
	uint8_t check3a[] = {
		0x80, 0x7d, 0xcb, 0x00,             // +0329  cmp BYTE PTR [ebp-0x35],0x0
		0x0f, 0x84, 0x8d, 0x01, 0x00, 0x00, // +032D  je +0x18d
		0xa1, CONV_LE(off_gpGlobals)        // +0333  mov eax,ds:gpGlobals
		0xf3, 0x0f, 0x10, 0x05,             // +0338  movss xmm0,DWORD PTR ds:xxxxxxxx (float: 0.15f)
	};
	
	size_t check3b_base = 0x0340;
	uint8_t check3b[] = {
		0xf3, 0x0f, 0x58, 0x40, 0x0c,                  // +0340  addss xmm0,DWORD PTR [eax+curtime]
		0xf3, 0x0f, 0x11, 0x83, CONV_LE(off_nextcheck) // +0345  movss DWORD PTR [ebx+off_nextcheck],xmm0
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		check2_base, sizeof(check2), check2)) result = false;
	if (!func_verify(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		check3a_base, sizeof(check3a), check3a)) result = false;
	if (!func_verify(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		check3b_base, sizeof(check3b), check3b)) result = false;
	return result;
}


PATCH_APPLY
{
	/* unconditionally jump to the non-scout block that instantly collects
	 * credits instead of making them fly for 1 second */
	size_t data1_base = 0x01cc;
	uint8_t data1[] = {
		0x90, 0x90, 0x90, 0x90, 0x90, // +01CC  nop nop nop nop nop
		0xe9, 0x6c, 0x03, 0x00, 0x00, // +01D1  jmp +0x36c
	};
	
	func_write(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		data1_base, sizeof(data1), data1);
	
	
	/* reduce the delay between checks as scout from 150ms to 30ms */
	static const float delay_scout = 0.030f;
	size_t data2_base = 0x033c;
	const float *data2 = &delay_scout;
	
	func_write(CTFPlayerShared_RadiusCurrencyCollectionCheck,
		data2_base, sizeof(data2), &data2);
}
