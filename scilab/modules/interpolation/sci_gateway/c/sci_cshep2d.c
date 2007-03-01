/*-----------------------------------------------------------------------------------*/
/* INRIA */
/* AUTHOR : Bruno Pincon */
/*-----------------------------------------------------------------------------------*/ 
#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <string.h>
#include "stack-c.h"
#include "interpolation.h"
/*-----------------------------------------------------------------------------------*/ 
extern int C2F(cshep2) (int *n, double *x, double *y, double *z, int *nc, int *nw, 
		 int *nr, int *lcell, int *lnext, double *xmin, double *xmax, 
		 double *dx, double *dy, double *rmax, double *rw, double *a, int *ier);
/*-----------------------------------------------------------------------------------*/ 
int intcshep2d(char *fname,unsigned long fname_len)
{
  static char *Str[]={"cshep2d", "xyz", "lcell", "lnext", "grdim", "rmax", "rw", "a"};
  int minrhs=1, maxrhs=1, minlhs=1, maxlhs=1;
  int n, dim, nc, nw, nr, one=1, four=4, eight=8, nine=9, ier;
  int lxyz, lxyzn, lcell, lnext, lgrid, lrmax, lrw, la, ltlist, lar;

  double * xyz, * grid;

  CheckRhs(minrhs,maxrhs);
  CheckLhs(minlhs,maxlhs);

  GetRhsVar(1,"d", &n, &dim, &lxyz);
  if ( dim != 3  ||  n < 10 ) 
    { 
      Scierror(999,"%s: xyz must be a (n,3) real matrix with n >= 10 \r\n", fname);
      return 0;
    }

  /* choix pour nc (peut etre futur parametre optionnel) */
  nc = Min( 17, n-1 );
  /* choix pour nw */
  nw = Min( 30, n-1 );
  /* choix pour nr (grille nr x nr) */
  nr = (int) sqrt( n/3.0 ); /* comme n >= 10 nr >= 1 */

  /* all the information for the "interpolant" will be stored
   * in a tlist (which also contains the entry xyz)  
   */
  CreateVar(2,"t", &eight, &one, &ltlist);
  CreateListVarFromPtr(2, 1, "S", &one,  &eight, Str);
  CreateListVarFrom(2, 2, "d", &n ,   &dim,  &lxyzn, &lxyz);
  lcell = 4; lar = -1;
  CreateListVarFrom(2, 3, "I", &nr,   &nr,   &lcell, &lar); /* lcell */
  lnext = 4; lar = -1;
  CreateListVarFrom(2, 4, "I", &one,  &n,    &lnext, &lar); /* lnext */
  lar = -1;
  CreateListVarFrom(2, 5, "d", &one,  &four, &lgrid, &lar); /* xmin, ymin, dx, dy */
  lar = -1;
  CreateListVarFrom(2, 6, "d", &one,  &one,  &lrmax, &lar); /* rmax */
  lar = -1;
  CreateListVarFrom(2, 7, "d", &one,  &n,    &lrw,   &lar); /* rw */
  lar = -1;
  CreateListVarFrom(2, 8, "d", &nine, &n,    &la,    &lar); /* a */
  grid = stk(lgrid);
  xyz = stk(lxyz);
  
  /*      SUBROUTINE CSHEP2 (N,X,Y,F,NC,NW,NR, LCELL,LNEXT,XMIN,
   *                         YMIN,DX,DY,RMAX,RW,A,IER)
   */
  C2F(cshep2) ( &n, xyz, &xyz[n], &xyz[2*n], &nc, &nw, &nr, istk(lcell),
		istk(lnext), grid, &grid[1], &grid[2], &grid[3], stk(lrmax),
		stk(lrw), stk(la), &ier);

  if ( ier != 0 )
    {
      Scierror(999,"%s: duplicate nodes or all nodes colinears (ier = %d) \r\n", fname, ier);
      return 0;
    }

  LhsVar(1) = 2;
  PutLhsVar();
  return 0;
}
/*-----------------------------------------------------------------------------------*/ 
