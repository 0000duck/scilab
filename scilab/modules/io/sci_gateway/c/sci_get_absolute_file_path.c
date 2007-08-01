/*
 * Provides get_absolute_file_path to scilab
 * @author Allan CORNET - INRIA 2007
 */
/*-----------------------------------------------------------------------------------*/ 
#include <string.h>
#include <stdio.h> /* FILE */
#ifdef _MSC_VER 
	#include <windows.h>
#else 
	#include <unistd.h>
	#define GETCWD(x,y) getcwd(x,y)
#endif 

#include "gw_io.h"
#include "FileExist.h"
#include "../../../core/src/c/scicurdir.h"
#include "directories.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "getfiledesc.h"
#include "getfileinfo.h"
/*-----------------------------------------------------------------------------------*/
int C2F(sci_get_absolute_file_path) _PARAMS((char *fname,unsigned long fname_len))
{
	int l1,n1,m1;

	CheckRhs(1,1);
	CheckLhs(1,1);
	
	if (! (GetType(1) == sci_strings))
	{
		Scierror(999,"parameter incorrect must be a string (a filename).\r\n");
		return 0;
	}
	else
	{
		char *filename=NULL;

		GetRhsVar(1,"c",&m1,&n1,&l1);
		if ( n1==1 )
		{
			int i=0;
			int fdmax=0;
			char fileNameFormList[PATH_MAX];
			char *absolute_file_path=NULL;

			filename=cstk(l1);

			C2F(getfiledesc)(&fdmax);
			for(i=0;i<fdmax;i++)
			{
				FILE fa;
				integer swap2=0;
				integer type=0;
				integer mode=0;
				
				integer lf=0;
				integer ierr=0;
				
				int posBeginFileName=0;

				C2F(getfileinfo)(&i, &fa, &swap2,&type,&mode,fileNameFormList,&lf,&ierr);
				posBeginFileName=(int)(strlen(fileNameFormList)-strlen(filename));

				if (posBeginFileName>0)
				{
					char *cmptmp=NULL;
					cmptmp=&fileNameFormList[posBeginFileName];
					if (strcmp(cmptmp,filename)==0)
					{
						absolute_file_path=(char *)MALLOC(sizeof(char)*(strlen(fileNameFormList)+1));
						if (absolute_file_path)
						{
							strncpy(absolute_file_path,fileNameFormList,posBeginFileName);
							absolute_file_path[posBeginFileName]='\0';
							break;
						}
					}
				}
			}

			if (!absolute_file_path) /* file not found in list of files opened by scilab */
			{
				int ierr=0;
				int lpath=0;
				char *path=NULL;
				path=(char*)MALLOC(sizeof(char)*(PATH_MAX+1));
				if (path)
				{
					C2F(scigetcwd)(&path,&lpath,&ierr);
					if (ierr) /* Problem to get current directory */
					{
						m1=0; n1=0; l1=0; /* returns a empty string */
						CreateVar(Rhs+1,"c",  &m1, &n1, &l1);
						LhsVar(1)=Rhs+1;
						C2F(putlhsvar)();
						FREE(path);path=NULL;
						return 0;
					}
					else
					{
						absolute_file_path=(char *)MALLOC(sizeof(char)*(lpath+(int)strlen(DIR_SEPARATOR)+1));
						strncpy(absolute_file_path,path,lpath);
						absolute_file_path[lpath]='\0';
						/* Add '\' or '/' */
						strcat(absolute_file_path,DIR_SEPARATOR);
					}
					FREE(path);path=NULL;
				}
			}

			n1=1;
			CreateVarFromPtr( Rhs+1, "c",(m1=(int)strlen(absolute_file_path), &m1),&n1,&absolute_file_path);
			LhsVar(1)=Rhs+1;
			C2F(putlhsvar)();

			if (absolute_file_path){FREE(absolute_file_path);absolute_file_path=NULL;}
			return 0;

		}
		else
		{
			Scierror(999,"First parameter incorrect, must be a string (a file).\r\n");
			return 0;
		}
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/

