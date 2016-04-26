/*
    Copyright (C) 2010 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef LONG_EXTRAS_H
#define LONG_EXTRAS_H

#ifdef LONG_EXTRAS_INLINES_C
#define LONG_EXTRAS_INLINE FLINT_DLL
#else
#define LONG_EXTRAS_INLINE static __inline__
#endif

#include <gmp.h>
#include "flint.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Properties ****************************************************************/

FLINT_DLL size_t z_sizeinbase(slong n, int b);

/* Randomisation  ************************************************************/

FLINT_DLL mp_limb_signed_t z_randtest(flint_rand_t state);

FLINT_DLL mp_limb_signed_t z_randtest_not_zero(flint_rand_t state);

FLINT_DLL mp_limb_signed_t z_randint(flint_rand_t state, mp_limb_t limit);

#ifdef __cplusplus
}
#endif

#endif

