/*------------------------------------------------------------------------*/
/* file: get_bar_width_property.c                                         */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the bar_width field of a         */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_bar_width_property( sciPointObj * pobj )
{
  if ( sciGetEntityType (pobj) == SCI_POLYLINE )
  {
    return sciReturnDouble( pPOLYLINE_FEATURE (pobj)->bar_width ) ;
  }
  else
  { 
    sciprint("bar_with property does not exist for this handle.\n");
    return -1 ;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/
