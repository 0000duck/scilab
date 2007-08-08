/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include "gw_windows_tools.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "scilabmode.h"
/*-----------------------------------------------------------------------------------*/
int C2F(sci_chartooem) _PARAMS((char *fname,unsigned long l))
{
	static int l1,n1,m1;
	char *Output=NULL;

	CheckRhs(1,1);
	CheckLhs(0,1);

	if (GetType(1) == sci_strings)	
	{
		char *Charstring=NULL;

		GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
		Charstring=cstk(l1);

		Output=(char*)MALLOC((strlen(Charstring)+1)*sizeof(char));
		if (getScilabMode() == SCILAB_STD)
		{
			CharToOem(Charstring,Output);
		}
		else
		{
			wsprintf(Output,"%s",Charstring);
		}
	}
	else
	{
		Scierror(999,"parameter must be a string.");
		return 0;
	}
	
	n1=1;
	CreateVarFromPtr( Rhs+1,STRING_DATATYPE,(m1=(int)strlen(Output), &m1),&n1,&Output);
	LhsVar(1) = Rhs+1;
	C2F(putlhsvar)();	
	if (Output) {FREE(Output);Output=NULL;}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
