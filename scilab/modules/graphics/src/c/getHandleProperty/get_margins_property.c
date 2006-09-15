/*------------------------------------------------------------------------*/
/* file: get_margins_property.c                                           */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the margins field of             */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_margins_property( sciPointObj * pobj )
{

  if ( sciGetEntityType (pobj) != SCI_SUBWIN )
  {
    sciprint("margins property does not exist for this handle.\n") ;
    return -1 ;
  }

  return sciReturnRowVector( pSUBWIN_FEATURE (pobj)->ARect, 4 ) ;

}
/*------------------------------------------------------------------------*/
