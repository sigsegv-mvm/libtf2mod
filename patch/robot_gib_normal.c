#include "all.h"


PATCH(robot_gib_normal);
/* make robots gib under the same conditions as normal players */


static func_t *func1;


PATCH_INIT
{
	/* CTFBot::ShouldGib(CTakeDamageInfo const&) */
	func1 = func_register(
		"_ZN6CTFBot9ShouldGibERK15CTakeDamageInfo");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_obj_name(&sym1,
		"g_pGameRules");
	uintptr_t off1 = dl_baseaddr + sym1.addr;
	
	symbol_t sym2;
	symtab_func_name(&sym2,
		"_ZN9CTFPlayer9ShouldGibERK15CTakeDamageInfo");
	uintptr_t off2 = calc_relative_jump(func1, 0x001f, dl_baseaddr + sym2.addr);
	
	symbol_t sym3;
	symtab_func_name(&sym3,
		"_ZNK9CTFPlayer10IsMiniBossEv");
	uintptr_t off3 = calc_relative_jump(func1, 0x0029, dl_baseaddr + sym3.addr);
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x8b, 0x15, CONV_LE(off1)                 // +0000  mov edx,DWORD PTR ds:g_pGameRules
		0x55,                                     // +0006  push ebp
		0x89, 0xe5,                               // +0007  mov ebp,esp
		0x8b, 0x45, 0x08,                         // +0009  mov eax,DWORD PTR [ebp+0x8]
		0x8b, 0x4d, 0x0c,                         // +000C  mov ecx,DWORD PTR [ebp+0xc]
		0x80, 0xba, 0x9a, 0x09, 0x00, 0x00, 0x00, // +000F  cmp BYTE PTR [edx+0x99a],0x0
		0x75, 0x10,                               // +0016  jne +0x10
		0x89, 0x4d, 0x0c,                         // +0018  mov DWORD PTR [ebp+0xc],ecx
		0x89, 0x45, 0x08,                         // +001B  mov DWORD PTR [ebp+0x8],eax
		0x5d,                                     // +001E  pop ebp
		0xe9, CONV_LE(off2)                       // +001F  jmp CTFPlayer::ShouldGib
		0x8d, 0x74, 0x26, 0x00,                   // +0024  lea esi,[esi+eiz*1+0x0]
		0x5d,                                     // +0028  pop ebp
		0xe9, CONV_LE(off3)                       // +0029  jmp CTFPlayer::IsMiniBoss
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the conditional jump for MvM mode */
	func_write_nop(func1, 0x0016, 2);
}
