/* Copyright INRIA */
#ifndef __CALLINTERF__
#define __CALLINTERF__
#include "machine.h"

/********************************************************
 * Table of hard coded Scilab interface
 *  to add a new interface add a declaration and a new entry
 *  at the end of the Interfaces array
 *  The maximum number of interfaces is bound to DynInterfStart
 *  ( file /core/src/c/addinter.h )
 ********************************************************/

/* 01  C2F(gw_user)(); FREE */	#include "gw_user.h"
/* 02 */						#include "../../../linear_algebra/includes/gw_linear_algebra.h"
/* 03  C2F(gw_user)(); FREE */
/* 04  C2F(gw_user)(); FREE */
/* 05 */						#include "../../../io/includes/gw_io.h"
/* 06 */						#include "../../../elementary_functions/includes/gw_elementary_functions.h"
/* 07 */						#include "../../../graphics/includes/gw_graphics.h"
/* 08 */						#include "../../../cacsd/includes/gw_cacsd0.h"
/* 09 */						#include "../../../cacsd/includes/gw_cacsd1.h"
/* 10 */						#include "../../../cacsd/includes/gw_cacsd2.h"
/* 11 */						#include "../../../optimization/includes/gw_optim.h"
/* 12 */						#include "../../../differential_equations/includes/gw_differential_equations1.h"
/* 13 */						#include "gw_core.h"
/* 14  C2F(gw_user)(); FREE */
/* 15 */						#include "../../../metanet/includes/gw_metanet.h"
/* 16 */						#include "../../../polynomials/includes/gw_polynomials.h"
/* 17 */						#include "../../../data_structures/includes/gw_data_structures1.h"
/* 18 */						#include "../../../signal_processing/includes/gw_signal.h"
/* 19 */						#include "../../../interpolation/includes/gw_interpolation.h"
/* 20 */						#include "../../../cacsd/includes/gw_cacsd3.h"
/* 21 */						#include "../../../string/includes/gw_string.h"
/* 22 */						#include "../../../symbolic/includes/gw_symbolic.h"
/* 23 */						#include "../../../boolean/includes/gw_boolean.h"
/* 24  C2F(gw_user2)(); FREE */	#include "gw_user2.h"
/* 25 */						#include "../../../gui/includes/gw_gui.h"
/* 26 */						#include "../../../differential_equations/includes/gw_differential_equations2.h"
/* 27 */						#include "../../../sparse/includes/gw_sparse.h"
/* 28 */						#include "../../../cacsd/includes/gw_slicot.h"
/* 29 */						#include "../../../differential_equations/includes/gw_differential_equations3.h"
/* 30 */						#include "../../../differential_equations/includes/gw_differential_equations4.h"
/* 31 */						#include "../../../differential_equations/includes/gw_differential_equations5.h"
/* 32 */						#include "../../../differential_equations/includes/gw_differential_equations6.h"
/* 33  C2F(gw_user)(); FREE */
/* 34 */						#include "../../../fileio/includes/gw_fileio.h"
/* 35 */						#include "../../../arnoldi/includes/gw_arnoldi.h"
/* 36 */						#include "../../../special_functions/includes/gw_special_functions1.h"
/* 37 */						#include "../../../statistics/includes/gw_statistics.h"
/* 38 */						#include "../../../randlib/includes/gw_randlib.h"
/* 39 */						#include "../../../special_functions/includes/gw_special_functions2.h"

/* 40 */						#include "../../../tclsci/includes/gw_tclsci.h"

/* 41 */						#include "../../../data_structures/includes/gw_data_structures2.h"

/* 42 */						#include "../../../pvm/includes/gw_pvm.h"

/* 43 */						#include "../../../integer/includes/gw_integer.h"
/* 44 */						#include "../../../linear_algebra/includes/gw_linear_algebra2.h"

/* 45 */						#include "../../../scicos/includes/gw_scicos.h"

/* 46 */						#include "../../../scicos/includes/gw_cscicos.h"

/* 47 */						#include "../../../windows_tools/includes/gw_windows_tools.h"

/* 48 */						#include "../../../time/includes/gw_time.h"
/* 49 */						#include "../../../sound/includes/gw_sound.h"
/* 50 */						#include "../../../localization/includes/gw_localization.h"

/* 51 */						#include "../../../fftw/includes/gw_fftw.h"
/* 52 */						#include "../../../jvm/includes/gw_jvm.h"
/* 53 */						#include "../../../shell/includes/gw_shell.h"

/* 54 */						#include "../../../completion/includes/gw_completion.h"
/* 55 */						#include "../../../history_manager/includes/gw_history_manager.h"

/* 56 */						#include "../../../spreadsheet/includes/gw_spreadsheet.h"

/* 55 *///                        #include "../../../mpi/includes/gw_mpi.h"


/*-------------------------------------
 * long jump to stop interface computation
 * @param n
 *-------------------------------------*/

void errjump (int n);


/** table of interfaces **/

typedef struct {
	int  (*fonc)(void);
} OpTab ;

/**
 * call the apropriate interface according to the value of k
 * @param k the number of the interface
 * @return
 */
int C2F(callinterf) (int *k);

#endif /*__CALLINTERF__*/
