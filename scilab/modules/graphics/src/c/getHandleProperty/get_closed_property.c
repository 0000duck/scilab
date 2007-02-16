/*------------------------------------------------------------------------*/
/* file: get_closed_property.c                                            */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the closed field of              */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_closed_property( sciPointObj * pobj )
{
  if(sciGetEntityType(pobj) != SCI_POLYLINE)
  {
    sciprint("closed property does not exist for this handle.\n") ;
    return -1 ;
  }

  if ( pPOLYLINE_FEATURE(pobj)->closed == 1 )
  {
    return sciReturnString( "on" ) ;
  }
  else
  {
    return sciReturnString( "off" ) ;
  }
}
/*------------------------------------------------------------------------*/
