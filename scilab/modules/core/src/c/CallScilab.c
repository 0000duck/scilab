/*-----------------------------------------------------------------------------------*/
/* INRIA 2005 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include "CallScilab.h"
#include "MALLOC.h"
#include "../../../graphics/includes/WindowList.h"
#include "../../../graphics/includes/GetProperty.h"
#include "ScilabEventsLoop.h"
#include "../../../io/includes/setenvc.h"
#include "setgetSCIpath.h"
#include "fromc.h"
#include "sciquit.h" /* ExitScilab */
#include "tmpdir.h"
#include "fromc.h"
#include "inisci-c.h"
#include "scirun.h"
#include "scilabmode.h"
#include "dynamic_menus.h"
#include "scilabDefaults.h"
#ifdef _MSC_VER
#include "../../../windows_tools/src/c/scilab_windows/SetScilabEnvironmentVariables.h"
#include "../../../windows_tools/src/c/scilab_windows/getScilabDirectory.h"
#endif
#include "localization.h"

#ifdef _MSC_VER
#define putenv _putenv
#endif

/*-----------------------------------------------------------------------------------*/
static int StartScilabIsOK=FALSE;
/*-----------------------------------------------------------------------------------*/
#ifdef _MSC_VER
static void SetSciEnv(void)
{
  char *ScilabDirectory=NULL;

  ScilabDirectory = getScilabDirectory(TRUE);

  if (ScilabDirectory == NULL)
  {
	MessageBox (NULL, _("Error"), "getScilabDirectory()", MB_ICONSTOP | MB_OK);
	exit(1);
  }
  SetScilabEnvironmentVariables(ScilabDirectory);

  if (ScilabDirectory){FREE(ScilabDirectory);ScilabDirectory=NULL;}		
  
}
#endif
/*-----------------------------------------------------------------------------------*/
void DisableInteractiveMode(void)
{
	setScilabMode(SCILAB_NWNI);
}
/*-----------------------------------------------------------------------------------*/
int StartScilab(char *SCIpath,char *ScilabStartup,int *Stacksize)
{
	int bOK=FALSE;

	char *ScilabStartupUsed=NULL;
	char *InitStringToScilab=NULL;
	int StacksizeUsed=0;
	int lengthStringToScilab=0;

	static int iflag=-1,ierr=0;

	if (StartScilabIsOK) return bOK;

	SetFromCToON();

	if (SCIpath==NULL)
	{
		#ifdef _MSC_VER
			SetSciEnv();
		#else
		{
			char env[2048];
			setSCIpath(SCIpath);
			sprintf(env,"SCI=%s",SCIpath);
			putenv(env);
		}
		#endif
	}
	else
	{
		char env[2048];
		setSCIpath(SCIpath);
		sprintf(env,"SCI=%s",SCIpath);
		putenv(env);
	}

	if (ScilabStartup==NULL)
	{
		ScilabStartupUsed=(char*)MALLOC((strlen(DEFAULTSCILABSTARTUP)+1)*sizeof(char));
		sprintf(ScilabStartupUsed,"%s",DEFAULTSCILABSTARTUP);
	}
	else
	{
		ScilabStartupUsed=(char*)MALLOC((strlen(DEFAULTSCILABSTARTUP)+1)*sizeof(char));
		sprintf(ScilabStartupUsed,"%s",ScilabStartup);
	}
	
	if (Stacksize==NULL)
	{
		StacksizeUsed=DEFAULTSTACKSIZE;
	}
	else
	{
		StacksizeUsed=*Stacksize;
	}

	/* running the startup */ 
	C2F(settmpdir)();

	/* Scilab Initialization */ 
	C2F(inisci)(&iflag,&StacksizeUsed,&ierr);

	if ( ierr > 0 ) 
    {
	  bOK=FALSE;
      return bOK;
    }

	lengthStringToScilab=(int)(strlen("exec(\"SCI/etc/scilab.start\",-1);quit;")+strlen(ScilabStartupUsed));
	InitStringToScilab=(char*)MALLOC(lengthStringToScilab*sizeof(char));
	sprintf(InitStringToScilab,"exec(\"%s\",-1);quit;",ScilabStartupUsed);
	
	C2F(scirun)(InitStringToScilab,(long int)strlen(InitStringToScilab));

	if (ScilabStartupUsed) {FREE(ScilabStartupUsed);ScilabStartupUsed=NULL;}
	if (InitStringToScilab) {FREE(InitStringToScilab);InitStringToScilab=NULL;}

	bOK=TRUE;
	StartScilabIsOK=TRUE;

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
int TerminateScilab(char *ScilabQuit)
{
	if (StartScilabIsOK)
	{
		ExitScilab();
		StartScilabIsOK=FALSE;
		return TRUE;
	}

	return FALSE;
}
/*-----------------------------------------------------------------------------------*/
void ScilabDoOneEvent(void)
{
	if ( getScilabMode() != SCILAB_NWNI )
	{
		ScilabEventsLoop();

		while(ismenu()==1 ) 
		{
			C2F(scirun)("quit;",(int)strlen("quit;"));
		}
	}
}
/*-----------------------------------------------------------------------------------*/
int ScilabHaveAGraph(void)
{
  return sciHasFigures();
}
/*-----------------------------------------------------------------------------------*/
