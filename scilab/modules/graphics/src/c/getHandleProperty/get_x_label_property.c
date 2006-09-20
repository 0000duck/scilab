/*------------------------------------------------------------------------*/
/* file: get_x_label_property.c                                           */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the x_label field of             */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_x_label_property( sciPointObj * pobj )
{
  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint("x_label property undefined for this object\n.") ;
    return -1 ;
  }
  return sciReturnHandle( sciGetHandle( pSUBWIN_FEATURE(pobj)->mon_x_label ) ) ;
}
/*------------------------------------------------------------------------*/
