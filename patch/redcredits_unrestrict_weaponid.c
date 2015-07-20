#include "all.h"


PATCH(redcredits_unrestrict_weaponid);
/* allow red credits to drop from revolver headshots */


static func_t *func1;


PATCH_INIT
{
	/* CTFPlayer::Event_Killed(CTakeDamageInfo const&) */
	func1 = func_register(
		"_ZN9CTFPlayer12Event_KilledERK15CTakeDamageInfo");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_Z27WeaponID_IsSniperRifleOrBowi");
	uintptr_t off1 = calc_relative_jump(func1, 0x089c, dl_baseaddr + sym1.addr);
	
	
	size_t check1_base = 0x089c;
	uint8_t check1[] = {
		0xe8, CONV_LE(off1) // +089C  call WeaponID_IsSniperRifleOrBow
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	void *buf;
	if ((buf = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED) {
		err(1, "mmap for %s failed", __func__);
	}
	
	
	uintptr_t off1 = calc_relative_jump(func1, 0x089c, (uintptr_t)buf);
	
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_Z27WeaponID_IsSniperRifleOrBowi");
	uintptr_t off2 = (dl_baseaddr + sym1.addr) - ((uintptr_t)buf + 0x001b);
	
	
	uint8_t data1[] = {
		0xe8, CONV_LE(off1) // +089C  call buf
	};
	
	/* wrapper function: return true for 0x2b (revolver weapon ID);
	 * otherwise, simply call WeaponID_IsSniperRifleOrBow */
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
	
	
	func_write(func1, 0x089c, sizeof(data1), data1);
	memcpy(buf, data2, sizeof(data2));
}
