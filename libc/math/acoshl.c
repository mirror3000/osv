#include "libm.h"

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
long double acoshl(long double x)
{
	return acosh(x);
}
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
/* acosh(x) = log(x + sqrt(x*x-1)) */
long double acoshl(long double x)
{
	union {
		long double f;
		struct{uint64_t m; int16_t se; uint16_t pad;} i;
	} u = {.f = x};

	if (u.i.se < 0x3fff + 1)
		/* x < 2, invalid if x < 1 or nan */
		return log1pl(x-1 + sqrtl((x-1)*(x-1)+2*(x-1)));
	if (u.i.se < 0x3fff + 32)
		/* x < 0x1p32 */
		return logl(2*x - 1/(x+sqrtl(x*x-1)));
	return logl(x) + 0.693147180559945309417232121458176568L;
}
#endif
