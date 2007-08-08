/*-----------------------------------------------------------------------------------*/
/**
 * @author Allan CORNET INRIA 2007
 */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include "gw_history_manager.h"
#include "MALLOC.h"
#include "machine.h"
#include "stack-c.h"
#include "HistoryManager.h"
#include "InitializeHistoryManager.h"
#include "TerminateHistoryManager.h"
#include "getCommentDateSession.h"
/*-----------------------------------------------------------------------------------*/
int C2F(sci_historymanager) _PARAMS((char *fname,unsigned long fname_len))
{
	int l1 = 0,n1 = 0,m1 = 0;
	char *Output=NULL;

	CheckRhs(0,1) ;
	CheckLhs(0,1) ;

	if (Rhs == 0)
	{
		Output=(char*)MALLOC(4*sizeof(char));
		if (historyIsEnabled()) strcpy(Output,"on");
		else strcpy(Output,"off");
	}
	else
	{
		if (GetType(1) == sci_strings)
		{
			char *param=NULL;

			GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
			param=cstk(l1);

			if ( (strcmp(param,"off")==0) || (strcmp(param,"on")==0) )
			{
				Output=(char*)MALLOC(4*sizeof(char));

				if (strcmp(param,"off")==0)
				{
					if (historyIsEnabled()) TerminateHistoryManager();
					strcpy(Output,"off");
				}
				else /* 'on' */
				{
					
					if (!historyIsEnabled()) 
					{
						char *commentbeginsession = NULL;
						InitializeHistoryManager();

						/* add date & time @ begin session */
						commentbeginsession = getCommentDateSession(TRUE);
						appendLineToScilabHistory(commentbeginsession);
						if (commentbeginsession) {FREE(commentbeginsession);commentbeginsession=NULL;}
					}
					
					strcpy(Output,"on");
				}
			}
			else
			{
				Scierror(999,"Invalid parameter : 'on' or 'off'");
				return 0;
			}
		}
	}

	n1=1;
	CreateVarFromPtr(Rhs+ 1,STRING_DATATYPE,(m1=(int)strlen(Output), &m1),&n1,&Output);
	LhsVar(1) = Rhs+1;
	C2F(putlhsvar)();	
	if (Output) {FREE(Output);Output=NULL;}

	return 0;
}
/*-----------------------------------------------------------------------------------*/
