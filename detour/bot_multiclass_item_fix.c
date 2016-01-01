#include "all.h"


DETOUR(bot_multiclass_item_fix);
/* translate multiclass item entity class names into their class specific
 * versions when added thru CTFBot::AddItem (fixes saxxy, shotgun, etc.) */


static CBaseEntity* (*trampoline_CreateEntityByName)(char const*, int);


static func_t *func_CItemGeneration_SpawnItem;
static func_t *func_CItemGeneration_GenerateRandomItem;
static func_t *func_CTFBot_AddItem;


/* don't just call TranslateWeaponEntForClass directly, because doing so will
 * actually break certain useful things (such as giving tf_weapon_parachute to
 * classes other than soldier and demo) */
static const char *_smart_TranslateWeaponEntForClass(const char *name, int classnum)
{
	const char *xlat = TranslateWeaponEntForClass(name, classnum);
	
	/* if TranslateWeaponEntForClass gave us an empty string, return a more
	 * sensible entity class name instead (where possible) */
	if (strcmp(xlat, "") == 0) {
		/* tf_weapon_shotgun: default to tf_weapon_shotgun_primary */
		if (strcasecmp(name, "tf_weapon_shotgun") == 0) {
			return "tf_weapon_shotgun_primary";
		}
		
		/* passthru the original entity class for these cases */
		if (strcasecmp(name, "tf_weapon_pistol") == 0 ||
			strcasecmp(name, "tf_weapon_shovel") == 0 ||
			strcasecmp(name, "tf_weapon_bottle") == 0 ||
			strcasecmp(name, "tf_weapon_parachute") == 0 ||
			strcasecmp(name, "tf_weapon_revolver") == 0) {
			return name;
		}
	}
	
	return xlat;
}


static CBaseEntity* detour_CreateEntityByName(const char *name, int i1)
{
	/* CTFBot::AddItem only knows how to deal with human-readable item names,
	 * not entity class names, so we can't use TranslateWeaponEntForClass in
	 * that function directly
	 * 
	 * we finally get the entity class name 3 calls deep when
	 * CItemGeneration::SpawnItem calls CreateEntityByName, but now we don't
	 * have any context about which player the item is being spawned for, so we
	 * don't know which TF2 player class to translate it for
	 * 
	 * the solution is to do some really ugly stack operations: we translate the
	 * entity class name once we're deep in the call chain at
	 * CreateEntityByName, but we dig through the call stack to figure out what
	 * the this pointer was set to in CTFBot::AddItem's frame
	 * 
	 * this is super ugly, but it's the least ugly way I could think of to make
	 * it actually work
	 */
	
	
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (!func_owns_addr(caller1,
		func_CItemGeneration_SpawnItem)) {
		//pr_debug("%s: fail caller1\n", __func__);
		goto passthru;
	}
	
	uintptr_t caller2 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(1));
	if (!func_owns_addr(caller2,
		func_CItemGeneration_GenerateRandomItem)) {
		//pr_debug("%s: fail caller2\n", __func__);
		goto passthru;
	}
	
	uintptr_t caller3 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(2));
	if (!func_owns_addr(caller3,
		func_CTFBot_AddItem)) {
		//pr_debug("%s: fail caller3\n", __func__);
		goto passthru;
	}
	
	uintptr_t caller3_frame = (uintptr_t)__builtin_frame_address(3);
	CTFBot* bot = *(CTFBot **)(caller3_frame + 0x8);
	int bot_class = *prop_CTFPlayer_m_iClass(bot);
	
	//pr_debug("%s:\n"
	//	"caller3_frame = %08x\n"
	//	"&bot = %08x\n"
	//	"bot = %08x\n"
	//	"class = %d\n",
	//	__func__,
	//	caller3_frame,
	//	caller3_frame + 0x8,
	//	(uintptr_t)bot,
	//	bot_class);
	
	name = _smart_TranslateWeaponEntForClass(name, bot_class);
	
	
passthru:
	return trampoline_CreateEntityByName(name, i1);
}


DETOUR_SETUP
{
	func_CItemGeneration_SpawnItem =
		func_register(CItemGeneration_SpawnItem);
	func_CItemGeneration_GenerateRandomItem =
		func_register(CItemGeneration_GenerateRandomItem);
	func_CTFBot_AddItem =
		func_register(CTFBot_AddItem);
	
	DETOUR_CREATE(CreateEntityByName);
	
	return true;
}
