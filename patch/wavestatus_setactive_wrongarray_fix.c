#include "all.h"


PATCH(wavestatus_setactive_wrongarray_fix);
/* CTFObjectiveResource::SetMannVsMachineWaveClassActive has a typo error,
 * such that for indexes 12-23, it modifies the m_nMannVsMachineWaveClassCounts2
 * instead of m_bMannVsMachineWaveClassActive2 as it should */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFObjectiveResource",
		"m_nMannVsMachineWaveClassCounts2");
	
	uintptr_t off2 = calc_relative_jump(CTFObjectiveResource_SetMannVsMachineWaveClassActive, 0x0094,
		CBaseEntity_NetworkStateChanged);
	
	
	size_t check1_base = 0x0080;
	uint8_t check1[] = {
		0x8d, 0x84, 0x0e, CONV_LE(off1)     // +0080  lea eax,[esi+ecx*1+m_nMannVsMachineWaveClassCounts2]
		0x81, 0xe7, 0xff, 0x00, 0x00, 0x00, // +0087  and edi,0xff
		0x89, 0x34, 0x24,                   // +008D  mov DWORD PTR [esp],esi
		0x89, 0x44, 0x24, 0x04,             // +0090  mov DWORD PTR [esp+0x4],eax
		0xe8, CONV_LE(off2)                 // +0094  call CBaseEntity::NetworkStateChanged(void*)
		0x89, 0xbc, 0x9e, CONV_LE(off1)     // +0099  mov DWORD PTR [esi+ebx*4+m_nMannVsMachineWaveClassCounts2],edi
	};
	
	
	bool result = true;
	if (!func_verify(CTFObjectiveResource_SetMannVsMachineWaveClassActive,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	uintptr_t off1 = sendprop_offset("CTFObjectiveResource",
		"m_bMannVsMachineWaveClassActive2");
	
	uintptr_t off2 = calc_relative_jump(CTFObjectiveResource_SetMannVsMachineWaveClassActive, 0x0092,
		CBaseEntity_NetworkStateChanged);
	
	
	/*  */
	size_t data1_base = 0x0080;
	uint8_t data1[] = {
		0x8d, 0x84, 0x1e, CONV_LE(off1)     // +0080  lea eax,[esi+ebx*1+m_bMannVsMachineWaveClassActive2]
		0x90, 0x90, 0x90, 0x90,             // +0087  nop nop nop nop
		0x89, 0x34, 0x24,                   // +008B  mov DWORD PTR [esp],esi
		0x89, 0x44, 0x24, 0x04,             // +008E  mov DWORD PTR [esp+0x4],eax
		0xe8, CONV_LE(off2)                 // +0092  call CBaseEntity::NetworkStateChanged(void*)
		0x89, 0xf8,                         // +0097  mov eax,edi
		0x88, 0x84, 0x1e, CONV_LE(off1)     // +0099  mov BYTE PTR [esi+ebx*1+m_bMannVsMachineWaveClassActive2],al
	};
	
	
	func_write(CTFObjectiveResource_SetMannVsMachineWaveClassActive,
		data1_base, sizeof(data1), data1);
}
