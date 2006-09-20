/*------------------------------------------------------------------------*/
/* file: get_title_property.c                                             */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the title field of               */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_title_property( sciPointObj * pobj )
{
  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint("title property undefined for this object\n.") ;
    return -1 ;
  }
  return sciReturnHandle( sciGetHandle( pSUBWIN_FEATURE(pobj)->mon_title ) ) ;
}
/*------------------------------------------------------------------------*/
