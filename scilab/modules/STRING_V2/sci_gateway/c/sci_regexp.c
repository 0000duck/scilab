/*------------------------------------------------------------------------*/
/* File: sci_regexp.c                                                     */
/* Copyright INRIA 2007                                                   */
/* @Authors : Cong Wu                                                     */
/* desc : search position of a character string in an other string
          using regular expression .                                      */
/*------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "gw_string.h"
#include "machine.h"
#include "pcre.h"
#include "pcreposix.h"
#include "stack-c.h"
#include "machine.h"
#include "MALLOC.h"
#include "localization.h"
#include "freeArrayOfString.h"
#include "pcre_private.h"
/*------------------------------------------------------------------------*/
#define CHAR_S 's'
#define CHAR_R 'r'
/* TODO : Add tests !!! man , bench , search memory leak , and optimize ... */
/* Not finish !!! :( */
/*------------------------------------------------------------------------*/
int C2F(sci_regexp) _PARAMS((char *fname,unsigned long fname_len))
{
	char typ = CHAR_S;
    char **Str = NULL;
	char **Str2 = NULL;
	char *pointer=NULL;
	char *save=NULL;

	int i = 0; /* loop indice */

    int mn = 0; /* dimension parameter 1 m*n */

    int m2 = 0,n2 = 0;
	int mn2 = 0; /* m2*n2 */

    int outIndex = 0;
    int numRow = 1;
    int j;

	int *values = NULL;
	int *values_end= NULL;
    int *position = NULL;

	int nbValues = 0;
	int nbValues_end=0;
    int nbposition = 0;
	char **match=NULL;

	/* Are you sure for Lhs and Rhs */
    CheckRhs(1,3);
    CheckLhs(1,3);

    if (VarType(1) == sci_matrix)
	{
		int m1 = 0;
		int n1 = 0;

		GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&Str);
		if ((m1 == 0) && (n1 == 0))
		{
			int l = 0;
			CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l);
			LhsVar(1) = Rhs+1 ;
			C2F(putlhsvar)();
			return 0;
		}
	}
	else
	{
		int m1 = 0;
		int n1 = 0;

		GetRhsVar(1,MATRIX_OF_STRING_DATATYPE,&m1,&n1,&Str);
		mn = m1*n1;  
	}

	
	if (mn != 1)
    {
		freeArrayOfString(Str,mn);
        Scierror(36, _("First input argument is incorrect.\n")); /* @TODO : detail why it is incorrect */
        return 0;
    }

    GetRhsVar(2,MATRIX_OF_STRING_DATATYPE,&m2,&n2,&Str2);
    mn2 = m2*n2;  

	if ( (int)strlen(Str[0]) == 0 ) 
	{
		values = (int *)MALLOC(sizeof(int));
		values_end = (int *)MALLOC(sizeof(int));
		position = (int *)MALLOC(sizeof(int));
	}
	else
	{
		values = (int *)MALLOC( sizeof(int) * ( strlen(Str[0]) ) );
		values_end = (int *)MALLOC( sizeof(int) * ( strlen(Str[0]) ) );
		position = (int *)MALLOC( sizeof(int) * ( strlen(Str[0]) ) );
	}

    if (Rhs >= 3)
    {
		int m3 = 0;
		int n3 = 0;
		int l3 = 0;

        GetRhsVar(3,STRING_DATATYPE,&m3,&n3,&l3);

        if ( m3*n3 != 0) typ = cstk(l3)[0];

		/* TODO : What do you when it is not 'R' ? ? ? */
        if (typ == CHAR_R )
        {
			int x = 0;
			int w = 0;

			int Output_Start = 0;
			int Output_End = 0;
            
			/*When we use the regexp;*/
            for (x = 0; x < mn2; ++x)
            {
                pointer=Str[0];
                save = (char *)MALLOC( sizeof(char) * ( 500 ) );
				do
				{
					strcpy(save,Str2[x]);
					w = pcre_private(pointer,save,&Output_Start,&Output_End);
					if ( w == 0)
					{         
						values[nbValues++]=Output_Start+1;         /*adding the answer into the outputmatrix*/
						values_end[nbValues_end++]=Output_End; 
						position[nbposition++]=x+1;                /*The number according to the str2 matrix*/
	                    pointer=pointer+Output_End;				
					}
				}while(w == 0);
            }
        }
    }

	/* TODO : Why 50 ? */
	/* Please modify this */

 //   match = (char**)MALLOC(sizeof(char**)*(50));
	//for( i=0;i<nbValues;i++)
	//{
	//	match[i] = (char*)MALLOC(sizeof(char*)*(50));
	//    for(j=values[i]-1;j<values_end[i];j++)
	//	{
	//		match[i][j-values[i]+1]=Str[i][j];
	//	}
	//}


	freeArrayOfString(Str,mn);
	freeArrayOfString(Str2,mn2);

    numRow   = 1;/* Output values[] */ 
    outIndex = 0;
    CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE,&numRow,&nbValues,&outIndex);
    for ( i = 0 ; i < nbValues ; i++ )
    {
		stk(outIndex)[i] = (double)values[i] ;
    }
    LhsVar(1) = Rhs+1 ;

    numRow   = 1;
    outIndex = 0;
    CreateVar(Rhs+2,MATRIX_OF_DOUBLE_DATATYPE,&numRow,&nbValues_end,&outIndex);
    for ( i = 0 ; i < nbposition ; i++ )
    {
		stk(outIndex)[i] = (double)values_end[i] ;
    }
    LhsVar(2) = Rhs+2;  
    	
	//numRow =  values_end[nbValues_end]-values[nbValues]+1;
	//outIndex = 1 ;
	//CreateVarFromPtr(Rhs + 3,MATRIX_OF_STRING_DATATYPE, &numRow, &outIndex, match );
	//LhsVar(3) = Rhs + 3 ;
	

    C2F(putlhsvar)();

    if (values) {FREE(values); values = NULL;}
    if (position) {FREE(position); position = NULL;}

    return 0;
}
/*-----------------------------------------------------------------------------------*/
