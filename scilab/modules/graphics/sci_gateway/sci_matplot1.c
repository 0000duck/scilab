/*------------------------------------------------------------------------*/
/* file: sci_matplot1.c                                                   */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for matplot1 routine                                  */
/*------------------------------------------------------------------------*/

#include "sci_matplot.h"
#include "GetProperty.h"
#include "sci_demo.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "sciCall.h"
#include "dr1Call.h"

/*-----------------------------------------------------------------------------------*/
int sci_matplot1( char * fname, unsigned long fname_len )
{
  integer m1, n1, l1,m2,n2,l2;
  if ( Rhs <= 0 )
  {
    int one = 1 ;
    sci_demo(fname,"plot2d([0,10],[0,10],0);a=ones(50,50);a= 3*tril(a)+2*a;Matplot1(a,[4,4,9,9]);", &one);
    return 0;
  }

  CheckRhs(2,2);
  GetRhsVar(1, "d", &m1, &n1, &l1);
  GetRhsVar(2, "d", &m2, &n2, &l2);
  CheckLength(2,m2*n2,4);
  if ( m1 * n1 == 0 )
  {
    LhsVar(1) = 0 ;
    return 0 ;
  } 
  SciWin();

  /* NG beg */
  if ( version_flag() == 0 )
  {
    Objmatplot1 (stk(l1), &m1, &n1,stk(l2)) ;
  }
  else
  {
    Xmatplot1 (stk(l1), &m1, &n1,stk(l2)) ; /* NG end */
  }
  LhsVar(1)=0;
  return 0;
} 
/*-----------------------------------------------------------------------------------*/
