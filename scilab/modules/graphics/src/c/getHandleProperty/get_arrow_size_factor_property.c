/*------------------------------------------------------------------------*/
/* file: get_arrow_size_factor_property.c                                 */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the arrow_size_factor field of a */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_arrow_size_factor_property( sciPointObj * pobj )
{
  if( sciGetEntityType(pobj) != SCI_POLYLINE)
  {
    sciprint( "arrow_size_factor does not exist for this handle.\n" ) ;
    return -1 ;
  }
  return sciReturnDouble( pPOLYLINE_FEATURE(pobj)->arsize_factor ) ;
}
/*------------------------------------------------------------------------*/
