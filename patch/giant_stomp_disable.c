#include "all.h"


PATCH(giant_stomp_disable);
/* remove giant robots' ability to insta-destroy non-sentry buildings */


PATCH_CHECK
{
	uintptr_t off1 = calc_relative_jump(CTFBotMainAction_OnContact, 0x00ab,
		CTFPlayer_IsMiniBoss);
	
	
	size_t check1_base = 0x00a8;
	uint8_t check1[] = {
		0x89, 0x3c, 0x24,                   // +00A8  mov DWORD PTR [esp],edi
		0xe8, CONV_LE(off1)                 // +00AB  call CTFPlayer::IsMiniBoss
		0x84, 0xc0,                         // +00B0  test al,al
		0x74, 0x8c,                         // +00B2  je -0x74
		0x8b, 0x06,                         // +00B4  mov eax,DWORD PTR [esi]
		0x89, 0x34, 0x24,                   // +00B6  mov DWORD PTR [esp],esi
		0xff, 0x90, 0x50, 0x01, 0x00, 0x00, // +00B9  call DWORD PTR [eax+0x150] CBaseEntity::IsBaseObject
		0x84, 0xc0,                         // +00BF  test al,al
		0x0f, 0x84, 0x79, 0xff, 0xff, 0xff, // +00C1  je -0x87
		0x8b, 0xc0,                         // +00C7  mov eax,DWORD PTR [esi]
		0x89, 0x34, 0x24,                   // +00C9  mov DWORD PTR [esp],esi
		0xff, 0x90, 0x70, 0x0f, 0x00, 0x00, // +00CC  call DWORD PTR [eax+0x570] CBaseObject::GetType
		0x83, 0xf8, 0x02,                   // +00D2  cmp eax,0x2
		0x0f, 0x84, 0x05, 0x01, 0x00, 0x00, // +00D5  je +0x105
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMainAction_OnContact,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* always skip the stomp part of the code */
	size_t data1_base = 0x00d2;
	uint8_t data1[] = {
		0x90, 0x90, 0x90, 0x90,       // +00D2  nop nop nop nop
		0xe9, 0x05, 0x01, 0x00, 0x00, // +00D6  jmp +0x105
	};
	
	
	func_write(CTFBotMainAction_OnContact,
		data1_base, sizeof(data1), data1);
}
