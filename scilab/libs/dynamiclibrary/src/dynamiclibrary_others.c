/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "dynamiclibrary_others.h"
#include <stdlib.h>
#include <stdio.h>
/*-----------------------------------------------------------------------------------*/ 
#ifndef NULL
#define NULL 0
#endif
/*-----------------------------------------------------------------------------------*/ 
DynLibHandle LoadDynLibrary(char *libname)
{
	return (DynLibHandle) dlopen(libname,  RTLD_NOW | RTLD_GLOBAL);
}
/*-----------------------------------------------------------------------------------*/ 
BOOL FreeDynLibrary(DynLibHandle hInstance)
{
	BOOL bOK = FALSE;
	if (hInstance)
		{
			if (dlclose( hInstance)) bOK = TRUE;
		}
	#ifndef NDEBUG
	else 
		{
			printf("FreeDynLibrary: Cannot close a not-opened library.\n");
			fflush(NULL);
		}
	#endif

	return bOK;
}
/*-----------------------------------------------------------------------------------*/ 
DynLibFuncPtr GetDynLibFuncPtr(DynLibHandle hInstance,char *funcName)
{
	DynLibFuncPtr retFuncPtr = NULL ;
	
	if (hInstance)
	{
		retFuncPtr = dlsym(hInstance, funcName);
	}
	return retFuncPtr;
}
/*-----------------------------------------------------------------------------------*/ 
char * GetLastDynLibError(void)
{
	return dlerror();
}
/*-----------------------------------------------------------------------------------*/ 
