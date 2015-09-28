#include "all.h"


DETOUR(soundemitter_override_force_precache);
/* in CSoundEmitterSystem::LevelInitPreEntity, if the map name begins with
 * "mvm", then CSoundEmitterSystemBase::AddSoundOverrides is called 4 times:
 * - "scripts/mvm_level_sounds.txt"
 * - "scripts/mvm_level_sound_tweaks.txt"
 * - "scripts/game_sounds_vo_mvm.txt"
 * - "scripts/game_sounds_vo_mvm_mighty.txt"
 * 
 * however, the bool parameter defaults to not precaching the sound scripts,
 * and scripts/game_sounds_manifest.txt indicates that "mvm_level_sound*.txt"
 * were intended to be precached; the fact that they are not actually being
 * precached is probably responsible for these precache errors in MvM:
 * - "TFPlayer.FlareImpact"
 * - "TFPlayer.FlameOut"
 * - "TFPlayer.MedicChargedDeath"
 * - "Player.Spy_Shield_Break"
 * - "MVM.GiantSoldierRocketShootCrit"
 * 
 * to fix this, we'll intercept calls to AddSoundOverrides and forcibly enable
 * the precache parameter for those sound scripts */


static void (*trampoline_CSoundEmitterSystemBase_AddSoundOverrides)(CSoundEmitterSystemBase* this, char const*, bool);


static const char *scripts_to_cache[] = {
	"scripts/mvm_level_sounds.txt",
	"scripts/mvm_level_sound_tweaks.txt",
	NULL,
};


static void detour_CSoundEmitterSystemBase_AddSoundOverrides(CSoundEmitterSystemBase* this, char const* scriptfile, bool bPreload)
{
	for (const char **s = scripts_to_cache; *s != NULL; ++s) {
		if (strcmp(scriptfile, *s) == 0) {
			pr_debug("CSoundEmitterSystemBase::AddSoundOverrides:\n"
				"  forcing bPreload = true for '%s'\n", scriptfile);
			bPreload = true;
			break;
		}
	}
	
	trampoline_CSoundEmitterSystemBase_AddSoundOverrides(this, scriptfile, bPreload);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CSoundEmitterSystemBase_AddSoundOverrides);
	
	return true;
}
