/*
    Copyright (C) 2011 Sebastian Pancratz
    Copyright (C) 2009 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("divrem_f....");
    fflush(stdout);

    

    /* Check q*b + r = a when gcd(lead(B),p) = 1, no aliasing */
    for (i = 0; i < 500 * flint_test_multiplier(); i++)
    {
        fmpz_t f, p;
        fmpz_mod_poly_t a, b, q, r, t;

        fmpz_init(f);
        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(q, p);
        fmpz_mod_poly_init(r, p);
        fmpz_mod_poly_init(t, p);
        fmpz_mod_poly_randtest(a, state, n_randint(state, 100));
        fmpz_mod_poly_randtest_not_zero(b, state, n_randint(state, 100) + 1);

        {
            fmpz_t d;
            fmpz *leadB = fmpz_mod_poly_lead(b);

            fmpz_init(d);
            fmpz_gcd(d, p, leadB);
            while (!fmpz_is_one(d))
            {
                fmpz_divexact(leadB, leadB, d);
                fmpz_gcd(d, p, leadB);
            }
            fmpz_clear(d);
        }

        fmpz_mod_poly_divrem_f(f, q, r, a, b);
        fmpz_mod_poly_mul(t, q, b);
        fmpz_mod_poly_add(t, t, r);

        result = (fmpz_is_one(f) && fmpz_mod_poly_equal(a, t));
        if (!result)
        {
            flint_printf("FAIL (divrem):\n");
            flint_printf("p = "), fmpz_print(p), flint_printf("\n\n");
            flint_printf("f = "), fmpz_print(f), flint_printf("\n\n");
            flint_printf("a = "), fmpz_mod_poly_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpz_mod_poly_print(b), flint_printf("\n\n");
            flint_printf("q = "), fmpz_mod_poly_print(q), flint_printf("\n\n");
            flint_printf("r = "), fmpz_mod_poly_print(r), flint_printf("\n\n");
            flint_printf("t = "), fmpz_mod_poly_print(t), flint_printf("\n\n");
            abort();
        }

        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(q);
        fmpz_mod_poly_clear(r);
        fmpz_mod_poly_clear(t);
        fmpz_clear(f);
        fmpz_clear(p);
    }

    /* Check f | p when gcd(lead(B),p) > 1 */
    for (i = 0; i < 500 * flint_test_multiplier(); i++)
    {
        fmpz_t f, p, q1, q2;
        fmpz_mod_poly_t a, b, q, r, t;

        fmpz_init(f);
        fmpz_init(p);
        fmpz_init(q1);
        fmpz_init(q2);
        fmpz_randtest_unsigned(q1, state, 2 * FLINT_BITS);
        fmpz_randtest_unsigned(q2, state, 2 * FLINT_BITS);
        fmpz_add_ui(q1, q1, 2);
        fmpz_add_ui(q2, q2, 2);
        fmpz_mul(p, q1, q2);

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(q, p);
        fmpz_mod_poly_init(r, p);
        fmpz_mod_poly_init(t, p);
        fmpz_mod_poly_randtest(a, state, n_randint(state, 100));
        fmpz_mod_poly_randtest_not_zero(b, state, n_randint(state, 100) + 1);

        {
            fmpz_t d;
            fmpz *leadB = fmpz_mod_poly_lead(b);

            fmpz_init(d);
            fmpz_gcd(d, p, leadB);
            if (fmpz_is_one(d))
                fmpz_set(leadB, q1);
            fmpz_clear(d);
        }

        fmpz_mod_poly_divrem_f(f, q, r, a, b);
        fmpz_mod_poly_mul(t, q, b);
        fmpz_mod_poly_add(t, t, r);

        result = (fmpz_cmp_ui(f, 1) > 0 && fmpz_cmp(f, p) < 0 && fmpz_divisible(p, f));
        if (!result)
        {
            flint_printf("FAIL (factor):\n");
            flint_printf("p = "), fmpz_print(p), flint_printf("\n\n");
            flint_printf("f = "), fmpz_print(f), flint_printf("\n\n");
            flint_printf("q1 = "), fmpz_print(q1), flint_printf("\n\n");
            flint_printf("q2 = "), fmpz_print(q2), flint_printf("\n\n");
            flint_printf("a = "), fmpz_mod_poly_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpz_mod_poly_print(b), flint_printf("\n\n");
            flint_printf("q = "), fmpz_mod_poly_print(q), flint_printf("\n\n");
            flint_printf("r = "), fmpz_mod_poly_print(r), flint_printf("\n\n");
            flint_printf("t = "), fmpz_mod_poly_print(t), flint_printf("\n\n");
            abort();
        }

        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(q);
        fmpz_mod_poly_clear(r);
        fmpz_mod_poly_clear(t);
        fmpz_clear(f);
        fmpz_clear(p);
        fmpz_clear(q1);
        fmpz_clear(q2);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
