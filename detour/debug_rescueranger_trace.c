#include "all.h"


DETOUR(debug_rescueranger_trace);
/*  */


static bool (*trampoline_CTFPlayer_TryToPickupBuilding)(CTFPlayer* this);
static bool (*trampoline_CTFPlayer_CanPickupBuilding)(CTFPlayer* this, CBaseObject*);
static bool (*trampoline_CBulletPenetrateEnum_EnumEntity)(CBulletPenetrateEnum* this, IHandleEntity* ent);
static void (*trampoline_CEngineTrace_ClipRayToEntity)(CEngineTrace* this, Ray_t const*, unsigned int, IHandleEntity*, CGameTrace*);
static void (*trampoline_CEngineTrace_TraceRay)(CEngineTrace* this, Ray_t const*, unsigned int, ITraceFilter*, CGameTrace*);


static ConVar cvar_sigsegv_debug_rescueranger_trace;
static ConVar cvar_sigsegv_debug_rescueranger_trace_hull_fix;
static ConVar cvar_sigsegv_debug_rescueranger_trace_hull_fix2;


static func_t *func_CTFPlayer_TryToPickupBuilding;
static func_t *func_CBulletPenetrateEnum_EnumEntity;


static void _get_ent_info(CBaseEntity* ent, char *dst, size_t len)
{
	if (ent == NULL) {
		strlcpy(dst, "nullptr", len);
	} else {
		const char *m_iClassname = *prop_CBaseEntity_m_iClassname(ent);
		const char *m_iName = *prop_CBaseEntity_m_iName(ent);
		
		snprintf(dst, len,
			"0x%08x [ idx:%d class:\"%s\" name:\"%s\" ]",
			(uintptr_t)ent,
			ENTINDEX(ent),
			(m_iClassname != NULL ? m_iClassname : ""),
			(m_iName != NULL ? m_iName : ""));
	}
}


static bool detour_CTFPlayer_TryToPickupBuilding(CTFPlayer* this)
{
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0) {
		cl_con_printf("CALL CTFPlayer::TryToPickupBuilding\n");
	}
	
	bool result = trampoline_CTFPlayer_TryToPickupBuilding(this);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0) {
		cl_con_printf("RET  CTFPlayer::TryToPickupBuilding: %s\n",
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static bool detour_CTFPlayer_CanPickupBuilding(CTFPlayer* this, CBaseObject* obj)
{
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0) {
		cl_con_printf("CALL CTFPlayer::CanPickupBuilding(0x%08x #%d)\n",
			(uintptr_t)obj, ENTINDEX(obj));
	}
	
	bool result = trampoline_CTFPlayer_CanPickupBuilding(this, obj);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0) {
		cl_con_printf("RET  CTFPlayer::CanPickupBuilding: %s\n",
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}


static bool detour_CBulletPenetrateEnum_EnumEntity(CBulletPenetrateEnum* this, IHandleEntity* ent)
{
	bool result = trampoline_CBulletPenetrateEnum_EnumEntity(this, ent);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0) {
		char ent_info[4096];
		_get_ent_info(ent, ent_info, sizeof(ent_info));
		
		cl_con_printf(
			"[CBulletPenetrateEnum::EnumEntity]\n"
			"  ent:    %s\n"
			"  result: %s\n",
			ent_info,
			(result ? "TRUE" : "FALSE"));
	}
	
	return result;
}

static void detour_CEngineTrace_ClipRayToEntity(CEngineTrace* this, Ray_t const* ray, unsigned int mask, IHandleEntity* ent, CGameTrace* trace)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	bool caller_is_EnumEntity = func_owns_addr(caller1,
		func_CBulletPenetrateEnum_EnumEntity);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace_hull_fix) != 0 &&
		caller_is_EnumEntity) {
		mask &= ~0x40000000;
	}
	
	trampoline_CEngineTrace_ClipRayToEntity(this, ray, mask, ent, trace);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0 &&
		caller_is_EnumEntity) {
		char ent1_info[4096];
		char ent2_info[4096];
		_get_ent_info(ent, ent1_info, sizeof(ent1_info));
		_get_ent_info(trace->m_pEnt, ent2_info, sizeof(ent2_info));
		
		cl_con_printf(
			"[CEngineTrace::ClipRayToEntity from CBulletPenetrateEnum::EnumEntity]\n"
			"  pEnt:                 %s\n"
			"  startpos:             [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"  endpos:               [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"  plane.normal:         [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"       .dist:           %.2f\n"
			"       .type:           0x%02x\n"
			"       .signbits:       0x%02x\n"
			"  fraction:             %4.2f\n"
			"  contents:             0x%08x\n"
			"  dispFlags:            0x%04x\n"
			"  allsolid:             %s\n"
			"  startsolid:           %s\n"
			"  fractionleftsolid:    %4.2f\n"
			"  surface.name:         \"%s\"\n"
			"         .surfaceProps: 0x%04x\n"
			"         .flags:        0x%04x\n"
			"  hitgroup:             %d\n"
			"  physicsbone:          %d\n"
			"  m_pEnt:               %s\n"
			"  hitbox:               %d\n",
			ent1_info,
			trace->base.startpos.x, trace->base.startpos.y, trace->base.startpos.z,
			trace->base.endpos.x, trace->base.endpos.y, trace->base.endpos.z,
			trace->base.plane.normal.x, trace->base.plane.normal.y, trace->base.plane.normal.z,
			trace->base.plane.dist,
			trace->base.plane.type,
			trace->base.plane.signbits,
			trace->base.fraction,
			trace->base.contents,
			trace->base.dispFlags,
			(trace->base.allsolid ? "TRUE" : "FALSE"),
			(trace->base.startsolid ? "TRUE" : "FALSE"),
			trace->fractionleftsolid,
			trace->surface.name,
			trace->surface.surfaceProps,
			trace->surface.flags,
			trace->hitgroup,
			trace->physicsbone,
			ent2_info,
			trace->hitbox);
	}
}

