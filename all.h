#ifndef _LIBTF2MOD_ALL_H
#define _LIBTF2MOD_ALL_H


#define _GNU_SOURCE

/* c standard library */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <link.h>

/* posix */
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/user.h>

/* libbsd */
#include <err.h>
#include <bsd/string.h>

/* libdl */
#include <dlfcn.h>

/* libiberty */
#include <libiberty/demangle.h>

/* libelf */
#include <libelf.h>
#include <gelf.h>

/* sourcemod */
#include "sourcemod/asm.h"

/* this project */
#include "common.h"
#include "init.h"
#include "detour.h"
#include "symtab.h"
#include "vtable.h"
#include "util.h"
#include "patch.h"


#endif
