/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include "machine.h"
#include "stack-c.h"
/*-----------------------------------------------------------------------------------*/ 
extern int CdfBase __PARAMS((char *fname,int inarg,int oarg,int *callpos,char *option,char *errnames,int which,int (*fonc)(),void (*foncErr)()));
extern int C2F(cdffnc) __PARAMS((int *,double *,double *,double *,double *,double *,double *, int *,double *));
/*-----------------------------------------------------------------------------------*/ 
static void cdffncErr(int status,double bound);
/*-----------------------------------------------------------------------------------*/ 
/*
*  hand written interface 
*  Interface for cdffnc
*  Cumulative Distribution Function
*  Non-central F distribution
*/
/*-----------------------------------------------------------------------------------*/ 
int cdffncI(char* fname,unsigned long l)
{ 
	int minrhs = 5,maxrhs = 6,minlhs=1,maxlhs=2,m1,n1,l1;
	Nbvars = 0;
	CheckRhs(minrhs,maxrhs);
	CheckLhs(minlhs,maxlhs);
	GetRhsVar(1, "c", &m1, &n1, &l1);
	if ( strcmp(cstk(l1),"PQ")==0) 
	{
		static int callpos[6] = {4,5,0,1,2,3};
		CdfBase(fname,4,2,callpos,"PQ","F,Dfn,Dfd and Pnonc",1,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"F")==0) 
	{
		static int callpos[6] = {3,4,5,0,1,2};
		CdfBase(fname,5,1,callpos,"F","Dfn,Dfd,Pnonc,P and Q",2,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Dfn")==0) 
	{
		static int callpos[6] = {2,3,4,5,0,1};
		CdfBase(fname,5,1,callpos,"Dfn","Dfd,Pnonc,P,Q and F",3,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Dfd")==0) 
	{
		static int callpos[6] = {1,2,3,4,5,0};
		CdfBase(fname,5,1,callpos,"Dfd","Pnonc,P,Q,F and Dfn",4,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Pnonc")==0) 
	{
		static int callpos[6] = {0,1,2,3,4,5};
		CdfBase(fname,5,1,callpos,"Pnonc","P,Q,F,Dfn and Dfd",5,C2F(cdffnc),
			cdffncErr);
	}
	else 
	{
		Scierror(999,"%s: Wrong first argument %s\r\n",fname,cstk(l1));
	}      
	return 0;
}
/*-----------------------------------------------------------------------------------*/ 
static void cdffncErr(int status,double bound)
{
	static char *param[7]={"X", "P","Q","F","Dfn","Dfd","Pnonc"};
	switch ( status ) 
	{
	case 1 : Scierror(999,"answer appears to be lower than lowest search bound %f\r\n",bound);break;
	case 2 : Scierror(999,"answer appears to be higher than greatest search bound %f\r\n",bound);break;
	case 3 : Scierror(999," P + Q .ne. 1 \r\n");break ;
	default : 
		Scierror(999,"input parameter %c is out of range \r\n\tbound exceeded: %f\r\n",
			param[-status-1],bound);
	}
}
/*-----------------------------------------------------------------------------------*/ 
