#include "all.h"


PATCH(redcredits_doublecollect_fix);
/* if red credits land in an auto-collection zone, don't distribute the currency
 * value because they have already been collected  */


PATCH_CHECK
{
#if 0
	uintptr_t off1 = calc_relative_jump(CCurrencyPack_ComeToRest, 0x00d4,
		CTFGameRules_DistributeCurrencyAmount);
	
	
	size_t check1_base = 0x;
	uint8_t check1[] = {
		
	};
	
	
	bool result = true;
	if (!func_verify(,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
#endif
}


// c96a44:
// overwrite call target with new_func

// new_func:
// cmp BYTE PTR [esi+0x50a],0
// jne L1
// jmp CTFGameRules_DistributeCurrencyAmount
// L1:
// ret


PATCH_APPLY
{
#if 0
	void *new_func = alloc_func(1);
	
	
	uintptr_t off1 = calc_relative_jump(CTFPlayer_OnTakeDamage_Alive, 0x10d7,
		new_func);
	
	
	size_t data1_base = 0x10d7;
	uint8_t data1[] = {
		0xe9, CONV_LE(off1)     // jmp new_func
		0x90, 0x90, 0x90, 0x90, // nop x 4
	};
	
	
	uintptr_t dest_bad  = (uintptr_t)CTFPlayer_OnTakeDamage_Alive + 0x04e9;
	uintptr_t dest_good = (uintptr_t)CTFPlayer_OnTakeDamage_Alive + 0x10e0;
	
	uintptr_t off2 = dest_bad  - ((uintptr_t)new_func + 0x0009);
	uintptr_t off3 = dest_good - ((uintptr_t)new_func + 0x0012);
	uintptr_t off4 = dest_good - ((uintptr_t)new_func + 0x001b);
	uintptr_t off5 = dest_bad  - ((uintptr_t)new_func + 0x0029);
	uintptr_t off6 = dest_bad  - ((uintptr_t)new_func + 0x0036);
	uintptr_t off7 = dest_good - ((uintptr_t)new_func + 0x003b);
	
	
	/* add a test for m_iDamageCustom == 0x22 (bleed) */
	size_t data2_base = 0x0000;
	uint8_t data2[] = {
		0x83, 0xf8, 0x22,                         // +0000  cmp eax,0x22
		0x0f, 0x84, CONV_LE(off2)                 // +0003  je BAD
		0x83, 0xf8, 0x33,                         // +0009  cmp eax,0x33
		0x0f, 0x84, CONV_LE(off3)                 // +000c  je GOOD
		0x83, 0xf8, 0x01,                         // +0012  cmp eax,0x01
		0x0f, 0x84, CONV_LE(off4)                 // +0015  je GOOD
		0x8b, 0x85, 0x48, 0xff, 0xff, 0xff,       // +001b  mov eax,DWORD PTR [ebp-0xb8]
		0x85, 0xc0,                               // +0021  test eax,eax
		0x0f, 0x84, CONV_LE(off5)                 // +0023  je BAD
		0x83, 0xbb, 0xa8, 0x06, 0x00, 0x00, 0x01, // +0029  cmp DWORD PTR [ebx+0x6a8],0x1
		0x0f, 0x85, CONV_LE(off6)                 // +0030  jne BAD
		0xe9, CONV_LE(off7)                       // +0036  jmp GOOD
	};
	
	
	/* modify the original function to jump to our new function */
	func_write(CTFPlayer_OnTakeDamage_Alive,
		data1_base, sizeof(data1), data1);
	
	
	/* write the contents of the new function */
	memcpy(new_func, data2, sizeof(data2));
#endif
}
