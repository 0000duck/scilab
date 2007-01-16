/*-----------------------------------------------------------------------------------*/
/* INRIA 2005 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include "CallScilab.h"
#include "MALLOC.h"
#include "../../../graphics/includes/WindowList.h"
#include "setgetSCIpath.h"
#include "fromc.h"
#include "sciquit.h"

#if _MSC_VER
#define putenv _putenv
#endif

/*-----------------------------------------------------------------------------------*/
static char DefaultScilabStartup[]="SCI/etc/scilab.start";
static char DefaultScilabQuit[]="SCI/etc/scilab.quit";
static char DefaultSCIenv[]="../..";
static int DefaultStacksize=1000000;
static int StartScilabIsOK=FALSE;
/*-----------------------------------------------------------------------------------*/
extern int setenvc(char *string,char *value);
extern int C2F(inisci)(int *,int *,int *);
extern void C2F(settmpdir) (void);
extern int C2F(scirun)(char * startup, int lstartup);
extern int C2F(ismenu)();
extern void SetFromCToON(void);
extern void sciGetIdFigure (int *vect, int *id, int *flag);
extern BOOL GetWITH_GUI(void);
extern void SetWITH_GUI(BOOL ON);
/*-----------------------------------------------------------------------------------*/
#ifdef _MSC_VER
extern char *GetScilabDirectory(BOOL UnixStyle);
extern void InitWindowGraphDll(void);
extern void TextMessage1 (int ctrlflag);
extern void set_sci_env(char *DefaultSCIPATH);
#else
extern int C2F(sxevents)();
#endif
/*-----------------------------------------------------------------------------------*/
#ifdef _MSC_VER
static void SetSciEnv(void)
{
  char *ScilabDirectory=NULL;

  ScilabDirectory=GetScilabDirectory(TRUE);

  if (ScilabDirectory == NULL)
  {
	MessageBox (NULL, "Error", "GetScilabDirectory()", MB_ICONSTOP | MB_OK);
	exit(1);
  }
  set_sci_env(ScilabDirectory);

  if (ScilabDirectory){FREE(ScilabDirectory);ScilabDirectory=NULL;}		
  
}
#endif
/*-----------------------------------------------------------------------------------*/
void DisableInteractiveMode(void)
{
	SetWITH_GUI(FALSE);
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
		ScilabStartupUsed=(char*)MALLOC((strlen(DefaultScilabStartup)+1)*sizeof(char));
		sprintf(ScilabStartupUsed,"%s",DefaultScilabStartup);
	}
	else
	{
		ScilabStartupUsed=(char*)MALLOC((strlen(DefaultScilabStartup)+1)*sizeof(char));
		sprintf(ScilabStartupUsed,"%s",ScilabStartup);
	}
	
	if (Stacksize==NULL)
	{
		StacksizeUsed=DefaultStacksize;
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

#if _MSC_VER
	InitWindowGraphDll();
#endif

	lengthStringToScilab=(int)(strlen("exec(\"SCI/etc/scilab.start\",-1);quit;")+strlen(ScilabStartupUsed));
	InitStringToScilab=(char*)MALLOC(lengthStringToScilab*sizeof(char));
	sprintf(InitStringToScilab,"exec(\"%s\",-1);quit;",ScilabStartupUsed);
	
	C2F(scirun)(InitStringToScilab,strlen(InitStringToScilab));

	if (ScilabStartupUsed) {FREE(ScilabStartupUsed);ScilabStartupUsed=NULL;}
	if (InitStringToScilab) {FREE(InitStringToScilab);InitStringToScilab=NULL;}

	bOK=TRUE;
	StartScilabIsOK=TRUE;

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
int TerminateScilab(char *ScilabQuit)
{
	int bOK=FALSE;

	if (StartScilabIsOK)
	{
		ExitScilab();
		StartScilabIsOK=FALSE;
		bOK=TRUE;
	}

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
void ScilabDoOneEvent(void)
{
	if ( GetWITH_GUI() )
	{
		#if _MSC_VER
			TextMessage1 (1);
		#else 
			C2F(sxevents)();
		#endif

		while(C2F(ismenu)()==1 ) 
		{
			C2F(scirun)("quit;",(int)strlen("quit;"));
		}
	}
}
/*-----------------------------------------------------------------------------------*/
int ScilabHaveAGraph(void)
{
	integer iflag =0,ids,num;
	int vInt=0;

	if ( GetWITH_GUI() )
	{
			
          sciGetIdFigure (&ids,&num,&iflag);
          if (num > 0) { vInt = 1 ; }
	}
	else
	{
		vInt=0;
	}

	return vInt;
}
/*-----------------------------------------------------------------------------------*/
