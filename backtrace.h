#ifndef _LIBTF2MOD_BACKTRACE_H
#define _LIBTF2MOD_BACKTRACE_H


void print_backtrace(const char *from);
#define BACKTRACE() \
	print_backtrace(__func__)


#endif
