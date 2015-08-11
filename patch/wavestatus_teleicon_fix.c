#include "all.h"


PATCH(wavestatus_teleicon_fix);
/* fix RTR making the teleporter icon stay active on the wave status panel 
 * (this patch relies on a detour) */


PATCH_CHECK
{
	uintptr_t off1 = calc_relative_jump(CObjectTeleporter_FinishedBuilding, 0x001d,
		CBaseEntity_GetTeamNumber);
	
	uintptr_t off2 = (uintptr_t)g_pObjectiveResource;
	
	uintptr_t off3 = calc_relative_jump(CObjectTeleporter_FinishedBuilding, 0x0080,
		CTFObjectiveResource_IncrementTeleporterCount);
	
	
	size_t check1_base = 0x001a;
	uint8_t check1[] = {
		0x89, 0x1c, 0x24,   // +001A  mov [esp],ebx
		0xe8, CONV_LE(off1) // +001D  call CBaseEntity::GetTeamNumber() const
		0x83, 0xf8, 0x03,   // +0022  cmp eax,0x3
		0x74, 0x51,         // +0025  je +0x51
	};
	
	size_t check2_base = 0x0078;
	uint8_t check2[] = {
		0xa1, CONV_LE(off2) // +0078  mov eax,ds:g_pObjectiveResource
		0x89, 0x04, 0x24,   // +007D  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off3) // +0080  call CTFObjectiveResource::IncrementTeleporterCount()
		0xeb, 0xa0,         // +0085  jmp -0x60
	};
	
	
	bool result = true;
	if (!func_verify(CObjectTeleporter_FinishedBuilding,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CObjectTeleporter_FinishedBuilding,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* nop out the unconditional call to CTFObjectiveResource::IncrementTeleporterCount();
	 * we'll do our own conditional call in a detour hook */
	func_write_nop(CObjectTeleporter_FinishedBuilding,
		0x0078, 13);
}
