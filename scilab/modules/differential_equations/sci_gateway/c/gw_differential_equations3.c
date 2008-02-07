/*--------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include <string.h>
#ifdef _MSC_VER
#include <stdio.h>
#endif
#include "gw_differential_equations3.h"
#include "callFunctionFromGateway.h"
/*--------------------------------------------------------------------------*/
static gw_generic_table Tab[]=
{
	{C2F(sci_odc),"odedc"}
};
/*--------------------------------------------------------------------------*/
int C2F(gw_differential_equations3)(void)
{  
	callFunctionFromGateway(Tab);
	return 0;
}
/*--------------------------------------------------------------------------*/