static void detour_CEngineTrace_TraceRay(CEngineTrace* this, Ray_t const* ray, unsigned int mask, ITraceFilter* filter, CGameTrace* trace)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	bool caller_is_TryToPickupBuilding = func_owns_addr(caller1,
		func_CTFPlayer_TryToPickupBuilding);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace_hull_fix2) != 0 &&
		caller_is_TryToPickupBuilding) {
		mask &= ~0x40000000;
	}
	
	trampoline_CEngineTrace_TraceRay(this, ray, mask, filter, trace);
	
	if (ConVar_GetInt(&cvar_sigsegv_debug_rescueranger_trace) != 0 &&
		caller_is_TryToPickupBuilding) {
		char ent_info[4096];
		_get_ent_info(trace->m_pEnt, ent_info, sizeof(ent_info));
		
		cl_con_printf(
			"[CEngineTrace::TraceRay from CTFPlayer::TryToPickupBuilding]\n"
			"  startpos:             [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"  endpos:               [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"  plane.normal:         [ x:%+8.2f y:%+8.2f z:%+8.2f ]\n"
			"       .dist:           %.2f\n"
			"       .type:           0x%02x\n"
			"       .signbits:       0x%02x\n"
			"  fraction:             %4.2f\n"
			"  contents:             0x%08x\n"
			"  dispFlags:            0x%04x\n"
			"  allsolid:             %s\n"
			"  startsolid:           %s\n"
			"  fractionleftsolid:    %4.2f\n"
			"  surface.name:         \"%s\"\n"
			"         .surfaceProps: 0x%04x\n"
			"         .flags:        0x%04x\n"
			"  hitgroup:             %d\n"
			"  physicsbone:          %d\n"
			"  m_pEnt:               %s\n"
			"  hitbox:               %d\n",
			trace->base.startpos.x, trace->base.startpos.y, trace->base.startpos.z,
			trace->base.endpos.x, trace->base.endpos.y, trace->base.endpos.z,
			trace->base.plane.normal.x, trace->base.plane.normal.y, trace->base.plane.normal.z,
			trace->base.plane.dist,
			trace->base.plane.type,
			trace->base.plane.signbits,
			trace->base.fraction,
			trace->base.contents,
			trace->base.dispFlags,
			(trace->base.allsolid ? "TRUE" : "FALSE"),
			(trace->base.startsolid ? "TRUE" : "FALSE"),
			trace->fractionleftsolid,
			trace->surface.name,
			trace->surface.surfaceProps,
			trace->surface.flags,
			trace->hitgroup,
			trace->physicsbone,
			ent_info,
			trace->hitbox);
	}
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sigsegv_debug_rescueranger_trace,
		"sigsegv_debug_rescueranger_trace", "0", FCVAR_NOTIFY,
		"Debug: show trace results from CTFPlayer::TryToPickupBuilding");
	ConVar_ctor(&cvar_sigsegv_debug_rescueranger_trace_hull_fix,
		"sigsegv_debug_rescueranger_trace_hull_fix", "0", FCVAR_NOTIFY,
		"Debug: unset CONTENTS_HITBOX when CBulletPenetrateEnum::EnumEntity calls CEngineTrace::ClipRayToEntity");
	ConVar_ctor(&cvar_sigsegv_debug_rescueranger_trace_hull_fix2,
		"sigsegv_debug_rescueranger_trace_hull_fix2", "0", FCVAR_NOTIFY,
		"Debug: unset CONTENTS_HITBOX when CTFPlayer::TryToPickupBuilding calls CEngineTrace::TraceRay");
	
	func_CTFPlayer_TryToPickupBuilding =
		func_register(CTFPlayer_TryToPickupBuilding);
	func_CBulletPenetrateEnum_EnumEntity =
		func_register(CBulletPenetrateEnum_EnumEntity);
	
	DETOUR_CREATE(CTFPlayer_TryToPickupBuilding);
	DETOUR_CREATE(CTFPlayer_CanPickupBuilding);
	DETOUR_CREATE(CBulletPenetrateEnum_EnumEntity);
	DETOUR_CREATE(CEngineTrace_ClipRayToEntity);
	DETOUR_CREATE(CEngineTrace_TraceRay);
	
	return true;
}
