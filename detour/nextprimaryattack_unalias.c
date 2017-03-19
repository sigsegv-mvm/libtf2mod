#include "all.h"


DETOUR(nextprimaryattack_unalias);
/* calculate m_flNextPrimaryAttack in such a way that it will average out toward
 * the ideal firing interval instead of always rounding up to the tick
 * interval */


static void (*trampoline_CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);


static struct drand48_data prng_state;


static void detour_CTFWeaponBaseGun_PrimaryAttack(CTFWeaponBaseGun* this)
{
	float *m_flNextPrimaryAttack =
		prop_CTFWeaponBaseGun_m_flNextPrimaryAttack(this);
	
	trampoline_CTFWeaponBaseGun_PrimaryAttack(this);
	
	/* using double-precision floats here to ward off the FP demons */
	
#if 0
	/* figure out what the firing interval must have been */
	double t_now = (*gpGlobals)->curtime;
	double t_after = *m_flNextPrimaryAttack;
	double dt_fire = t_after - t_now;
	
	/* get simulation tick interval */
	double dt_tick = (*gpGlobals)->interval_per_tick;
	assert(dt_tick != 0.0);
	
	/* convert fire interval from seconds into ticks */
	double dtick_fire = dt_fire / dt_tick;
	
	/* split fire interval into integral and fractional parts */
	double dtick_fire_int;
	double dtick_fire_frac = modf(dtick_fire, &dtick_fire_int);
	assert(dtick_fire_frac >= 0.0 && dtick_fire_frac < 1.0);
	
	double rand_frac;
	assert(drand48_r(&prng_state, &rand_frac) == 0);
	
	/* do a random-round operation based on the fractional part */
	double dt_unaliased;
	if (dtick_fire_frac < rand_frac) {
		dt_unaliased = dtick_fire_int * dt_tick;
	} else {
		dt_unaliased = (dtick_fire_int + 1.0) * dt_tick;
	}
	
	/* add half of the tick interval to avoid float comparison issues */
	dt_unaliased += (dt_tick * 0.5);
	
	float t_unaliased = t_now + dt_unaliased;
	
	pr_info("CTFWeaponBaseGun::PrimaryAttack\n");
	pr_debug(
		"    t_now:             %7.3f\n"
		"    t_after:           %7.3f\n"
		"  dt_fire:             %7.3f\n"
		"    dt_tick:           %7.3f\n"
		"    dtick_fire:        %7.3f\n"
		"      dtick_fire_int:  %7.3f\n"
		"      dtick_fire_frac: %7.3f\n"
		"    rand_frac:         %7.3f\n"
		"    dt_unalised:       %7.3f\n"
		"  t_unaliased:         %7.3f\n",
		t_now, t_after,
		dt_fire,
		dt_tick,
		dtick_fire, dtick_fire_int, dtick_fire_frac,
		rand_frac,
		dt_unaliased, t_unaliased);
	
	/* apply and notify state change if necessary */
	if (*m_flNextPrimaryAttack != t_unaliased) {
		CBaseEntity_NetworkStateChanged(this, m_flNextPrimaryAttack);
		*m_flNextPrimaryAttack = t_unaliased;
	}
#endif
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFWeaponBaseGun_PrimaryAttack);
	
	return true;
}
