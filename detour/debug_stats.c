#include "all.h"


#define SUPPRESS_TFSTATS_RESETPLAYER  0
#define SUPPRESS_MVMSTATS_RESETPLAYER 0


DETOUR(debug_stats);
/*  */


static unknown_t (*trampoline_CMannVsMachineStats_ResetStats)(CMannVsMachineStats* this);
static unknown_t (*trampoline_CMannVsMachineStats_ResetPlayerEvents)(CMannVsMachineStats* this, CTFPlayer*);

static unknown_t (*trampoline_CTFGameStats_IncrementStat)(CTFGameStats* this, CTFPlayer*, TFStatType_t, int);
static unknown_t (*trampoline_CTFGameStats_ResetPlayerStats)(CTFGameStats* this, CTFPlayer*);


static unknown_t detour_CMannVsMachineStats_ResetStats(CMannVsMachineStats* this)
{
	UTIL_LogPrintf("[STATBUG] CMannVsMachineStats::ResetStats()\n");
	
	pr_info("CMannVsMachineStats::ResetStats:\n");
	pr_debug("  this   = %08x\n", (uintptr_t)this);
	
	pr_debug("  predicted user message:\n"
		"  name: MvMStatsReset (index 55)  payload: (len 0)\n");
	
	return trampoline_CMannVsMachineStats_ResetStats(this);
}

static unknown_t detour_CMannVsMachineStats_ResetPlayerEvents(CMannVsMachineStats* this, CTFPlayer* player)
{
	int entindex = ENTINDEX(player);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	UTIL_LogPrintf("[STATBUG] CMannVsMachineStats::ResetPlayerEvents(player entindex %d)\n", entindex);
	
	pr_info("CMannVsMachineStats::ResetPlayerEvents:\n");
	pr_debug("  this = %08x\n"
		"  player = %08x (entindex %d)\n",
		(uintptr_t)this, (uintptr_t)player, entindex);
	
	uint8_t payload[1];
	
	uint8_t **ptr = (uint8_t **)((uintptr_t)player + 0x20);
	if (ptr == NULL) {
		pr_debug("  player->dword_0x20 is NULL!\n");
		payload[0] = 0x00;
	} else {
		//pr_debug("  player->dword_0x20 = %08x\n", (uintptr_t)ptr);
		//mem_dump(*ptr, 0x270, false);
		uint8_t val = (*ptr)[0x6];
		//pr_debug("  player->dword_0x20->byte_0x6 = %u\n", val);
		payload[0] = val;
	}
	
	pr_debug("  predicted user message:\n"
		"  name: MvMResetPlayerStats (index 57)  payload: (len 1) %02x\n", payload[0]);
	
#if SUPPRESS_MVMSTATS_RESETPLAYER
	pr_warn("SUPPRESSING CMannVsMachineStats::ResetPlayerEvents!!\n");
	return 0;
#else
	return trampoline_CMannVsMachineStats_ResetPlayerEvents(this, player);
#endif
}


static unknown_t detour_CTFGameStats_IncrementStat(CTFGameStats* this, CTFPlayer* player, TFStatType_t type, int amount)
{
	int entindex = ENTINDEX(player);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	UTIL_LogPrintf("[STATBUG] CTFGameStats::IncrementStat(player entindex %d, type %02x, amount %d\n", entindex, type, amount);
	
	pr_info("CTFGameStats::IncrementStat:\n");
	pr_debug("  player = %08x (entindex %d)\n"
		"  type = %02x\n"
		"  amount = %d\n",
		(uintptr_t)player, entindex, type, amount);
	
	return trampoline_CTFGameStats_IncrementStat(this, player, type, amount);
}

static unknown_t detour_CTFGameStats_ResetPlayerStats(CTFGameStats* this, CTFPlayer* player)
{
	int entindex = ENTINDEX(player);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	UTIL_LogPrintf("[STATBUG] CTFGameStats::ResetPlayerStats(player entindex %d)\n", entindex);
	
	pr_info("CTFGameStats::ResetPlayerStats:\n");
	pr_debug("  player = %08x (entindex %d)\n",
		(uintptr_t)player, entindex);
	
#if SUPPRESS_TFSTATS_RESETPLAYER
	pr_warn("SUPPRESSING CTFGameStats::ResetPlayerStats!!\n");
	return 0;
#else
	return trampoline_CTFGameStats_ResetPlayerStats(this, player);
#endif
}


DETOUR_SETUP
{
	DETOUR_CREATE(CMannVsMachineStats_ResetStats);
	DETOUR_CREATE(CMannVsMachineStats_ResetPlayerEvents);
	
	//DETOUR_CREATE(CTFGameStats_IncrementStat);
	DETOUR_CREATE(CTFGameStats_ResetPlayerStats);
}
