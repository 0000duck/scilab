/*-----------------------------------------------------------------------------------*/
/* PVM functions interfaces */
/* Copyright (c) 1997 by Inria Lorraine.  All Rights Reserved */
/* Jean-Philippe Chancelier July 2002  */
/* Modified by Allan Cornet  INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include "gw_pvm.h"
#include "sci_pvm.h"
/*-----------------------------------------------------------------------------------*/ 
/******************************************
 * SCILAB function : pvm_bcast, fin = 7
 ******************************************/
int intspvm_bcast _PARAMS((char *fname,unsigned long fname_len))
{
  int m1,n1,l1,m3,n3,l3,un=1,l4,size,l5,used,ierr;
  int *Ipack,address,*header;
  CheckRhs(3,3);
  CheckLhs(1,1);
  /*  checking variable group */
  GetRhsVar(1,"c",&m1,&n1,&l1);
  /*  checking variable buff */
  header = GetData(2);
  /*  checking variable msgtag */
  GetRhsVar(3,"i",&m3,&n3,&l3);
  CheckScalar(3,m3,n3);
  /* cross variable size checking */
  CreateVar(4,"i",&un,&un,&l4);/* named: res */
  /* Use the rest of the stack as working area */ 
  CreateWork(5,&size,&l5); 
  Ipack= (int *) stk(l5);
  /* Build a pack vector for buff: size is the max size 
   * allowed for packing 
   */ 
  address = Top-Rhs+2;
  C2F(varpak)(&address,Ipack,&used,&size,&ierr); 
  switch (ierr ) { 
  case 1: Scierror(999,"%s: work space (stacksize) is too small d\r\n",fname);
    return 0;
  case 2: Scierror(999,"%s: Unknow type or not yet implemented\r\n",fname);
    return 0; 
  }
  C2F(scipvmbcast)(cstk(l1),&m1,Ipack,&used,(double *)header,istk(l3),istk(l4));
  LhsVar(1)= 4;
  pvm_error_check(fname,*istk(l4),fname_len);
  return 0;
}
/*-----------------------------------------------------------------------------------*/ 
