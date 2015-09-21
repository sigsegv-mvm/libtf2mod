#include "all.h"


DETOUR(perf_attr_nomunge);
/* disallow the registration of global attribute modifiers, which are horrible
 * for performance because they call vfprintf, malloc, and free EVERY TIME
 * CAttributeManager::AttribHookValue<T> is called */


static void (*trampoline_CAttributeManager_RegisterGlobalAttributeModifier)(bool (*)(void), void (*)(char const*, CUtlConstStringBase*));


static bool block_mvm;
static bool block_halloween;


static void detour_CAttributeManager_RegisterGlobalAttributeModifier(bool (*f_active)(void), void (*f_munger)(char const*, CUtlConstStringBase*))
{
	pr_info("CAttributeManager::RegisterGlobalAttributeModifier\n");
	
	bool block = false;
	
	if (f_munger == GlobalAttrModifier_MvMAttribHookMunger) {
		if (block_mvm) {
			pr_debug("  not registering "
				"GlobalAttrModifier_MvMAttribHookMunger\n");
			block = true;
		} else {
			pr_debug("  allowing registration of "
				"GlobalAttrModifier_MvMAttribHookMunger\n");
		}
	} else if (f_munger == GlobalAttrModifier_TFHalloweenAttribHookMunger) {
		if (block_halloween) {
			pr_debug("  not registering "
				"GlobalAttrModifier_TFHalloweenAttribHookMunger\n");
			block = true;
		} else {
			pr_debug("  allowing registration of "
				"GlobalAttrModifier_TFHalloweenAttribHookMunger\n");
		}
	} else {
		pr_debug("  allowing registration of unknown attr modifier\n");
		
	}
	
	if (!block) {
		trampoline_CAttributeManager_RegisterGlobalAttributeModifier(f_active,
			f_munger);
	}
}


DETOUR_SETUP
{
	/* only block the mungers if the pre-munging string patches applied okay */
	block_mvm       = patch_perf_attr_premunge_mvm.ok;
	block_halloween = patch_perf_attr_premunge_halloween.ok;
	
	if (!block_mvm) {
		pr_warn("patch_attr_premunge_mvm failed; "
			"won't block mvm munger\n");
	}
	if (!block_halloween) {
		pr_warn("patch_attr_premunge_halloween failed; "
			"won't block halloween munger\n");
	}
	
	if (!block_mvm && !block_halloween) {
		return false;
	}
	
	
	DETOUR_CREATE(CAttributeManager_RegisterGlobalAttributeModifier);
	
	return true;
}
