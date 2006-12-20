/*-----------------------------------------------------------------------------------*/
/* INRIA */
/* AUTHOR : Bruno Pincon */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include "stack-c.h"
#include "interpolation.h"
/*-----------------------------------------------------------------------------------*/ 
extern int good_order(double x[], int n);
extern int get_type(TableType *Tab, int dim_table, int *scistr, int strlength);
extern int C2F(derivd) (double *x, double *y, double *d, int *n, int *inc, int *type);
extern int C2F(dpchim) (int *n, double *x, double *y, double *d, int *inc);
extern int C2F(splinecub) (double *x, double *y, double *d, int *n, int *type,double *wk1, double *wk2, double *wk3, double *wk4);
/*-----------------------------------------------------------------------------------*/
#define NB_SPLINE_TYPE 7
static TableType SplineTable[NB_SPLINE_TYPE] = { 
	{ "not_a_knot"   , NOT_A_KNOT    },
	{ "natural"      , NATURAL       },
	{ "clamped"      , CLAMPED       },
	{ "periodic"     , PERIODIC      },
	{ "monotone"     , MONOTONE      },
	{ "fast"         , FAST          },
	{ "fast_periodic", FAST_PERIODIC }};
/*-----------------------------------------------------------------------------------*/ 
int intsplin(char *fname,unsigned long fname_len)
{
  int minrhs=2, maxrhs=4, minlhs=1, maxlhs=1;

  int mx, nx, lx, my, ny, ly, mc, nc, lc, n, spline_type;
  int *str_spline_type, ns;
  int /*i,*/ ld/*, flag*/;
  int mwk1, nwk1, lwk1, mwk2, nwk2, lwk2, mwk3, nwk3, lwk3, mwk4, nwk4, lwk4;
  double *x, *y, *d, *c;

  CheckRhs(minrhs,maxrhs);
  CheckLhs(minlhs,maxlhs);

  GetRhsVar(1,"d", &mx, &nx, &lx);
  GetRhsVar(2,"d", &my, &ny, &ly);

  if ( mx != my  ||  nx != ny  ||  mx != 1  &&  nx != 1 ) 
    { 
      Scierror(999,"%s: arg1 and arg2 must be 2 vectors with same size\r\n", fname);
      return 0;
    }
  n = mx*nx;    /* number of interpolation points */
  if ( n < 2 ) 
    { 
      Scierror(999,"%s: the number of interpolation points must be >= 2\r\n", fname);
      return 0;
    }
  x = stk(lx); y = stk(ly);
  if (! good_order(x, n))  /* verify strict increasing abscissae */
    {
      Scierror(999,"%s: elts of arg 1 not (strictly) increasing or +-inf detected\r\n", fname);
      return 0;
    }

  if ( Rhs >= 3 )   /* get the spline type */
    {
      GetRhsScalarString(3, &ns, &str_spline_type);
      spline_type =  get_type(SplineTable, NB_SPLINE_TYPE, str_spline_type, ns);
      if ( spline_type == UNDEFINED )
	{
	  Scierror(999,"%s: unknown spline_type\n\r",fname);
	  return 0;
	};
    }
  else
    spline_type = NOT_A_KNOT;

  if ( spline_type == CLAMPED ) /* get arg 4 which contains the end point slopes */
    {
      if ( Rhs != 4 )
	{
	  Scierror(999,"%s: for a clamped spline you must give the endpoint slopes\n\r",fname);
	  return 0;
	}
      GetRhsVar(4,"d", &mc, &nc, &lc);
      if ( mc*nc != 2 )
	{
	  Scierror(999,"%s: bad dimension for the 4 arg (endpoint slopes)\n\r",fname);
	  return 0;
	}
      c = stk(lc);
    }
  else if ( Rhs == 4 )
    {
      Scierror(999,"%s: 4 args are required only for a clamped spline\n\r",fname);
      return 0;
    }
    
  /*  verify y(1) = y(n) for periodic splines */
  if ( (spline_type == PERIODIC || spline_type == FAST_PERIODIC)  &&  y[0] != y[n-1] )
    {
      Scierror(999,"%s: for a periodic spline y(1) must be equal to y(n)\n\r",fname);
      return(0);
    };

  CreateVar(Rhs+1, "d", &mx,  &nx,   &ld); /* memory for d (only argument returned) */   
  d = stk(ld);

  switch(spline_type)
    {
    case(FAST) : case(FAST_PERIODIC) :
      nwk1 = 1;
      C2F(derivd) (x, y, d, &n, &nwk1, &spline_type);
      break;

    case(MONOTONE) :
      nwk1 = 1;
      C2F(dpchim) (&n, x, y, d, &nwk1);
      break;

    case(NOT_A_KNOT) : case(NATURAL) : case(CLAMPED) : case(PERIODIC) :
      /*  (the wk4 work array is used only in the periodic case) */
      mwk1 = n; nwk1 = 1; mwk2 = n-1; nwk2 = 1; mwk3 = n-1; nwk3 = 1; mwk4 = n-1; nwk4 = 1;
      CreateVar(Rhs+2, "d", &mwk1,  &nwk1,   &lwk1);
      CreateVar(Rhs+3, "d", &mwk2,  &nwk2,   &lwk2);
      CreateVar(Rhs+4, "d", &mwk3,  &nwk3,   &lwk3);
      lwk4 = lwk1;
      if (spline_type == CLAMPED) 
	{ d[0] = c[0]; d[n-1] = c[1]; };
      if (spline_type == PERIODIC)
	CreateVar(Rhs+5, "d", &mwk4,  &nwk4,   &lwk4);
      C2F(splinecub) (x, y, d, &n, &spline_type, stk(lwk1), stk(lwk2), stk(lwk3), stk(lwk4));
      break;
    }
  LhsVar(1) = Rhs+1;
  PutLhsVar();
  return 0;
}
