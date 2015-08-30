#include "all.h"


DETOUR(profile_attributes);
/*  */


//static unknown_t (*)();


/*static unknown_t detour_()
{
	
}*/


DETOUR_SETUP
{
	//DETOUR_CREATE();
}

// TODO: find best Linux API for precise timers (for use with profiling)

// add detours for these funcs:
// - GetAttribDefinitionByName
// - AttribHookValue<float>
// - AttribHookValue<int>
// get timestamp before; call trampoline; get timestamp after; print delta,
// possibly store average call time
