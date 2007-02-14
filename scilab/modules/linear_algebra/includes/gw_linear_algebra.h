/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __GW_LINEAR_ALGEBRA__
#define __GW_LINEAR_ALGEBRA__

#ifdef _MSC_VER
#include <windows.h>
#include <stdio.h>
#endif

#include <string.h>

#include "machine.h"
#include "stack-c.h"
#include "sciprint.h"

/*-----------------------------------------------------------------------------------*/
#define SCI_DOUBLE 1
#define STRING  10
#define REAL 0
#define COMPLEX 1
#define FUNCTION 13
#define STRINGREAL 27
#define STRINGCOMPLEX 12
#define YES 1
#define NO 0

/*-----------------------------------------------------------------------------------*/
typedef int (*Linear_Algebra_Interf) __PARAMS((char *fname,unsigned long l));

typedef struct table_struct 
{
	Linear_Algebra_Interf f;    /** function **/
	char *name;      /** its name **/
} LinearAlgebraTable;

int C2F(inthess)(char *fname,unsigned long fname_len);
int C2F(intqr)(char *fname,unsigned long fname_len);
int C2F(intbackslash)(char *fname,unsigned long fname_len);
int C2F(intbdiagr)(char *fname, long unsigned int fname_len);
int C2F(intdet)(char *fname,unsigned long fname_len);
int C2F(intinv)(char *fname,unsigned long fname_len);
int C2F(intlu)(char *fname,unsigned long fname_len);
int C2F(intrcond)(char *fname,unsigned long fname_len);
int C2F(intslash)(char *fname,unsigned long fname_len);
int C2F(intsvd)(char *fname,unsigned long fname_len);
int C2F(intlsq)(char *fname,unsigned long fname_len);
int C2F(intchol)(char *fname,unsigned long fname_len);
int C2F(inteig) (char *fname,unsigned long fname_len);
int C2F(intbalanc)(char *fname,unsigned long fname_len);
int C2F(intschur)(char *fname, unsigned long fname_len);

#endif /*  __GW_LINEAR_ALGEBRA__ */
/*-----------------------------------------------------------------------------------*/

