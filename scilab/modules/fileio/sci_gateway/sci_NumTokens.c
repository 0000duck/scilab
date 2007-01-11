/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include "machine.h"
#include "stack-c.h"
#include "fileio.h"
/*-----------------------------------------------------------------------------------*/ 
int int_objnumTokens(char *fname,unsigned long fname_len);
/*-----------------------------------------------------------------------------------*/ 
int int_objnumTokens(char *fname,unsigned long fname_len)
{
	static int l1,m1,n1,l2,un=1;
	Nbvars = 0;
	CheckRhs(1,1);
	GetRhsVar(1,"c",&m1,&n1,&l1);
	StringConvert(cstk(l1));  /* conversion */
	CreateVar(2, "d", &un, &un, &l2);
	*stk(l2) = (double) NumTokens(cstk(l1));
	LhsVar(1) = 2;
	PutLhsVar();
	return 0;
}  
/*-----------------------------------------------------------------------------------*/ 
