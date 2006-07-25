/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __SCI_TIMER__
#define __SCI_TIMER__

#ifdef _MSC_VER
  #include <windows.h>
#endif

#include <stdio.h>
#include "machine.h"
#include "stack-c.h"
#include "version.h"



#ifndef NULL
  #define NULL 0
#endif

#define TRUE  1
#define FALSE 0

int C2F(sci_timer) _PARAMS((char *fname,unsigned long fname_len));

#endif /* __SCI_TIMER__ */
/*-----------------------------------------------------------------------------------*/ 
