#include "all.h"


DETOUR(debug_player_attributes);
/*  */


static ConCommand ccmd_dump_player_attributes;


static void do_ccmd_dump_player_attributes(const CCommand *arg)
{
	const char *player_name = CCommand_Arg(arg, 1);
	if (strcmp(player_name, "") == 0) {
		return;
	}
	
	CTFPlayer* player = UTIL_PlayerByName(player_name);
	if (player == NULL) {
		return;
	}
	
	CAttributeList* attrlist = prop_CTFPlayer_m_AttributeList(player);
	cl_con_printf("%s: m_AttributeList has %d entries:\n",
		player_name, attrlist->m_Attributes.m_Size);
	
	CEconItemAttribute* attrs = attrlist->m_Attributes.m_Memory.m_pMemory;
	for (int i = 0; i < attrlist->m_Attributes.m_Size; ++i) {
		CEconItemAttribute* attr = attrs + i;
		cl_con_printf("  #%d: idx:%d currency:%d value:%f\n",
			i, attr->m_iAttributeDefinitionIndex, attr->m_nRefundableCurrency,
			attr->m_iRawValue32.f);
	}
}


DETOUR_SETUP
{
	ConCommand_ctor(&ccmd_dump_player_attributes,
		"sigsegv_debug_dump_player_attributes", do_ccmd_dump_player_attributes,
		"Debug: show contents of CTFPlayer::m_AttributeList",
		FCVAR_NONE, NULL);
	
	return true;
}
