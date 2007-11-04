/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include "gw_statistics.h"
#include "machine.h"
#include "stack-c.h"
#include "CdfBase.h"
#include "Scierror.h"
#include "localization.h"
/*-----------------------------------------------------------------------------------*/
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
	GetRhsVar(1,STRING_DATATYPE, &m1, &n1, &l1);
	if ( strcmp(cstk(l1),"PQ")==0)
	{
		static int callpos[6] = {4,5,0,1,2,3};
		CdfBase(fname,4,2,callpos,"PQ",_("F,Dfn,Dfd and Pnonc"),1,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"F")==0)
	{
		static int callpos[6] = {3,4,5,0,1,2};
		CdfBase(fname,5,1,callpos,"F",_("Dfn,Dfd,Pnonc,P and Q"),2,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Dfn")==0)
	{
		static int callpos[6] = {2,3,4,5,0,1};
		CdfBase(fname,5,1,callpos,"Dfn",_("Dfd,Pnonc,P,Q and F"),3,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Dfd")==0)
	{
		static int callpos[6] = {1,2,3,4,5,0};
		CdfBase(fname,5,1,callpos,"Dfd",_("Pnonc,P,Q,F and Dfn"),4,C2F(cdffnc),
			cdffncErr);
	}
	else if ( strcmp(cstk(l1),"Pnonc")==0)
	{
		static int callpos[6] = {0,1,2,3,4,5};
		CdfBase(fname,5,1,callpos,"Pnonc",_("P,Q,F,Dfn and Dfd"),5,C2F(cdffnc),
			cdffncErr);
	}
	else
	{
		Scierror(999,_("%s: Wrong first argument %s\n"),fname,cstk(l1));
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
static void cdffncErr(int status,double bound)
{
	static char *param[7]={"X", "P","Q","F","Dfn","Dfd","Pnonc"};
	switch ( status )
	{
	case 1 : Scierror(999,_("answer appears to be lower than lowest search bound %f\n"),bound);break;
	case 2 : Scierror(999,_("answer appears to be higher than greatest search bound %f\n"),bound);break;
	case 3 : Scierror(999," P + Q .ne. 1 \n");break ;
	default :
		Scierror(999,"input parameter %c is out of range \n\tbound exceeded: %f\n",
			param[-status-1],bound);
	}
}
/*-----------------------------------------------------------------------------------*/
