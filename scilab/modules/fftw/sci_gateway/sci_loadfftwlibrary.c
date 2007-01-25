/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include "sci_loadfftwlibrary.h"
#include "callfftw.h"
#include "Scierror.h"
#include "fftwlibname.h"
/*-----------------------------------------------------------------------------------*/ 
int sci_loadfftwlibrary __PARAMS((char *fname,unsigned long fname_len))
{
	static int l1,n1,m1;
	char *FFTWLibname=NULL;

	CheckRhs(1,1);

	if (GetType(1) == sci_strings)
	{
		GetRhsVar(1,"c",&m1,&n1,&l1);
		FFTWLibname=cstk(l1);
		setfftwlibname(FFTWLibname);

		n1=1;
		if ( LoadFFTWLibrary(FFTWLibname) )
		{
			CreateVar(Rhs+1, "b", &n1,&n1,&l1);
			*istk(l1)=(int)(TRUE);
		}
		else
		{
			CreateVar(Rhs+1, "b", &n1,&n1,&l1);
			*istk(l1)=(int)(FALSE);
		}

		LhsVar(1)=Rhs+1;
		C2F(putlhsvar)();
	}
	else
	{
		 Scierror(999,"Invalid parameter type.\n");
		 return 0;
	}
	return(0);
}
/*-----------------------------------------------------------------------------------*/ 
