#ifndef _LIBTF2MOD_INIT_H
#define _LIBTF2MOD_INIT_H


extern void            *dl_handle;
extern struct link_map *dl_linkmap;
extern uintptr_t        dl_baseaddr;


void tf2mod_init(void);


#endif
