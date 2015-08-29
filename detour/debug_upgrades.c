#include "all.h"


DETOUR(debug_upgrades);
/*  */


static void (*trampoline_CTFPlayer_RememberUpgrade)(CTFPlayer* this, int, CEconItemView*, int, int, bool);
static unsigned short (*trampoline_CUpgrades_ApplyUpgradeToItem)(CUpgrades* this, CTFPlayer*, CEconItemView*, int, int, bool, bool);
static void (*trampoline_CUpgrades_NotifyItemOnUpgrade)(CUpgrades* this, CTFPlayer*, unsigned short, bool);
static void (*trampoline_CUpgrades_PlayerPurchasingUpgrade)(CUpgrades* this, CTFPlayer*, int, int, bool, bool, bool);
static int (*trampoline_CTFGameRules_GetCostForUpgrade)(CTFGameRules* this, CMannVsMachineUpgrades*, int, int, CTFPlayer*);
static bool (*trampoline_CTFGameRules_CanUpgradeWithAttrib)(CTFGameRules* this, CTFPlayer*, int, unsigned short, CMannVsMachineUpgrades*);
static void (*trampoline_CTFPlayer_Regenerate)(CTFPlayer* this, bool);
static void (*trampoline_CTFPlayer_RemoveCurrency)(CTFPlayer* this, int);
static bool (*trampoline_CTFGameRules_IsUpgradeTierEnabled)(CTFGameRules* this, CTFPlayer*, int, int);
static int (*trampoline_CTFGameRules_GetUpgradeTier)(CTFGameRules* this, int);
static CEconItemView* (*trampoline_CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot)(CTFPlayer*, int, CEconEntity**);
static CEconItemAttributeDefinition* (*trampoline_CEconItemSchema_GetAttributeDefinitionByName)(CEconItemSchema* this, char const*);
static int (*trampoline_CEconItemView_GetItemDefIndex)(CEconItemView* this);


static void detour_CTFPlayer_RememberUpgrade(CTFPlayer* this, int i1, CEconItemView* item, int i2, int i3, bool b1)
{
	pr_info("CTFPlayer::RememberUpgrade");
	pr_debug("(player:%d, i1:%d, item:%08x, i2:%d, i3:%d, b1:%s)\n",
		ENTINDEX(this),
		i1,
		(uintptr_t)item,
		i2,
		i3,
		(b1 ? "TRUE" : "FALSE"));
	
	
	trampoline_CTFPlayer_RememberUpgrade(this, i1, item, i2, i3, b1);
}

static unsigned short detour_CUpgrades_ApplyUpgradeToItem(CUpgrades* this, CTFPlayer* player, CEconItemView* item, int i1, int i2, bool b1, bool b2)
{
	pr_info("CUpgrades::ApplyUpgradeToItem");
	
	unsigned short result = trampoline_CUpgrades_ApplyUpgradeToItem(this, player, item, i1, i2, b1, b2);
	
	
	pr_debug("(player:%d, item:%08x, i1:%d, i2:%d, b1:%s, b2:%s) = %04x\n",
		ENTINDEX(player),
		(uintptr_t)item,
		i1,
		i2,
		(b1 ? "TRUE" : "FALSE"),
		(b2 ? "TRUE" : "FALSE"),
		result);
	
	return result;
}

static void detour_CUpgrades_NotifyItemOnUpgrade(CUpgrades* this, CTFPlayer* player, unsigned short i1, bool b1)
{
	pr_info("CUpgrades::NotifyItemOnUpgrade");
	pr_debug("(player:%d, i1:%d, b1:%s)\n",
		ENTINDEX(player),
		i1,
		(b1 ? "TRUE" : "FALSE"));
	
	
	trampoline_CUpgrades_NotifyItemOnUpgrade(this, player, i1, b1);
}

static void detour_CUpgrades_PlayerPurchasingUpgrade(CUpgrades* this, CTFPlayer* player, int i1, int i2, bool b1, bool b2, bool b3)
{
	pr_info("CUpgrades::PlayerPurchasingUpgrade");
	pr_debug("(player:%d, i1:%d, i2:%d, b1:%s, b2:%s, b3:%s)\n",
		ENTINDEX(player),
		i1,
		i2,
		(b1 ? "TRUE" : "FALSE"),
		(b2 ? "TRUE" : "FALSE"),
		(b3 ? "TRUE" : "FALSE"));
	
	
	trampoline_CUpgrades_PlayerPurchasingUpgrade(this, player, i1, i2, b1, b2, b3);
}

