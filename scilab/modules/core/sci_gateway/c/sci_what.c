/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include <stdio.h>
#include "gw_core.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "sciprint.h"
#include "message_scilab.h"
/*-----------------------------------------------------------------------------------*/
int C2F(intwhat) _PARAMS((char *fname));
/*-----------------------------------------------------------------------------------*/
static const int nbrCommands=29;
/*-----------------------------------------------------------------------------------*/
static char *CommandWords[]={
	"if","else",
	"for","while",
	"end","select",
	"case","quit",
	"exit","return",
	"help","what",
	"who","pause",
	"clear","resume",
	"then","do",
	"apropos","abort",
	"break","elseif",
	"pwd","function",
	"endfunction","clc",
	"continue",
	"try","catch"
};
static char **LocalFunctionsTab=NULL;
static int SizeLocalFunctionsTab=0;
/*-----------------------------------------------------------------------------------*/
static int CreateLocalFunctionsTab(void);
static int IsACommand(char *primitive);
static void DispInternalFunctions(void);
static void DispCommands(void);
static void SortStrings(char **Strs,int SizeOfStrs);
/*-----------------------------------------------------------------------------------*/
extern char **GetFunctionsList(int *sizeList);
/*-----------------------------------------------------------------------------------*/
int C2F(sci_what) _PARAMS((char *fname,unsigned long fname_len))
{
	C2F(intwhat)(fname);
	return 0;
}
/*-----------------------------------------------------------------------------------*/
int C2F(intwhat) _PARAMS((char *fname))
{

	Rhs = Max(0, Rhs);
	CheckRhs(0,0);
	CheckLhs(1,2);

	SortStrings(CommandWords,nbrCommands);
	CreateLocalFunctionsTab();
	SortStrings(LocalFunctionsTab,SizeLocalFunctionsTab);


	if (Lhs == 1)
	{
		DispInternalFunctions();
		DispCommands();
		LhsVar(1)=0;
	}
	else /* Lhs == 2 */
	{
		int i2=0;

		int ncol=1;	
		int nrowFunctions=SizeLocalFunctionsTab;
		int nrowCommands=nbrCommands;

		CreateVarFromPtr(Rhs+1, "S", &nrowFunctions, &ncol, LocalFunctionsTab);
		LhsVar(1)=Rhs+1;

		CreateVarFromPtr(Rhs+2, "S", &nrowCommands, &ncol, CommandWords);
		LhsVar(2)=Rhs+2;

		for (i2=0;i2<nrowFunctions;i2++) { FREE(LocalFunctionsTab[i2]);LocalFunctionsTab[i2]=NULL; }
		FREE(LocalFunctionsTab);
	}

	C2F(putlhsvar)();
	return 0;
}
/*-----------------------------------------------------------------------------------*/
static void DispInternalFunctions(void)
{
	int i=0;

	sciprint("\n");
	message_scilab("core_message_138");
	sciprint("\n");
	for (i=1;i<SizeLocalFunctionsTab-1;i++)
	{
		sciprint("%+24s ",LocalFunctionsTab[i-1]);
		if (i%4==0) sciprint("\n");
	}
	sciprint("\n");
}
/*-----------------------------------------------------------------------------------*/
static void DispCommands(void)
{
	int i=0;
	sciprint("\n");
	message_scilab("core_message_139");
	sciprint("\n");
	for (i=1;i<nbrCommands+1;i++)
	{
		sciprint("%+24s ",CommandWords[i-1]);
		if (i%4==0) sciprint("\n");
	}
	sciprint("\n");
}
/*-----------------------------------------------------------------------------------*/
static int IsACommand(char *primitive)
{
	int bOK=FALSE;
	int i=0;
	for (i=0;i<nbrCommands;i++)
	{
		if (strcmp(CommandWords[i],primitive)==0)
		{
			return TRUE;
		}
	}
	return bOK;
}
/*-----------------------------------------------------------------------------------*/
static int CreateLocalFunctionsTab(void)
{
	char **LocalFunctionsTabTmp=NULL;
	int i=0;
	int j=0;
	int SizeTab=0;
	int MaxSizeWithoutCommands=0;

	LocalFunctionsTabTmp=GetFunctionsList(&SizeTab);

	if (LocalFunctionsTabTmp)
	{
		for (i=0;i<SizeTab;i++)
		{
			if ( !IsACommand(LocalFunctionsTabTmp[i]) ) MaxSizeWithoutCommands++;
		}

		LocalFunctionsTab=(char **)MALLOC(sizeof(char**)*MaxSizeWithoutCommands);

		if (LocalFunctionsTab == NULL) 
		{
			SizeLocalFunctionsTab = 0;
			return FALSE;
		}

		j=0;
		for (i=0;i<SizeTab;i++)
		{
			if ( !IsACommand(LocalFunctionsTabTmp[i]) ) 
			{
				LocalFunctionsTab[j]=(char*)MALLOC( (strlen(LocalFunctionsTabTmp[i])+1)*sizeof(char) );
				strcpy(LocalFunctionsTab[j],LocalFunctionsTabTmp[i]);
				j++;
			}
		}

		if (LocalFunctionsTabTmp)
		{
			for (i=0;i<SizeTab;i++)	
			{ 
				if (LocalFunctionsTabTmp[i])
				{
					FREE(LocalFunctionsTabTmp[i]);
					LocalFunctionsTabTmp[i]=NULL;
				}
			}
			FREE(LocalFunctionsTabTmp);
			LocalFunctionsTabTmp=NULL;
		}
	}
	else
	{
		SizeLocalFunctionsTab = 0;
		return FALSE;
	}

	SizeLocalFunctionsTab=MaxSizeWithoutCommands;

	return TRUE;
}
/*-----------------------------------------------------------------------------------*/
static void SortStrings(char **Strs,int SizeOfStrs)
{
	int fin,i;
	for(fin=SizeOfStrs-1;fin>0;fin--)
	{
		int Sorted=FALSE;
		for(i=0;i<fin;i++)
		{
			if(strcmp(Strs[i],Strs[i+1])>0)
			{
				char *tmp;
				memcpy(&tmp,Strs+i,sizeof(char *));
				memcpy(Strs+i,Strs+(i+1),sizeof(char *));
				memcpy(Strs+(i+1),&tmp,sizeof(char *));
				Sorted=TRUE;
			}
		}
		if(!Sorted)break;
	}
}
/*-----------------------------------------------------------------------------------*/
