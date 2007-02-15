/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "gw_core.h"
#include "machine.h"
#include "stack-c.h"
#include "Scierror.h"
#include "Funtab.h"
/*-----------------------------------------------------------------------------------*/
extern int IsAScalar(int RhsNumber);
/*-----------------------------------------------------------------------------------*/
static BOOL Is_a_correct_function_name(char *functionname);
/*-----------------------------------------------------------------------------------*/
int C2F(sci_newfun) _PARAMS((char *fname,unsigned long fname_len))
{
	static int l1,n1,m1;

	CheckRhs(2,2);
	CheckLhs(1,1);

	if ( (GetType(1) == sci_strings) &&  IsAScalar(2) )
	{
		char *VarName=NULL;
		int nameptr=0;
		
		GetRhsVar(1,"c",&m1,&n1,&l1);
		VarName=cstk(l1);

		GetRhsVar(2,"i",&m1,&n1,&l1);
		nameptr=*istk(l1);

		if (nameptr > 0)
		{
			if (Is_a_correct_function_name(VarName))
			{
				int id[nsiz];
				int zero=0;
				int fptr=nameptr;
				int job=3;

				C2F(cvname)(id,VarName,&zero,strlen(VarName));
				C2F(funtab)(id,&fptr,&job,VarName,strlen(VarName));

				LhsVar(1)=0;
				PutLhsVar();
			}
			else
			{
				Scierror(999,"function-name is incorrect.\n");
				return 0;
			}
		}
		else
		{
			Scierror(999,"nameptr argument must be >0.\n");
			return 0;
		}
	}
	else
	{
		Scierror(999,"See help newfun.\n");
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
static BOOL Is_a_correct_function_name(char *functionname)
{
	BOOL bOK=TRUE;
	int i=0;

	for(i=0;i<(int)strlen(functionname);i++)
	{
		if (functionname[i] == ' ')
		{
			return FALSE;
		}
		if (functionname[i] == '+')
		{
			return FALSE;
		}
		if (functionname[i] == '-')
		{
			return FALSE;
		}
		if (functionname[i] == '/')
		{
			return FALSE;
		}
		if (functionname[i] == '\\')
		{
			return FALSE;
		}
		if (functionname[i] == '.')
		{
			return FALSE;
		}
		if (functionname[i] == '*')
		{
			return FALSE;
		}
		if (functionname[i] == ',')
		{
			return FALSE;
		}
		if (functionname[i] == '!')
		{
			return FALSE;
		}
		if (functionname[i] == ';')
		{
			return FALSE;
		}
		if (functionname[i] == '&')
		{
			return FALSE;
		}
		/* To be continued ... :( */
	}
	return bOK;
}
/*-----------------------------------------------------------------------------------*/
