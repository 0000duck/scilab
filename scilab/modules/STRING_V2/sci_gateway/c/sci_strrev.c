/*----------------------------------------------------------------------------*/
/* Copyright INRIA 2007 */
/* @Author : Allan CORNET */
/*----------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "gw_string.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
#include "stringsstrrev.h"
/*----------------------------------------------------------------------------*/
int C2F(sci_strrev) _PARAMS((char *fname,unsigned long fname_len))
{
	CheckRhs(1,1);
	CheckLhs(0,1);

	if (GetType(1) == sci_strings)
	{
		int m1 = 0; int n1 = 0;
		char **InputStrings = NULL;
		int m1n1 = 0; /* m1 * n1 */

		char **OutputStrings = NULL;

		GetRhsVar(1,MATRIX_OF_STRING_DATATYPE,&m1,&n1,&InputStrings);
		m1n1 = m1 * n1;

		OutputStrings = strings_strrev(InputStrings,m1n1);

		if (OutputStrings)
		{
			CreateVarFromPtr(Rhs+1,MATRIX_OF_STRING_DATATYPE,&m1,&n1,OutputStrings);
			LhsVar(1) = Rhs+1 ;
			C2F(putlhsvar)();
			freeArrayOfString(InputStrings,m1n1);
			freeArrayOfString(OutputStrings,m1n1);
		}
		else
		{
			freeArrayOfString(InputStrings,m1n1);
			Scierror(999,"%s: Out of memory.\n",fname);
			return 0;
		}
	}
	else
	{
		Scierror(999,_("%s : Invalid input parameter.\n"),fname);
	}
	return 0;
}
/*--------------------------------------------------------------------------*/
