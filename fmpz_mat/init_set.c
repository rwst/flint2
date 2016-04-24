/*
    Copyright (C) 2010 William Hart
    Copyright (C) 2010 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include "fmpz_mat.h"

void
fmpz_mat_init_set(fmpz_mat_t mat, const fmpz_mat_t src)
{
    fmpz_mat_init(mat, src->r, src->c);
    fmpz_mat_set(mat, src);
}
