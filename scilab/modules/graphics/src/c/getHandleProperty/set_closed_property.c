/*------------------------------------------------------------------------*/
/* file: set_closed_property.c                                            */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the closed field of                */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_closed_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  if(sciGetEntityType(pobj) != SCI_POLYLINE)
  {
    sciprint( "closed property does not exist for this handle.\n" ) ;
    return SET_PROPERTY_ERROR ;
  }

  if ( isStringParamEqual( stackPointer, "on" ) )
  {
    pPOLYLINE_FEATURE(pobj)->closed = 1 ;
  }
  else if ( isStringParamEqual( stackPointer, "off" ) )
  {
    pPOLYLINE_FEATURE(pobj)->closed = 0 ;
  }
  else
  {
    sciprint("Nothing to do (value must be 'on/off').\n") ;
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_SUCCEED ;
}
/*------------------------------------------------------------------------*/
