/*-----------------------------------------------------------------------*/
/* Copyright INRIA 2007                                                  */
/* @Author : Allan CORNET                                                */
/*-----------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "gw_string.h"
#include "machine.h"
#include "stack-c.h"
#include "Scierror.h"
#include "localization.h"
#include "BOOL.h"
#include "freeArrayOfString.h"
#include "isletter.h"
#include "MALLOC.h"
/*----------------------------------------------------------------------------*/
int C2F(sci_isletter) _PARAMS((char *fname,unsigned long fname_len))
{
	int Type_One = 0;
	
	CheckRhs(1,1);
	CheckLhs(1,1);

	Type_One = VarType(1);
	if (Type_One == sci_strings)
	{
		char **Input_StringMatrix = NULL;
		BOOL *values = NULL;
		int Row_Num = 0,Col_Num = 0;
		int mn = 0; /* Row_Num * Col_Num */

		GetRhsVar(1,MATRIX_OF_STRING_DATATYPE,&Row_Num,&Col_Num,&Input_StringMatrix);
		mn = Row_Num * Col_Num;

		if (mn != 1)
		{
			freeArrayOfString(Input_StringMatrix,mn);
			Scierror(999,_("%s : First input argument has a wrong dimension, expecting a string.\n"),fname);
			return 0;
		}

		values = isletter(Input_StringMatrix[0]);

		if (values)
		{
			int m1 = 1;
			int n1 = (int)strlen(Input_StringMatrix[0]);
			CreateVarFromPtr(Rhs+1,MATRIX_OF_BOOLEAN_DATATYPE, &m1, &n1, &values);
			LhsVar(1)=Rhs+1;
			C2F(putlhsvar)();

			freeArrayOfString(Input_StringMatrix,mn);
			if (values) {FREE(values);values = NULL;}
		}
		else
		{
			/* returns [] */
			int m1 = 0;
			int n1 = 0;
			int l = 0;
			CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l);
			LhsVar(1) = Rhs+1 ;
			C2F(putlhsvar)();
			return 0;
		}
	}
	else
	{
		Scierror(999,_("%s : First input argument has a wrong type, expecting a string.\n"),fname);
	}
	return 0;
}
/*--------------------------------------------------------------------------*/

