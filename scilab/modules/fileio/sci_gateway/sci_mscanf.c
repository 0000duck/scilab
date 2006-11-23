/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include "Scierror.h"
#include "machine.h"
#include "MALLOC.h"
#include "stack-c.h"
#include "do_xxscanf.h"
#include "do_xxprintf.h"
/*-----------------------------------------------------------------------------------*/ 
#define MAXSTR 512
/*-----------------------------------------------------------------------------------*/ 
extern int StringConvert __PARAMS((char *str));
extern int C2F(xscion) __PARAMS((int *));
extern void C2F (zzledt) ();
extern int do_xxscanf (char *fname, FILE *fp, char *format, int *nargs, char *strv, int *retval, rec_entry *buf, sfdir *type);
extern int Store_Scan __PARAMS((int *nrow,int *ncol,sfdir *type_s,sfdir *type,int *retval, int*retval_s, rec_entry *buf, entry **data,int rowcount,int n));
extern int Sci_Store(int nrow, int ncol, entry *data, sfdir *type, int retval_s);
extern void Free_Scan(int nrow, int ncol, sfdir *type_s, entry **data);
/*-----------------------------------------------------------------------------------*/ 
int int_objscanf(char *fname,unsigned long fname_len)
{
	static char String[MAXSTR];
	static int l1, m1, n1, len= MAXSTR-1,iarg,maxrow,nrow,rowcount,ncol;
	int args,retval,retval_s,lline,status,iflag,err,n_count;
	int interrupt=0;
	entry *data;
	rec_entry buf[MAXSCAN];
	sfdir  type[MAXSCAN],type_s[MAXSCAN];

	Nbvars = 0;
	CheckRhs(1,2);
	if (Rhs==2) 
	{
		GetRhsVar(1,"i",&m1,&n1,&l1);
		if (m1*n1 != 1) 
		{
			Scierror(999,"Error: in scanf: incorrect first argument\r\n");
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

	GetRhsVar(iarg,"c",&m1,&n1,&l1); /** format **/
	n_count=StringConvert(cstk(l1))+1;  /* conversion */

	/** Read a line with Scilab read function **/
	C2F(xscion)(&iflag);

	if (n_count>1) 
	{
		Scierror(999,"Error: in scanf: format cannot include \\n \r\n");
		return 0;
	}

	nrow=maxrow; 
	rowcount = -1; /* number-1 of result lines already got */
	while (1)
	{
		rowcount++;
		if ((maxrow >= 0) && (rowcount >= maxrow)) break;

		/* get a line */
		C2F(xscion)(&iflag);
		C2F(zzledt)(String,&len,&lline,&status,&interrupt,&iflag,strlen(String));

		if(status != 0) 
		{
			Scierror(999,"Error: in scanf\r\n");
			return 0;
		}

		if (lline == 0) {String[0] = ' ';lline=1;}
		/** use the scaned line as input **/
		args = Rhs; /* args set to Rhs on entry */
		if (do_xxscanf("scanf",(FILE *) 0,cstk(l1),&args,String,&retval,buf,type) < 0) return 0;

		if ( retval == EOF)
		{
			/* 
			Scierror(999,"Error: in %s: end of file reached\r\n",fname);
			return 0;
			*/
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
				break;

			case MEM_LACK:
				Free_Scan(rowcount,ncol,type_s,&data);
				Scierror(999,"Error: in scanf: cannot allocate more memory \r\n");
				return 0;
				break;
			}

			if (err ==MISMATCH) break;
		}
	} /*  while (1) */

	/* create Scilab variables with each column of data */
	err=Sci_Store(rowcount,ncol,data,type_s,retval_s);
	if (err==MEM_LACK) { Scierror(999,"Error: in sscanf: cannot allocate more memory \r\n");}
	return 0;
} 
/*-----------------------------------------------------------------------------------*/ 
