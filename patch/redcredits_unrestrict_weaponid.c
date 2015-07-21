#include "all.h"


PATCH(redcredits_unrestrict_weaponid);
/* allow red credits to drop from revolver headshots */


PATCH_INIT
{
	
}


PATCH_CHECK
{
	uintptr_t off1 = calc_relative_jump(CTFPlayer_Event_Killed, 0x089c,
		WeaponID_IsSniperRifleOrBow);
	
	
	size_t check1_base = 0x089c;
	uint8_t check1[] = {
		0xe8, CONV_LE(off1) // +089C  call WeaponID_IsSniperRifleOrBow
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_Event_Killed,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	void *new_func = alloc_func(1);
	
	
	uintptr_t off1 = calc_relative_jump(CTFPlayer_Event_Killed, 0x089c,
		new_func);
	
	uintptr_t off2 = (uintptr_t)WeaponID_IsSniperRifleOrBow -
		((uintptr_t)new_func + 0x001b);
	
	
	size_t data1_base = 0x089c;
	uint8_t data1[] = {
		0xe8, CONV_LE(off1) // +089C  call buf
	};
	
	/* wrapper function: return true for 0x2b (revolver weapon ID);
	 * otherwise, simply call WeaponID_IsSniperRifleOrBow */
	size_t data2_base = 0x0000;
	uint8_t data2[] = {
		0x55,                         // +0000  push ebp
		0x89, 0xe5,                   // +0001  mov ebp,esp
		0x83, 0xec, 0x10,             // +0003  sub esp,0x10
		0xb8, 0x01, 0x00, 0x00, 0x00, // +0006  mov eax,1
		0x8b, 0x55, 0x08,             // +000B  mov edx,DWORD PTR [ebp+0x8]
		0x83, 0xfa, 0x2b,             // +000E  cmp edx,0x2b
		0x74, 0x08,                   // +0011  je +0x8
		0x89, 0x14, 0x24,             // +0013  mov DWORD PTR [esp],edx
		0xe8, CONV_LE(off2)           // +0016  call WeaponID_IsSniperRifleOrBow
		0x89, 0xec,                   // +001B  mov esp,ebp
		0x5d,                         // +001D  pop ebp
		0xc3,                         // +001E  ret
	};
	
	
	/* modify the original function to jump to our new function */
	func_write(CTFPlayer_Event_Killed,
		data1_base, sizeof(data1), data1);
	
	
	/* write the contents of the new function */
	memcpy(new_func, data2, sizeof(data2));
}
