/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/ 
#include "intrealtime.h"
/*-----------------------------------------------------------------------------------*/ 
extern int C2F(realtime)(double *t);
extern int C2F(realtimeinit)(double *t,double *scale); 
/*-----------------------------------------------------------------------------------*/ 
int C2F(intrealtimeinit) _PARAMS((char *fname,unsigned long fname_len))
{
 int m1,n1,l1;
 double zer=0.0;
 CheckRhs(1,1);
 CheckLhs(1,1);
 /*  checking variable scale */
 GetRhsVar(1,"d",&m1,&n1,&l1);
 CheckScalar(1,m1,n1);
 /* cross variable size checking */
 C2F(realtimeinit)(&zer,stk(l1));
 LhsVar(1)=0;
 return 0;
}
/*-----------------------------------------------------------------------------------*/  
int C2F(intrealtime) _PARAMS((char *fname,unsigned long fname_len))
{
 int m1,n1,l1;
 CheckRhs(1,1);
 CheckLhs(1,1);
 /*  checking variable t */
 GetRhsVar(1,"d",&m1,&n1,&l1);
 CheckScalar(1,m1,n1);
 /* cross variable size checking */
 C2F(realtime)(stk(l1));
 LhsVar(1)=0;
 return 0;
}               
/*-----------------------------------------------------------------------------------*/ 
