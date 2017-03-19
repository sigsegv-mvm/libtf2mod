#include <cstdio>
#include <tier1/convar.h>
#include <datamap.h>
#include <server_class.h>
//#include <basecombatweapon_shared.h>
#include <tier1/utlmap.h>
#include <shareddefs.h>
#include <trace.h>
#include <gametrace.h>
#include <string_t.h>
#include <isaverestore.h>
#include <variant_t.h>
#include <edict.h>
#include <iserverunknown.h>
#include <iservernetworkable.h>
#include <basehandle.h>
#include <ehandle.h>
#include <predictable_entity.h>
#include <entitylist_base.h>
#include <predictableid.h>
#include <util.h>
#include <takedamageinfo.h>
#include <touchlink.h>
#include <groundlink.h>
#include <networkvar.h>
#include <baseentity_shared.h>
#include <baseentity.h>
#include <entitylist.h>
#include <entityoutput.h>


#define SIZEOF(_type) \
	printf("%-40s  %-5u  %#-5x\n", "sizeof(" #_type ")", sizeof(_type), sizeof(_type));


int main()
{
	SIZEOF(ConCommandBase)
	SIZEOF(ConCommand)
	puts("");
	
	SIZEOF(ConCommandBase)
	SIZEOF(IConVar)
	SIZEOF(ConVar)
	puts("");
	
	SIZEOF(CCommand)
	puts("");
	
	SIZEOF(FnCommandCallback_t)
	SIZEOF(FnCommandCallbackVoid_t)
	puts("");
	
	SIZEOF(ICommandCallback)
	SIZEOF(ICommandCompletionCallback)
	SIZEOF(IConCommandBaseAccessor)
	puts("");
	
	SIZEOF(ConVarRef)
	puts("");
	
	SIZEOF(SendProp);
	SIZEOF(SendTable);
	SIZEOF(ServerClass);
	puts("");
	
	SIZEOF(typedescription_t);
	SIZEOF(datamap_t);
	puts("");
	
	//SIZEOF(CTakeDamageInfo);
	//SIZEOF(CDmgAccumulator);
	CUtlMap<int, double>* map;
	SIZEOF(*map);
	puts("");
	
	SIZEOF(FireBulletsInfo_t);
	puts("");
	
	SIZEOF(cplane_t);
	SIZEOF(csurface_t);
	SIZEOF(CBaseTrace);
	SIZEOF(CGameTrace);
	puts("");
	
	SIZEOF(COutputEvent);
	puts("");
	
	
	/*ConVar *c = reinterpret_cast<ConVar *>(malloc(4096));
	
	uintptr_t p_start = (uintptr_t)c;
	uintptr_t p_m_pNext = (uintptr_t)&c->m_pNext;
	uintptr_t p_m_pParent = (uintptr_t)&c->m_pParent;
	uintptr_t p_m_fMaxVal = (uintptr_t)&c->m_fMaxVal;
	uintptr_t p_m_fnChangeCallback = (uintptr_t)&c->m_fnChangeCallback;
	printf("ConVar offsets:\n"
		"m_pNext:            %#x\n"
		"m_pParent:          %#x\n"
		"m_fMaxVal:          %#x\n"
		"m_fnChangeCallback: %#x\n",
		p_m_pNext - p_start,
		p_m_pParent - p_start,
		p_m_fMaxVal - p_start,
		p_m_fnChangeCallback - p_start);*/
	
	return 0;
}
