/*-----------------------------------------------------------------------------------*/
/* Author : Pierre MARECHAL                                                          */
/* Scilab team                                                                       */
/* Copyright INRIA                                                                   */
/*                                                                                   */
/* Date : 24 august 2006                                                             */
/*-----------------------------------------------------------------------------------*/

#ifndef __INTGETRELATIVEFILENAME__
#define __INTGETRELATIVEFILENAME__

#ifdef _MSC_VER
	#include <windows.h>
#endif

#include <stdio.h>
#include "machine.h"
#include "stack-c.h"

#ifndef NULL
	#define NULL 0
#endif

#define MAX_PATH_LONG 32767
#define MAX_FILENAME_LEN 512

#ifdef _MSC_VER
	#define ABSOLUTE_NAME_START 3
	#define SLASH '\\'
#else
	#define ABSOLUTE_NAME_START 1
	#define SLASH '/'
#endif

// ABSOLUTE_NAME_START
// 
// The number of characters at the start of an absolute filename.  e.g. in DOS,
// absolute filenames start with "X:\" so this value should be 3, in UNIX they start
// with "\" so this value should be 1.

// SLASH
// set this to '\\' for DOS or '/' for UNIX

int C2F(sci_getrelativefilename) _PARAMS((char *fname));
char* getrelativefilename(char *currentDirectory, char *absoluteFilename);

#endif /* __INTGETRELATIVEFILENAME__ */
/*-----------------------------------------------------------------------------------*/ 
