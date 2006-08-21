/*------------------------------------------------------------------------*/
/* file: sci_param3d.h                                                    */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for contour2d1 routine                                */
/*------------------------------------------------------------------------*/

#include "sci_contour2d1.h"
#include "Graphics.h"
#include "GetCommandArg.h"

/*-----------------------------------------------------------------------------------*/
int sci_contour2d1( char * fname, unsigned long fname_len )
{
  int flagx=0,nz=10; /* default number of level curves : 10 */
  integer m1,n1,l1,m2,n2,l2,m3,n3,l3,m4,n4,l4,l5;
  double  *hl1, *hl2;
  double *znz= NULL;
  int ix4, i, un = 1;

  CheckRhs(3,4);
  CheckLhs(2,2);

  GetRhsVar(1, "d", &m1, &n1, &l1);
  CheckVector(1,m1,n1);
  GetRhsVar(2, "d", &m2, &n2, &l2);
  CheckVector(2,m2,n2);
  GetRhsVar(3, "d", &m3, &n3, &l3);
  if (m3 * n3 == 0) { LhsVar(1) = 0; return 0; }
  if (m3 == 1 || n3 == 1) {
    Scierror(999,"%s: third argument is a vector, expecting a matrix\r\n",fname);
    return 0;
  }

  CheckDimProp(1,3, m1 * n1 != m3); 
  CheckDimProp(2,3, m2 * n2 != n3); 

  /*     number of level curves */
  if ( Rhs == 4 ) 
  {
    GetRhsVar(4, "d", &m4, &n4, &l4);
    if (m4 * n4 == 1) {
      flagx = 0;  nz = Max(1,(integer) *stk(l4)),znz= stk(l4);
    } else {
      flagx = 1;  nz = m4 * n4; znz=stk(l4);
    }
  }

  ix4 = Max(nz,2);
  CreateVar(Rhs+1,"i",&un,&ix4,&l5);
  for (i =0 ; i < ix4 ; ++i) *istk(l5 + i ) = i+1;
  if (nz == 1) *istk(l5 +1) = 1;

  C2F(contourif)(stk(l1),stk(l2),stk(l3),&m3,&n3,&flagx,&nz,znz,istk(l5));
  C2F(getconts)(&hl1, &hl2, &m1, &n1);
  if (n1 == 0)
  {
    CreateVar(6,"d", &n1, &n1, &l1);
    CreateVar(7,"d", &n1, &n1, &l2);
  }
  else 
  {
    CreateVarFromPtr(6,"d", &m1, &n1, &hl1);
    CreateVarFromPtr(7,"d", &m1, &n1, &hl2);
  }
  LhsVar(1)=6;
  LhsVar(2)=7;
  return 0;
}
/*-----------------------------------------------------------------------------------*/