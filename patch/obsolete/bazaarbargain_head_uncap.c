#include "all.h"


PATCH(bazaarbargain_head_uncap);
/* remove the 6-head cap on the Bazaar Bargain */


static func_t *func1;


PATCH_INIT
{
	/* CTFSniperRifleDecap::GetCount() */
	func1 = func_register(
		"_ZN19CTFSniperRifleDecap8GetCountEv");
}


PATCH_CHECK
{
	size_t check1_base = 0x005e;
	uint8_t check1[] = {
		0x8b, 0x86, 0x00, 0x23, 0x00, 0x00, // +005E  mov eax,DWORD PTR [esi+0x2300]
		0xbb, 0x06, 0x00, 0x00, 0x00,       // +0064  mov ebx,0x6
		0x8b, 0x75, 0xfc,                   // +0069  mov esi,DWORD PTR [ebp-0x4]
		0x83, 0xf8, 0x06,                   // +006C  cmp eax,0x6
		0x0f, 0x4e, 0xd8,                   // +006F  cmovle ebx,eax
		0x89, 0xd8,                         // +0072  mov eax,ebx
		0x8b, 0x5d, 0xf8,                   // +0074  mov ebx,DWORD PTR [ebp-0x8]
		0x89, 0xec,                         // +0077  mov esp,ebp
		0x5d,                               // +0079  pop ebp
		0xc3,                               // +007A  ret
	};
	
	
	bool result = true;
	/*if (!func_verify(func1, check1_base, sizeof(check1), check1)) */result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the EBX->EAX move instruction to disable the cap */
	func_write_nop(func1, 0x0072, 2);
}
