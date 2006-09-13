/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "MALLOC.h"
#include "machine.h"
#include "stack-c.h"
#include "getmodules.h"
/*-----------------------------------------------------------------------------------*/ 
int C2F(sci_getmodules) _PARAMS((char *fname,unsigned long fname_len))
{
	struct MODULESLIST *Modules=NULL;
	int i=0;

	int ncol=0;	
	int nrow=0;

	Modules=getmodules();
	if (!Modules)
	{
		Scierror(999,"Warning : Problems with %s.\n",fname);
		return 0;
	}

	ncol=1;
	nrow=Modules->numberofModules;

	CreateVarFromPtr(Rhs+1, "S", &nrow, &ncol, Modules->ModuleList);
	LhsVar(1)=Rhs+1;
	C2F(putlhsvar)();

	/* je ne libere pas Modules pour accelerer le prochain appel � getmodule */

	return 0;
}
/*-----------------------------------------------------------------------------------*/ 