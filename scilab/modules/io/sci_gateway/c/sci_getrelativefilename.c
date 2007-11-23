/**
 * @Author : Pierre MARECHAL - INRIA 2006
 */
 /*--------------------------------------------------------------------------*/
#include <string.h>
#include <ctype.h>
#include "gw_io.h"
#include "MALLOC.h"
#include "sci_getrelativefilename.h"
#include "machine.h"
#include "Scierror.h"
#include "localization.h"
 /*--------------------------------------------------------------------------*/
/* ================================================================================== */
// sci_getrelativefilename
//
// scilab interface to getrelativefilename
/* ================================================================================== */
int C2F(sci_getrelativefilename) _PARAMS((char *fname, unsigned long l))
{
	static int l1,n1,m1,l2,n2,m2;

	CheckRhs(2,2);
	CheckLhs(1,1);

	if (! ((GetType(1) == sci_strings) && (GetType(2) == sci_strings ) ) ){

		Scierror(999,_("parameter incorrect must be a string (a filename)."));
		return 0;

	}else{

		char *param1=NULL;
		char *param2=NULL;
		char *result=(char*)MALLOC(PATH_MAX*sizeof(char));

		GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
		GetRhsVar(2,STRING_DATATYPE,&m2,&n2,&l2);

		if ( n1==1 ){
			param1=cstk(l1);
		}else{
			Scierror(999,_("First input argument incorrect, must be a string (a directory)."));
			return 0;
		}

		if ( n2==1 ){
			param2=cstk(l2);
		}else{
			Scierror(999,_("Second input argument incorrect, must be a string (a filename)."));
			return 0;
		}

		// make sure the names are not too long

		if( strlen(param1) > PATH_MAX )
		{
			Scierror(999,_("The first input argument is too long : must be less than %d characters"),PATH_MAX);
		}

		if( strlen(param2) > PATH_MAX )
		{
			Scierror(999,_("The second input argument is too long : must be less than %d characters"),PATH_MAX);
		}

		result = getrelativefilename(param1,param2);

		CreateVarFromPtr(Rhs+3,STRING_DATATYPE,(m1=(int)strlen(result), &m1),&n1,&result);
		LhsVar(1)=Rhs+3;
		if (result) {FREE(result);result=NULL;}
		C2F(putlhsvar)();
	}

	return 0;
}

/* ================================================================================== */
// getrelativefilename
//
// Given the absolute current directory and an absolute file name, returns a relative file name.
// For example, if the current directory is C:\foo\bar and the filename C:\foo\whee\text.txt is given,
// GetRelativeFilename will return ..\whee\text.txt.
/* ================================================================================== */

char* getrelativefilename(char *currentDirectory, char *absoluteFilename)
{
	// declarations - put here so this should work in a C compiler
	int afMarker = 0, rfMarker = 0;
	int cdLen = 0, afLen = 0;
	int i = 0;
	int levels = 0;
	char *relativeFilename= (char*)MALLOC(PATH_MAX*sizeof(char));

	cdLen = (int)strlen(currentDirectory);
	afLen = (int)strlen(absoluteFilename);

	// make sure the names are not too short
	if( cdLen < ABSOLUTE_NAME_START+1 || afLen < ABSOLUTE_NAME_START+1)
	{
		// fix bug 2181
		strcpy(relativeFilename, absoluteFilename);
		return relativeFilename;
	}

	// Handle DOS names that are on different drives:
	if(tolower(currentDirectory[0]) != tolower(absoluteFilename[0]))
	{
		// not on the same drive, so only absolute filename will do
		strcpy(relativeFilename, absoluteFilename);
		return relativeFilename;
	}

	// they are on the same drive, find out how much of the current directory
	// is in the absolute filename
	i = ABSOLUTE_NAME_START;

	#if defined(_MSC_VER)
		while(i < afLen && i < cdLen && tolower(currentDirectory[i])==tolower(absoluteFilename[i]) )
		{
			i++;
		}
	#else
		while(i < afLen && i < cdLen && currentDirectory[i] == absoluteFilename[i])
		{
			i++;
		}
	#endif

	if(i == cdLen && (absoluteFilename[i] == DIR_SEPARATOR[0] || absoluteFilename[i-1] == DIR_SEPARATOR[0]))
	{
		// the whole current directory name is in the file name,
		// so we just trim off the current directory name to get the
		// current file name.
		if(absoluteFilename[i] == DIR_SEPARATOR[0])
		{
			// a directory name might have a trailing slash but a relative
			// file name should not have a leading one...
			i++;
		}

		strcpy(relativeFilename, &absoluteFilename[i]);
		return relativeFilename;
	}

	// The file is not in a child directory of the current directory, so we
	// need to step back the appropriate number of parent directories by
	// using "..\"s.  First find out how many levels deeper we are than the
	// common directory
	afMarker = i;
	levels = 1;

	// count the number of directory levels we have to go up to get to the
	// common directory
	while(i < cdLen)
	{
		i++;
		if(currentDirectory[i] == DIR_SEPARATOR[0])
		{
			// make sure it's not a trailing slash
			i++;
			if(currentDirectory[i] != '\0')
			{
				levels++;
			}
		}
	}

	// move the absolute filename marker back to the start of the directory name
	// that it has stopped in.
	while(afMarker > 0 && absoluteFilename[afMarker-1] != DIR_SEPARATOR[0])
	{
		afMarker--;
	}

	// check that the result will not be too long
	if(levels * 3 + afLen - afMarker > PATH_MAX)
	{
		return NULL;
	}

	// add the appropriate number of "..\"s.
	rfMarker = 0;
	for(i = 0; i < levels; i++)
	{
		relativeFilename[rfMarker++] = '.';
		relativeFilename[rfMarker++] = '.';
		relativeFilename[rfMarker++] = DIR_SEPARATOR[0];
	}

	// copy the rest of the filename into the result string
	strcpy(&relativeFilename[rfMarker], &absoluteFilename[afMarker]);

	return relativeFilename;
}
