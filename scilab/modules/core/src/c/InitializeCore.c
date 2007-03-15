/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include <stdlib.h>
#include "InitializeCore.h"
#include "SciEnv.h"
#include "getmodules.h"
#include "hashtable_core.h"
#include "sciprint.h"
#include "LoadFunctionsTab.h"
#include "prompt.h"
#include "message_scilab.h"
/*-----------------------------------------------------------------------------------*/ 
BOOL InitializeCore(void)
{
	BOOL bOK=FALSE;
	int pause=0;

	SciEnv();

	getmodules();

	if ( create_hashtable_scilab_functions(MAXTAB) == 0 ) 
	{
		message_scilab("core_message_128");
		exit(1);
	}

	LoadFunctionsTab();

	/* Set prompt level */
	C2F(setprlev)(&pause);

	return bOK;
}
/*-----------------------------------------------------------------------------------*/ 

