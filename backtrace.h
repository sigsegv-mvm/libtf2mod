#ifndef _LIBTF2MOD_BACKTRACE_H
#define _LIBTF2MOD_BACKTRACE_H


void print_backtrace(const char *from);
void print_backtrace_cl_con(const char *from, const char *prefix, int skip);

#define BACKTRACE() \
	print_backtrace(__func__)
#define BACKTRACE_CL_CON() \
	print_backtrace_cl_con(__func__, "", 0)
#define BACKTRACE_CL_CON_EX(_prefix, _skip) \
	print_backtrace_cl_con(__func__, _prefix, _skip)


#endif
