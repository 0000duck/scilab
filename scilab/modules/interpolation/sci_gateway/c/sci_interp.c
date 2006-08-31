/*-----------------------------------------------------------------------------------*/
/* INRIA */
/* AUTHOR : Bruno Pincon */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include "stack-c.h"
#include "interpolation.h"
/*-----------------------------------------------------------------------------------*/ 
extern int get_type(TableType *Tab, int dim_table, int *scistr, int strlength);
extern int C2F(evalpwhermite) (double *t, double *st, double *dst, double *ddst, double *dddst,int *m, double *x, double *y, double *d, int *n, int *outmode);
/*-----------------------------------------------------------------------------------*/ 
int intinterp1(char *fname,unsigned long fname_len)
{
  int minrhs=4, maxrhs=5, minlhs=1, maxlhs=4;

  int mt, nt, lt, mx, nx, lx, my, ny, ly, md, nd, ld, ns, *str_outmode;
  int n, m, outmode, lst, ldst, lddst, ldddst;
/*  double *x;*/

  CheckRhs(minrhs,maxrhs);
  CheckLhs(minlhs,maxlhs);

  GetRhsVar(1,"d", &mt, &nt, &lt);
  GetRhsVar(2,"d", &mx, &nx, &lx);
  GetRhsVar(3,"d", &my, &ny, &ly);
  GetRhsVar(4,"d", &md, &nd, &ld);

  if ( mx != my  ||  nx != ny  ||  md != mx || nd != nx || mx != 1  &&  nx != 1 || mx*nx < 2) 
    { 
      Scierror(999,"%s: bad inputs \r\n", fname);
      return 0;
    }
  n = mx*nx;    /* number of interpolation points */
  m = mt*nt;    /* number of points to interpolate */

  if ( Rhs == 5 )   /* get the outmode */
    {
      GetRhsScalarString(5, &ns, &str_outmode);
      outmode =  get_type(OutModeTable, NB_OUTMODE, str_outmode, ns);
      if ( outmode == UNDEFINED )
	{
	  Scierror(999,"%s: unknown outmode type\n\r",fname);
	  return 0;
	};
    }
  else
    outmode = C0;  /* default outmode */

  /* memory for st, dst, ddst, dddst */
  CreateVar(Rhs+1, "d", &mt,  &nt, &lst);
  CreateVar(Rhs+2, "d", &mt,  &nt, &ldst);
  CreateVar(Rhs+3, "d", &mt,  &nt, &lddst);
  CreateVar(Rhs+4, "d", &mt,  &nt, &ldddst);

  /*      subroutine EvalPWHermite(t, st, dst, ddst, dddst, m, x, y, d, n, outmode)
   *      integer m, n, outmode
   *      double precision t(m), st(m), dst(m), ddst(m), dddst(m), x(n), y(n), d(n)
   */
  C2F(evalpwhermite) (stk(lt), stk(lst), stk(ldst), stk(lddst), stk(ldddst),
                      &m, stk(lx), stk(ly), stk(ld), &n, &outmode);

  LhsVar(1) = Rhs+1;
  LhsVar(2) = Rhs+2;
  LhsVar(3) = Rhs+3;
  LhsVar(4) = Rhs+4;
  PutLhsVar();
  return 0;
}
