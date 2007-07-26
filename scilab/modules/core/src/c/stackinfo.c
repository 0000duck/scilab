/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#ifdef HAVE_LIMITS_H
#include <limits.h>
#define MAXLONG LONG_MAX
#else 
#ifdef HAVE_VALUES_H
#include <values.h>
#endif /* HAVE_VALUES_H */
#endif /* !HAVE_LIMITS_H */

#include "stackinfo.h"
#include "stack-def.h"
#include "stack-c.h"
#include "MALLOC.h"
/*-----------------------------------------------------------------------------------*/
#ifndef MAXLONG
#define MAXLONG LONG_MAX
#endif

#ifndef LONG_MAX 
#define LONG_MAX 2147483647L 
#endif 

#ifndef MAXLONG
#define MAXLONG LONG_MAX
#endif
/*-----------------------------------------------------------------------------------*/
#define LengthNameVariableScilabMax 24
/*-----------------------------------------------------------------------------------*/
static void cleanFortranString(char *fortanbuffer);
/*-----------------------------------------------------------------------------------*/
integer C2F(getstackinfo)(integer *total,integer *used)
{
	*used = C2F(vstk).lstk[C2F(vstk).isiz - 1] - C2F(vstk).lstk[C2F(vstk).bot - 1] + 1;
	*total = C2F(vstk).lstk[C2F(vstk).isiz - 1] - C2F(vstk).lstk[0];
	return(0);
}
/*-----------------------------------------------------------------------------------*/
integer C2F(getgstackinfo)(integer *total,integer *used)
{
	*used = C2F(vstk).lstk[C2F(vstk).gtop] - C2F(vstk).lstk[C2F(vstk).isiz + 1] + 1;
	*total = C2F(vstk).lstk[C2F(vstk).gbot - 1] - C2F(vstk).lstk[C2F(vstk).isiz + 1] ;
	return(0);
}
/*-----------------------------------------------------------------------------------*/
integer C2F(getvariablesinfo)(integer *total,integer *used)
{
	*used = C2F(vstk).isiz - C2F(vstk).bot ;
	*total = C2F(vstk).isiz - 1;
	return 0;
}
/*-----------------------------------------------------------------------------------*/
integer C2F(getgvariablesinfo)(integer *total,integer *used)
{
	*used = C2F(vstk).gtop - C2F(vstk).isiz - 1;
	*total = 10000 - C2F(vstk).isiz - 1;
	return 0;
}
/*-----------------------------------------------------------------------------------*/
BOOL is_a_valid_size_for_scilab_stack(int sizestack)
{
	BOOL bOK=TRUE;
	double dsize = ((double) sizeof(double)) * (sizestack);
	unsigned long ulsize = ((unsigned long)sizeof(double)) * (sizestack);
	if ( dsize != (double) ulsize)
	{
		bOK=FALSE;
	}
	return bOK;
}
/*-----------------------------------------------------------------------------------*/
unsigned long get_max_memory_for_scilab_stack(void)
{
	return MAXLONG/sizeof(double);
}
/*-----------------------------------------------------------------------------------*/
char *getLocalNamefromId(int n)
{
	integer *id=NULL;	
	integer one = 1;
	char *Name=NULL;

	id=&C2F(vstk).idstk[C2F(vstk).bot * 6 - 6];
	id -= 7;
	Name = (char*)MALLOC(sizeof(char)*LengthNameVariableScilabMax+1);

	C2F(cvname)(&id[n * 6 + 1], Name, &one,LengthNameVariableScilabMax);

	cleanFortranString(Name);
	return Name;
}
/*-----------------------------------------------------------------------------------*/
char *getGlobalNamefromId(int n)
{
	integer *id=NULL;	
	static integer one = 1;
	char *Name=NULL;

	id=&C2F(vstk).idstk[(C2F(vstk).isiz + 2) * 6 - 6];
	id -= 7;
	Name = (char*)MALLOC(sizeof(char)*LengthNameVariableScilabMax+1);

	C2F(cvname)(&id[(n+1) * 6 + 1], Name, &one,LengthNameVariableScilabMax);

	cleanFortranString(Name);
	return Name;
}
/*-----------------------------------------------------------------------------------*/
int getLocalSizefromId(int n)
{
	int LocalSize=0;
	int Lused=0;
	int Ltotal=0;

	C2F(getvariablesinfo)(&Ltotal,&Lused);

	if ( (n >= 0) && ( n < Lused ) )
	{
		LocalSize=(int)(C2F(vstk).lstk[C2F(vstk).bot + n] - C2F(vstk).lstk[C2F(vstk).bot + n - 1]);
	}
	else
	{
		LocalSize=-1;
	}

	return LocalSize;
}
/*-----------------------------------------------------------------------------------*/
int getGlobalSizefromId(int n)
{
	int GlobalSize=0;
	int Gused=0;
	int Gtotal=0;

	C2F(getgvariablesinfo)(&Gtotal,&Gused);

	if ( (n >= 0) && ( n < Gused ) )
	{
		GlobalSize=(int)(C2F(vstk).lstk[C2F(vstk).isiz + 2 + n] - C2F(vstk).lstk[C2F(vstk).isiz + 2 + n - 1]);
	}
	else
	{
		GlobalSize=-1;
	}
	return GlobalSize;
}
/*-----------------------------------------------------------------------------------*/
static void cleanFortranString(char *fortanbuffer)
{
	int i = 0;
	fortanbuffer[LengthNameVariableScilabMax]='\0';

	for (i=0;i<LengthNameVariableScilabMax;i++)
	{
		if (fortanbuffer[i] == '\0')
		{
			break;
		}
		else if (fortanbuffer[i] == ' ')
		{
			fortanbuffer[i] = '\0';
			break;
		}
	}
}
/*-----------------------------------------------------------------------------------*/