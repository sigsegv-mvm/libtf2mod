#include "all.h"


DETOUR(debug_wavecounts);
/* add debug output for CTFObjectiveResource wave count info changes */


static unknown_t (*trampoline_CTFObjectiveResource_AddMannVsMachineWaveClassFlags)(CTFObjectiveResource* this, int, unsigned int);
static unknown_t (*trampoline_CTFObjectiveResource_ClearMannVsMachineWaveClassFlags)(CTFObjectiveResource* this);
static unknown_t (*trampoline_CTFObjectiveResource_DecrementMannVsMachineWaveClassCount)(CTFObjectiveResource* this, string_t, unsigned int);
static unknown_t (*trampoline_CTFObjectiveResource_DecrementTeleporterCount)(CTFObjectiveResource* this);
static int (*trampoline_CTFObjectiveResource_GetMannVsMachineWaveClassCount)(CTFObjectiveResource* this, int);
static unknown_t (*trampoline_CTFObjectiveResource_IncrementMannVsMachineWaveClassCount)(CTFObjectiveResource* this, string_t, unsigned int);
static unknown_t (*trampoline_CTFObjectiveResource_IncrementTeleporterCount)(CTFObjectiveResource* this);
static unknown_t (*trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassActive)(CTFObjectiveResource* this, string_t, bool);
static unknown_t (*trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassCount)(CTFObjectiveResource* this, int, int);
static unknown_t (*trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassName)(CTFObjectiveResource* this, int, string_t);


static unknown_t detour_CTFObjectiveResource_AddMannVsMachineWaveClassFlags(CTFObjectiveResource* this, int index, unsigned int flags)
{
	pr_info("[WaveCount] AddFlags    [idx:%d] = %04x\n", index, flags);
	return trampoline_CTFObjectiveResource_AddMannVsMachineWaveClassFlags(this, index, flags);
}

static unknown_t detour_CTFObjectiveResource_ClearMannVsMachineWaveClassFlags(CTFObjectiveResource* this)
{
	pr_special("[WaveCount] ClearFlags\n");
	return trampoline_CTFObjectiveResource_ClearMannVsMachineWaveClassFlags(this);
}

static unknown_t detour_CTFObjectiveResource_DecrementMannVsMachineWaveClassCount(CTFObjectiveResource* this, string_t name, unsigned int flags)
{
	pr_warn("[WaveCount] -Class      [name:\"%s\" flags:%04x]\n", name.pszValue, flags);
	return trampoline_CTFObjectiveResource_DecrementMannVsMachineWaveClassCount(this, name, flags);
}

static unknown_t detour_CTFObjectiveResource_DecrementTeleporterCount(CTFObjectiveResource* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* get the caller's CObjectTeleporter* this */
	CBaseEntity* caller_this = *(CBaseEntity**)(caller_frame + 8);
	int bldg_entindex = ENTINDEX(caller_this);
	
	
	pr_warn("[WaveCount] -Teleporter [entindex:%d]\n", bldg_entindex);
	return trampoline_CTFObjectiveResource_DecrementTeleporterCount(this);
}

static int detour_CTFObjectiveResource_GetMannVsMachineWaveClassCount(CTFObjectiveResource* this, int index)
{
	int count = trampoline_CTFObjectiveResource_GetMannVsMachineWaveClassCount(this, index);
	pr_debug("[WaveCount] GetCount    [idx:%d] = %d\n", index, count);
	return count;
}

static unknown_t detour_CTFObjectiveResource_IncrementMannVsMachineWaveClassCount(CTFObjectiveResource* this, string_t name, unsigned int flags)
{
	pr_warn("[WaveCount] +Class      [name:\"%s\" flags:%04x]\n", name.pszValue, flags);
	return trampoline_CTFObjectiveResource_IncrementMannVsMachineWaveClassCount(this, name, flags);
}

static unknown_t detour_CTFObjectiveResource_IncrementTeleporterCount(CTFObjectiveResource* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* get the caller's CObjectTeleporter* this */
	CBaseEntity* caller_this = *(CBaseEntity**)(caller_frame + 8);
	int bldg_entindex = ENTINDEX(caller_this);
	
	
	pr_warn("[WaveCount] +Teleporter [entindex:%d]\n", bldg_entindex);
	return trampoline_CTFObjectiveResource_IncrementTeleporterCount(this);
}

static unknown_t detour_CTFObjectiveResource_SetMannVsMachineWaveClassActive(CTFObjectiveResource* this, string_t name, bool active)
{
	pr_special("[WaveCount] %cActive     [name:\"%s\"]\n", (active ? '+' : '-'), name.pszValue);
	return trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassActive(this, name, active);
}

static unknown_t detour_CTFObjectiveResource_SetMannVsMachineWaveClassCount(CTFObjectiveResource* this, int index, int count)
{
	pr_info("[WaveCount] SetCount    [idx:%d] = %d\n", index, count);
	return trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassCount(this, index, count);
}

static unknown_t detour_CTFObjectiveResource_SetMannVsMachineWaveClassName(CTFObjectiveResource* this, int index, string_t name)
{
	pr_special("[WaveCount] SetName     [idx:%d] = \"%s\"\n", index, name.pszValue);
	return trampoline_CTFObjectiveResource_SetMannVsMachineWaveClassName(this, index, name);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFObjectiveResource_AddMannVsMachineWaveClassFlags);
	DETOUR_CREATE(CTFObjectiveResource_ClearMannVsMachineWaveClassFlags);
	DETOUR_CREATE(CTFObjectiveResource_DecrementMannVsMachineWaveClassCount);
	//DETOUR_CREATE(CTFObjectiveResource_DecrementTeleporterCount);
	DETOUR_CREATE(CTFObjectiveResource_GetMannVsMachineWaveClassCount);
	DETOUR_CREATE(CTFObjectiveResource_IncrementMannVsMachineWaveClassCount);
	//DETOUR_CREATE(CTFObjectiveResource_IncrementTeleporterCount);
	DETOUR_CREATE(CTFObjectiveResource_SetMannVsMachineWaveClassActive);
	DETOUR_CREATE(CTFObjectiveResource_SetMannVsMachineWaveClassCount);
	DETOUR_CREATE(CTFObjectiveResource_SetMannVsMachineWaveClassName);
	
	return true;
}
