/*--------------------------------------------------------------------------*/
/**
 * @author Allan CORNET INRIA 2007
 */
/*--------------------------------------------------------------------------*/
#include "gw_jvm.h"
#include "MALLOC.h"
#include "machine.h"
#include "stack-c.h"
#include "Scierror.h"
#include "addToClasspath.h"
#include "getClasspath.h"
#include "localization.h"
#include "freeArrayOfString.h"
/*--------------------------------------------------------------------------*/
int C2F(sci_javaclasspath) _PARAMS((char *fname,unsigned long fname_len))
{
	Rhs = Max(Rhs,0);
	CheckRhs(0,1);
	CheckLhs(0,1);

	if (Rhs == 0)
	{
		int nbRow=0;
		int nbCol=1;
		char **Strings=NULL;

		Strings=getClasspath(&nbRow);
		CreateVarFromPtr( Rhs+1,MATRIX_OF_STRING_DATATYPE, &nbRow, &nbCol,Strings );

		LhsVar(1)=Rhs+1;
		C2F(putlhsvar)();
		freeArrayOfString(Strings,nbRow*nbCol);
	}
	else
	{
		if ( GetType(1) == sci_strings )
		{
			static int n1=0,m1=0;
			int i=0;
			char **classPaths=NULL;

			GetRhsVar(1,MATRIX_OF_STRING_DATATYPE,&m1,&n1,&classPaths);

			for (i = 0; i<m1*n1 ;i++)
			{
				if (!addToClasspath(classPaths[i]))
				{
					Scierror(999,_("%s: Could not add URL to system classloader : %s.\n"),fname,classPaths[i]);
					freeArrayOfString(classPaths,m1*n1);
					return 0;
				}
			}
			LhsVar(1) = 0;
			C2F(putlhsvar)();	
			freeArrayOfString(classPaths,m1*n1);
		}
		else
		{
			Scierror(999,_("%s: Wrong type for input argument: String expected.\n"),fname);
		}
	}
	return 0;
}
/*--------------------------------------------------------------------------*/
