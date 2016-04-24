/*
    Copyright (C) 2012 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "nmod_poly.h"

void
_fmpz_poly_taylor_shift_divconquer(fmpz * poly, const fmpz_t c, slong len)
{
    fmpz d[2];

    if (len <= 1 || fmpz_is_zero(c))
        return;

    if (len == 2)
    {
        fmpz_addmul(poly, poly + 1, c);
        return;
    }

    d[0] = *c;
    d[1] = 1;

    _fmpz_poly_compose_divconquer(poly, poly, len, d, 2);
}

void
fmpz_poly_taylor_shift_divconquer(fmpz_poly_t g, const fmpz_poly_t f,
    const fmpz_t c)
{
    if (f != g)
        fmpz_poly_set(g, f);

    _fmpz_poly_taylor_shift_divconquer(g->coeffs, c, g->length);
}
