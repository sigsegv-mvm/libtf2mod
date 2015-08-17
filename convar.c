#include "all.h"


static ConCommand cmd_listmods;


static void callback_listmods(CCommand const* args)
{
	// TODO
}


void convar_init(void)
{
	ConCommand_ctor(&cmd_listmods, "sigsegv_listmods", &callback_listmods,
		NULL, 0, NULL);
}
