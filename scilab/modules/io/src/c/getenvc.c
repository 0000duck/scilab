/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Scilab */
/*-----------------------------------------------------------------------------------*/ 
#if _MSC_VER
	#include <Windows.h> /* GetEnvironmentVariable */
#else
	#include <stdlib.h> /* getenv */
#endif
#include <string.h> /* strlen */
#include "getenvc.h"
/*-----------------------------------------------------------------------------------*/
void C2F(getenvc)(int *ierr,char *var,char *buf,int *buflen,int *iflag)
{
	#ifdef _MSC_VER
	if (GetEnvironmentVariable(var,buf,(DWORD)buflen)==0)
	{
		if ( *iflag == 1 ) sciprint("You must define the environment variable %s\r\n",var);
		*ierr=1;
	}
	else
	{
		*buflen = strlen(buf);
		*ierr=0;
	}
	#else
	char *local;
	if ( (local=getenv(var)) == 0)
	{
		if ( *iflag == 1 ) sciprint("You must define the environment variable %s\r\n",var);
		*ierr=1;
	}
	else 
	{
		strncpy(buf,local,*buflen);
		*buflen = strlen(buf);
		*ierr=0;
	}
	#endif
}
/*-----------------------------------------------------------------------------------*/

