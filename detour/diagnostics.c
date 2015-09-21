#include "all.h"


DETOUR(diagnostics);
/* diagnostic traces of various functions */


DETOUR_SETUP
{
	
	
	return true;
}
