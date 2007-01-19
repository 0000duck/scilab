/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __GW_GUI__
#define __GW_GUI__

#ifdef _MSC_VER
  #include <windows.h>
  #include <stdio.h>
#endif

#include <string.h>

#include "machine.h"
#include "stack-c.h"
#include "sciprint.h"

typedef int (*Gui_Interf) __PARAMS((char *fname,unsigned long l));

int C2F(gw_gui)(void);

typedef struct table_struct 
{
  Gui_Interf f;    /** function **/
  char *name;      /** its name **/
} GuiTable;

/*-----------------------------------------------------------------------------------*/
int C2F(sci_x_dialog) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_x_message) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_x_choose) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_x_mdialog) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_xchoicesi) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_addmenu_old) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_delmenu_old) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_setmenu_old) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_unsetmenu_old) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_xgetfile) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_x_message_modeless) _PARAMS((char *fname,unsigned long fname_len));
int sci_clc( char *fname, unsigned long fname_len ) ;
int sci_raise_window( char * fname, unsigned long fname_len ) ;
int sci_tohome( char * fname, unsigned long fname_len ) ;
BOOL GetWITH_GUI(void);

#endif /*  __GW_GUI__ */
/*-----------------------------------------------------------------------------------*/

