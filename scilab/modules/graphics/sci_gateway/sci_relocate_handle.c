/*------------------------------------------------------------------------*/
/* file: sci_relocate_handle.h                                            */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for relocate_handle routine                           */
/*------------------------------------------------------------------------*/

#include "sci_relocate_handle.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "HandleManagement.h"

/*-----------------------------------------------------------------------------------*/

int sci_relocate_handle( char * fname, unsigned long fname_len )
{
  int handleCol ;
  int handleRow ;
  int nbHandle ;
  int handleStkIndex ;
  int parentCol ;
  int parentRow ;
  int parentStkIndex ;
  int outIndex ;
  int i ;
  unsigned long * handleArray = NULL ;

  /* the function should be called with relocate_handle( handle, parent_handle ) */
  CheckRhs(2,2) ;
  CheckLhs(0,1) ;


  GetRhsVar( 1, "h", &handleRow, &handleCol, &handleStkIndex ) ;
  nbHandle = handleRow * handleCol ;
  GetRhsVar( 2, "h", &parentRow, &parentCol, &parentStkIndex ) ;

  if ( parentCol * parentRow != 1 )
  {
    Scierror(999,"%s :Handles must be relocated under a single parent.\r\n",fname);
    return 0 ;
  }

  /* create an array of handles */
  handleArray = MALLOC( nbHandle * sizeof( unsigned long ) ) ;
  if ( handleArray == NULL )
  {
    Scierror(999,"Memory full, aborting operation.\r\n",fname);
    return 0 ;
  }

  for ( i = 0 ; i < nbHandle ; i++ )
  {
    handleArray[i] = (unsigned long) *hstk( handleStkIndex + i ) ;
  }

  if ( sciRelocateHandles( handleArray          ,
                           handleRow * handleCol,
                           (unsigned long) *hstk( parentStkIndex ) ) != 0 )
  {
    return 0 ;
  }
  FREE( handleArray ) ;
  CreateVar( Rhs + 1, "h", &handleCol, &handleRow, &outIndex ) ;
  *hstk(outIndex) = *hstk(handleStkIndex) ;
  LhsVar(1) = Rhs + 1 ;
  return 0 ;

}
/*-----------------------------------------------------------------------------------*/
