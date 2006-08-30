/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include "stack-c.h"
/*-----------------------------------------------------------------------------------*/
extern double F2C(dgammacody)(double *);
extern double F2C(betaln)(double *, double *);
/*-----------------------------------------------------------------------------------*/
int sci_beta(char *fname,unsigned long fname_len)
{
  /*
   *   z = beta(x, y)
   *
   *      x, y : matrices of the same size of positive reals
   *
   *   For small x+y values uses the expression with the
   *   gamma function, else the exponential applied on the log beta
   *   function (provided in the dcd lib)
   *
   *   The switch limit have been set by using the gp-pari software.
   *
   *    AUTHOR 
   *       Bruno Pincon <Bruno.Pincon@iecn.u-nancy.fr>
   *
   */
  int mx, nx, itx, lx, lxc, my, ny, ity, ly, lyc,/* it,*/ lz, i;
  double *x, *y, *z, xpy;
  double switch_limit = 2;

  CheckLhs(1,1); CheckRhs(2,2);
  GetRhsCVar(1, "d", &itx, &mx, &nx, &lx, &lxc); x = stk(lx);
  GetRhsCVar(2, "d", &ity, &my, &ny, &ly, &lyc); y = stk(ly);
  CheckSameDims(1,2,mx,nx,my,ny);
  if ( itx == 1  ||  ity == 1 )
    {
      Scierror(999,"%s don't work for complex arguments \r\n", fname);
      return 0;
    };

  CreateVar(3, "d", &mx, &nx, &lz); z = stk(lz);

  for ( i = 0 ; i < mx*nx ; i++ )
    {
      if ( x[i] <= 0.0  ||  y[i] <= 0.0 )
	{
	  Scierror(999,"%s: arguments must be positive \r\n", fname);
	  return 0;
	}
      xpy = x[i] + y[i];
      if ( xpy <= switch_limit )
	z[i] = F2C(dgammacody)(&x[i]) * F2C(dgammacody)(&y[i]) / F2C(dgammacody)(&xpy);
      else
	z[i] = exp(F2C(betaln)(&x[i], &y[i]));
    }
  LhsVar(1) = 3;
  return 0;
}
/*-----------------------------------------------------------------------------------*/
