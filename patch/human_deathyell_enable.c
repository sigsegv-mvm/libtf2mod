#include "all.h"


PATCH(human_deathyell_enable);
/* make the MvM death sound happen along with regular death yells instead of replacing them */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFGameRulesProxy",
		"m_bPlayingMannVsMachine");
	
	
	size_t check1_base = 0x0024;
	uint8_t check1[] = {
		0x8b, 0x5d, 0xf4, // +0024  mov ebx,DWORD PTR [ebp-0xc]
		0x8b, 0x75, 0xf8, // +0027  mov esi,DWORD PTR [ebp-0x8]
		0x8b, 0x7d, 0xfc, // +002A  mov edi,DWORD PTR [ebp-0x4]
		0x89, 0xec,       // +002D  mov esp,ebp
		0x5d,             // +002F  pop ebp
		0xc3,             // +0030  ret
	};
	
	size_t check2_base = 0x009a;
	uint8_t check2[] = {
		0x80, 0xba, CONV_LE(off1) 0x00,     // +009A  cmp BYTE PTR [edx+m_bPlayingMannVsMachine],0x0
		0x0f, 0x85, 0xc1, 0x01, 0x00, 0x00, // +00A1  jne +0x1c1
	};
	
	size_t check3_base = 0x02a6;
	uint8_t check3[] = {
		0xe9, 0x79, 0xfd, 0xff, 0xff, // +02A6  jmp -0x287
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_DeathSound,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFPlayer_DeathSound,
		check2_base, sizeof(check2), check2)) result = false;
	if (!func_verify(CTFPlayer_DeathSound,
		check3_base, sizeof(check3), check3)) result = false;
	return result;
}


PATCH_APPLY
{
	/* go back to the regular death sound code instead of jumping to the exit */
	uintptr_t target = (0x00a7 - (0x02a6 + 5));
	
	
	func_write(CTFPlayer_DeathSound,
		0x02a7, sizeof(target), &target);
}
