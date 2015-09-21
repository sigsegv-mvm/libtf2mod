#include "all.h"


DETOUR(profile_attributes);
/*  */


static float (*trampoline_CAttributeManager_AttribHookValue_float)(float, char const*, CBaseEntity const*, CUtlVector*, bool);

static void (*trampoline_GlobalAttrModifier_MvMAttribHookMunger)(char const*, CUtlConstStringBase*);
static void (*trampoline_GlobalAttrModifier_TFHalloweenAttribHookMunger)(char const*, CUtlConstStringBase*);

static CEconItemAttributeDefinition* (*trampoline_CEconItemSchema_GetAttributeDefinitionByName)(CEconItemSchema* this, char const*);
static CEconItemDefinition* (*trampoline_CEconItemSchema_GetItemDefinitionByName)(CEconItemSchema* this, char const*);

static unknown_t (*trampoline_CMannVsMachineUpgradeManager_GetAttributeIndexByName)(CMannVsMachineUpgradeManager* this, char const*);


static FILE *prof_log;


static float detour_CAttributeManager_AttribHookValue_float(float value, char const* name, CBaseEntity const* ent, CUtlVector* v1, bool b1)
{
	static uint64_t callnum = 0;
	static int64_t t_sum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	float result = trampoline_CAttributeManager_AttribHookValue_float(value, name, ent, v1, b1);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		
		t_sum += dt;
		
		if (callnum % 1000 == 0) {
			int64_t t_sum_msec = t_sum / 1000000;
			int64_t t_sum_usec = (t_sum / 1000) % 1000;
			
			struct timespec t_now;
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_now);
			int64_t t_wall = conv_timespec_to_nsec(&t_now);
			
			int64_t t_wall_sec  = t_wall / 1000000000LL;
			int64_t t_wall_msec = (t_wall / 1000000) % 1000;
			
			pr_debug("[PROF:AttribHookValue<float>] "
				"wall %lld.%03lld; %lld calls; %lld.%03lld ms\n",
				t_wall_sec, t_wall_msec, callnum, t_sum_msec, t_sum_usec);
			
			fprintf(prof_log, "AttribHookValue<float>,%llu,,%llu,\n",
				callnum, t_sum);
			fflush(prof_log);
		}
		
		
#if 0
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:AttribHookValue<float>('%s')] %lld.%03lld us\n",
			name, dt_usec, dt_nsec);
		
		fprintf(prof_log, "AttribHookValue<float>,%llu,%lld,,%s\n",
			callnum, dt, name);
		fflush(prof_log);
#endif
	} else {
		pr_warn("[PROF:AttribHookValue<float>('%s')] FAILED\n",
			name);
	}
	++callnum;
	
	
	return result;
}


static void detour_GlobalAttrModifier_MvMAttribHookMunger(char const* s1, CUtlConstStringBase* s2)
{
	static uint64_t callnum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	trampoline_GlobalAttrModifier_MvMAttribHookMunger(s1, s2);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:MvMAttribHookMunger('%s')] %lld.%03lld us\n",
			s1, dt_usec, dt_nsec);
		
		fprintf(prof_log, "MvMAttribHookMunger,%llu,%lld,,%s\n",
			callnum, dt, s1);
		fflush(prof_log);
	} else {
		pr_warn("[PROF:MvMAttribHookMunger('%s')] FAILED\n",
			s1);
	}
	++callnum;
}


static void detour_GlobalAttrModifier_TFHalloweenAttribHookMunger(char const* s1, CUtlConstStringBase* s2)
{
	static uint64_t callnum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	trampoline_GlobalAttrModifier_TFHalloweenAttribHookMunger(s1, s2);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:TFHalloweenAttribHookMunger('%s')] %lld.%03lld us\n",
			s1, dt_usec, dt_nsec);
		
		fprintf(prof_log, "TFHalloweenAttribHookMunger,%llu,%lld,,%s\n",
			callnum, dt, s1);
		fflush(prof_log);
	} else {
		pr_warn("[PROF:TFHalloweenAttribHookMunger('%s')] FAILED\n",
			s1);
	}
	++callnum;
}


