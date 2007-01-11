/*------------------------------------------------------------------------*/
/* file: sci_xgrid.c                                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xgrid routine                                     */
/*------------------------------------------------------------------------*/

#include "sci_xgrid.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "stack-c.h"
#include "SetProperty.h"
#include "GetProperty.h"
#include "DrawObjects.h"

/*-----------------------------------------------------------------------------------*/
int sci_xgrid(char *fname,unsigned long fname_len)
{
  integer style = 1,m1,n1,l1;
  int status = 0 ;
  CheckRhs(-1,1);
  if (Rhs == 1) {
    GetRhsVar(1,"d",&m1,&n1,&l1);
    CheckScalar(1,m1,n1);
    style = (integer) *stk(l1);
  }
  SciWin();
  LhsVar(1)=0;
  status = sciSetGridStyle( sciGetSelectedSubWin(sciGetCurrentFigure()), style, style, style ) ;
  if ( status == 0 )
  {
    sciDrawObj( sciGetCurrentFigure() ) ;
  }

  return status ;
} 
/*-----------------------------------------------------------------------------------*/
