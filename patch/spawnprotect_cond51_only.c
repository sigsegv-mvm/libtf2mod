#include "all.h"


PATCH(spawnprotect_cond51_only);
/* remove conds 5 and 8 from robot spawn protection, leaving only cond 51 */


static func_t *func1;


PATCH_INIT
{
	/* CTFBotMainAction::Update(CTFBot*, float) */
	func1 = func_register(
		"_ZN16CTFBotMainAction6UpdateEP6CTFBotf");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_ZN15CTFPlayerShared7AddCondE7ETFCondfP11CBaseEntity");
	uintptr_t off1 = calc_relative_jump(func1, 0x0695, dl_baseaddr + sym1.addr);
	
	symbol_t sym2;
	symtab_func_name(&sym2,
		"_ZN15CTFPlayerShared7AddCondE7ETFCondfP11CBaseEntity");
	uintptr_t off2 = calc_relative_jump(func1, 0x06db, dl_baseaddr + sym2.addr);
	
	
	size_t check1_base = 0x0677;
	uint8_t check1[] = {
		0x8b, 0x45, 0xc8,                               // +0677  mov eax,DWORD PTR [ebp-0x38]
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +067A  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, 0x00, 0x00, 0x00, 0x3f, // +0682  mov DWORD PTR [esp+0x8],0x3f000000
		0xc7, 0x44, 0x24, 0x04, 0x05, 0x00, 0x00, 0x00, // +068A  mov DWORD PTR [esp+0x4],0x5
		0x89, 0x04, 0x24,                               // +0692  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off1)                             // +0695  call CTFPlayerShared::AddCond
	};
	
	size_t check2_base = 0x06bd;
	uint8_t check2[] = {
		0x8b, 0x45, 0xc8,                               // +06BD  mov eax,DWORD PTR [ebp-0x38]
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +06C0  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, 0x00, 0x00, 0x00, 0x3f, // +06C8  mov DWORD PTR [esp+0x8],0x3f000000
		0xc7, 0x44, 0x24, 0x04, 0x08, 0x00, 0x00, 0x00, // +06D0  mov DWORD PTR [esp+0x4],0x8
		0x89, 0x04, 0x24,                               // +06D8  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off2)                             // +06DB  call CTFPlayerShared::AddCond
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(func1, check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out both function calls */
	func_write_nop(func1, 0x0695, 5);
	func_write_nop(func1, 0x06db, 5);
}
