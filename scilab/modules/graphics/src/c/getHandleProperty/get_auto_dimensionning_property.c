/*------------------------------------------------------------------------*/
/* file: get_auto_dimensionning_property.c                                */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the auto_dimensionning field of  */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_auto_dimensionning_property( sciPointObj * pobj )
{
  if ( sciGetEntityType( pobj ) == SCI_TEXT )
  {
    if ( sciGetAutoSize( pobj ) )
    {
      return sciReturnString( "on" ) ;
    }
    else
    {
      return sciReturnString( "off" ) ;
    }
  }
  sciprint("auto_dimensionning property does not exist for this handle.\n") ;
  return -1 ;
}
/*------------------------------------------------------------------------*/
