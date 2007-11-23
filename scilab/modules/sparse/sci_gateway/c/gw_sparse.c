/*--------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include "gw_sparse.h"
#include "callFunctionFromGateway.h"
/*--------------------------------------------------------------------------*/
static gw_generic_table Tab[]=
{
	{C2F(sci_sparsefunc),"sparse"},
	{C2F(sci_spget),"spget"},
	{C2F(sci_full),"full"},
	{C2F(sci_lufact),"lufact"},
	{C2F(sci_lusolve),"lusolve"},
	{C2F(sci_ludel),"ludel"},
	{C2F(sci_luget),"luget"},
	{C2F(sci_spclean),"spclean"},
	{C2F(sci_nnz),"nnz"},
	{C2F(sci_spmax),"spmax"},
	{C2F(sci_spmin),"spmin"},
	{C2F(sci_spmatrix),"spmatrix"},
	{C2F(sci_spchol),"spchol"},
	{C2F(sci_readmps),"readmps"},
	{C2F(sci_fadj2sp),"fadj2sp"},
	{C2F(sci_spcompa),"spcompa"},
	{C2F(sci_ordmmd),"ordmmd"},
	{C2F(sci_blkfc1i),"blkfc1i"},
	{C2F(sci_blkslvi),"blkslvi"},
	{C2F(sci_inpnvi),"inpnvi"},
	{C2F(sci_sfinit),"sfinit"},
	{C2F(sci_symfcti),"symfcti"},
	{C2F(sci_bfinit),"bfinit"},
	{C2F(sci_msparse),"msparse"},
	{C2F(sci_mspget),"mspget"},
	{C2F(sci_mfull),"mfull"}
};
/*--------------------------------------------------------------------------*/
int C2F(gw_sparse)()
{  
	callFunctionFromGateway(Tab);
	return 0;
}
/*--------------------------------------------------------------------------*/
