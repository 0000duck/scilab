/*------------------------------------------------------------------------*/
/* file: sci_xgraduate.c                                                  */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xgraduate routine                                 */
/*------------------------------------------------------------------------*/

#include "sci_xgraduate.h"
#include "stack-c.h"
#include "Format.h"

/*-----------------------------------------------------------------------------------*/
int sci_xgraduate(char *fname,unsigned long fname_len)
{
  double xa,xi;
  integer m1,n1,l1,m2,n2,l2,i;
  integer kMinr,kMaxr,ar,lr,np1,np2,un=1;

  CheckRhs(2,2);
  CheckLhs(2,7);
  GetRhsVar(1,"d",&m1,&n1,&l1);  CheckScalar(1,m1,n1);
  GetRhsVar(2,"d",&m2,&n2,&l2);  CheckScalar(2,m2,n2);

  C2F(graduate)(stk(l1),stk(l2),&xi,&xa,&np1,&np2,&kMinr,&kMaxr,&ar);

  *stk(l1) = xi;
  *stk(l2) = xa;

  if (Lhs >= 3) { CreateVar(3,"d",&un,&un,&lr); *stk(lr ) = (double) np1;  }
  if (Lhs >= 4) { CreateVar(4,"d",&un,&un,&lr); *stk(lr ) = (double) np2;  }
  if (Lhs >= 5) { CreateVar(5,"d",&un,&un,&lr); *stk(lr ) = (double) kMinr;  }
  if (Lhs >= 6) { CreateVar(6,"d",&un,&un,&lr); *stk(lr ) = (double) kMaxr;  }
  if (Lhs >= 7) { CreateVar(7,"d",&un,&un,&lr); *stk(lr ) = (double) ar;  }
  for (i= 1; i <= Lhs ; i++) { LhsVar(i) = i ; }
  return 0;
}
/*-----------------------------------------------------------------------------------*/
