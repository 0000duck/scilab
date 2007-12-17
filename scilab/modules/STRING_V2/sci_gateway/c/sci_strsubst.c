/*------------------------------------------------------------------------*/
/* File: sci_strsubst.c                                                   */
/* Copyright INRIA 2007                                                   */
/* @Authors : Cong Wu , Allan CORNET                                      */
/* desc : substitute a character string by another in a character string  */
/*------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "gw_string.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "freeArrayOfString.h"
#include "strsubst.h"

/*-------------------------------------------------------------------------------------*/
int C2F(sci_strsubst) _PARAMS((char *fname,unsigned long fname_len))
{
	CheckRhs(3,3);
	CheckLhs(1,1);

	if ( (VarType(2) == sci_strings) && (VarType(2) == sci_strings) ) /* @TODO why do we have it twice ? */
	{
		switch (VarType(1))
		{
			case sci_matrix :
			{
				int m = 0, n = 0 , l = 0;
				GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m,&n,&l);
				if ( (m == 0) && (n == 0) ) /* strsubst([],...) */
				{
					l = 0;
					CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,&m,&n,&l);
					LhsVar(1) = Rhs+1 ;
					C2F(putlhsvar)();
					return 0;

				}
				else
				{
					Scierror(999,_("%s : Wrong size for first input argument, expecting a scalar.\n"), fname);
					return 0;
				}
			}
			break;

			case sci_strings:
			{
				int m1 = 0 , n1 = 0;
				int m1n1 = 0; /* m1 * n1 */
				char **Input_StringMatrix_One = NULL;

				int m2 = 0 , n2 = 0;
				int m2n2 = 0; /* m2 * n2 */
				char **Input_StringMatrix_Two = NULL;

				int m3 = 0 , n3 = 0;
				int m3n3 = 0; /* m2 * n2 */
				char **Input_StringMatrix_Three = NULL;

				char **Output_StringMatrix = NULL;

				GetRhsVar(1,MATRIX_OF_STRING_DATATYPE,&m1,&n1,&Input_StringMatrix_One);
				m1n1 = m1 * n1 ;
				
				GetRhsVar(2,MATRIX_OF_STRING_DATATYPE,&m2,&n2,&Input_StringMatrix_Two);
				m2n2 = m2 * n2 ;

				if (m2n2 != 1)
				{
					freeArrayOfString(Input_StringMatrix_One,m1n1);
					freeArrayOfString(Input_StringMatrix_Two,m2n2);
					Scierror(36,_("%s : Wrong size for second input argument, expecting a scalar.\n"), fname);
					return 0;
				}
				GetRhsVar(3,MATRIX_OF_STRING_DATATYPE,&m3,&n3,&Input_StringMatrix_Three);
				m3n3 = m3 * n3 ;
				if (m3n3 != 1)
				{
					freeArrayOfString(Input_StringMatrix_One,m1n1);
					freeArrayOfString(Input_StringMatrix_Two,m2n2);
					freeArrayOfString(Input_StringMatrix_Three,m3n3);
					Scierror(36,_("%s : Wrong size for third input argument, expecting a scalar.\n"),fname);
					return 0;
				}

				Output_StringMatrix = strsubst(Input_StringMatrix_One,m1n1,Input_StringMatrix_Two[0],Input_StringMatrix_Three[0]);
				freeArrayOfString(Input_StringMatrix_One,m1n1);
				freeArrayOfString(Input_StringMatrix_Two,m2n2);
				freeArrayOfString(Input_StringMatrix_Three,m3n3);

				/* put on scilab stack */
				CreateVarFromPtr( Rhs+1,MATRIX_OF_STRING_DATATYPE, &m1, &n1,Output_StringMatrix );
				LhsVar(1) = Rhs+1 ;
				C2F(putlhsvar)();
				freeArrayOfString(Output_StringMatrix,m1n1);
			}
			break;

			default:
			{
				Scierror(999,_("%s : Wrong type for first input argument.\n"),fname);
				return 0;
			}
			break;
		}
	}
	else
	{
		Scierror(999,_("%s : Wrong type for input argument(s).\n"),fname);
	}
	return 0;
}
/*-------------------------------------------------------------------------------------*/
