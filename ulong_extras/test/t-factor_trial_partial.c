/*
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
#include "ulong_extras.h"

int main(void)
{
   int i, j, result;
   FLINT_TEST_INIT(state);
   

   flint_printf("factor_trial_partial....");
   fflush(stdout);
 
   for (i = 0; i < 1000 * flint_test_multiplier(); i++) /* Test random numbers */
   {
      mp_limb_t n1, n2, prod, limit;
      n_factor_t factors;

      n_factor_init(&factors);

      n1 = n_randtest_not_zero(state);
      limit = n_sqrt(n1);
      n2 = n_factor_trial_partial(&factors, n1, &prod, UWORD(10000), limit);
      
      if (n1 != n2*prod)
      {
         flint_printf("FAIL:\n");
         flint_printf("n1 = %wu, n2 = %wu, prod = %wu\n", n1, n2, prod);
         abort();
      }

      for (j = 0; j < factors.num; j++)
      {
         n2 *= n_pow(factors.p[j], factors.exp[j]);
      }

      result = (n1 == n2);
      if (!result)
      {
         flint_printf("FAIL:\n");
         flint_printf("n1 = %wu, n2 = %wu\n", n1, n2); 
         abort();
      }
   }

   FLINT_TEST_CLEANUP(state);
   
   flint_printf("PASS\n");
   return 0;
}
