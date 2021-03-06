/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011, 2010 Sebastian Pancratz
    Copyright (C) 2008, 2009 William Hart
    Copyright (C) 2013 Martin Lee

******************************************************************************/

#undef ulong
#define ulong ulongxx/* interferes with system includes */

#include <stdlib.h>

#undef ulong

#include <gmp.h>

#define ulong mp_limb_t

#include "fmpz_vec.h"
#include "fmpz_mod_poly.h"

void _fmpz_mod_poly_div_newton_n_preinv (fmpz* Q, const fmpz* A, slong lenA,
                                   const fmpz* B, slong lenB, const fmpz* Binv,
                                   slong lenBinv, const fmpz_t mod)
{
    const slong lenQ = lenA - lenB + 1;
    fmpz * Arev;

    Arev = _fmpz_vec_init(lenQ);

    _fmpz_poly_reverse(Arev, A + (lenA - lenQ), lenQ, lenQ);

    _fmpz_mod_poly_mullow(Q, Arev, lenQ, Binv, FLINT_MIN(lenQ, lenBinv), mod,
                          lenQ);

    _fmpz_poly_reverse(Q, Q, lenQ, lenQ);

    _fmpz_vec_clear(Arev, lenQ);
}


void fmpz_mod_poly_div_newton_n_preinv(fmpz_mod_poly_t Q,
                               const fmpz_mod_poly_t A, const fmpz_mod_poly_t B,
                               const fmpz_mod_poly_t Binv)
{
    const slong lenA = A->length, lenB = B->length, lenQ = lenA - lenB + 1,
                lenBinv = Binv->length;
    fmpz *q;

    if (lenB == 0)
    {
        flint_printf("Exception (fmpz_mod_poly_div_newton_n_preinv). Division by zero.\n");
        flint_abort();
    }

    if (lenA < lenB)
    {
        fmpz_mod_poly_zero(Q);
        return;
    }

    if (lenA > 2 * lenB - 2)
    {
        flint_printf ("Exception (fmpz_mod_poly_div_newton_n_preinv).\n");
    }

    if (Q == A || Q == B || Q == Binv)
    {
        q = _fmpz_vec_init(lenQ);
    }
    else
    {
        fmpz_mod_poly_fit_length(Q, lenQ);
        q = Q->coeffs;
    }

    _fmpz_mod_poly_div_newton_n_preinv (q, A->coeffs, lenA, B->coeffs, lenB,
                                    Binv->coeffs, lenBinv, &(B->p));

    if (Q == A || Q == B || Q == Binv)
    {
        _fmpz_vec_clear(Q->coeffs, Q->alloc);
        Q->coeffs = q;
        Q->alloc  = lenQ;
        Q->length = lenQ;
    }
    else
    {
        _fmpz_mod_poly_set_length(Q, lenQ);
    }
}
