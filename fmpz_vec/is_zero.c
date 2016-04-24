/*
    Copyright (C) 2010 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"

int
_fmpz_vec_is_zero(const fmpz * vec, slong len)
{
    slong i;
    for (i = 0; i < len; i++)
        if (vec[i] != WORD(0))
            return 0;
    return 1;
}
