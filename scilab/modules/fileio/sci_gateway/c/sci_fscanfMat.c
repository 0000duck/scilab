/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/*-----------------------------------------------------------------------------------*/
#include "MALLOC.h"
#include "fileio.h"
#include "gw_fileio.h"
#include "Scierror.h"
#include "localization.h"
/*-----------------------------------------------------------------------------------*/
#define INFOSIZE 1024
/*-----------------------------------------------------------------------------------*/
static int  Info_size = 0;
static char *Info= NULL;
/*-----------------------------------------------------------------------------------*/
static int ReadLine(FILE *fd,int *mem);
/*-----------------------------------------------------------------------------------*/
int int_objfscanfMat(char *fname,unsigned long fname_len)
{
	char **Str=NULL;
	int mem=0;
	double x;
	static int l1, m1, n1,l2,m2,n2;
	int i,j,rows,cols,lres,n;
	int vl=-1;
	FILE  *f;
	char *Format;
	if ( Info == NULL )
	{
		if (( Info =MALLOC(INFOSIZE*sizeof(char)))==NULL)
		{
			Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"),fname);
			return 0;
		}
		Info_size = INFOSIZE;
	}

	Nbvars = 0;
	CheckRhs(1,1); /** just 1 **/
	CheckLhs(1,2);
	GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);/* file name */

	if ( Rhs == 2)
	{
		GetRhsVar(2,STRING_DATATYPE,&m2,&n2,&l2);/* format */
		StringConvert(cstk(l2));  /* conversion */
		Format = cstk(l2);
	}
	else
	{
		Format = 0;
	}

	if (( f = fopen(cstk(l1),"r")) == (FILE *)0)
	{
		Scierror(999,_("Error: in function %s, cannot open file %s\n"),fname,cstk(l1));
		return 0;
	}
	/*** first pass to get colums and rows ***/
	strcpy(Info,"--------");
	n =0;
	while ( sscanf(Info,"%lf",&x) <= 0 && n != EOF )
	{
		n=ReadLine(f,&mem);
		if ( mem == 1)
		{
			FREE(Info);Info=NULL;
			fclose(f);
			Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"),fname);
			return 0;
		}
		vl++;
	}

	if ( n == EOF )
	{
		FREE(Info);Info=NULL;
		fclose(f);
		Scierror(999,_("Error: in function %s, cannot read data in file %s\n"),fname,cstk(l1));
		return 0;
	}
	cols = NumTokens(Info);
	rows = 1;

	while (1)
	{
		n=ReadLine(f,&mem);
		if ( mem == 1)
		{
			FREE(Info);Info=NULL;
			fclose(f);
			Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"),fname);
			return 0;
		}

		if ( n == EOF ||  n == 0 ) break;
		if ( sscanf(Info,"%lf",&x) <= 0) break;
		rows++;
	}

	if ( cols == 0 || rows == 0) rows=cols=0;

	CreateVar(Rhs+1,MATRIX_OF_DOUBLE_DATATYPE, &rows, &cols, &lres);

	/** second pass to read data **/
	rewind(f);
	/** skip non numeric lines **/

	if ( Lhs >= 2 && vl != 0 )
	{
		if ((Str = MALLOC((vl+1)*sizeof(char *)))==NULL)
		{
			FREE(Info);Info=NULL;
			fclose(f);
			Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"), fname);
			return 0;
		}

		Str[vl]=NULL;
	}

	for ( i = 0 ; i < vl ; i++)
	{
		ReadLine(f,&mem);
		if ( mem == 1)
		{
			FREE(Info);Info=NULL;
			fclose(f);
			for (j=0;j<i;j++) FREE(Str[j]);
			FREE(Str);
			Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"),fname);
			return 0;
		}

		if ( Lhs >= 2)
		{
			if ((Str[i]=MALLOC((strlen(Info)+1)*sizeof(char)))==NULL)
			{
				FREE(Info);Info=NULL;
				fclose(f);
				for (j=0;j<i;j++) FREE(Str[j]);
				FREE(Str);
				Scierror(999,_("Error: in function %s, cannot allocate enough memory\n"), fname);
				return 0;
			}
			strcpy(Str[i],Info);
		}
	}

	if ( Lhs >= 2)
	{
		int un=1,zero=0,l;

		if ( vl > 0 )
		{
			int i2=0;
			CreateVarFromPtr(Rhs+2,MATRIX_OF_STRING_DATATYPE,&vl,&un,Str);
			if (Str)
			{
				for (i2=0;i2<vl;i2++)
				{
					if (Str[i2])
					{
						FREE(Str[i2]);
						Str[i2]=NULL;
					}
				}
				FREE(Str);
				Str=NULL;
			}
		}
		else
		{
			CreateVar(Rhs+2,STRING_DATATYPE,&zero,&zero,&l);
		}

		LhsVar(2)=Rhs+2;
	}

	for (i=0; i < rows ;i++)for (j=0;j < cols;j++)
	{
		double xloc;
		fscanf(f,"%lf",&xloc);
		*stk(lres+i+rows*j)=xloc;
	}

	fclose(f);
	LhsVar(1)=Rhs+1;
	PutLhsVar();
	/* just in case Info is too Big */
	if ( Info_size > INFOSIZE )
	{
		Info_size = INFOSIZE;
		Info = REALLOC(Info,Info_size*sizeof(char));
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
static int ReadLine(FILE *fd,int *mem)
{
	int n=0;

	while (1)
	{
		char c = (char) fgetc(fd);

		if ( n == Info_size )
		{
			char * Info1=NULL;
			int New_Size = Info_size + INFOSIZE;

			Info1=MALLOC(New_Size*sizeof(char));
			if (Info1==NULL)
			{
				*mem=1;
				return EOF;
			}
			else
			{
				memset(Info1,0,New_Size);
				memcpy(Info1,Info,Info_size);
				Info_size=New_Size;
				FREE(Info);
				Info=Info1;
			}
		}

		Info[n]= c ;
		if ( c == '\n') { Info[n] = '\0' ; return 1;}
		else if ( c == (char)EOF ) return EOF;
		n++;
	}
}
/*-----------------------------------------------------------------------------------*/
