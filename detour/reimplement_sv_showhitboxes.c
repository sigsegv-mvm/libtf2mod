#include "all.h"


DETOUR(reimplement_sv_showhitboxes);
/* re-implement cvar sv_showhitboxes (based on Source SDK 2013) */


static void (*trampoline_CServerGameDLL_PreClientUpdate)(CServerGameDLL* this, bool);


static ConVar sv_showhitboxes;


static void detour_CServerGameDLL_PreClientUpdate(CServerGameDLL* this, bool simulating)
{
	trampoline_CServerGameDLL_PreClientUpdate(this, simulating);
	
	if (ConVar_GetInt(&sv_showhitboxes) == -1) {
		return;
	}
	
	if (ConVar_GetInt(&sv_showhitboxes) == 0) {
		CBaseEntity* pEntity = NULL;
		while ((pEntity = CGlobalEntityList_FindEntityByName(gEntList, pEntity,
			ConVar_GetString(&sv_showhitboxes),
			NULL, NULL, NULL, NULL)) != NULL) {
			CBaseAnimating *anim = DYNAMIC_CAST(pEntity,
				CBaseEntity, CBaseAnimating);
			if (anim != NULL) {
				CBaseAnimating_DrawServerHitboxes(anim, 0.0f, false);
			}
		}
	} else {
		edict_t* edict = CVEngineServer_PEntityOfEntIndex(*engine,
			ConVar_GetInt(&sv_showhitboxes));
		CBaseEntity* pEntity = CBaseEntity_Instance(edict);
		CBaseAnimating* anim = DYNAMIC_CAST(pEntity,
			CBaseEntity, CBaseAnimating);
		
		if (anim != NULL) {
			CBaseAnimating_DrawServerHitboxes(anim, 0.0f, false);
		}
	}
}


DETOUR_SETUP
{
	ConVar_ctor(&sv_showhitboxes, "sv_showhitboxes", "-1", FCVAR_CHEAT,
		"Send server-side hitboxes for specified entity to client (NOTE:  "
		"this uses lots of bandwidth, use on listen server only).");
	
	DETOUR_CREATE(CServerGameDLL_PreClientUpdate);
	
	return true;
}
