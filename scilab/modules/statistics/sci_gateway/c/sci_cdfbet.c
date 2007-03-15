/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include "gw_statistics.h"
#include "machine.h"
#include "stack-c.h"
#include "CdfBase.h"
/*-----------------------------------------------------------------------------------*/ 
extern int C2F(cdfbet) __PARAMS((int *,double *,double *,double *,double *,double *,double *, int *,double *));
/*-----------------------------------------------------------------------------------*/ 
static void cdfbetErr(int status,double bound);
/*-----------------------------------------------------------------------------------*/ 
/*
*  hand written interface 
*  Interface for cdfbet 
*
*      SUBROUTINE CDFBET( WHICH, P, Q, X, Y, A, B, STATUS, BOUND )
*               Cumulative Distribution Function
*                         BETa Distribution
*/
/*-----------------------------------------------------------------------------------*/ 
int cdfbetI(char* fname,unsigned long l)
{ 
	int minrhs = 5,maxrhs = 6,minlhs=1,maxlhs=2,m1,n1,l1;
	Nbvars = 0;
	CheckRhs(minrhs,maxrhs);
	CheckLhs(minlhs,maxlhs);
	GetRhsVar(1, "c", &m1, &n1, &l1);
	if ( strcmp(cstk(l1),"PQ")==0) 
	{
		static int callpos[6] = {4,5,0,1,2,3};
		CdfBase(fname,4,2,callpos,"PQ","X,Y,A and B",1,C2F(cdfbet),
			cdfbetErr);
	}
	else if ( strcmp(cstk(l1),"XY")==0) 
	{
		static int callpos[6] = {2,3,4,5,0,1};
		CdfBase(fname,4,2,callpos,"XY","A,B,P and Q",2,C2F(cdfbet),
			cdfbetErr);
	}
	else if ( strcmp(cstk(l1),"A")==0) 
	{
		static int callpos[6] = {1,2,3,4,5,0};
		CdfBase(fname,5,1,callpos,"A","B,P,Q,X and Y",3,C2F(cdfbet),
			cdfbetErr);
	}
	else if ( strcmp(cstk(l1),"B")==0) 
	{
		static int callpos[6] = {0,1,2,3,4,5};
		CdfBase(fname,5,1,callpos,"B","P,Q,X,Y and A",4,C2F(cdfbet),
			cdfbetErr);
	}
	else 
	{
		Scierror(999,"%s: Wrong first argument %s\r\n",fname,cstk(l1));
		return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/ 
static void cdfbetErr(int status,double bound)
{
	static char param[]="-PQXYAB";
	switch ( status ) 
	{
	case 1 : Scierror(999,"answer appears to be lower than lowest search bound %f\r\n",bound);break;
	case 2 : Scierror(999,"answer appears to be higher than greatest search bound %f\r\n",bound);break;
	case 3 : Scierror(999," P + Q .ne. 1 \r\n");break ;
	case 4 : Scierror(999," X + Y .ne. 1 \r\n");break;
	default : 
		Scierror(999,"input parameter %c is out of range \r\n\tbound exceeded: %f\r\n",
			param[-status-1],bound);
	}
}
/*-----------------------------------------------------------------------------------*/ 
