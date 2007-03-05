/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include <stdio.h>
#include "machine.h"
#include "stack-c.h"
#include "do_xxprintf.h"
#include "do_xxscanf.h"
#include "fileio.h"
#include "files.h"
#include "gw_fileio.h"
/*-----------------------------------------------------------------------------------*/ 
int int_objfscanf(char *fname,unsigned long fname_len)
{
	static int l1, m1, n1,l2,m2,n2,iarg,maxrow,nrow,rowcount,ncol;
	FILE  *f;
	int args,retval,err;
	int retval_s=0;
	entry *data=NULL;
	long int pos;

	rec_entry buf[MAXSCAN];
	sfdir  type[MAXSCAN],type_s[MAXSCAN];

	Nbvars = 0;
	CheckRhs(2,3);

	if (Rhs==3) 
	{
		GetRhsVar(1,"i",&m1,&n1,&l1);
		if (m1*n1 != 1 ) 
		{
			Scierror(999,"Error: in fscanf: incorrect first argument\r\n");
			return 0;
		}
		iarg=2;
		maxrow=*istk(l1);
	}
	else
	{
		iarg=1;
		maxrow=1;
	}

	GetRhsVar(iarg,"i",&m1,&n1,&l1);
	GetRhsVar(iarg+1,"c",&m2,&n2,&l2);/* format */

	StringConvert(cstk(l2));  /* conversion */
	if ((f= GetFile(istk(l1))) == (FILE *)0)
	{
		Scierror(999,"fprintf:\t wrong file descriptor %d\r\n",*istk(l1));
		return 0;
	}

	nrow=maxrow; 
	rowcount = -1;

	while (1) 
	{
		rowcount++;
		if ((maxrow >= 0) && (rowcount >= maxrow)) break;
		args = Rhs; /* args set to Rhs on entry */
		pos=ftell(f);
		if ( do_xxscanf("fscanf",f,cstk(l2),&args,(char *)0,&retval,buf,type) < 0 )  return 0;
		if ( retval == EOF) 
		{
			/* 
			Scierror(999,"Error: in %s: end of file reached\r\n",fname);
			*/
			break;
		}
		if ((err=Store_Scan(&nrow,&ncol,type_s,type,&retval,&retval_s,buf,&data,rowcount,args)) <0 )
		{
			switch (err) 
			{
			case MISMATCH:
				if (maxrow>=0) 
				{
					Free_Scan(rowcount,ncol,type_s,&data);
					Scierror(999,"Error: in fscanf: data mismatch\r\n");
					return 0;
				}
				fseek(f,pos,SEEK_SET);
				break;

			case MEM_LACK:
				Free_Scan(rowcount,ncol,type_s,&data);
				Scierror(999,"Error: in fscanf: cannot allocate more memory \r\n");
				return 0;
				break;
			}
			if (err==MISMATCH) break;
		}
	} /* while */

	/* create Scilab variable with each column of data */
	err=Sci_Store(rowcount,ncol,data,type_s,retval_s);
	Free_Scan(rowcount,ncol,type_s,&data);
	if (err==MEM_LACK) { Scierror(999,"Error: in sscanf: cannot allocate more memory \r\n");}
	return 0;
}  
/*-----------------------------------------------------------------------------------*/ 