static int detour_CTFGameRules_GetCostForUpgrade(CTFGameRules* this, CMannVsMachineUpgrades* upgrades, int i1, int i2, CTFPlayer* player)
{
	pr_info("CTFGameRules::GetCostForUpgrade");
	
	int result = trampoline_CTFGameRules_GetCostForUpgrade(this, upgrades, i1, i2, player);
	
	
	pr_debug("(player:%d, upgrades:%08x, i1:%d, i2:%d) = %d\n",
		ENTINDEX(player),
		(uintptr_t)upgrades,
		i1,
		i2,
		result);
	
	return result;
}

static bool detour_CTFGameRules_CanUpgradeWithAttrib(CTFGameRules* this, CTFPlayer* player, int i1, unsigned short i2, CMannVsMachineUpgrades* upgrades)
{
	pr_info("CTFGameRules::CanUpgradeWithAttrib");
	
	bool result = trampoline_CTFGameRules_CanUpgradeWithAttrib(this, player, i1, i2, upgrades);
	
	
	pr_debug("(player:%d, upgrades:%08x, i1:%d, i2:%d) = %s\n",
		ENTINDEX(player),
		(uintptr_t)upgrades,
		i1,
		i2,
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static void detour_CTFPlayer_Regenerate(CTFPlayer* this, bool b1)
{
	pr_info("CTFPlayer::Regenerate");
	pr_debug("(this:%d, b1:%s)\n",
		ENTINDEX(this),
		(b1 ? "TRUE" : "FALSE"));
	
	
	trampoline_CTFPlayer_Regenerate(this, b1);
}

static void detour_CTFPlayer_RemoveCurrency(CTFPlayer* this, int i1)
{
	pr_info("CTFPlayer::RemoveCurrency");
	pr_debug("(this:%d, i1:%d)\n",
		ENTINDEX(this),
		i1);
	
	
	trampoline_CTFPlayer_RemoveCurrency(this, i1);
}

static bool detour_CTFGameRules_IsUpgradeTierEnabled(CTFGameRules* this, CTFPlayer* player, int i1, int i2)
{
	pr_info("CTFGameRules::IsUpgradeTierEnabled");
	
	bool result = trampoline_CTFGameRules_IsUpgradeTierEnabled(this, player, i1, i2);
	
	
	pr_debug("(player:%d, i1:%d, i2:%d) = %s\n",
		ENTINDEX(player),
		i1,
		i2,
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static int detour_CTFGameRules_GetUpgradeTier(CTFGameRules* this, int i1)
{
	pr_info("CTFGameRules::GetUpgradeTier");
	
	int result = trampoline_CTFGameRules_GetUpgradeTier(this, i1);
	
	
	pr_debug("(i1:%d) = %d\n",
		i1,
		result);
	
	return result;
}

static CEconItemView* detour_CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot(CTFPlayer* player, int i1, CEconEntity** item)
{
	pr_info("CTFPlayerSharedUtils::GetEconItemViewByLoadoutSlot");
	
	CEconItemView* result =
		trampoline_CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot(player, i1, item);
	
	
	pr_debug("(player:%d, i1:%d, item:%08x) = %08x\n",
		ENTINDEX(player),
		i1,
		(uintptr_t)(*item),
		(uintptr_t)result);
	
	return result;
}

static CEconItemAttributeDefinition* detour_CEconItemSchema_GetAttributeDefinitionByName(CEconItemSchema* this, char const* name)
{
	pr_info("CEconItemSchema::GetAttributeDefinitionByName");
	
	CEconItemAttributeDefinition* result =
		trampoline_CEconItemSchema_GetAttributeDefinitionByName(this, name);
	
	
	pr_debug("(name:'%s') = %08x\n",
		name,
		(uintptr_t)result);
	
	return result;
}

static int detour_CEconItemView_GetItemDefIndex(CEconItemView* this)
{
	pr_info("CEconItemView::GetItemDefIndex");
	
	int result = trampoline_CEconItemView_GetItemDefIndex(this);
	
	
	pr_debug("(this:%08x) = %d\n",
		(uintptr_t)this,
		result);
	
	return result;
}



DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_RememberUpgrade);
	DETOUR_CREATE(CUpgrades_ApplyUpgradeToItem);
	DETOUR_CREATE(CUpgrades_NotifyItemOnUpgrade);
	DETOUR_CREATE(CUpgrades_PlayerPurchasingUpgrade);
	DETOUR_CREATE(CTFGameRules_GetCostForUpgrade);
	DETOUR_CREATE(CTFGameRules_CanUpgradeWithAttrib);
	DETOUR_CREATE(CTFPlayer_Regenerate);
	DETOUR_CREATE(CTFPlayer_RemoveCurrency);
	DETOUR_CREATE(CTFGameRules_IsUpgradeTierEnabled);
	DETOUR_CREATE(CTFGameRules_GetUpgradeTier);
	DETOUR_CREATE(CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot);
	DETOUR_CREATE(CEconItemSchema_GetAttributeDefinitionByName);
	DETOUR_CREATE(CEconItemView_GetItemDefIndex);
}
