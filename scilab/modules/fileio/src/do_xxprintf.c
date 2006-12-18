/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/ 
#include <stdio.h>
#include <ctype.h>  
#include "machine.h"
#include "MALLOC.h"
#include "stack-c.h"
#include "do_xxprintf.h"
#include "Scierror.h"
#include "sciprint.h"
/*-----------------------------------------------------------------------------------*/
typedef int (*XXPRINTF) __PARAMS((FILE *, char *,...));
typedef int (*FLUSH) __PARAMS((FILE *));
/*-----------------------------------------------------------------------------------*/
#define  PF_C		0
#define  PF_S		1
#define  PF_D		2
#define  PF_LD		3
#define  PF_F		4
#define  MAX_SPRINTF_SIZE  4096
/*-----------------------------------------------------------------------------------*/
static char sprintf_buffer[MAX_SPRINTF_SIZE];
static char *sprintf_limit = sprintf_buffer + MAX_SPRINTF_SIZE;
/*-----------------------------------------------------------------------------------*/
static int voidflush(FILE *fp);
static int GetScalarInt(char *fname,int *first,int *arg,int narg, int *ir,int ic,int *ival);
static int GetString (char *fname,int *first,int *arg,int narg, int *ir,int ic,char **sval);
static int GetScalarDouble(char *fname,int *first,int *arg,int narg, int *ir,int ic,double *dval);
static void error_on_rval(XXPRINTF xxprintf,FLUSH flush,char *target);
static int call_printf(XXPRINTF xxprintf,char *target,char *p,char *sval,int *asterisk,int asterisk_count,int conversion_type,double dval );
static void set_xxprintf(FILE *fp,XXPRINTF *xxprintf,FLUSH *flush,char **target);
/*-----------------------------------------------------------------------------------*/
extern int SciStrtoStr(int *Scistring, int *nstring, int *ptrstrings, char **strh);
/*-----------------------------------------------------------------------------------*/
static void error_on_rval(XXPRINTF xxprintf,FLUSH flush,char *target)
{
	(*xxprintf) ((VPTR) target, "\n");
	(*flush) ((FILE *) target);
	Scierror(998,"Error:\tprintf: not enough arguments\r\n");
}
/*-----------------------------------------------------------------------------------*/
static int call_printf(XXPRINTF xxprintf,char *target,char *p,char *sval,int *asterisk,int asterisk_count,int conversion_type,double dval )
{
	/* for switch on number of '*' and type */
	#define  choosetype(num,type)  (5*(num)+(type))

	int retval=-1;	

	switch (choosetype (asterisk_count, conversion_type))
	{
		case choosetype (0, PF_S):
		retval += (*xxprintf) ((VPTR) target, p, sval);
		FREE(sval);
		break;

		case choosetype (1, PF_S):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], sval);
		FREE(sval);
		break;

		case choosetype (2, PF_S):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], asterisk[1], sval);
		FREE(sval);
		break;

		case choosetype (0, PF_C):
		retval += (*xxprintf) ((VPTR) target, p, sval[0]);
		FREE(sval);
		break;

		case choosetype (1, PF_C):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], sval[0]);
		FREE(sval);
		break;

		case choosetype (2, PF_C):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], asterisk[1],sval[0]);
		FREE(sval);
		break;

		case choosetype (0, PF_D):
		retval += (*xxprintf) ((VPTR) target, p, (int) dval);
		break;

		case choosetype (1, PF_D):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], (int) dval);
		break;

		case choosetype (2, PF_D):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], asterisk[1], (int) dval);
		break;

		case choosetype (0, PF_LD):
		retval += (*xxprintf) ((VPTR) target, p, (long int) dval);
		break;

		case choosetype (1, PF_LD):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], (long int) dval);
		break;

		case choosetype (2, PF_LD):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], asterisk[1], (long int) dval);
		break;

		case choosetype (0, PF_F):
		retval += (*xxprintf) ((VPTR) target, p, dval);
		break;

		case choosetype (1, PF_F):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], dval);
		break;

		case choosetype (2, PF_F):
		retval += (*xxprintf) ((VPTR) target, p, asterisk[0], asterisk[1], dval);
		break;
	}
	return retval;
}
/*-----------------------------------------------------------------------------------*/
static void set_xxprintf(FILE *fp,XXPRINTF *xxprintf,FLUSH *flush,char **target)
{
	if (fp == (FILE *) 0)		
	{
		/* sprintf */
		*target = sprintf_buffer;
		*flush = voidflush;
		*xxprintf = (XXPRINTF) sprintf;
	}
	else if ( fp == stdout ) 
	{
		/* sciprint2 */
		*target =  (char *) 0; 
		*flush = fflush;
		*xxprintf = (XXPRINTF) sciprint2;
	}
	else 
	{
		/* fprintf */
		*target = (char *) fp;
		*flush = fflush;
		*xxprintf = (XXPRINTF) fprintf;
	}
}
/*-----------------------------------------------------------------------------------*/
int do_xxprintf (char *fname, FILE *fp, char *format, int nargs, int argcount, int lcount, char **strv)
{
	int retval=0; /* return value */
	int arg_count = 0;
	int	ccount = 0;

	XXPRINTF xxprintf=NULL; /* sprintf sciprint2 fprintf */
	FLUSH   flush=NULL;
	char *target=NULL;
	register char *currentchar=NULL;

	currentchar = format;
	arg_count = argcount;
	ccount = 1;

	set_xxprintf(fp,&xxprintf,&flush,&target);
	
	/* "scan" string format. */
	while (TRUE)
	{
		char *p=NULL;
		char *sval=NULL;

		int prev=0; 
		int ival=0;
		int low_flag = 0;
		int	high_flag = 0;
		
		int asterisk_count = 0;
		int asterisk[2];
		int rval=0;

		int conversion_type = 0;
		double dval = 0.0;
		register char *tmpcurrentchar=NULL;
		
		asterisk[0]=0;
		asterisk[1]=0;

		if (fp)		
		{
			while (*currentchar != '%')
			{
				switch (*currentchar) 
				{
				case 0 : 
					fflush (fp);
					return (retval);
					break;
				case '\\':
					currentchar++;
					switch (*currentchar) 
					{
					case 0 : 
						fflush (fp);
						return (retval);
						break;
					case 'r':
						(*xxprintf) ((VPTR) target, "\r");
						currentchar++;
						retval++;
						break;
					case 'n':
						if ( fp == stdout ) (*xxprintf) ((VPTR) target, "\r");
						(*xxprintf) ((VPTR) target, "\n");
						currentchar++;
						retval++;
						break;
					case 't':
						(*xxprintf) ((VPTR) target, "\t");
						currentchar++;
						retval++;
						break;
					case '\\':
						(*xxprintf) ((VPTR) target, "\\");
						currentchar++;
						retval++;
						break;
					default:
						/* putc */
						(*xxprintf) ((VPTR) target, "%c",*currentchar);
						currentchar++;
						retval++;
					}
					break;
				default:
					/* putc */
					(*xxprintf) ((VPTR) target, "%c",*currentchar);
					currentchar++;
					retval++;
					break;
				}
			}
		}
		else
		{
			/* sprintf() */
			while (*currentchar != '%')
			{
				if (*currentchar == 0)
				{
					if (target > sprintf_limit)	/* over sprintf_limit */
					{
						Scierror(998,"Error:\tsprintf problem, buffer too small\r\n");
						return RET_BUG;
					}
					else
					{
						/* done */
						*target = '\0';
						*strv = sprintf_buffer;
						return (retval);
					}
				}
				else
				{
					*target++ = *currentchar++;
					retval++;
				}
			}
		}

		if (*++currentchar == '%')	/* %% */
		{
			if (fp)
			{
				/* putc */
				(*xxprintf) ((VPTR) target, "%c",*currentchar);
				retval++;
			}
			else
			{
				*target++ = *currentchar;
			}
			currentchar++;
			continue;
		}

		p = currentchar - 1;

		/* remove '-' '+' ' ' '#' '0' */
		while (*currentchar == '-' || *currentchar == '+' || *currentchar == ' ' || *currentchar == '#' || *currentchar == '0') currentchar++;

		asterisk_count = 0;	
		if (*currentchar == '*')
		{
			rval=GetScalarInt(fname,&prev,&arg_count,nargs,&ccount,lcount,&ival);

			if (rval <= 0) 
			{
				if (rval== NOT_ENOUGH_ARGS) 
				{
					error_on_rval(xxprintf,flush,target);
					return RET_BUG;
				}
				return rval;
			}

			asterisk[asterisk_count++] = ival;
			currentchar++;

		}
		else while ( isdigit(((int)*currentchar)))  currentchar++;

		if (*currentchar == '.')		/* precision */
		{
			currentchar++;
			if (*currentchar == '*')
			{
				rval=GetScalarInt(fname,&prev,&arg_count,nargs,&ccount,lcount,&ival);
				if (rval <= 0) {
					if (rval== NOT_ENOUGH_ARGS)
					{
						error_on_rval(xxprintf,flush,target);
						return RET_BUG;
					}
					return rval;
				}
				asterisk[asterisk_count++] = ival;
				currentchar++;
			}
			else while ( isdigit(((int)*currentchar)) ) currentchar++;
		}

		low_flag = high_flag = 0;

		if (*currentchar == 'l')
		{
			currentchar++;
			low_flag = 1;
		}
		else if (*currentchar == 'h')
		{
			currentchar++;
			high_flag = 1;
		}

		/* set conversion_type */
		tmpcurrentchar=currentchar;
		switch (*(currentchar++))
		{
		case 's': case 'c':
			{
				if (low_flag + high_flag)
				{
					if (*tmpcurrentchar == 's')
					{
						Scierror(998,"Warning:\tprintf: bad conversion l or h flag mixed with s directive\r\n");
					}
					else /* 'c' */
					{
						Scierror(998,"Warning:\tprintf: bad conversion l or h flag mixed with c directive\r\n");
					}
				}

				rval=GetString(fname,&prev,&arg_count,nargs,&ccount,lcount,&sval);

				if (rval <= 0) 
				{
					if (rval== NOT_ENOUGH_ARGS) 
					{
						error_on_rval(xxprintf,flush,target);
						return RET_BUG;
					}
					return rval;
				}

				if (*tmpcurrentchar == 's')
				{
					conversion_type = PF_S;
				}
				else /* 'c' */
				{
					conversion_type = PF_C;
				}
				break;
			}

		case 'd': case 'x': case 'X':
			rval=GetScalarDouble(fname,&prev,&arg_count,nargs,&ccount,lcount,&dval);
			if (rval <= 0) 
			{
				if (rval== NOT_ENOUGH_ARGS) 
				{
					error_on_rval(xxprintf,flush,target);
					return RET_BUG;
				}
				return rval;
			}
			conversion_type = PF_D;
			break;

		case 'i': case 'u':
			rval=GetScalarDouble(fname,&prev,&arg_count,nargs,&ccount,lcount,&dval);
			if (rval <= 0) 
			{
				if (rval== NOT_ENOUGH_ARGS)
				{
					error_on_rval(xxprintf,flush,target);
					return RET_BUG;
				}
				return rval;
			}
			conversion_type = low_flag ? PF_LD : PF_D;
			break;

		case 'e': case 'g': case 'f': case 'E': case 'G':
			if (high_flag + low_flag)
			{
				Scierror(998,"Error:\tprintf: bad conversion\r\n");
				return RET_BUG;
			}
			rval=GetScalarDouble(fname,&prev,&arg_count,nargs,&ccount,lcount,&dval);
			if (rval <= 0) 
			{
				if (rval== NOT_ENOUGH_ARGS)
				{
					error_on_rval(xxprintf,flush,target);
					return RET_BUG;
				}
				return rval;
			}
			conversion_type = PF_F;
			break;

		case 'o':
			Scierror(998,"Error:\tprintf: \"o\" format not allowed\r\n");
			return RET_BUG;
			break;

		default:
			Scierror(998,"Error:\tprintf: bad conversion\r\n");
			return RET_BUG;
		}

		tmpcurrentchar=NULL;
		{
			char backupcurrentchar;
			backupcurrentchar = *currentchar;
			*currentchar = 0;

			call_printf(xxprintf,target,p,sval,asterisk,asterisk_count,conversion_type,dval );

			if (fp == (FILE *) 0) while (*target) target++;
			*currentchar = backupcurrentchar;
		}
    }
	return (retval);
}

