#include "all.h"


void patch_eh_32targets(void)
{
	pr_special("PATCH: %s\n", __func__);
	
	/* CTFSniperRifle::ExplosiveHeadShot(CTFPlayer*, CTFPlayer*) */
	func_t *func = func_register(
		"_ZN14CTFSniperRifle17ExplosiveHeadShotEP9CTFPlayerS1_");
	
	
	uint8_t check1[] = {
		0x55,                               // +0000  push ebp
		0x89, 0xe5,                         // +0001  mov ebp,esp
		0x57,                               // +0003  push edi
		0x56,                               // +0004  push esi
		0x53,                               // +0005  push ebx
		0x81, 0xec, 0x1c, 0x01, 0x00, 0x00, // +0006  sub esp,0x11c
	};
	
	uint8_t check2[] = {
		0x8d, 0xb5, 0x48, 0xff, 0xff, 0xff, // +0142  lea esi,[ebp-0xb8]
	};
	
	uint8_t check3[] = {
		0xc7, 0x44, 0x24, 0x08, 0x0c, 0x00, 0x00, 0x00, // +0153  mov DWORD PTR [esp+0x8],0xc
	};
	
	
	func_verify(func, 0x0000, sizeof(check1), check1);
	func_verify(func, 0x0142, sizeof(check2), check2);
	func_verify(func, 0x0153, sizeof(check3), check3);
	
	
	/* increase the stack frame allocation from 0x11c to 0x31c */
	uint8_t data1[] = { 0x1c, 0x03, 0x00, 0x00 };
	func_write(func, 0x0008, sizeof(data1), data1);
	
	/* move the entity array local variable from [ebp-0xb8] to [ebp-0x1f0] */
	uint8_t data2[] = { 0x10, 0xfe, 0xff, 0xff };
	func_write(func, 0x0144, sizeof(data2), data2);
	
	/*  increase the array size parameter for CFlaggedEntitiesEnum from 0xc to 0x20 */
	uint8_t data3[] = { 0x20, 0x00, 0x00, 0x00 };
	func_write(func, 0x0157, sizeof(data3), data3);
}
