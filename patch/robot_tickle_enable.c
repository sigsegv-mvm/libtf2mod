#include "all.h"


PATCH(robot_tickle_enable);
/* allow robots to be tickled by the Holiday Punch */


static func_t *func1;


PATCH_INIT
{
	/* CTFPlayer::CanBeForcedToLaugh() */
	func1 = func_register(
		"_ZN9CTFPlayer18CanBeForcedToLaughEv");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_obj_name(&sym1,
		"g_pGameRules");
	uintptr_t off1 = dl_baseaddr + sym1.addr;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                                     // +0000  push ebp
		0x89, 0xe5,                               // +0001  mov ebp,esp
		0x83, 0xec, 0x18,                         // +0003  sub esp,0x18
		0xa1, CONV_LE(off1)                       // +0006  mov eax,ds:g_pGameRules
		0x89, 0x5d, 0xf8,                         // +000B  mov DWORD PTR [ebp-0x8],ebx
		0xbb, 0x01, 0x00, 0x00, 0x00,             // +000E  mov ebx,0x1
		0x89, 0x75, 0xfc,                         // +0013  mov DWORD PTR [ebp-0x4],esi
		0x8b, 0x75, 0x08,                         // +0016  mov esi,DWORD PTR [ebp+0x8]
		0x85, 0xc0,                               // +0019  test eax,eax
		0x74, 0x09,                               // +001B  je +0x9
		0x80, 0xb8, 0x9a, 0x09, 0x00, 0x00, 0x00, // +001D  cmp BYTE PTR [eax+0x99a],0x0
		0x75, 0x12,                               // +0024  jne +0x12
		0x89, 0xd8,                               // +0026  mov eax,ebx
		0x8b, 0x75, 0xfc,                         // +0028  mov esi,DWORD PTR [ebp-0x4]
		0x8b, 0x5d, 0xf8,                         // +002B  mov ebx,DWORD PTR [ebp-0x8]
		0x89, 0xec,                               // +002E  mov esp,ebp
		0x5d,                                     // +0030  pop ebp
		0xc3,                                     // +0031  ret
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the conditional jumps so the function always returns true */
	func_write_nop(func1, 0x001b, 2);
	func_write_nop(func1, 0x0024, 2);
}
