/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "gw_core.h"
#include "machine.h"
#include "stack-c.h"
#include "scilines.h"
#include "Scierror.h"
#include "MALLOC.h"
/*-----------------------------------------------------------------------------------*/
int C2F(sci_lines) _PARAMS((char *fname,unsigned long fname_len))
{
	CheckRhs(0,2);
	CheckLhs(1,1);

	if (Rhs ==  0)
	{
		int n1 = 0,m1 = 0;
		int *paramoutINT = NULL;
		paramoutINT=(int*)MALLOC(sizeof(int)*2);
		
		paramoutINT[0] = getColumnsSize();
		paramoutINT[1] = getLinesSize();
		
		n1=1; m1=2;
		CreateVarFromPtr(Rhs+1,MATRIX_OF_INTEGER_DATATYPE, &n1, &m1, &paramoutINT);

		LhsVar(1) = Rhs+1;
		C2F(putlhsvar)();	

		if (paramoutINT) { FREE(paramoutINT); paramoutINT = NULL;}
	}
	else
	{
		if (Rhs == 2)
		{
			if ( GetType(2) == sci_matrix )
			{
				int l2 = 0,n2 = 0, m2 = 0;
				int columns = 0;

				GetRhsVar(2,MATRIX_OF_DOUBLE_DATATYPE,&m2,&n2,&l2);
				columns = (int)*stk(l2);
				setColumnsSize(columns);
			}
			else
			{
				Scierror(999,"Invalid parameter(s).\n");
				return 0;
			}
		}

		if ( GetType(1) == sci_matrix )
		{
			int l1 = 0,n1 = 0, m1 = 0;
			int lines = 0;

			GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1);
			lines = (int)*stk(l1);
			setLinesSize(lines);
		}
		else
		{
			Scierror(999,"Invalid parameter(s).\n");
			return 0;
		}

		LhsVar(1) = 0;
		C2F(putlhsvar)();
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
