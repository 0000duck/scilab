/*--------------------------------------------------------------------------*/
/* INRIA 2006 */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include "machine.h"
#include "stack-c.h"
#include "CdfBase.h"
#include "Scierror.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
int  CdfBase(char *fname,int inarg,int oarg,int *callpos,char *option,char *errnames,int which,int (*fonc)(),void (*foncErr)() )
{
	int i,status=0,m[6],n[6],l[6];
	double bound;
	if ( Rhs != inarg+1 )
	{
		Scierror(999,_("%s: Rhs must be %d for '%s' option'\n"),fname,inarg+1,option);
		return 1;
	}
	for ( i = 0 ; i < inarg ; i++ )
	{
		GetRhsVar(i+2,MATRIX_OF_DOUBLE_DATATYPE, &m[i], &n[i], &l[i]);
	}
	for ( i = 1 ; i < inarg ; i++)
		if ( m[i] != m[i-1] || n[i] != n[i-1])
		{
			Scierror(999,_("%s %s must have same size\n"),fname,errnames);
			return 1;
		}
		for ( i = 0 ; i < oarg ; i++)
			CreateVar(i+2+inarg,MATRIX_OF_DOUBLE_DATATYPE,&m[0],&n[0],&l[i+inarg]);
		switch ( inarg+oarg)
		{
		case 5:
			for ( i=0 ; i < m[0]*n[0]; i++)
			{
				(*fonc)(&which,stk(l[callpos[0]]+i),stk(l[callpos[1]]+i),
					stk(l[callpos[2]] +i),stk(l[callpos[3]]+i),
					stk(l[callpos[4]]+i),
					&status,&bound);
				if (status != 0)
				{
					(*foncErr)(status,bound); return 1;
				}
			}
			break;
		case 6:
			for ( i=0 ; i < m[0]*n[0]; i++)
			{
				(*fonc)(&which,stk(l[callpos[0]]+i),stk(l[callpos[1]]+i),
					stk(l[callpos[2]] +i),stk(l[callpos[3]]+i),
					stk(l[callpos[4]] +i),stk(l[callpos[5]]+i),
					&status,&bound);
				if (status != 0)
				{
					/** Scierror(999,"i=%d\n",i); **/
					(*foncErr)(status,bound); return 1;
				}
			}
			break;
		case 4:
			for ( i=0 ; i < m[0]*n[0]; i++)
			{
				(*fonc)(&which,stk(l[callpos[0]]+i),stk(l[callpos[1]]+i),
					stk(l[callpos[2]] +i),stk(l[callpos[3]]+i),
					&status,&bound);
				if (status != 0)
				{
					(*foncErr)(status,bound); return 1;
				}
			}
			break;
		}
		for ( i = 0 ; i < oarg ; i++)
			LhsVar(i+1) = i+2+inarg;
		PutLhsVar();
		return 0;
}
/*--------------------------------------------------------------------------*/




