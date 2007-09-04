/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include <stdio.h>
#include "more.h"
#include "scilabmode.h"
#include "sciprint.h"
#include "../../../console/includes/GetCharWithoutOutput.h"
#include "../../../console/includes/ConsolePrintf.h"
#if _MSC_VER
#include "windows/GetCharWithEventsLoop.h"
#else
#include "others/GetCharWithEventsLoop.h"
#endif
/*-----------------------------------------------------------------------------------*/ 
#define MSG_MORE "[More (y or n ) ?] "
/*-----------------------------------------------------------------------------------*/ 
int linesmore(void)
{
	int retval = 0;
	if (getScilabMode() != SCILAB_STD) 
	{
		int ch = 0;
		/* Scilab has not his own window */
		sciprint(MSG_MORE);

		ch = GetCharWithEventsLoop(1);
	
		if ( (ch != ' ') && (ch != '\n') && (ch != 'y') ) retval = 1;
		sciprint("\n");
	}
	else
	{
		/* scilab has his own window */
		int ch = 0;
		ConsolePrintf(MSG_MORE);
		ch = GetCharWithoutOutput();
		if ( ch == 110 ) retval = 1;
		ConsolePrintf("\n");
	}
	return retval;
}
/*-----------------------------------------------------------------------------------*/ 
