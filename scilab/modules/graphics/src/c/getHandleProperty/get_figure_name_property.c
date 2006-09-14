/*------------------------------------------------------------------------*/
/* file: get_figure_name_property.c                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the figure_name field of a       */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_figure_name_property( sciPointObj * pobj )
{
  if ( sciGetEntityType(pobj) != SCI_FIGURE )
  {
    sciprint("figure_name property undefined for this object") ;
    return -1;
  }
  return sciReturnString( sciGetName( pobj ) ) ;

}
/*------------------------------------------------------------------------*/
