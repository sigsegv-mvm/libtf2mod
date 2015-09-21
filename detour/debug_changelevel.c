#include "all.h"


DETOUR(debug_changelevel);
/*  */


static bool (*trampoline_CPopulationManager_IsValidMvMMap)(CPopulationManager* this, char const*);


static bool detour_CPopulationManager_IsValidMvMMap(CPopulationManager* this, char const* map_name)
{
	bool result = trampoline_CPopulationManager_IsValidMvMMap(this, map_name);
	pr_debug("CTFPopulationManager::IsValidMvMMap('%s') = %s\n",
		map_name,
		(result ? "TRUE" : "FALSE"));
	return result;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CPopulationManager_IsValidMvMMap);
	
	return true;
}
