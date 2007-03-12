/*-----------------------------------------------------------------------------------*/ 
#include "gw_sound.h"
#ifdef _MSC_VER
	#pragma comment(lib, "winmm.lib")
#endif
/*-----------------------------------------------------------------------------------*/ 
extern int C2F(cluni0) __PARAMS((char *name, char *nams, integer *ln, long int name_len,long int nams_len));  
/*-----------------------------------------------------------------------------------*/ 
/* FILENAME_MAX is set to 14 on hp */
#ifdef hppa 
#undef FILENAME_MAX
#define FILENAME_MAX 4096 
#endif 
/*-----------------------------------------------------------------------------------*/ 
static char filename[FILENAME_MAX];
static int out_n;
static long int lout;
/*-----------------------------------------------------------------------------------*/ 
int C2F(playsound)(char *fname,char *command,unsigned long fname_len);
/*-----------------------------------------------------------------------------------*/ 
/* SCILAB function : PlaySound */
/*-----------------------------------------------------------------------------------*/ 
int sci_Playsound __PARAMS((char *fname,unsigned long fname_len))
{
  char *command=NULL;
  int m1,n1,l1,un=1,rep,m2,n2,l2;
  CheckRhs(1,2);
  CheckLhs(0,1);
  /*  checking variable file */
  GetRhsVar(1,"c",&m1,&n1,&l1);
  if ( Rhs == 2 ) 
  {
      GetRhsVar(2,"c",&m2,&n2,&l2);
      command = cstk(l2);
  }
  /*** first call to get the size **/
  lout=FILENAME_MAX;
  C2F(cluni0)(cstk(l1), filename, &out_n,m1*n1,lout);
  rep = C2F(playsound)(filename,command,(int)strlen(filename));
  if ( Lhs == 1 ) 
  {
      CreateVar(2,"d",&un,&un,&l2);
      *stk(l2)= rep;
      LhsVar(1)=2;
  }
  else
  {
    if ( rep == -1 ) 
		{
			Scierror(999,"Error in PlaySound\r\n");
		}
    LhsVar(1)=0;
  }
  PutLhsVar();
  return 0;
}
/*-----------------------------------------------------------------------------------*/ 
int C2F(playsound)(char *fname,char *command,unsigned long fname_len)
{

#ifdef _MSC_VER
  /* Stop Playing*/
  PlaySound(NULL,NULL,SND_PURGE);	
  /* Play Wav file	*/
  PlaySound(filename,NULL,SND_ASYNC|SND_FILENAME);
  return 0;
#else 
  /* linux : a player should be detected by configure ?
   */
  char system_cmd[FILENAME_MAX+10];
  int rep ;
  sprintf(system_cmd,"%s  %s > /dev/null 2>&1",(command == NULL) ? "play": command, filename);  
  rep = system(system_cmd);
  return rep;
#endif 
}
/*-----------------------------------------------------------------------------------*/ 
