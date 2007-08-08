/*------------------------------------------------------------------------*/
/* file: sci_xrects.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy, Jean-Philipe Chancelier  */
/* desc : interface for xrects routine                                    */
/*------------------------------------------------------------------------*/

#include "sci_xrects.h"
#include "stack-c.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "sciCall.h"
#include "DrawObjects.h"
#include "GetProperty.h"
#include "SetProperty.h"
#include "CurrentObjectsManagement.h"

/*-----------------------------------------------------------------------------------*/
int sci_xrects( char *fname, unsigned long fname_len )
{
  integer m1,n1,l1,m2,n2,l2;
  long  hdl;
  int i;
  sciPointObj * psubwin = NULL ;
  SciWin();
  CheckRhs(1,2);

  GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1);

  if (m1 != 4) {
    Scierror(999,"%s: rects has a wrong size (4,n) expected \r\n",fname);
    return 0;
  }


  if (Rhs == 2) 
  {
    GetRhsVar(2,MATRIX_OF_INTEGER_DATATYPE,&m2,&n2,&l2);
    CheckVector(2,m2,n2);
    if (m2 * n2 != n1) {
      Scierror(999,"%s: first and second arguments have incompatible length\r\n",fname);
      return 0;
    }
  }
  else 
  {
    m2=1,n2=n1; 
	CreateVar(2,MATRIX_OF_INTEGER_DATATYPE,&m2,&n2,&l2);
    for (i = 0; i < n2; ++i)  { *istk(l2 + i) = 0; }
  }  
  
  psubwin = sciGetCurrentSubWin();

  for (i = 0; i < n1; ++i) { 
    /*       j = (i==0) ? 0 : 1; */
    if (*istk(l2+i) == 0){
      /** fil(i) = 0 rectangle i is drawn using the current line style (or color).**/
      /* color setting is done now */
      int foreground = sciGetForeground(psubwin);
      Objrect (stk(l1+(4*i)),stk(l1+(4*i)+1),stk(l1+(4*i)+2),stk(l1+(4*i)+3),
        &foreground,NULL,FALSE,TRUE,0,&hdl,FALSE);
    }
    else
    {
      if (*istk(l2+i) < 0){
        /** fil(i) < 0 rectangle i is drawn using the line style (or color) **/
        int tmp = - (*istk(l2+i));
        Objrect (stk(l1+(4*i)),stk(l1+(4*i)+1),stk(l1+(4*i)+2),stk(l1+(4*i)+3),
          &tmp,NULL,FALSE,TRUE,0,&hdl,FALSE);
      }
      else         
        /** fil(i) > 0   rectangle i is filled using the pattern (or color) **/
        Objrect (stk(l1+(4*i)),stk(l1+(4*i)+1),stk(l1+(4*i)+2),stk(l1+(4*i)+3),
        NULL,istk(l2+i),TRUE,FALSE,0,&hdl,FALSE);
    }
  }
  /** construct Compound and make it current object **/
  sciSetCurrentObj (ConstructCompoundSeq (n1));  

  sciDrawObjIfRequired(sciGetCurrentObj ());

  LhsVar(1)=0;
  return 0;
} 
/*-----------------------------------------------------------------------------------*/
