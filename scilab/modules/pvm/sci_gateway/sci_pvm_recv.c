/*-----------------------------------------------------------------------------------*/
/* PVM functions interfaces */
/* Copyright (c) 1997 by Inria Lorraine.  All Rights Reserved */
/* Jean-Philippe Chancelier July 2002  */
/* Modified by Allan Cornet  INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include "sci_pvm_recv.h"
/*-----------------------------------------------------------------------------------*/ 
extern void pvm_error_check(char *fname,int err);
/*-----------------------------------------------------------------------------------*/ 
/******************************************
 * SCILAB function : pvm_recv, fin = 21
 ******************************************/
int intspvm_recv(char *fname)
{
  int m1,n1,l1,m2,n2,l2,un=1,l3,used,size,l5,count=5,l,tid,tag;
  CheckRhs(2,2);
  CheckLhs(1,4);
  /*  checking variable tid */
  GetRhsVar(1,"i",&m1,&n1,&l1);
  CheckScalar(1,m1,n1);
  tid=*istk(l1);
  /*  checking variable tag */
  GetRhsVar(2,"i",&m2,&n2,&l2);
  CheckScalar(2,m2,n2);
  tag=*istk(l2);
  /* space for info */ 
  CreateVar(3,"i",&un,&un,&l3);/* named: res */
  /* space for paking info */ 
  CreateWork(4,&size,&l5); 
  /* variable at position 4 is created as a scalar matrix 
   * but we transmit stk(l5-2) to scipvmrecv which 
   * then can change the header of object at position 4 
   */ 
  C2F(scipvmrecv)(stk(l5-2),&size,&used,&tid,&tag,istk(l3));
  /* now we know the exact size used */
  SetWorkSize(4,&used);
  LhsVar(1)=4;
  LhsVar(2)=3;
  LhsVar(3)=1;
  LhsVar(4)=2;
  /* since 1 and 2 could be ref */ 
  if ( IsRef(1) ) { 
    CreateVar(count,"i",&un,&un,&l);
    *istk(l)=tid;
    LhsVar(3)=count;
    count++;
  }
  if ( IsRef(2) ) { 
    CreateVar(count,"i",&un,&un,&l);
    *istk(l)=tag;
    LhsVar(4)=count;
  }
  pvm_error_check(fname,*istk(l3));
  return 0;
}
/*-----------------------------------------------------------------------------------*/ 
