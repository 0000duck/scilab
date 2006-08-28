/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include "../stack-c.h"
/*-----------------------------------------------------------------------------------*/
extern void C2F(msgs)(int *n, int* ierr);
extern void  C2F(zbeshv) (double *xr,double *xi,int* nx, double *alpha, int *na,int *kode, int *K, double *rr,double *ri, double *wr, double *wi, int *ierr);
/*-----------------------------------------------------------------------------------*/
int intbesselh(char *fname,unsigned long fname_len)
/* Author Serge Steer, Copyright INRIA 2005 */
{
  int m1,n1,l1,m2,n2,it2,l2,/*l2r,*/l2i,mr,nr,itr,lr,li,lwi,lwr,rhs1;
  int r1,r2,na,nx,kode,lpos;
  int un=1,ierr;
  int K;

  static int *Lstk    = C2F(vstk).lstk-1;

 
  CheckRhs(2,4);
  kode = 1;
  rhs1 = Rhs;
  if (Rhs==4) { /* normalized bessel required */
    GetRhsVar(4,"d",&m1,&n1,&l1);CheckScalar(1,m1,n1);
    kode = (int)*stk(l1)+1;
    rhs1--;
  }
  K = 1; 
  if (Rhs > 2) { /* normalized bessel required */
    GetRhsVar(2,"d",&m1,&n1,&l1);CheckScalar(1,m1,n1);
    K = (int)*stk(l1);
  }

  GetRhsVar(1,"d",&m1,&n1,&l1); /* get alpha */
  r1=l1>Lstk[Bot]; /* true if the variable has been passed by reference */

  GetRhsCVar(rhs1,"d",&it2,&m2,&n2,&l2,&l2i); /* get x */
  r2=l2>Lstk[Bot];/* true if the variable has been passed by reference */
  
  if (m1*n1 == 0) { /*besselh([],x) */
    LhsVar(1)=1;
    return 0;
  }
  if (m2*n2 == 0) { /*besselh(alpha,[]) */
    LhsVar(1)=rhs1;
    return 0;
  }

  itr=1;
  lpos=Rhs;
  if(it2 == 0) {
    int i;
    CreateVar(lpos+1,"d",&m2,&n2,&l2i);
    for (i=0;i<m2*n2;i++) *stk(l2i+i)=0.0;
    lpos=lpos+1;
  }
  if (m1*n1 == 1) { /*bessely(scalar,matrix) */
    double wr[3],wi[3];
    mr=m2;
    nr=n2;    
    CreateCVar(lpos+1,"d",&itr,&mr,&nr,&lr,&li);
    LhsVar(1)=lpos+1;
 
    nx=m2*n2;
    na=1;
    C2F(zbeshv) (stk(l2),stk(l2i),&nx,stk(l1),&na,&kode,&K,stk(lr),stk(li),wr,wi,&ierr);
  }

  else if (m2*n2 == 1) { /* bessely(matrix,scalar) */
    int lwr,lwi,nw;
    mr=m1;
    nr=n1;   
    CreateCVar(lpos+1,"d",&itr,&mr,&nr,&lr,&li);
    nx=1;
    na=m1*n1;
    nw=3*na;
    CreateCVar(lpos+2,"d",&itr,&nx,&nw,&lwr,&lwi);
    C2F(zbeshv) (stk(l2),stk(l2i),&nx,stk(l1),&na,&kode,&K,stk(lr),stk(li),stk(lwr),stk(lwi),&ierr);

    LhsVar(1)=lpos+1;
  }
  else if ((m1==1 && n2==1)|| (n1==1 && m2==1)) { /* bessely(row,col) or bessely(col,row) */
    int un=1,nw;
    mr=m2*n2;
    nr=m1*n1;
    CreateCVar(lpos+1,"d",&itr,&mr,&nr,&lr,&li);
    nx=m2*n2;
    na=m1*n1;
    nw=3*na;
    CreateCVar(lpos+2,"d",&itr,&un,&nw,&lwr,&lwi);
    C2F(zbeshv) (stk(l2),stk(l2i),&nx,stk(l1),&na,&kode,&K, stk(lr),stk(li),stk(lwr),stk(lwi),&ierr);

    LhsVar(1)=lpos+1;
  }
  else { /* element wise case */
    double wr[2],wi[2];
    CheckDimProp(1,2,m1*n1!=m2*n2) 
    mr=m2;
    nr=n2;  
    CreateCVar(lpos+1,"d",&itr,&mr,&nr,&lr,&li);
    LhsVar(1)=lpos+1;
    nx=mr*nr;
    na=-1;
    C2F(zbeshv) (stk(l2),stk(l2i),&nx,stk(l1),&na,&kode,&K,stk(lr),stk(li),wr,wi,&ierr);
  }
  if (ierr==2) {
    if ( C2F(errgst).ieee==0) { 
      ierr=69;
      C2F(error)(&ierr);
    }
    else if ( C2F(errgst).ieee==1) {
     ierr=63;
     C2F(msgs)(&ierr,&un);
 
    }
  }
  else if (ierr==3) {/* inacurate result */
    ierr=4;
    C2F(msgs)(&ierr,&un);
  }
  else if (ierr==4||ierr==5) {
    if ( C2F(errgst).ieee==0) { 
      ierr=69;
      C2F(error)(&ierr);
    }
    else if ( C2F(errgst).ieee==1) {
     ierr=107;
     C2F(msgs)(&ierr,&un);
    }
 }
 

  return 0;
}  
/*-----------------------------------------------------------------------------------*/
