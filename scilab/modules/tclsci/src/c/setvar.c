/*--------------------------------------------------------------------------*/
/* CORNET Allan */
/* INRIA */
/*--------------------------------------------------------------------------*/
#include "setvar.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
BOOL SetVarMatrix(Tcl_Interp *TCLinterpreter,char *VarName,int ptrValues,int m,int n)
{
	BOOL bOK = TRUE;
	int i=0,j=0;
	int k=0;

	double *MatrixDouble=(double*)MALLOC((m*n)*sizeof(double));

	/* Efface valeur precedente */
	Tcl_UnsetVar(TCLinterpreter, VarName, TCL_GLOBAL_ONLY);

	for (i=0;i<m*n;i++)
	{
		MatrixDouble[i]=*stk(ptrValues++);
	}

	k=0;
	for (i=1;i<m+1;i++)
	{
		char VarValueWithIndice[2048];
		char VarNameWithIndice[2048];

		for (j=1;j<n+1;j++)
		{	
			int bOKsprintf1=0;
			int bOKsprintf2=0;

			bOKsprintf1=sprintf(VarNameWithIndice,"%s(%d,%d)",VarName,i,j);
			bOKsprintf2=sprintf(VarValueWithIndice,"%.10lf",MatrixDouble[(i-1)+m*(j-1)]);

			if ( (bOKsprintf1 == -1) || (bOKsprintf2 == -1) )
			{
				Scierror(999,_("Variable too long.\n"));
				return FALSE;
			}

			if (TCLinterpreter == NULL)
			{
				Scierror(999,_("TCL_SetVar: Error TCL interpreter not initialized.\n"));
				return FALSE;
			}

			if (!Tcl_SetVar(TCLinterpreter,VarNameWithIndice,VarValueWithIndice,0))
			{
				bOK = FALSE ;
			}
		}
	}
	if (MatrixDouble) {FREE(MatrixDouble);MatrixDouble=NULL;}
	return bOK;
}
/*--------------------------------------------------------------------------*/
BOOL SetVarScalar(Tcl_Interp *TCLinterpreter,char *VarName,double VarValue)
{
	BOOL bOK = FALSE;

	/* just a scalar */
	char buffer[2048];

	sprintf(buffer,"%.10lf", VarValue);

	if (TCLinterpreter == NULL)
	{
		Scierror(999,_("TCL_SetVar: Error TCL interpreter not initialized.\n"));
		return FALSE;
	}

	/* Efface valeur precedente */
	Tcl_UnsetVar(TCLinterpreter, VarName, TCL_GLOBAL_ONLY);

	if (!Tcl_SetVar(TCLinterpreter,VarName,buffer,TCL_GLOBAL_ONLY))
	{
		bOK = FALSE ;
	}
	else
	{
		bOK = TRUE;
	}
	return bOK;
}
/*--------------------------------------------------------------------------*/
BOOL SetVarStrings(Tcl_Interp *TCLinterpreter,char *VarName,char **Str,int m,int n)
{
	BOOL bOK = FALSE;

	int i=0,j=0;
	int l=0;
	BOOL TestOnAllTcl_SetVar = TRUE;

	if (TCLinterpreter == NULL)
	{
		Scierror(999,_("TCL_SetVar: Error TCL interpreter not initialized.\n"));
		return FALSE;
	}

	for (j=1;j<n+1;j++)
	{
		for (i=1;i<m+1;i++)
		{	
			char VarArrayName[1024];
			sprintf(VarArrayName,"%s(%d,%d)",VarName,i,j);
			if (Tcl_SetVar(TCLinterpreter, VarArrayName, Str[l++], TCL_GLOBAL_ONLY))
			{
				if (TestOnAllTcl_SetVar) TestOnAllTcl_SetVar=TRUE;
			}
			else
			{
				TestOnAllTcl_SetVar = FALSE;
			}
		}
	}
	bOK = TestOnAllTcl_SetVar;

	return bOK;
}
/*--------------------------------------------------------------------------*/
BOOL SetVarAString(Tcl_Interp *TCLinterpreter,char *VarName,char **Str)
{
	BOOL bOK = FALSE;

	if (TCLinterpreter == NULL)
	{
		Scierror(999,_("TCL_SetVar: Error TCL interpreter not initialized.\n"));
		return FALSE;
	}

	if ( !Tcl_SetVar(TCLinterpreter, VarName, Str[0], TCL_GLOBAL_ONLY) )
	{
		bOK = FALSE;
	}
	else
	{
		bOK = TRUE;
	}
	return bOK;
}
/*--------------------------------------------------------------------------*/
