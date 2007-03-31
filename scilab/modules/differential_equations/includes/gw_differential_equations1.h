/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/* Sylvestre LEDRU */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __GW_DIFFERENTIAL_EQUATIONS1__
#define __GW_DIFFERENTIAL_EQUATIONS1__
/*-----------------------------------------------------------------------------------*/
#include "machine.h"
/*-----------------------------------------------------------------------------------*/
int C2F(gw_differential_equations1)(void);
/*-----------------------------------------------------------------------------------*/
int C2F(sci_ode) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_intg) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_feval) _PARAMS((char *fname,unsigned long fname_len));
int C2F(sci_bvode) _PARAMS((char *fname,unsigned long fname_len));
/*-----------------------------------------------------------------------------------*/
#endif  /* __GW_DIFFERENTIAL_EQUATIONS1__ */
/*-----------------------------------------------------------------------------------*/
