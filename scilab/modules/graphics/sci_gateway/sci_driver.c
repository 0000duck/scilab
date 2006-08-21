/*------------------------------------------------------------------------*/
/* file: sci_driver.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for driver routine                                    */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "sci_driver.h"
#include "stack-c.h"
#include "Graphics.h"

/*-----------------------------------------------------------------------------------*/
int sci_driver(char *fname,unsigned long fname_len)
{
  integer m1=3,n1=1,l1,v ;
  double dv;
  CheckRhs(-1,1);
  CheckLhs(0,1);
  if (Rhs <= 0) 
  {
    CreateVar(1,"c",&m1,&n1,&l1);
    C2F(dr1)("xgetdr", cstk(l1), &v, &v, &v, &v, &v, &v, &dv, &dv, &dv, &dv, 7L, m1);
    LhsVar(1) = 1;
  } 
  else 
  {
    GetRhsVar(1,"c",&m1,&n1,&l1);
    C2F(dr1)("xsetdr", cstk(l1), &v, &v, &v, &v, &v, &v, &dv, &dv, &dv, &dv, 7L, m1);
    LhsVar(1)=0;
  }
  return 0;
}
/*-----------------------------------------------------------------------------------*/