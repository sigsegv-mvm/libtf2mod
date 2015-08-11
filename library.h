#ifndef _LIBTF2MOD_LIBRARY_H
#define _LIBTF2MOD_LIBRARY_H


void lib_hook(const char *path, void *handle);

library_info_t *lib_find(const char *name);

library_info_t *lib_first(void);
library_info_t *lib_next(library_info_t *lib);


#endif
