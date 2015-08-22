#include "all.h"


DETOUR(medishield_teamskin_enable);
/* make the medigun shield use the model skin for its team number */


static CTFMedigunShield* (*trampoline_CTFMedigunShield_Create)(CTFPlayer*);

static uintptr_t off_CTFMedigunShield_m_nSkin;


static CTFMedigunShield* detour_CTFMedigunShield_Create(CTFPlayer* player)
{
	//pr_info("CTFMedigunShield::Create\n");
	
	
	CTFMedigunShield* this = trampoline_CTFMedigunShield_Create(player);
	//pr_debug("  this = %08x\n", (uintptr_t)this);
	if (this != NULL) {
		int teamnum = CBaseEntity_GetTeamNumber(this);
		int *m_nSkin = (int *)((uintptr_t)this +
			off_CTFMedigunShield_m_nSkin);
		
		//pr_debug("  teamnum = %d\n", teamnum);
		//pr_debug("  m_nSkin = %d\n", *m_nSkin);
		
		bool changed = false;
		if (teamnum == TFTEAM_RED && *m_nSkin != 0) {
			//pr_debug("  team is RED; changing m_nSkin to 0\n");
			*m_nSkin = 0;
			changed = true;
		} else if (teamnum == TFTEAM_BLUE && *m_nSkin != 1) {
			//pr_debug("  team is BLU; changing m_nSkin to 1\n");
			*m_nSkin = 1;
			changed = true;
		}
		
		if (changed) {
			//pr_debug("  m_nSkin network state changed\n");
			CBaseEntity_NetworkStateChanged(this, m_nSkin);
		}
	}
	
	return this;
}


DETOUR_SETUP
{
	if (off_CTFMedigunShield_m_nSkin == 0) {
		off_CTFMedigunShield_m_nSkin = sendprop_offset(
			"CTFMedigunShield", "m_nSkin");
		
		if (off_CTFMedigunShield_m_nSkin == 0) {
			pr_warn("%s: off_CTFMedigunShield_m_nSkin = 0\n", __func__);
			return;
		}
	}
	
	
	DETOUR_CREATE(CTFMedigunShield_Create);
}
