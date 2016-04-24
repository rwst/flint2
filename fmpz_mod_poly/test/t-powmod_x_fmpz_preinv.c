/*
    Copyright (C) 2009 William Hart
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Lina Kulakova
    Copyright (C) 2013 Martin Lee

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#undef ulong
#define ulong ulongxx/* interferes with system includes */

#include <stdlib.h>
#include <stdio.h>

#undef ulong

#include <gmp.h>

#define ulong mp_limb_t

#include "flint.h"
#include "fmpz_vec.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);
    

    flint_printf("powmod_x_fmpz_preinv....");
    fflush(stdout);

    /* No aliasing */
    for (i = 0; i < 50 * flint_test_multiplier(); i++)
    {
        fmpz_mod_poly_t a, res1, res2, f, finv;
        fmpz_t p;
        ulong exp;
        fmpz_t expz;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));
        exp = n_randint(state, 50);


        fmpz_mod_poly_init(f, p);
        fmpz_mod_poly_init(finv, p);
        fmpz_mod_poly_init(res1, p);
        fmpz_mod_poly_init(res2, p);

        fmpz_mod_poly_randtest_not_zero(f, state, n_randint(state, 50) + 1);
        fmpz_init_set_ui(expz, exp);

        fmpz_mod_poly_reverse (finv, f, f->length);
        fmpz_mod_poly_inv_series_newton (finv, finv, f->length);

        fmpz_mod_poly_init2(a, p, f->length-1);
        fmpz_mod_poly_set_coeff_ui (a, 1, 1);
        fmpz_mod_poly_powmod_x_fmpz_preinv(res1, expz, f, finv);
        fmpz_mod_poly_powmod_fmpz_binexp_preinv(res2, a, expz, f, finv);

        result = (fmpz_mod_poly_equal(res1, res2));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("expz:\n"); fmpz_print(expz), flint_printf("\n\n");
            flint_printf("a:\n"); fmpz_mod_poly_print(a), flint_printf("\n\n");
            flint_printf("f:\n"); fmpz_mod_poly_print(f), flint_printf("\n\n");
            flint_printf("finv:\n"); fmpz_mod_poly_print(finv), flint_printf("\n\n");
            flint_printf("res1:\n"); fmpz_mod_poly_print(res1), flint_printf("\n\n");
            flint_printf("res2:\n"); fmpz_mod_poly_print(res2), flint_printf("\n\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(f);
        fmpz_mod_poly_clear(res1);
        fmpz_mod_poly_clear(res2);
        fmpz_mod_poly_clear(finv);
        fmpz_clear(expz);
    }

    /* Aliasing of res and f */
    for (i = 0; i < 25 * flint_test_multiplier(); i++)
    {
        fmpz_mod_poly_t res, f, finv;
        fmpz_t p;
        ulong exp;
        fmpz_t expz;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));
        exp = n_randint(state, 50);
        fmpz_init_set_ui(expz, exp);

        fmpz_mod_poly_init(f, p);
        fmpz_mod_poly_init(finv, p);
        fmpz_mod_poly_init(res, p);

        fmpz_mod_poly_randtest_not_zero(f, state, n_randint(state, 50) + 1);

        fmpz_mod_poly_reverse (finv, f, f->length);
        fmpz_mod_poly_inv_series_newton (finv, finv, f->length);

        fmpz_mod_poly_powmod_x_fmpz_preinv(res, expz, f, finv);
        fmpz_mod_poly_powmod_x_fmpz_preinv(f, expz, f, finv);

        result = (fmpz_mod_poly_equal(res, f));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("f:\n"); fmpz_mod_poly_print(f), flint_printf("\n\n");
            flint_printf("finv:\n"); fmpz_mod_poly_print(finv), flint_printf("\n\n");
            flint_printf("expz:\n"); fmpz_print(expz), flint_printf("\n\n");
            flint_printf("res:\n"); fmpz_mod_poly_print(res), flint_printf("\n\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(f);
        fmpz_mod_poly_clear(finv);
        fmpz_mod_poly_clear(res);
        fmpz_clear(expz);
    }

    /* Aliasing of res and finv */
    for (i = 0; i < 25 * flint_test_multiplier(); i++)
    {
        fmpz_mod_poly_t res, f, finv;
        fmpz_t p;
        ulong exp;
        fmpz_t expz;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));
        exp = n_randint(state, 50);
        fmpz_init_set_ui(expz, exp);

        fmpz_mod_poly_init(f, p);
        fmpz_mod_poly_init(finv, p);
        fmpz_mod_poly_init(res, p);

        fmpz_mod_poly_randtest_not_zero(f, state, n_randint(state, 50) + 1);


        fmpz_mod_poly_reverse (finv, f, f->length);
        fmpz_mod_poly_inv_series_newton (finv, finv, f->length);

        fmpz_mod_poly_powmod_x_fmpz_preinv(res, expz, f, finv);
        fmpz_mod_poly_powmod_x_fmpz_preinv(finv, expz, f, finv);

        result = (fmpz_mod_poly_equal(res, finv));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("f:\n"); fmpz_mod_poly_print(f), flint_printf("\n\n");
            flint_printf("expz:\n"); fmpz_print(expz), flint_printf("\n\n");
            flint_printf("finv:\n"); fmpz_mod_poly_print(finv), flint_printf("\n\n");
            flint_printf("res:\n"); fmpz_mod_poly_print(res), flint_printf("\n\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(f);
        fmpz_mod_poly_clear(finv);
        fmpz_mod_poly_clear(res);
        fmpz_clear(expz);
    }

    /* Check that x^(b+c) = x^b * x^c */
    for (i = 0; i < 50 * flint_test_multiplier(); i++)
    {
        fmpz_mod_poly_t res1, res2, res3, res4, f, finv;
        fmpz_t p;
        fmpz_t exp1, exp2, exp3;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));

        fmpz_init(exp1);
        fmpz_init(exp2);
        fmpz_randtest(exp1, state, 200);
        if (fmpz_sgn(exp1) == -1) fmpz_neg(exp1, exp1);
        fmpz_randtest(exp2, state, 200);
        if (fmpz_sgn(exp2) == -1) fmpz_neg(exp2, exp2);

        fmpz_mod_poly_init(f, p);
        fmpz_mod_poly_init(finv, p);
        fmpz_mod_poly_init(res1, p);
        fmpz_mod_poly_init(res2, p);
        fmpz_mod_poly_init(res3, p);
        fmpz_mod_poly_init(res4, p);

        fmpz_mod_poly_randtest_not_zero(f, state, n_randint(state, 50) + 1);

        fmpz_mod_poly_reverse (finv, f, f->length);
        fmpz_mod_poly_inv_series_newton (finv, finv, f->length);

        fmpz_mod_poly_powmod_x_fmpz_preinv(res1, exp1, f, finv);
        fmpz_mod_poly_powmod_x_fmpz_preinv(res2, exp2, f, finv);
        fmpz_mod_poly_mulmod(res4, res1, res2, f);
        fmpz_init(exp3);
        fmpz_add(exp3, exp1, exp2);
        fmpz_mod_poly_powmod_x_fmpz_preinv(res3, exp3, f, finv);

        result = (fmpz_mod_poly_equal(res4, res3));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("f:\n"); fmpz_mod_poly_print(f), flint_printf("\n\n");
            flint_printf("res3:\n"); fmpz_mod_poly_print(res3), flint_printf("\n\n");
            flint_printf("res4:\n"); fmpz_mod_poly_print(res4), flint_printf("\n\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(f);
        fmpz_mod_poly_clear(finv);
        fmpz_mod_poly_clear(res1);
        fmpz_mod_poly_clear(res2);
        fmpz_mod_poly_clear(res3);
        fmpz_mod_poly_clear(res4);
        fmpz_clear(exp1);
        fmpz_clear(exp2);
        fmpz_clear(exp3);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
