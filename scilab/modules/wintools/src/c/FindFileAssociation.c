/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include <shlwapi.h>
#include "FindFileAssociation.h"
#include "MALLOC.h"
/*-----------------------------------------------------------------------------------*/ 
char *FindFileAssociation (char *ptrFindStr,char *Extra) 
{
	char *ptrResult = NULL ;

	if ( ptrFindStr )
	{
		char szDefault[MAX_PATH];
		DWORD ccDefault = MAX_PATH;
		HRESULT rc = AssocQueryString (0, ASSOCSTR_EXECUTABLE,ptrFindStr, Extra, szDefault, &ccDefault);
		if (ccDefault)
		{
			if (rc==S_OK)
			{
				ptrResult=(char*)MALLOC(sizeof(char)*(strlen(szDefault)+1));
				strcpy(ptrResult,szDefault);
			}
		}
	}
	return ptrResult;

}
/*-----------------------------------------------------------------------------------*/

