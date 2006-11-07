/*-----------------------------------------------------------------------------------*/
/* Author : Pierre MARECHAL                                                          */
/* Scilab team                                                                       */
/* Copyright INRIA                                                                   */
/*                                                                                   */
/* Date : 24 august 2006                                                             */
/*-----------------------------------------------------------------------------------*/

#include "sci_getrelativefilename.h"
#include "MALLOC.h"
#include <string.h>

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
		
		Scierror(999,"parameter incorrect must be a string (a filename).");
		return 0;
	
	}else{

		char *param1=NULL;
		char *param2=NULL;
		char *result=(char*)MALLOC(MAX_PATH_LONG*sizeof(char));

		GetRhsVar(1,"c",&m1,&n1,&l1);
		GetRhsVar(2,"c",&m2,&n2,&l2);
		
		if ( n1==1 ){
			param1=cstk(l1);
		}else{
			Scierror(999,"First parameter incorrect, must be a string (a directory).");
			return 0;
		}
		
		if ( n2==1 ){
			param2=cstk(l2);
		}else{
			Scierror(999,"Second parameter incorrect, must be a string (a filename).");
			return 0;
		}
		
		// make sure the names are not too long
		
		if( strlen(param1) > MAX_FILENAME_LEN )
		{
			Scierror(999,"The first parameter is too long : must be less than %d caracters",MAX_FILENAME_LEN);
		}
		
		if( strlen(param2) > MAX_FILENAME_LEN )
		{
			Scierror(999,"The second parameter is too long : must be less than %d caracters",MAX_FILENAME_LEN);
		}
		
		result = getrelativefilename(param1,param2);
		
		CreateVarFromPtr(3,"c",(m1=(int)strlen(result), &m1),&n1,&result);
		LhsVar(1)=3;
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
	char *relativeFilename= (char*)MALLOC(MAX_FILENAME_LEN*sizeof(char));
	
	cdLen = strlen(currentDirectory);
	afLen = strlen(absoluteFilename);
	
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
	
	if(i == cdLen && (absoluteFilename[i] == SLASH || absoluteFilename[i-1] == SLASH))
	{
		// the whole current directory name is in the file name,
		// so we just trim off the current directory name to get the
		// current file name.
		if(absoluteFilename[i] == SLASH)
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
		if(currentDirectory[i] == SLASH)
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
	while(afMarker > 0 && absoluteFilename[afMarker-1] != SLASH)
	{
		afMarker--;
	}
	
	// check that the result will not be too long
	if(levels * 3 + afLen - afMarker > MAX_FILENAME_LEN)
	{
		return NULL;
	}
	
	// add the appropriate number of "..\"s.
	rfMarker = 0;
	for(i = 0; i < levels; i++)
	{
		relativeFilename[rfMarker++] = '.';
		relativeFilename[rfMarker++] = '.';
		relativeFilename[rfMarker++] = SLASH;
	}
	
	// copy the rest of the filename into the result string
	strcpy(&relativeFilename[rfMarker], &absoluteFilename[afMarker]);
	
	return relativeFilename;
}
