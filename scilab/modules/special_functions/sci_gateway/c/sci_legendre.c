/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#ifdef _MSC_VER
	#include <Windows.h>
#endif
#include "stack-c.h"
/*-----------------------------------------------------------------------------------*/
extern void C2F(dxlegf)(double *dnu1, int *nudiff, int *mu1, int *mu2, double *x,int *id, double *pqa, int *ipqa, int *ierror);
/*-----------------------------------------------------------------------------------*/
static double return_an_inf();
static int verify_cstr(double x[], int nb_elt, int *xmin, int *xmax);
/*-----------------------------------------------------------------------------------*/
int sci_legendre(char *fname,unsigned long fname_len)
{
  /*
   *   Interface onto the (Slatec) dxleg.f code. 
   *   Scilab calling sequence :
   *
   *   p = legendre(n, m, x [, norm_flag] )
   *
   *      x is a vector with mnx elements (it is better to
   *        have a row vector but this is not forced)
   *
   *      n : a non negative integer scalar (or a vector of such
   *          integer regularly speced with an increment of 1)
   *      m : same constraints than for n
   *
   *      n and m may not be both vectors
   *
   *      norm_flag : optionnal. When it is present and equal to "norm"
   *                  it is a normalised version which is computed
   *    AUTHOR 
   *       Bruno Pincon <Bruno.Pincon@iecn.u-nancy.fr>
   */
  int it, lc, mM, nM, lM, m1, m2, mN, nN, lN, n1, n2, mx, nx, lx, mnx, ms, ns, ls;
  int M_is_scalar = 0, N_is_scalar = 0, normalised, MNp1, lpqa, lipqa, *ipqa;
  double *x, xx, dnu1, *pqa;
  int id, ierror, i, j, nudiff;

  CheckLhs(1,1); CheckRhs(3,4);
  GetRhsVar(1, "d", &mN, &nN, &lN);

  if ( ! verify_cstr(stk(lN), mN*nN, &n1, &n2) )
    {
      Scierror(999,"%s: bad first argument\r\n", fname);
      return 0;
    };
  if ( mN == 1 && nN == 1) N_is_scalar = 1;

  GetRhsVar(2, "d", &mM, &nM, &lM);
  if ( ! verify_cstr(stk(lM), mM*nM, &m1, &m2) )
    {
      Scierror(999,"%s: bad second argument\r\n", fname);
      return 0;
    }
  if ( mM == 1 && nM == 1) M_is_scalar = 1;

  if ( ! M_is_scalar  &&  ! N_is_scalar )
    {
      Scierror(999,"%s: only one of arg1 and arg2 may be a vector\r\n", fname);
      return 0;
    };
       
  GetRhsCVar(3,"d", &it, &mx, &nx, &lx, &lc);
  if ( it != 0 )
    {
      Scierror(999,"%s: 3th argument must be a real matrix\r\n", fname);
      return 0;
    };

  mnx = mx*nx;
  x = stk(lx);
  for ( i = 0 ; i < mnx ; i++ )
    if ( ! (fabs(x[i]) < 1.0) ) 
      {
	Scierror(999,"%s: 3th argument must be a matrix with elements in (-1,1)\r\n", fname);
	return 0;
      };
  
  if ( Rhs == 4 )
    {
      GetRhsVar(4,"c", &ms, &ns, &ls);
      if ( strcmp(cstk(ls),"norm") == 0)
	normalised = 1;
      else
	normalised = 0;
    }
  else
    normalised = 0;
  
  MNp1 = max (n2 - n1, m2 - m1) + 1;

  CreateVar(Rhs+1, "d", &MNp1, &mnx, &lpqa); pqa = stk(lpqa);
  CreateVar(Rhs+2, "i", &MNp1, &mnx, &lipqa); ipqa = istk(lipqa);

  if ( normalised )
    id = 4;
  else
    id = 3;

  nudiff = n2-n1;  
  dnu1 = (double) n1;

  for ( i = 0 ; i < mnx ; i++ )
    {
      xx = fabs(x[i]); /* dxleg computes only for x in [0,1) */
      F2C(dxlegf) (&dnu1, &nudiff, &m1, &m2, &xx, &id, 
		   stk(lpqa+i*MNp1), istk(lipqa+i*MNp1), &ierror);
      if ( ierror != 0 )
	{
	  if ( ierror == 207 )
	    Scierror(999,"%s: overflow or underflow of an extended range number\r\n", fname);
	  else
	    Scierror(999,"%s: error number %d\r\n", fname, ierror);
	  return 0;
	};
    }

  /*  dxlegf returns the result under a form (pqa,ipqa) (to 
   *  compute internaly with an extended exponent range)
   *  When the "exponent" part (ipqa) is 0 then the number is exactly
   *  given by pqa else it leads to an overflow or an underflow.
   */
  for ( i = 0 ; i < mnx*MNp1 ; i++ )
    {
      if ( ipqa[i] < 0 ) 
	pqa[i] = 0.0;
      if ( ipqa[i] > 0 )
	pqa[i] = pqa[i] * return_an_inf(); /* pqa[i] * Inf  to have the sign */
    }

  /* complete the result by odd/even symmetry for negative x */
  for ( i = 0 ; i < mnx ; i++ ) {
    if ( x[i] < 0.0 ) {
      if ( (n1+m1) % 2 == 1 ) {
	for ( j = 0 ; j < MNp1 ; j+=2 )
	  pqa[i*MNp1 + j] = -pqa[i*MNp1 + j];
      }
      else {
	for ( j = 1 ; j < MNp1 ; j+=2 )
	  pqa[i*MNp1 + j] = -pqa[i*MNp1 + j];
      }
    }
  }
  LhsVar(1) = Rhs+1;
  return 0;
}
/*-----------------------------------------------------------------------------------*/
static double return_an_inf()
{
	/*    AUTHOR 
	*       Bruno Pincon <Bruno.Pincon@iecn.u-nancy.fr>
	*/
	static int first = 1;
	static double inf = 1.0;

	if ( first )
	{
		inf = inf/(inf - (double) first);
		first = 0;
	}
	return (inf);
}
/*-----------------------------------------------------------------------------------*/
static int verify_cstr(double x[], int nb_elt, int *xmin, int *xmax)
{
	/*    1/ verify that the array x is formed by non negative integers
	*       regularly spaced with increment equal to 1 (if yes return 1
	*       if not return 0)
	*    2/ computes the min and the max
	*
	*    AUTHOR 
	*       Bruno Pincon <Bruno.Pincon@iecn.u-nancy.fr>
	*/
	int i;
	if ( ! (floor(x[0]) == x[0]  &&  x[0] >= 0 ))
		return 0;
	for ( i = 1 ; i < nb_elt ; i++ )
		if ( x[i] != x[i-1]+1.0 )
			return 0;

	*xmin = (int) x[0];
	*xmax = (int) x[nb_elt-1];
	return 1;
} 
/*-----------------------------------------------------------------------------------*/
