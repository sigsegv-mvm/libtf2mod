#include "all.h"


PATCH(medicbot_ai_xbow_heal_part1);
/*  */


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)typeinfo_for_CWeaponMedigun;
	
	uintptr_t off2 = (uintptr_t)typeinfo_for_CTFWeaponBase;
	
	uintptr_t off3 = CALC_RELJMP(CTFBotMedicHeal_Update, 0x08e1,
		__dynamic_cast);
	
	
	size_t check1_base = 0x08c1;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +08C1  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, CONV_LE(off1)           // +08C9  mov DWORD PTR [esp+0x8],ds:typeinfo_for_CWeaponMedigun
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off2)           // +08D1  mov DWORD PTR [esp+0x4],ds:typeinfo_for_CTFWeaponBase
		0x89, 0x04, 0x24,                               // +08D9  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off3)                             // +08DC  call __dynamic_cast
		0xc6, 0x85, 0x58, 0xff, 0xff, 0xff, 0x00,       // +08E1  mov BYTE PTR [ebp-0xa8],0x0
		0x85, 0xc0,                                     // +08E8  test eax,eax
		0x89, 0xc3,                                     // +08EA  mov ebx,eax
		0xc6, 0x85, 0x60, 0xff, 0xff, 0xff, 0x01,       // +08EC  mov BYTE PTR [ebp-0xa0],0x1
		0x0f, 0x84, 0x47, 0x01, 0x00, 0x00,             // +08F3  je +0x147
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMedicHeal_Update,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	void *new_func = alloc_func(1);
	
	
	uintptr_t off1 = CALC_RELJMP(CTFBotMedicHeal_Update, 0x08c6,
		new_func);
	
	
	size_t data1_base = 0x08c1;
	uint8_t data1[] = {
		0xe9, CONV_LE(off1)                 // +08C1  jmp new_func
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08C6  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08CC  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08D2  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08D8  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08DE  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08E4  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08EA  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +08F0  nop x 6
		0x90, 0x90, 0x90,                   // +08F6  nop x 3
	};
	
	
	uintptr_t dest_medi = (uintptr_t)CTFBotMedicHeal_Update + 0x08f9;
	uintptr_t dest_xbow = (uintptr_t)CTFBotMedicHeal_Update + 0x19fd;
	uintptr_t dest_fail = (uintptr_t)CTFBotMedicHeal_Update + 0x0a40;
	
	uintptr_t off2 = (uintptr_t)typeinfo_for_CWeaponMedigun;
	
	uintptr_t off3 = (uintptr_t)typeinfo_for_CTFWeaponBase;
	
	uintptr_t off4 = CALC_RELJMP(new_func, 0x0030,
		__dynamic_cast);
	
	uintptr_t off5 = dest_medi - ((uintptr_t)new_func + 0x003b);
	
	uintptr_t off6 = (uintptr_t)typeinfo_for_CTFCrossbow;
	
	uintptr_t off7 = CALC_RELJMP(new_func, 0x005d,
		__dynamic_cast);
	
	uintptr_t off8 = dest_xbow - ((uintptr_t)new_func + 0x0067);
	
	uintptr_t off9 = dest_fail - ((uintptr_t)new_func + 0x006c);
	
	
	/* if the dynamic_cast to CWeaponMedigun failed, then try a dynamic_cast to
	 * CTFCrossbow before giving up completely */
	size_t data2_base = 0x0000;
	uint8_t data2[] = {
		0xc6, 0x85, 0x58, 0xff, 0xff, 0xff, 0x00,       // +0000  mov BYTE PTR [ebp-0xa8],0x0
		0xc6, 0x85, 0x60, 0xff, 0xff, 0xff, 0x01,       // +0007  mov BYTE PTR [ebp-0xa0],0x1
		
		0x89, 0xc3,                                     // +000E  mov ebx,eax
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +0010  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, CONV_LE(off2)           // +0018  mov DWORD PTR [esp+0x8],ds:typeinfo_for_CWeaponMedigun
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off3)           // +0020  mov DWORD PTR [esp+0x4],ds:typeinfo_for_CTFWeaponBase
		0x89, 0x04, 0x24,                               // +0028  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off4)                             // +002B  call __dynamic_cast
		
		0x85, 0xc0,                                     // +0030  test eax,eax
		0x0f, 0x45, 0xd8,                               // +0032  cmovne ebx,eax
		0x0f, 0x85, CONV_LE(off5)                       // +0035  jne dest_medi
		
		0x89, 0xd8,                                     // +003B  mov eax,ebx
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +003D  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, CONV_LE(off6)           // +0045  mov DWORD PTR [esp+0x8],ds:typeinfo_for_CTFCrossbow
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off3)           // +004D  mov DWORD PTR [esp+0x4],ds:typeinfo_for_CTFWeaponBase
		0x89, 0x04, 0x24,                               // +0055  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off7)                             // +0058  call __dynamic_cast
		
		0x85, 0xc0,                                     // +005D  test eax,eax
		0x89, 0xc3,                                     // +005F  mov ebx,eax
		0x0f, 0x85, CONV_LE(off8)                       // +0061  jne dest_xbow
		
		0xe9, CONV_LE(off9)                             // +0067  jmp dest_fail
	};
	
	
	/* modify the original function to jump to our new function */
	func_write(CTFBotMedicHeal_Update,
		data1_base, sizeof(data1), data1);
	
	
	/* write the contents of the new function */
	memcpy(new_func, data2, sizeof(data2));
}
