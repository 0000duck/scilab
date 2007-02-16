/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "gw_core.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "stackinfo.h"
#include "Scierror.h"
/*-----------------------------------------------------------------------------------*/
#define LengthNameVariableScilabMax 24
/*-----------------------------------------------------------------------------------*/
char *getLocalNamefromId(int n);
char *getGlobalNamefromId(int n);
/*-----------------------------------------------------------------------------------*/
struct VariableStruct
{
 char *NameVariable;
 int SizeVariable;
};
/*-----------------------------------------------------------------------------------*/
static BOOL SetVariablesStructs(struct VariableStruct **GVstruct,int *GlenStructArray,struct VariableStruct **LVstruct,int *LlenStructArray);
static void DispVariables(struct VariableStruct* Vstruct,char *Message,int lenStructArray,int memused,int memtotal,int varused,int vartotal);
static void SortVarsStructByStrings(struct VariableStruct *Vstruct,int SizeStruct);
static BOOL FreeVariableStructArray(struct VariableStruct* Vstruct,int lenStructArray);
int getLocalSizefromId(int n);
int getGlobalSizefromId(int n);
/*-----------------------------------------------------------------------------------*/
static int NoRhs(struct VariableStruct* GVstruct,int GlenStructArray,struct VariableStruct* LVstruct,int LlenStructArray,BOOL Sorted);
static int OneLhs(struct VariableStruct* Vstruct,int lenStructArray,BOOL Sorted);
static int TwoLhs(struct VariableStruct* Vstruct,int lenStructArray,BOOL Sorted);
/*-----------------------------------------------------------------------------------*/
int C2F(sci_who) _PARAMS((char *fname,unsigned long fname_len))
 {
	 static int l1,n1,m1;

	 struct VariableStruct *GlobalVariables = NULL;
	 struct VariableStruct *LocalVariables = NULL;

	 int NbrVarsGlobal=0;
	 int NbrVarsLocal=0;

	 Rhs=Max(0,Rhs);
	 CheckRhs(0,2);
	 CheckLhs(0,2);

	 SetVariablesStructs(&GlobalVariables,&NbrVarsGlobal,&LocalVariables,&NbrVarsLocal);

	 if (Rhs == 0) /* who() */
	 {
		NoRhs(GlobalVariables,NbrVarsGlobal,LocalVariables,NbrVarsLocal,FALSE);
	 }
	 else
	 if (Rhs == 1) /* who('get') or who('global') or who('sorted')*/
	 {
		 if (GetType(1) == sci_strings) 
		 {
			 char *Param1String=NULL;
			 GetRhsVar(1,"c",&m1,&n1,&l1);
			 Param1String=cstk(l1);

			 if ( (strcmp(Param1String,"get")==0) ||
			      (strcmp(Param1String,"local")==0) ||
			      (strcmp(Param1String,"global")==0) ||
				  (strcmp(Param1String,"sorted")==0) )
			 {
				if (strcmp(Param1String,"sorted")==0)
				{
					NoRhs(GlobalVariables,NbrVarsGlobal,LocalVariables,NbrVarsLocal,TRUE);
				}
				else
				if (strcmp(Param1String,"global")==0)
				{
					if (Lhs == 1)
					{
						OneLhs(GlobalVariables,NbrVarsGlobal,FALSE);
					}
					else /* Lhs == 2 */
					{
						TwoLhs(GlobalVariables,NbrVarsGlobal,FALSE);
					}
				}
				else /* get or local */
				{
					if (Lhs == 1)
					{
						OneLhs(LocalVariables,NbrVarsLocal,FALSE);
					}
					else /* Lhs == 2 */
					{
						TwoLhs(LocalVariables,NbrVarsLocal,FALSE);
					}
				}
			 }
			 else
			 {
				 FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
				 FreeVariableStructArray(LocalVariables,NbrVarsLocal);

				 Scierror(999,"first parameter must be 'local' , 'get' , 'global' or 'sorted'.\r\n");
				 return 0;
			 }
		 }
		 else
		 {
			 FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
			 FreeVariableStructArray(LocalVariables,NbrVarsLocal);

			 Scierror(999,"first parameter must be 'local' , 'get' , 'global' or 'sorted'.\r\n");
			 return 0;
		 }
	 }
	 else
	 if (Rhs == 2) /* who('get','sorted') or who('global','sorted') */
	 {
		 if ( (GetType(1) == sci_strings) && (GetType(2) == sci_strings) )
		 {
			  char *Param1String=NULL;
			  char *Param2String=NULL;

			  GetRhsVar(1,"c",&m1,&n1,&l1);
			  Param1String=cstk(l1);

			  GetRhsVar(2,"c",&m1,&n1,&l1);
			  Param2String=cstk(l1);

			  if (strcmp(Param2String,"sorted"))
			  {
				  FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
				  FreeVariableStructArray(LocalVariables,NbrVarsLocal);

				  Scierror(999,"second parameter must be 'sorted'.\r\n");
				  return 0;
			  }
			  else
			  {
				  if ( (strcmp(Param1String,"get")==0) ||
				   	   (strcmp(Param1String,"local")==0) ||
				  	   (strcmp(Param1String,"global")==0) )
				  {
					if (strcmp(Param1String,"global")==0)
					{
						if (Lhs == 1)
						{
							OneLhs(GlobalVariables,NbrVarsGlobal,TRUE);
						}
						else /* Lhs == 2 */
						{
							TwoLhs(GlobalVariables,NbrVarsGlobal,TRUE);
						}
				    }
					else /* get or local */
					{
						if (Lhs == 1)
						{
							OneLhs(LocalVariables,NbrVarsLocal,TRUE);
						}
						else /* Lhs == 2 */
						{
							TwoLhs(LocalVariables,NbrVarsLocal,TRUE);
						}
					}
				  }
				else
				{
					FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
					FreeVariableStructArray(LocalVariables,NbrVarsLocal);

					Scierror(999,"first parameter must be 'local' , 'get' or 'global'.\r\n");
					return 0;
				 }
			  }
		 }
		 else
		 {
			 FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
			 FreeVariableStructArray(LocalVariables,NbrVarsLocal);

			 Scierror(999,"first parameter must be 'local' , 'get' , 'global' and second parameter must be 'sorted'.\r\n");
			 return 0;
		 }
	 }

	 FreeVariableStructArray(GlobalVariables,NbrVarsGlobal);
	 FreeVariableStructArray(LocalVariables,NbrVarsLocal);

	 return 0;
 }
 /*-----------------------------------------------------------------------------------*/
 char *getLocalNamefromId(int n)
 {
	 integer *id=NULL;	
	 static integer c__1 = 1;
	 int i=0;
	 char *Name=NULL;
	 id=&C2F(vstk).idstk[C2F(vstk).bot * 6 - 6];
	 id -= 7;
	 Name = (char*)MALLOC(sizeof(char)*LengthNameVariableScilabMax+1);

	 C2F(cvname)(&id[n * 6 + 1], Name, &c__1,LengthNameVariableScilabMax);

	 Name[LengthNameVariableScilabMax]='\0';
	 for (i=0;i<LengthNameVariableScilabMax+1;i++)
	 {
		 if (Name[i] == ' ')
		 {
			 Name[i] = '\0';
			 return Name;
		 }
	 }
	 return Name;
 }
 /*-----------------------------------------------------------------------------------*/
 char *getGlobalNamefromId(int n)
 {
	 integer *id=NULL;	
	 static integer c__1 = 1;
	 int i=0;
	 char *Name=NULL;
	 id=&C2F(vstk).idstk[(C2F(vstk).isiz + 2) * 6 - 6];
	 id -= 7;
	 Name = (char*)MALLOC(sizeof(char)*LengthNameVariableScilabMax+1);

	 C2F(cvname)(&id[(n+1) * 6 + 1], Name, &c__1,LengthNameVariableScilabMax);

	 Name[LengthNameVariableScilabMax]='\0';

	 for (i=0;i<LengthNameVariableScilabMax+1;i++)
	 {
		 if (Name[i] == ' ')
		 {
			 Name[i] = '\0';
			 return Name;
		 }
	 }

	 return Name;
 }
 /*-----------------------------------------------------------------------------------*/
 int getLocalSizefromId(int n)
 {
	 int LocalSize=0;
	 int Lused=0;
	 int Ltotal=0;

	 C2F(getvariablesinfo)(&Ltotal,&Lused);
	 
	 if ( (n >= 0) && ( n < Lused ) )
	 {
		 LocalSize=(int)(C2F(vstk).lstk[C2F(vstk).bot + n] - C2F(vstk).lstk[C2F(vstk).bot + n - 1]);
	 }
	 else
	 {
		 LocalSize=-1;
	 }

	 return LocalSize;
 }
 /*-----------------------------------------------------------------------------------*/
 int getGlobalSizefromId(int n)
 {
	 int GlobalSize=0;
	 int Gused=0;
	 int Gtotal=0;

	 C2F(getgvariablesinfo)(&Gtotal,&Gused);

	 if ( (n >= 0) && ( n < Gused ) )
	 {
		 GlobalSize=(int)(C2F(vstk).lstk[C2F(vstk).isiz + 2 + n] - C2F(vstk).lstk[C2F(vstk).isiz + 2 + n - 1]);
	 }
	 else
	 {
		 GlobalSize=-1;
	 }
	 return GlobalSize;
 }
 /*-----------------------------------------------------------------------------------*/
 static void SortVarsStructByStrings(struct VariableStruct *Vstruct,int SizeStruct)
 {
	 int fin,i;
	 for(fin=SizeStruct-1;fin>0;fin--)
	 {
		 int Sorted=FALSE;
		 for(i=0;i<fin;i++)
		 {
			 if(strcmp(Vstruct[i].NameVariable,Vstruct[i+1].NameVariable)>0)
			 {
				 struct VariableStruct StructTmp;

				 StructTmp.NameVariable = Vstruct[i].NameVariable;
				 StructTmp.SizeVariable = Vstruct[i].SizeVariable;

				 Vstruct[i].NameVariable = Vstruct[i+1].NameVariable;
				 Vstruct[i].SizeVariable = Vstruct[i+1].SizeVariable;

				 Vstruct[i+1].NameVariable = StructTmp.NameVariable;
				 Vstruct[i+1].SizeVariable = StructTmp.SizeVariable;

				 Sorted=TRUE;
			 }
		 }
		 if(!Sorted)break;
	 }
 }
 /*-----------------------------------------------------------------------------------*/
  static void DispVariables(struct VariableStruct* Vstruct,char *Message,int lenStructArray,int memused,int memtotal,int varused,int vartotal)
 {
	 int i=0;

	 sciprint("\n%s\n\n",Message);
	 for (i=1;i<lenStructArray+1;i++)
	 {
		 sciprint("%+24s ",Vstruct[i-1].NameVariable);
		 if (i%4==0) sciprint("\n");
	 }

	 sciprint("\n\n");
	 sciprint(" using %10d elements out of  %10d.\n",memused,memtotal);
	 sciprint(" and   %10d variables out of %10d.\n",varused,vartotal);

 }
 /*-----------------------------------------------------------------------------------*/
 static BOOL FreeVariableStructArray(struct VariableStruct* Vstruct,int lenStructArray)
 {
	 BOOL bOK=FALSE;
	 if (Vstruct)
	 {
		 int i=0;
		 for (i=0;i<lenStructArray;i++)
		 {
			 if (Vstruct[i].NameVariable) {FREE(Vstruct[i].NameVariable);Vstruct[i].NameVariable=NULL;}
			 Vstruct[i].SizeVariable=-1;
		 }
		 FREE(Vstruct);
		 Vstruct=NULL;
		 bOK=TRUE;
	 }
	 return bOK;
 }
 /*-----------------------------------------------------------------------------------*/
 static BOOL SetVariablesStructs(struct VariableStruct **GVstruct,int *GlenStructArray,struct VariableStruct **LVstruct,int *LlenStructArray)
 {
	 BOOL bOK=FALSE;
	 int j=0;

	 int Gused=0;
	 int Gtotal=0;
	 int Lused=0;
	 int Ltotal=0;

	 C2F(getvariablesinfo)(&Ltotal,&Lused);
	 C2F(getgvariablesinfo)(&Gtotal,&Gused);

	 *LlenStructArray=Lused;
	 *GlenStructArray=Gused;

	 if (*GlenStructArray) *GVstruct = (struct VariableStruct *)MALLOC(sizeof(struct VariableStruct)* (*GlenStructArray+1));
	 if (*LlenStructArray) *LVstruct = (struct VariableStruct *)MALLOC(sizeof(struct VariableStruct)*(*LlenStructArray+1));

	 if ( (GVstruct) && (LVstruct) )
	 {
		 for (j=1;j<*LlenStructArray+1;++j)
		 {
			 (*LVstruct)[j-1].NameVariable = getLocalNamefromId(j);
			 (*LVstruct)[j-1].SizeVariable = getLocalSizefromId(j-1);
		 }

		 for (j=0;j< *GlenStructArray;j++)
		 {
			 (*GVstruct)[j].NameVariable = getGlobalNamefromId(j);
			 (*GVstruct)[j].SizeVariable = getGlobalSizefromId(j);
		 }
		 bOK= TRUE;
	 }
	 return bOK;
 }
 /*-----------------------------------------------------------------------------------*/
 static int NoRhs(struct VariableStruct* GVstruct,int GlenStructArray,struct VariableStruct* LVstruct,int LlenStructArray,BOOL Sorted)
 {
	 integer memtotal=0;
	 integer memused=0;
	 integer vartotal=0;
	 integer varused=0;

	 integer gmemtotal=0;
	 integer gmemused=0;
	 integer gvartotal=0;
	 integer gvarused=0;

	 C2F(getstackinfo)(&memtotal,&memused);
	 C2F(getvariablesinfo)(&vartotal,&varused);

	 if (Sorted) SortVarsStructByStrings(LVstruct,LlenStructArray);

	 DispVariables(LVstruct,"your variables are :",LlenStructArray,memused,memtotal,varused,vartotal);

	 C2F(getgstackinfo)(&gmemtotal,&gmemused);
	 C2F(getgvariablesinfo)(&gvartotal,&gvarused);

	 if (Sorted) SortVarsStructByStrings(GVstruct,GlenStructArray);

	 DispVariables(GVstruct,"your global variables are :",GlenStructArray,gmemused,gmemtotal,gvarused,gvartotal);

	 LhsVar(1) = 0;
	 C2F(putlhsvar)();
	 return 0;
 }
