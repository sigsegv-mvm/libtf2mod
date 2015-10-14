#include "all.h"


DETOUR(init);
/* hook CGameServerDLL::DLLInit so we don't initialize too early */


static bool (*trampoline_CServerGameDLL_DLLInit)(CServerGameDLL* this, void* (*)(char const*, int*), void* (*)(char const*, int*), void* (*)(char const*, int*), CGlobalVars*);


static bool detour_CServerGameDLL_DLLInit(CServerGameDLL* this, void* (*f1)(char const*, int*), void* (*f2)(char const*, int*), void* (*f3)(char const*, int*), CGlobalVars* globals)
{
	bool result = trampoline_CServerGameDLL_DLLInit(this, f1, f2, f3, globals);
	
	tf2mod_init();
	
	return result;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CServerGameDLL_DLLInit);
	
	return true;
}
