/*
    Copyright (C) 2007 David Howden
    Copyright (C) 2007, 2008, 2009, 2010 William Hart
    Copyright (C) 2008 Richard Howell-Peak
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2011 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include <gmp.h>
#include "flint.h"
#include "fmpz_poly.h"

void
fmpz_poly_factor_concat(fmpz_poly_factor_t res, const fmpz_poly_factor_t fac)
{
    slong i;

    fmpz_mul(&(res->c), &(res->c), &(fac->c));

    for (i = 0; i < fac->num; i++)
        fmpz_poly_factor_insert(res, fac->p + i, fac->exp[i]);
}
