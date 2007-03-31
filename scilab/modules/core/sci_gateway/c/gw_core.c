/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#ifdef _MSC_VER
#include <Windows.h>
#include "ExceptionMessage.h"
#endif
#include "gw_core.h"
#include "stack-c.h"
/*-----------------------------------------------------------------------------------*/
typedef int (*Core_Interf) __PARAMS((char *fname,unsigned long l));
typedef struct table_struct 
{
	Core_Interf f;    /** function **/
	char *name;      /** its name **/
} CoreTable;
/*-----------------------------------------------------------------------------------*/
static CoreTable Tab[]=
{
{C2F(sci_debug),"debug"},
{C2F(sci_who),"who"},
{C2F(sci_lines),"lines"},
{C2F(sci_argn),"argn"},
{C2F(sci_fort),"fort"},
{C2F(sci_comp),"comp"},
{C2F(sci_call),"call"},
{C2F(sci_mode),"mode"},
{C2F(sci_type),"type"},
{C2F(sci_error),"error"},
{C2F(sci_resume),"resume"},
{C2F(sci_return),"return"},
{C2F(sci_format),"format"},
{C2F(sci_isdef),"isdef"},
{C2F(sci_exists),"exists"},
{C2F(sci_errcatch),"errcatch"},
{C2F(sci_errclear),"errclear"},
{C2F(sci_iserror),"iserror"},
{C2F(sci_predef),"predef"},
{C2F(sci_newfun),"newfun"},
{C2F(sci_clearfun),"clearfun"},
{C2F(sci_funptr),"funptr"},
{C2F(sci_macr2lst),"macr2lst"},
{C2F(sci_setbpt),"setbpt"},
{C2F(sci_delbpt),"delbpt"},
{C2F(sci_dispbpt),"dispbpt"},
{C2F(sci_funcprot),"funcprot"},
{C2F(sci_whereis),"whereis"},
{C2F(sci_where),"where"},
{C2F(sci_havewindow),"havewindow"},
{C2F(sci_stacksize),"stacksize"},
{C2F(sci_mtlb_mode),"mtlb_mode"},
{C2F(sci_link),"link"},
{C2F(sci_ulink),"ulink"},
{C2F(sci_c_link),"c_link"},
{C2F(sci_addinter),"addinter"},
{C2F(sci_clear),"clear"},
{C2F(sci_what),"what"},
{C2F(sci_sciargs),"sciargs"},
{C2F(sci_chdir),"chdir"},
{C2F(sci_ieee),"ieee"},
{C2F(sci_typename),"typename"},
{C2F(sci_global),"global"},
{C2F(sci_pwd),"pwd"},
{C2F(sci_clearglobal),"clearglobal"},
{C2F(sci_isglobal),"isglobal"},
{C2F(sci_gstacksize),"gstacksize"},
{C2F(sci_intppty),"intppty"},
{C2F(sci_lasterror),"lasterror"},
{C2F(sci_getversion),"getversion"},
{C2F(sci_loadhistory),"loadhistory"},
{C2F(sci_savehistory),"savehistory"},
{C2F(sci_gethistory),"gethistory"},
{C2F(sci_resethistory),"resethistory"},
{C2F(sci_macr2tree),"macr2tree"},
{C2F(sci_getos),"getos"},
{C2F(sci_banner),"banner"},
{C2F(sci_fromjava),"fromjava"},
{C2F(sci_getmemory),"getmemory"},
{C2F(sci_fromc),"fromc"},
{C2F(sci_getmd5),"getmd5"},
{C2F(sci_warning),"warning"},
{C2F(sci_getcwd),"getcwd"},
{C2F(sci_getmodules),"getmodules"},
{C2F(sci_with_module),"with_module"},
{C2F(sci_getdynlibext),"getdynlibext"}
};
/*-----------------------------------------------------------------------------------*/
int C2F(gw_core)()
{  
	Rhs = Max(0, Rhs);

	/**
	* recursion from intdeff
	* TODO : need more comment
	*/
	if ( C2F(recu).rstk[C2F(recu).pt-1] == 901) 
	{
		Fin=6;
	}

#ifdef _MSC_VER
	#ifndef _DEBUG
		_try
		{
			(*(Tab[Fin-1].f)) (Tab[Fin-1].name,strlen(Tab[Fin-1].name));
		}
		_except (EXCEPTION_EXECUTE_HANDLER)
		{	
			ExceptionMessage(GetExceptionCode(),Tab[Fin-1].name);
		}
	#else
		(*(Tab[Fin-1].f)) (Tab[Fin-1].name,strlen(Tab[Fin-1].name));
	#endif
#else
		(*(Tab[Fin-1].f)) (Tab[Fin-1].name,strlen(Tab[Fin-1].name));
#endif
	return 0;
}
/*-----------------------------------------------------------------------------------*/
