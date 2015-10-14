#include "all.h"


PATCH(playerupgrade_sell_fix);
/* fix a bug added in Gun Mettle that assumes the item defindex should be set to
 * 0 for character upgrades when searching the player's upgrade history, when
 * the index should actually be set to -1 for character upgrades */


PATCH_CHECK
{
	size_t check1_base = 0x01b5;
	uint8_t check1[] = {
		0xc7, 0x85, 0x74, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, // +01B5  mov DWORD PTR [ebp-0x18c],0x0
		0x8b, 0xb5, 0x78, 0xfe, 0xff, 0xff,                         // +01BF  mov esi,DWORD PTR [ebp-0x188]
		0x85, 0xf6,                                                 // +01C5  test esi,esi
		0x74, 0x23,                                                 // +01C7  je +0x23
	};
	
	
	bool result = true;
	if (!func_verify(CUpgrades_PlayerPurchasingUpgrade,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	size_t data1_base = 0x01b5;
	uint8_t data1[] = {
		0xc7, 0x85, 0x74, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, // +01B5  mov DWORD PTR [ebp-0x18c],0xffff
	};
	
	
	/* change the default item index from 0x0000 to 0xffff */
	func_write(CUpgrades_PlayerPurchasingUpgrade,
		data1_base, sizeof(data1), data1);
}