/*-----------------------------------------------------------------------------------*/
 static int TwoLhs(struct VariableStruct* Vstruct,int lenStructArray,BOOL Sorted)
 {
	 char **Tab=NULL;
	 int *Size=NULL;
	 int i=0;
	 int m=0;
	 int n=0;

	 if (Sorted) SortVarsStructByStrings(Vstruct,lenStructArray);

	 Tab=(char **)MALLOC(sizeof(char*)*lenStructArray);
	 Size=(int *)MALLOC(sizeof(int*)*lenStructArray);

	 for (i=0;i<lenStructArray;i++)
	 {
		 Tab[i] = (char*)MALLOC(sizeof(char)*strlen(Vstruct[i].NameVariable));
		 sprintf(Tab[i],"%s",Vstruct[i].NameVariable);
		 Size[i]=Vstruct[i].SizeVariable;
	 }

	 m=lenStructArray;
	 n=1;

	 CreateVarFromPtr(Rhs+1, "S", &m, &n, Tab);
	 LhsVar(1) = Rhs+1;

	 CreateVarFromPtr(Rhs+2, "i", &m, &n, &Size);
	 LhsVar(2) = Rhs+2;

	 C2F(putlhsvar)();

	 if (Tab) {FREE(Tab);Tab=NULL;}
	 if (Size) {FREE(Size);Size=NULL;}
	 return 0;
 }
 /*-----------------------------------------------------------------------------------*/
 static int OneLhs(struct VariableStruct* Vstruct,int lenStructArray,BOOL Sorted)
 {
	 int i=0;
	 int m=0;
	 int n=0;

	 char **LocalTab = NULL;

	 if (Sorted) SortVarsStructByStrings(Vstruct,lenStructArray);

	 LocalTab=(char **)MALLOC(sizeof(char*)*(lenStructArray));

	 for (i=0;i<lenStructArray;i++)
	 {
		 if (strlen(Vstruct[i].NameVariable)>0)
		 {
			 LocalTab[i] = (char*)MALLOC(sizeof(char)*strlen(Vstruct[i].NameVariable)+1);
			 strcpy(LocalTab[i],Vstruct[i].NameVariable);
		 }
	 }

	 m=lenStructArray;
	 n=1;
	 CreateVarFromPtr(Rhs+1, "S", &m, &n,LocalTab);
	 LhsVar(1)=Rhs+1;


	 for (i=0;i<lenStructArray;i++) 
	 { 
		 FREE(LocalTab[i]);
		 LocalTab[i]=NULL; 
	 }
	 FREE(LocalTab);

	 C2F(putlhsvar)();
	 return 0;
 }
/*-----------------------------------------------------------------------------------*/
