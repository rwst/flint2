/*
    Copyright (C) 2007 David Howden
    Copyright (C) 2007, 2008, 2009, 2010 William Hart
    Copyright (C) 2008 Richard Howell-Peak
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2011 Sebastian Pancratz
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/



#ifdef T

#include "templates.h"

void
TEMPLATE(T, poly_factor_concat) (TEMPLATE(T, poly_factor_t) res,
                                 const TEMPLATE(T, poly_factor_t) fac,
                                 const TEMPLATE(T, ctx_t) ctx)
{
    slong i;

    for (i = 0; i < fac->num; i++)
        TEMPLATE(T, poly_factor_insert) (res, fac->poly + i, fac->exp[i], ctx);
}


#endif