/*-----------------------------------------------------------------------------------*/
static int voidflush(FILE *fp)
{
	return 0;
}
/*-----------------------------------------------------------------------------------*/
static int GetScalarInt(char *fname, int *prev, int *arg, int narg, int *ic, int ir, int *ival)
{
	int mx,nx,lx;

	if (*prev != 1) 
	{
		*arg=*arg+1;*ic=1;
		*prev = 1;
	}

	if (! C2F(getrhsvar)(arg,"i",&mx,&nx,&lx,1L))
		return RET_BUG;
	else 
	{
		if ( (*ic>nx) || (*prev != 1)) 
		{
			*arg=*arg+1;
			if (*arg > narg ) return NOT_ENOUGH_ARGS;
			*ic=1;
			if (! C2F(getrhsvar)(arg,"i",&mx,&nx,&lx,1L))
				return RET_BUG;
		}
	}
	if (ir>mx) return RET_END;
	*ival =  *(istk(lx+ir-1+mx*(*ic-1)));
	*ic=*ic+1;
	return OK;
}
/*-----------------------------------------------------------------------------------*/
static int  GetString(char *fname, int *prev, int *arg, int narg, int *ic, int ir, char **sval)
{
	int mx,nx,il,ild,lw,k,one=1;
	char *p;

	if (*prev != 2) 
	{
		*arg = *arg+1;*ic=1;
		*prev = 2;
	}
	lw = *arg + Top - Rhs;

	if (! C2F(getwsmat)(fname,&Top,&lw,&mx,&nx,&il,&ild, strlen(fname))) return RET_BUG;
	else 
	{
		if ( *ic>nx ) 
		{
			*arg=*arg+1;
			if (*arg>narg ) return NOT_ENOUGH_ARGS;
			*ic=1;
			lw = *arg + Top - Rhs;
			if (! C2F(getwsmat)(fname,&Top,&lw,&mx,&nx,&il,&ild, strlen(fname))) return RET_BUG;
		}
	}
	if (ir>mx) return RET_END;
	k=ir-1+mx*(*ic-1);
	if (SciStrtoStr(istk(il-1+*istk(ild+k)),&one,istk(ild+k),&p) < 0) return MEM_LACK;
	*ic=*ic+1;
	*sval = p;
	return OK;
}
/*-----------------------------------------------------------------------------------*/
static int GetScalarDouble(char *fname, int *prev, int *arg, int narg, int *ic, int ir, double *dval)
{
	int mx,nx,lx;

	if (*prev != 1) 
	{
		*arg = *arg+1;
		*ic=1;
		*prev = 1;
	}
	if (! C2F(getrhsvar)(arg,"d",&mx,&nx,&lx,1L)) return RET_BUG;
	else 
	{
		if ( *ic>nx) 
		{
			*arg=*arg+1;
			if (*arg > narg ) return NOT_ENOUGH_ARGS;
			*ic=1;
			if (! C2F(getrhsvar)(arg,"d",&mx,&nx,&lx,1L))return RET_BUG;
		}
	}
	if (ir>mx) return RET_END;
	*dval =  *(stk(lx+ir-1+mx*(*ic-1)));
	*ic=*ic+1;
	return OK;
}
/*-----------------------------------------------------------------------------------*/
