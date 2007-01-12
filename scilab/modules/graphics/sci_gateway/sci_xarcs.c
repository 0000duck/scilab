/*------------------------------------------------------------------------*/
/* file: sci_xarcs.h                                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xarcs routine                                      */
/*------------------------------------------------------------------------*/

#include "sci_xarcs.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "SetProperty.h"
#include "GetProperty.h"
#include "sciCall.h"

/*-----------------------------------------------------------------------------------*/
int sci_xarcs(char *fname,unsigned long fname_len)
{
  integer m1,n1,l1,m2,n2,l2;

  /* NG beg */
  long  hdl;
  int i,a1,a2;
  /* NG end */
  SciWin();
  CheckRhs(1,2);

  GetRhsVar(1,"d",&m1,&n1,&l1);
  if ( strcmp(fname,"xarcs") == 0) {
    if (m1 != 6) {
      Scierror(999,"%s: arcs has a wrong size (6,n) expected \r\n",fname);
      return 0;
    }
  } else {
    if (m1 != 4) {
      Scierror(999,"%s: rects has a wrong size (4,n) expected \r\n",fname);
      return 0;
    }
  }

  if (Rhs == 2) 
  {
    GetRhsVar(2,"i",&m2,&n2,&l2);
    CheckVector(2,m2,n2);
    if (m2 * n2 != n1) {
      Scierror(999,"%s: first and second arguments have incompatible length\r\n",fname);
      return 0;
    }
  }
  else 
  {
    int i2;
    m2=1,n2=n1; CreateVar(2,"i",&m2,&n2,&l2);
    for (i2 = 0; i2 < n2; ++i2)
    { 
      *istk(l2 + i2) =  sciGetForeground(sciGetSelectedSubWin(sciGetCurrentFigure ()));
    }
  }  
  /* NG beg */
  for (i = 0; i < n1; ++i)
  { 
    a1=(int)(*stk(l1+(6*i)+4));
    a2=(int)(*stk(l1+(6*i)+5));
    Objarc (&a1,&a2,stk(l1+(6*i)),stk(l1+(6*i)+1),
      stk(l1+(6*i)+2),stk(l1+(6*i)+3),istk(l2+i),NULL,FALSE,TRUE,&hdl); 
  }
  /** construct Compound and make it current object **/
  sciSetCurrentObj (ConstructCompoundSeq (n1));
  /* NG end */
  LhsVar(1)=0;
  return 0;
} 
/*-----------------------------------------------------------------------------------*/
