/*------------------------------------------------------------------------*/
/* file: sci_xarrows.h                                                    */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xarrows routine                                   */
/*------------------------------------------------------------------------*/

#include "sci_xarrows.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "sciCall.h"
#include "stack-c.h"
#include "GetProperty.h"

/*-----------------------------------------------------------------------------------*/
int sci_xarrows(char *fname,unsigned long fname_len)
{
  integer dstyle = -1,m1,n1,l1,m2,n2,l2,m3=1,n3=1,l3;
  integer *style,flag;
  integer m4,n4,l4,mn2;
  double arsize=-1.0;

  SciWin();
  CheckRhs(2,4);

  GetRhsVar(1,"d",&m1,&n1,&l1);
  GetRhsVar(2,"d",&m2,&n2,&l2);
  mn2 = m2 * n2;
  CheckSameDims(1,2,m1,n1,m2,n2);
  if (mn2 == 0) {   LhsVar(1)=0;  return 0;} 

  if (Rhs >= 3) { GetRhsVar(3,"d",&m3,&n3,&l3); CheckScalar(3,m3,n3); arsize = *stk(l3); } 

  if (Rhs >= 4) { 
    GetRhsVar(4,"i",&m4,&n4,&l4); CheckVector(4,m4,n4);
    if (m4 * n4 == 1) dstyle = *istk(l4);
    if (m4 * n4 != 1 && m2 * n2 / 2 != m4 * n4) {
      Scierror(999,"%s: style has a wrong size (%d), expecting (%d)\r\n",fname,m4*n4, m2 * n2 / 2 );
      return 0;
    }
  }
  /* NG beg */
  if (Rhs == 4 && m4 * n4 != 1)
  {
    style=istk(l4) ;
    flag = 1 ;
  } 
  else {
    style = &dstyle ;
    flag = 0;
  }
  
  Objsegs (style,flag,mn2,stk(l1),stk(l2),arsize);
  

  LhsVar(1)=0;
  return 0;
} 


/*-----------------------------------------------------------------------------------*/
