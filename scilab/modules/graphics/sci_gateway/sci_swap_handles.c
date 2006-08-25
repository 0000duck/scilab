/*------------------------------------------------------------------------*/
/* file: sci_swap_handles.c                                               */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for swap_handles routine                              */
/*------------------------------------------------------------------------*/

#include "sci_swap_handles.h"
#include "stack-c.h"
#include "HandleManagement.h"

/*-----------------------------------------------------------------------------------*/
int sci_swap_handles( char * fname, unsigned long fname_len )
{
  int firstHdlCol  ;
  int firstHdlRow  ;
  int secondHdlCol ;
  int secondHdlRow ;
  int firstHdlStkIndex  ;
  int secondHdlStkIndex ;

  CheckRhs( 2, 2 ) ;
  CheckLhs( 0, 1 ) ;

  GetRhsVar( 1, "h", &firstHdlRow, &firstHdlCol, &firstHdlStkIndex ) ;
  GetRhsVar( 2, "h", &secondHdlRow, &secondHdlCol, &secondHdlStkIndex ) ;

  if ( firstHdlRow * firstHdlCol != 1 || secondHdlRow * secondHdlCol != 1 )
  {
    Scierror(999,"%s : Routine can only swap two single handles.\r\n",fname);
    return 0 ;
  }

  /* get the two handles and swap them */
  swapHandles( (unsigned long) *hstk( firstHdlStkIndex  ),
               (unsigned long) *hstk( secondHdlStkIndex ) ) ;
  LhsVar(1) = 0 ;
  return 0 ;
}
/*-----------------------------------------------------------------------------------*/
