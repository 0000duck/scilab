/*------------------------------------------------------------------------*/
/* file: sci_xclea.c                                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xclea routine                                     */
/*------------------------------------------------------------------------*/

#include "sci_xclea.h"
#include "stack-c.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
int sci_xclea( char *fname,unsigned long fname_len )
{
  integer m1,n1,l1,m2,n2,l2,m3,n3,l3,m4,n4,l4;

  /* TODO translate in new graphic mode */

  CheckRhs(1,4);
  switch ( Rhs ) 
  {
  case 1 :
    GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1); 
    CheckLength(1,m1*n1,4);
    
    break;
  case 4 :
    GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1); CheckScalar(1,m1,n1);
    GetRhsVar(2,MATRIX_OF_DOUBLE_DATATYPE,&m2,&n2,&l2); CheckScalar(2,m2,n2);
    GetRhsVar(3,MATRIX_OF_DOUBLE_DATATYPE,&m3,&n3,&l3); CheckScalar(3,m3,n3);
    GetRhsVar(4,MATRIX_OF_DOUBLE_DATATYPE,&m4,&n4,&l4); CheckScalar(4,m4,n4);
    
    break;
  default :
    Scierror(999,_("%s: Wrong number of input argument(s): 1 or 4 expected.\n"),fname,Rhs);
  }
  LhsVar(1)=0;
  return 0;
} 
/*--------------------------------------------------------------------------*/
