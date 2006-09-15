/*------------------------------------------------------------------------*/
/* file: get_zoom_box_property.c                                          */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the zoom_box field of            */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_zoom_box_property( sciPointObj * pobj )
{
  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint( "zoom_box property does not exist for this handle.\n" ) ;
    return -1 ;
  }

  if ( sciGetZooming( pobj ) )
  {
    return sciReturnRowVector( pSUBWIN_FEATURE(pobj)->ZRect, 4 ) ;
  }
  else
  {
    return sciReturnEmptyMatrix() ;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/
