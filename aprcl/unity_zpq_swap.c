/*
    Copyright (C) 2015 Vladimir Glazachev

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include "aprcl.h"

void
unity_zpq_swap(unity_zpq f, unity_zpq g)
{
    fmpz_mod_poly_t *temp = f->polys;
    f->polys = g->polys;
    g->polys = temp;
}

