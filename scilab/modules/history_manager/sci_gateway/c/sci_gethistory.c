/*--------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/ 
#include "gw_history_manager.h"
#include "machine.h"
#include "stack-c.h"
#include "localization.h"
#include "MALLOC.h"
#include "HistoryManager.h"
/*--------------------------------------------------------------------------*/
int C2F(sci_gethistory) _PARAMS((char *fname,unsigned long fname_len))
{
	static int l1 = 0, m1 = 0, n1 = 0;	
	CheckRhs(0,1);
	CheckLhs(1,1);

	if (getNumberOfLinesInScilabHistory() <= 0)
	{
		m1=0; n1=0;
		CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,  &m1, &n1, &l1);
		LhsVar(1)=Rhs+1;
		C2F(putlhsvar)();
		return 0;
	}

	if (Rhs == 1) 
	{
		if (GetType(1) == sci_matrix)
		{
			int N = 0;
			char *line = NULL;
			GetRhsVar(1,MATRIX_OF_INTEGER_DATATYPE,&m1,&n1,&l1);
			N = *istk(l1);
			line = getNthLineInScilabHistory(N);
			if (line)
			{
				n1=1;
				CreateVarFromPtr(Rhs+ 1,STRING_DATATYPE,(m1=(int)strlen(line), &m1),&n1,&line);
				FREE(line);
			}
			else
			{
				m1=0; n1=0;
				CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,  &m1, &n1, &l1);
			}
		}
		else
		{
			Scierror(999,_("parameter must be a integer.\n"));
			return 0;
		}
	}
	else
	{
		char **lines = NULL;
		int nblines = 0;

		nblines = getSizeAllLinesOfScilabHistory();
		lines = getAllLinesOfScilabHistory();

		if (lines)
		{
			int m = 0, n = 0;

			m = nblines;
			n = 1;

			CreateVarFromPtr(Rhs+1,MATRIX_OF_STRING_DATATYPE, &m, &n, lines);
			LhsVar(1) = Rhs+1;
			if (lines)
			{
				int i = 0;

				for (i=0;i < nblines;i++) 
				{ 
					if (lines[i])
					{
						FREE(lines[i]);
						lines[i]=NULL; 
					}
				}
				FREE(lines);
				lines=NULL; 
			}
		}
		else
		{
			m1=0; n1=0;
			CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,  &m1, &n1, &l1);
		}
	}
	
	LhsVar(1)=Rhs+1;
	C2F(putlhsvar)();
	return 0;
}
/*--------------------------------------------------------------------------*/