static CEconItemAttributeDefinition* detour_CEconItemSchema_GetAttributeDefinitionByName(CEconItemSchema* this, char const* name)
{
	static uint64_t callnum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	CEconItemAttributeDefinition* result =
		trampoline_CEconItemSchema_GetAttributeDefinitionByName(this, name);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:GetAttributeDefinitionByName('%s')] %lld.%03lld us\n",
			name, dt_usec, dt_nsec);
		
		fprintf(prof_log, "GetAttributeDefinitionByName,%llu,%lld,,%s\n",
			callnum, dt, name);
		fflush(prof_log);
	} else {
		pr_warn("[PROF:GetAttributeDefinitionByName('%s')] FAILED\n",
			name);
	}
	++callnum;
	
	
	return result;
}


static CEconItemDefinition* detour_CEconItemSchema_GetItemDefinitionByName(CEconItemSchema* this, char const* name)
{
	static uint64_t callnum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	CEconItemDefinition* result =
		trampoline_CEconItemSchema_GetItemDefinitionByName(this, name);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:GetItemDefinitionByName('%s')] %lld.%03lld us\n",
			name, dt_usec, dt_nsec);
		
		fprintf(prof_log, "GetItemDefinitionByName,%llu,%lld,,%s\n",
			callnum, dt, name);
		fflush(prof_log);
	} else {
		pr_warn("[PROF:GetItemDefinitionByName('%s')] FAILED\n",
			name);
	}
	++callnum;
	
	
	return result;
}


static unknown_t detour_CMannVsMachineUpgradeManager_GetAttributeIndexByName(CMannVsMachineUpgradeManager* this, char const* name)
{
	static uint64_t callnum = 0;
	struct timespec t0, t1;
	bool fail = false;
	
	
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t0) != 0) {
		warn("clock_gettime failed for t0 in %s\n", __func__);
		fail = true;
	}
	unknown_t result = trampoline_CMannVsMachineUpgradeManager_GetAttributeIndexByName(this, name);
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1) != 0) {
		warn("clock_gettime failed for t1 in %s\n", __func__);
		fail = true;
	}
	
	
	if (!fail) {
		/* delta-T in nanoseconds */
		int64_t dt = conv_timespec_to_nsec(&t1) - conv_timespec_to_nsec(&t0);
		
		/* delta-T in microseconds and nanoseconds */
		int64_t dt_usec = dt / 1000;
		int64_t dt_nsec = dt % 1000;
		
		pr_debug("[PROF:GetAttributeIndexByName('%s')] %lld.%03lld us\n",
			name, dt_usec, dt_nsec);
		
		fprintf(prof_log, "GetAttributeIndexByName,%llu,%lld,,%s\n",
			callnum, dt, name);
		fflush(prof_log);
	} else {
		pr_warn("[PROF:GetAttributeIndexByName('%s')] FAILED\n",
			name);
	}
	++callnum;
	
	
	return result;
}


DETOUR_SETUP
{
	if ((prof_log = fopen("prof.csv", "w")) == NULL) {
		warn("fopen('prof.csv') failed");
		return false;
	}
	fprintf(prof_log, "FUNC,CALLNUM,DT_NS,T_SUM_NS,ARG\n");
	fflush(prof_log);
	
	
	//DETOUR_CREATE(CAttributeManager_AttribHookValue_float);
	
	//DETOUR_CREATE(GlobalAttrModifier_MvMAttribHookMunger);
	//DETOUR_CREATE(GlobalAttrModifier_TFHalloweenAttribHookMunger);
	
	DETOUR_CREATE(CEconItemSchema_GetAttributeDefinitionByName);
	DETOUR_CREATE(CEconItemSchema_GetItemDefinitionByName);
	DETOUR_CREATE(CMannVsMachineUpgradeManager_GetAttributeIndexByName);
	
	return true;
}


// get timestamp before; call trampoline; get timestamp after; print delta,
// possibly store average call time

// add detours for these funcs:
// - GetAttribDefinitionByName
// - AttribHookValue<float>
// - AttribHookValue<int>
