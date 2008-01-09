/*--------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include "gw_fileio.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "FindFileExtension.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
int C2F(sci_fileext) _PARAMS((char *fname,unsigned long fname_len))
{
	Rhs=Max(Rhs,0);

	CheckRhs(1,1);
	CheckLhs(1,1);

	if (GetType(1) == sci_strings)
	{
		int n1 = 0, m1 = 0, l1 = 0;

		char *filename = NULL;
		char *extension = NULL;
		
		GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
		filename = cstk(l1);

		if (filename) extension = FindFileExtension(filename);

		if (extension)
		{
			n1 = 1;
			CreateVarFromPtr(Rhs+1,STRING_DATATYPE,(m1=(int)strlen(extension), &m1),&n1,&extension);
		}
		else
		{
			l1 = 0; m1 = 0; n1 = 0;
			CreateVarFromPtr(Rhs+ 1,MATRIX_OF_DOUBLE_DATATYPE,&n1,&m1,&l1);
		}
		LhsVar(1)=Rhs+1;
		C2F(putlhsvar)();
	}
	else
	{
		Scierror(999,_("%s: Wrong type for first input argument: String expected.\n"),fname);
	}
	return 0;
}
/*--------------------------------------------------------------------------*/

