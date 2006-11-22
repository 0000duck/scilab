/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include "Scierror.h"
#include "machine.h"
#include "MALLOC.h"
#include "stack-c.h"
#include "do_xxprintf.h"
/*-----------------------------------------------------------------------------------*/ 
int int_objsprintf(char *fname,unsigned long fname_len)
{
	unsigned long lstr;
	static int l1, m1, n1,n2,lcount,rval,blk=200;
	static int k;
	char ** strs;
	char *str,*str1;
	int n,nmax,cat_to_last,ll;
	char *ptrFormat=NULL;
	int i=0;
	int NumberPercent=0;

	Nbvars = 0;
	CheckRhs(1,1000);
	CheckLhs(0,1);
	if ( Rhs < 1 ) 
	{ 
		Scierror(999,"Error:\tRhs must be > 0\r\n");
		return 0;
	}
	for (k=2;k<=Rhs;k++) {
		if (VarType(k) !=1 && VarType(k) !=10) {OverLoad(k);return 0;}
	}
	GetRhsVar(1,"c",&m1,&n1,&l1);
	ptrFormat=cstk(l1);

	for(i=0;i<(int)strlen(ptrFormat);i++)
	{
		if (ptrFormat[i]=='%') {
			NumberPercent++;
			if (ptrFormat[i+1]=='%') {NumberPercent--;i++;}
		}
	}

	if (NumberPercent<Rhs-1)
	{
		Scierror(999,"sprintf: Invalid format.\r\n");
		return 0;
	}

	n=0; /* output line counter */
	nmax=0;
	strs=NULL;
	lcount=1;
	cat_to_last=0;

	while (1) 
	{
		if ((rval=do_xxprintf("sprintf",(FILE *) 0,cstk(l1),Rhs,1,lcount,
			(char **) &lstr)) < 0) break; 
		lcount++;
		str=(char *) lstr;
		str1=str;
		while (*str != '\0') {
			if (strncmp(str,"\\n",2) ==0) {
				k=(int)(str-str1);
				if (! cat_to_last) 
				{ 
					/*add a new line */
					if (n==nmax) 
					{
						nmax+=blk;
						if (strs) strs = (char **) REALLOC(strs,nmax*sizeof(char **));
						else strs = (char **) MALLOC(nmax*sizeof(char **));
						if ( strs == NULL) goto mem;
					}
					if ((strs[n]=MALLOC((k+1))) == NULL) goto mem;
					strncpy(strs[n],str1, k);
					strs[n][k]='\0';
					n++;
				}
				else { /* cat to previous line */
					ll=strlen(strs[n-1]);
					if ((strs[n-1]=REALLOC(strs[n-1],(k+1+ll))) == NULL) goto mem;
					strncpy(&(strs[n-1][ll]),str1, k);
					strs[n-1][k+ll]='\0';
				}
				k=0;
				str+=2;
				str1=str;
				cat_to_last=0;
			}
			else
				str++;
		}
		k=(int)(str-str1);
		if (k>0) {
			if ((! cat_to_last) || (n == 0)) { /*add a new line */
				if (n==nmax) {
					nmax+=blk;
					if (strs)
					{
						if ((strs = (char **) REALLOC(strs,nmax*sizeof(char **))) == NULL) goto mem;
					}
					else
					{
						if ( (strs = (char **) MALLOC(nmax*sizeof(char **))) == NULL) goto mem;
					}

				}
				if ((strs[n]=MALLOC((k+1))) == NULL) goto mem;
				strncpy(strs[n],str1, k);
				strs[n][k]='\0';
				n++;

			}
			else { /* cat to previous line */
				ll=strlen(strs[n-1]);
				if ((strs[n-1]=REALLOC(strs[n-1],(k+1+ll))) == NULL) goto mem;
				strncpy(&(strs[n-1][ll]),str1, k);
				strs[n-1][k+ll]='\0';
			}
		}
		if (strncmp(str-2,"\\n",2) !=0) cat_to_last=1;
		if (Rhs == 1) break;

	}
	if (rval == RET_BUG) return 0;
	/** Create a Scilab String : lstr must not be freed **/
	n2=1;
	CreateVarFromPtr(Rhs+1, "S", &n, &n2, strs);
	for (k=0;k<n;k++) FREE(strs[k]);
	FREE(strs);
	LhsVar(1)=Rhs+1;
	PutLhsVar();    
	return 0;
mem:
	Scierror(999,"sprintf: cannot allocate cannot allocate more memory \r\n");
	return 0;
}  
/*-----------------------------------------------------------------------------------*/ 
