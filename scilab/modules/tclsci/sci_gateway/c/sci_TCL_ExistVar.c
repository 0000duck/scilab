/*-----------------------------------------------------------------------------------*/
/* INRIA 2005 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include "TCL_Global.h"
#include "gw_tclsci.h"
#include "error_scilab.h"
/*-----------------------------------------------------------------------------------*/
int C2F(sci_TCL_ExistVar) _PARAMS((char *fname,unsigned long l))
{
	static int l1,n1,m1;
	static int l2,n2,m2;

	Tcl_Interp *TCLinterpreter=NULL;

	CheckRhs(1,2);
	CheckLhs(1,1);
	
	if (GetType(1) == sci_strings)
	{
		char *VarName=NULL;

		GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
		VarName=cstk(l1);

		if (TCLinterp == NULL)
		{
			error_scilab(999,"tclsci_error_12",fname);
			return 0;
		}
		
		if (Rhs==2)
		{
			/* two arguments given - get a pointer on the slave interpreter */
			if (GetType(2) == sci_strings)
			{
				GetRhsVar(2,STRING_DATATYPE,&m2,&n2,&l2);
				TCLinterpreter=Tcl_GetSlave(TCLinterp,cstk(l2));
				if (TCLinterpreter==NULL)
				{
					error_scilab(999,"tclsci_error_16",fname);
					return 0;
				}
			}
			else
			{
				error_scilab(999,"tclsci_error_15");
				return 0;
			}
		}
		else
		{
			/* only one argument given - use the main interpreter */
			TCLinterpreter=TCLinterp;
		}

		n1=1;
		if ( Tcl_GetVar(TCLinterpreter, VarName, TCL_GLOBAL_ONLY) )
		{
			CreateVar(Rhs+1,MATRIX_OF_BOOLEAN_DATATYPE, &n1,&n1,&l1);
			*istk(l1)=(int)(TRUE);
		}
		else
		{
			CreateVar(Rhs+1,MATRIX_OF_BOOLEAN_DATATYPE, &n1,&n1,&l1);
			*istk(l1)=(int)(FALSE);
		}
	
		LhsVar(1)=Rhs+1;
		C2F(putlhsvar)();
	}
	else
	{
		error_scilab(999,"tclsci_error_15",fname);
		return 0;
	}
	
	return 0;
}
/*-----------------------------------------------------------------------------------*/
