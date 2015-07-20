#include "all.h"


PATCH(nextprimaryattack_unalias);
/* calculate m_flNextPrimaryAttack based on previous value rather than "now" */


static func_t *func1;


PATCH_INIT
{
	/* CTFWeaponBaseGun::PrimaryAttack() */
	func1 = func_register(
		"_ZN16CTFWeaponBaseGun13PrimaryAttackEv");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_obj_name(&sym1,
		"gpGlobals");
	uintptr_t off1 = dl_baseaddr + sym1.addr;
	
	
	size_t check1_base = 0x028d;
	uint8_t check1[] = {
		0xa1, CONV_LE(off1)                 // +028D  mov eax,ds:gpGlobals
		0x8d, 0x7d, 0xd8,                   // +0292  lea edi,[ebp-0x28]
		0xb9, 0x04, 0x00, 0x00, 0x00,       // +0295  mov ecx,0x4
		0xf3, 0x0f, 0x10, 0x45, 0xc0,       // +029A  movss xmm0,DWORD PTR [ebp-0x40]
		0xf3, 0x0f, 0x58, 0x40, 0x0c,       // +029F  addss xmm0,DWORD PTR [eax+0xc]
		0x8d, 0x83, 0xb4, 0x05, 0x00, 0x00, // +02A4  lea eax,[ebx+0x5b4]
		0x89, 0xc6,                         // +02AA  mov esi,eax
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* make the calculation relative to the previous value of m_flNextPrimaryAttack */
	uint8_t data[] = {
		0x8d, 0x83, 0xb4, 0x05, 0x00, 0x00, // +029A  lea eax,[ebx+0x5b4]
		0xf3, 0x0f, 0x10, 0x45, 0xc0,       // +02A0  movss xmm0,DWORD PTR [ebp-0x40]
		0xf3, 0x0f, 0x58, 0x00,             // +02A5  addss xmm0,DWORD PTR [eax]
		0x90,                               // +02A9  nop
		0x89, 0xc6,                         // +02AA  mov esi,eax
	};
	
	
	func_write(func1, 0x029a, sizeof(data), data);
}
