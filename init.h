#ifndef _LIBTF2MOD_INIT_H
#define _LIBTF2MOD_INIT_H


extern void* (*real_dlopen)(char const*, int);


void tf2mod_init(void);


#endif
