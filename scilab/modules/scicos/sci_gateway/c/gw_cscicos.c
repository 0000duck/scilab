/*  Scicos
*
*  Copyright (C) INRIA - Allan CORNET
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* See the file ./license.txt
*/
/*--------------------------------------------------------------------------*/
/* INRIA 2008 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include "gw_cscicos.h"
#include "stack-c.h"
#include "callFunctionFromGateway.h"
/*--------------------------------------------------------------------------*/ 
static gw_generic_table Tab[]={
	{C2F(sci_scicos_time),"scicos_time"},
	{C2F(sci_duplicate),"duplicate"},
	{C2F(sci_diffobjs),"diffobjs"},
	{C2F(sci_pointer_xproperty),"pointer_xproperty"},
	{C2F(sci_phase_simulation),"phase_simulation"},
	{C2F(sci_set_xproperty),"set_xproperty"},
	{C2F(sci_set_blockerror),"set_blockerror"},
	{C2F(sci_ctree2),"ctree2"},
	{C2F(sci_ctree3),"ctree3"},
	{C2F(sci_ctree4),"ctree4"},
	{C2F(sci_scicosim),"scicosim"},
	{C2F(sci_getscicosvars),"getscicosvars"},
	{C2F(sci_curblockc),"curblockc"},
	{C2F(sci_buildouttb),"buildouttb"},
	{C2F(sci_permutobj),"permutobj"},
	{C2F(sci_xstringb2),"xstringb2"},
	{C2F(sci_end_scicosim),"end_scicosim"}
};
/*--------------------------------------------------------------------------*/ 
int C2F(gw_cscicos)()
{  
	Rhs = Max(0, Rhs);
	callFunctionFromGateway(Tab);
	C2F(putlhsvar)();
	
	return 0;
}
/*--------------------------------------------------------------------------*/ 

