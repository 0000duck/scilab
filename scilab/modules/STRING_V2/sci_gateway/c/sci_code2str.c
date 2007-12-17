/*------------------------------------------------------------------------*/
/* File: sci_code2str.c                                                   */
/* Copyright INRIA 2007                                                   */
/* @Authors : Cong Wu                                                     */
/* desc : str=code2str(c)
          Returns character string associated with Scilab integer codes.
          str is such that c(i) is the Scilab integer code of part(str,i))*/
/*------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "gw_string.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "localization.h"
#include "code2str.h"
/*--------------------------------------------------------------------------*/
int C2F(sci_code2str) _PARAMS((char *fname,unsigned long fname_len))
{
	char **Output_Matrix = NULL;
	int Row_Num = 0,Col_Num = 0;
	int *Input_Matrix = NULL; /* Input matrix */

	int numRow = 1;
	int numCol = 0;
	int outIndex = 0 ;

	CheckRhs(1,1);
	CheckLhs(1,1);

	if (VarType(1) == sci_matrix)
	{
		int Stack_position = 0;
		GetRhsVar(1,MATRIX_OF_INTEGER_DATATYPE,&Row_Num,&Col_Num,&Stack_position);
		Input_Matrix=istk(Stack_position); /* Input*/
	}
	else
	{
		Scierror(999,_("%s : Wrong type for first input argument: scalar or string matrix expected.\n"),fname);
		return 0;
	}

	numCol   = Row_Num*Col_Num ;

	/* Allocation output matrix */
	Output_Matrix = (char**)MALLOC(sizeof(char*)); 

	if (Output_Matrix == NULL)
	{
		Scierror(999,_("%s : Memory allocation error.\n"),fname);
		return 0;
	}

	if (numCol != 0) 
	{
		Output_Matrix[0]=(char*)MALLOC(sizeof(char*)*(numCol));
	}
	else Output_Matrix[0]=(char*)MALLOC(sizeof(char*));

	if (Output_Matrix[0] == NULL)
	{
		FREE(Output_Matrix);
		Output_Matrix = NULL;
		Scierror(999,_("%s : Memory allocation error.\n"),fname);
		return 0;
	}

	/* code2str algorithm */

	code2str(Output_Matrix,Input_Matrix,Row_Num*Col_Num);

	/* put on scilab stack */
	numRow   = 1 ; /*Output number row */
	outIndex = 0 ;
	CreateVar(Rhs+1,STRING_DATATYPE,&numRow,&numCol,&outIndex);
	strncpy(cstk(outIndex), &Output_Matrix[0][0] ,numCol ) ;
	LhsVar(1) = Rhs+1 ;
	C2F(putlhsvar)();

	/* free pointers */
	if (Output_Matrix[0]) { FREE(Output_Matrix[0]); Output_Matrix[0]=NULL;}
	if (Output_Matrix) {FREE(Output_Matrix); Output_Matrix=NULL; }
	return 0;
}
/*--------------------------------------------------------------------------*/ 
