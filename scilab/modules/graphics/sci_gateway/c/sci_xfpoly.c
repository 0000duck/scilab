/*------------------------------------------------------------------------*/
/* file: sci_xfpoly.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xfpoly routine                                    */
/*------------------------------------------------------------------------*/

#include "sci_xfpoly.h"
#include "stack-c.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "SetProperty.h"
#include "ObjectStructure.h"
#include "DrawObjects.h"
#include "sciCall.h"
#include "GetProperty.h"
#include "CurrentObjectsManagement.h"

/*-----------------------------------------------------------------------------------*/
int sci_xfpoly(char *fname,unsigned long fname_len)
{
  integer close=0,m1,n1,l1,m2,n2 ,l2,m3,n3,l3,mn1 ;

  long hdl; /* NG */
  sciPointObj * psubwin = NULL ;

  CheckRhs(2,3);

  GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1);
  GetRhsVar(2,MATRIX_OF_DOUBLE_DATATYPE,&m2,&n2,&l2);
  CheckSameDims(1,2,m1,n1,m2,n2);

  if (Rhs == 3) {
    GetRhsVar(3,MATRIX_OF_DOUBLE_DATATYPE,&m3,&n3,&l3);
    CheckScalar(3,m3,n3);
    close = (integer) *stk(l3);
  } 
  mn1 = m1 * n1;


  psubwin = sciGetCurrentSubWin();

  if(close == 0)
  {
    close = sciGetForeground(sciGetCurrentSubWin());
  }
  Objfpoly (stk(l1),stk(l2),mn1,&close,&hdl,0);

  sciDrawObjIfRequired(sciGetCurrentObj ());

  LhsVar(1)=0;
  return 0;

}

/*-----------------------------------------------------------------------------------*/
