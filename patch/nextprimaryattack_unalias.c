#include "all.h"


PATCH(nextprimaryattack_unalias);
/* calculate m_flNextPrimaryAttack based on previous value rather than "now" */
/* BUG: causes sniper rifle to instantly shoot multiple times during one tick,
 * depleting ammo and causing havoc */
/* we should see if we can make a minigun-specific hook/patch instead */


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)gpGlobals;
	
	
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
	if (!func_verify(CTFWeaponBaseGun_PrimaryAttack,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* make the calculation relative to the previous value of m_flNextPrimaryAttack */
	size_t data1_base = 0x029a;
	uint8_t data1[] = {
		0x8d, 0x83, 0xb4, 0x05, 0x00, 0x00, // +029A  lea eax,[ebx+0x5b4]
		0xf3, 0x0f, 0x10, 0x45, 0xc0,       // +02A0  movss xmm0,DWORD PTR [ebp-0x40]
		0xf3, 0x0f, 0x58, 0x00,             // +02A5  addss xmm0,DWORD PTR [eax]
		0x90,                               // +02A9  nop
		0x89, 0xc6,                         // +02AA  mov esi,eax
	};
	
	
	func_write(CTFWeaponBaseGun_PrimaryAttack,
		data1_base, sizeof(data1), data1);
}
