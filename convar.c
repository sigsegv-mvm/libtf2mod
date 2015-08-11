#include "all.h"


static void cmd_callback2(CCommand const* args)
{
	UTIL_LogPrintf("[CMD] sigsegv_statreset2\n");
	
	CTFPlayer *player = UTIL_PlayerByIndex(2);
	CTFGameStats_ResetPlayerStats(CTF_GameStats, player);
}

static void cmd_callback3(CCommand const* args)
{
	UTIL_LogPrintf("[CMD] sigsegv_statreset3\n");
	
	CTFPlayer *player = UTIL_PlayerByIndex(3);
	CTFGameStats_ResetPlayerStats(CTF_GameStats, player);
}


uint8_t cmd2[1024];
uint8_t cmd3[1024];


void convars(void)
{
	ConCommand_ctor(&cmd2, "sigsegv_statreset2", &cmd_callback2, NULL, 0, NULL);
	ConCommand_ctor(&cmd3, "sigsegv_statreset3", &cmd_callback3, NULL, 0, NULL);
}
