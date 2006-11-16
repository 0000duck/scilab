/*-----------------------------------------------------------------------------------*/
/* INRIA */
/* AUTHOR : Bruno Pincon */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include "stack-c.h"
#include "interpolation.h"
/*-----------------------------------------------------------------------------------*/ 
extern int good_order(double x[], int n);
extern int C2F(dset)();
extern void sciprint();
/* from dspfit.f */
extern int C2F(spfit)(double *xp, double *yp, double *wp, int *m, double *x, int *l,double *y, double *d, double *wk, int *ierr);
/*-----------------------------------------------------------------------------------*/ 
int intlsq_splin(char *fname,unsigned long fname_len)
{
  /*   interface code for [y, d] = lsq_splin(xd, yd [, wd], x)  */

  int minrhs=3, maxrhs=4, minlhs=1, maxlhs=2;

  int mxd, nxd, lxd, myd, nyd, lyd, mx, nx, lx, mwd, nwd, lwd;
  int ly, ld, lwork, ndata, n, one=1, mwork, ierr;
  double un=1.0;

  CheckRhs(minrhs,maxrhs);
  CheckLhs(minlhs,maxlhs);

  GetRhsVar(1,"d", &mxd, &nxd, &lxd);
  GetRhsVar(2,"d", &myd, &nyd, &lyd);
  ndata = mxd*nxd;  /* number of data points */
  if ( ndata < 4  ||  mxd != myd  || nxd != nyd  ||  mxd != 1  &&  nxd != 1 ) 
    { 
      Scierror(999,"%s: arg 1 and 2 must be vectors of same size with at least %d elements\r\n",
	       fname, 4);
      return 0;
    }

  if ( Rhs == 4 ) 
    {
      GetRhsVar(3,"d", &mwd, &nwd, &lwd);
      if ( mxd != mwd  ||  nxd != nwd )
	{ 
	  Scierror(999,"%s: bad input for arg 3\r\n", fname);
	  return 0;
	}
    }
  GetRhsVar(Rhs,"d", &mx, &nx, &lx);
  n = mx*nx;
  if ( n < 2  ||  mx != 1  &&  nx != 1 )
    { 
      Scierror(999,"%s: bad input for x \r\n", fname);
      return 0;
    }
  
  if (! good_order(stk(lx), n))   /* verify strict increasing abscissae */
    {
      Scierror(999,"%s: elts of arg %d not (strictly) increasing or +-inf detected\r\n", fname, Rhs);
      return 0;
    }

  CreateVar(Rhs+1, "d", &mx,  &nx,   &ly);
  CreateVar(Rhs+2, "d", &mx,  &nx,   &ld);
  mwork = 7*n+18;
  CreateVar(Rhs+3, "d", &mwork, &one, &lwork); 
  if ( Rhs == 3 )
    {
      CreateVar(Rhs+4, "d", &mxd, &nxd, &lwd);
      C2F(dset)( &ndata, &un, stk(lwd), &one);  /* set all the weight = 1  */ 
    }

  C2F(spfit)(stk(lxd), stk(lyd), stk(lwd), &ndata, stk(lx), &n, stk(ly),
	     stk(ld), stk(lwork), &ierr);

  if (ierr == -1)
    {
      Scierror(999,"%s: not enought points for the fit \r\n", fname);
      return 0;
    }
  else if (ierr == 1)
    sciprint("%s warning: rank deficiency of the least square matrix\r\n", fname);

  LhsVar(1) = Rhs+1;
  LhsVar(2) = Rhs+2;
  PutLhsVar();
  return 0;
}
/*-----------------------------------------------------------------------------------*/ 
