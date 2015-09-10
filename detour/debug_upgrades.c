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


static void detour_CTFPlayer_RememberUpgrade(CTFPlayer* this, int class, CEconItemView* item, int upgrade, int cost, bool sell)
{
	pr_info("CTFPlayer::RememberUpgrade");
	pr_debug("(player:%d, class:%d, item:%08x, upgrade:%d, cost:%d, sell:%s)\n",
		ENTINDEX(this),
		class,
		(uintptr_t)item,
		upgrade,
		cost,
		(sell ? "TRUE" : "FALSE"));
	
	
	trampoline_CTFPlayer_RememberUpgrade(this, class, item, upgrade, cost, sell);
}

static unsigned short detour_CUpgrades_ApplyUpgradeToItem(CUpgrades* this, CTFPlayer* player, CEconItemView* item, int upgrade, int cost, bool sell, bool b2)
{
	unsigned short result = trampoline_CUpgrades_ApplyUpgradeToItem(this, player, item, upgrade, cost, sell, b2);
	
	
	pr_info("CUpgrades::ApplyUpgradeToItem");
	pr_debug("(player:%d, item:%08x, upgrade:%d, cost:%d, sell:%s, b2:%s) = %04x\n",
		ENTINDEX(player),
		(uintptr_t)item,
		upgrade,
		cost,
		(sell ? "TRUE" : "FALSE"),
		(b2 ? "TRUE" : "FALSE"),
		result);
	
	return result;
}

static void detour_CUpgrades_NotifyItemOnUpgrade(CUpgrades* this, CTFPlayer* player, unsigned short attr, bool sell)
{
	pr_info("CUpgrades::NotifyItemOnUpgrade");
	pr_debug("(player:%d, attr:%d, sell:%s)\n",
		ENTINDEX(player),
		attr,
		(sell ? "TRUE" : "FALSE"));
	
	
	trampoline_CUpgrades_NotifyItemOnUpgrade(this, player, attr, sell);
}

static void detour_CUpgrades_PlayerPurchasingUpgrade(CUpgrades* this, CTFPlayer* player, int slot, int upgrade, bool sell, bool b2, bool b3)
{
	pr_info("CUpgrades::PlayerPurchasingUpgrade");
	pr_debug("(player:%d, slot:%d, upgrade:%d, sell:%s, b2:%s, b3:%s)\n",
		ENTINDEX(player),
		slot,
		upgrade,
		(sell ? "TRUE" : "FALSE"),
		(b2 ? "TRUE" : "FALSE"),
		(b3 ? "TRUE" : "FALSE"));
	
	
	trampoline_CUpgrades_PlayerPurchasingUpgrade(this, player, slot, upgrade, sell, b2, b3);
}

static int detour_CTFGameRules_GetCostForUpgrade(CTFGameRules* this, CMannVsMachineUpgrades* upgrades, int slot, int class, CTFPlayer* player)
{
	int result = trampoline_CTFGameRules_GetCostForUpgrade(this, upgrades, slot, class, player);
	
	
	pr_info("CTFGameRules::GetCostForUpgrade");
	pr_debug("(player:%d, upgrades:%08x, slot:%d, class:%d) = %d\n",
		ENTINDEX(player),
		(uintptr_t)upgrades,
		slot,
		class,
		result);
	
	return result;
}

static bool detour_CTFGameRules_CanUpgradeWithAttrib(CTFGameRules* this, CTFPlayer* player, int slot, unsigned short attr, CMannVsMachineUpgrades* upgrades)
{
	bool result = trampoline_CTFGameRules_CanUpgradeWithAttrib(this, player, slot, attr, upgrades);
	
	
	pr_info("CTFGameRules::CanUpgradeWithAttrib");
	pr_debug("(player:%d, upgrades:%08x, slot:%d, attr:%d) = %s\n",
		ENTINDEX(player),
		(uintptr_t)upgrades,
		slot,
		attr,
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static void detour_CTFPlayer_Regenerate(CTFPlayer* this, bool ammo)
{
	pr_info("CTFPlayer::Regenerate");
	pr_debug("(this:%d, ammo:%s)\n",
		ENTINDEX(this),
		(ammo ? "TRUE" : "FALSE"));
	
	
	trampoline_CTFPlayer_Regenerate(this, ammo);
}

static void detour_CTFPlayer_RemoveCurrency(CTFPlayer* this, int amount)
{
	pr_info("CTFPlayer::RemoveCurrency");
	pr_debug("(this:%d, amount:%d)\n",
		ENTINDEX(this),
		amount);
	
	
	trampoline_CTFPlayer_RemoveCurrency(this, amount);
}

static bool detour_CTFGameRules_IsUpgradeTierEnabled(CTFGameRules* this, CTFPlayer* player, int attr, int upgrade)
{
	bool result = trampoline_CTFGameRules_IsUpgradeTierEnabled(this, player, attr, upgrade);
	
	
	pr_info("CTFGameRules::IsUpgradeTierEnabled");
	pr_debug("(player:%d, attr:%d, upgrade:%d) = %s\n",
		ENTINDEX(player),
		attr,
		upgrade,
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static int detour_CTFGameRules_GetUpgradeTier(CTFGameRules* this, int upgrade)
{
	int result = trampoline_CTFGameRules_GetUpgradeTier(this, upgrade);
	
	
	pr_info("CTFGameRules::GetUpgradeTier");
	pr_debug("(upgrade:%d) = %d\n",
		upgrade,
		result);
	
	return result;
}

static CEconItemView* detour_CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot(CTFPlayer* player, int slot, CEconEntity** item)
{
	CEconItemView* result =
		trampoline_CTFPlayerSharedUtils_GetEconItemViewByLoadoutSlot(player, slot, item);
	
	
	pr_info("CTFPlayerSharedUtils::GetEconItemViewByLoadoutSlot");
	pr_debug("(player:%d, slot:%d, item:%08x) = %08x\n",
		ENTINDEX(player),
		slot,
		(item != NULL ? (uintptr_t)(*item) : 0),
		(uintptr_t)result);
	
	return result;
}

static CEconItemAttributeDefinition* detour_CEconItemSchema_GetAttributeDefinitionByName(CEconItemSchema* this, char const* name)
{
	CEconItemAttributeDefinition* result =
		trampoline_CEconItemSchema_GetAttributeDefinitionByName(this, name);
	
	
	pr_info("CEconItemSchema::GetAttributeDefinitionByName");
	pr_debug("(name:'%s') = %08x\n",
		name,
		(uintptr_t)result);
	
	return result;
}

static int detour_CEconItemView_GetItemDefIndex(CEconItemView* this)
{
	int result = trampoline_CEconItemView_GetItemDefIndex(this);
	
	
	pr_info("CEconItemView::GetItemDefIndex");
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
