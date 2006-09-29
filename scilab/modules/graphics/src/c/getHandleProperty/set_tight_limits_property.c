/*------------------------------------------------------------------------*/
/* file: set_tight_limits_property.c                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the tight_limits field of          */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_tight_limits_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint("tight_limits property does not exists for this handle.\n") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( isStringParamEqual( stackPointer, "on" ) )
  {
    pSUBWIN_FEATURE (pobj)->tight_limits = FALSE;
  }
  else if ( isStringParamEqual( stackPointer, "off" ) )
  {
    pSUBWIN_FEATURE (pobj)->tight_limits = TRUE;
  }
  else
  {
    sciprint("Second argument must be 'on' or 'off'.\n") ;
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_SUCCEED ;
}
/*------------------------------------------------------------------------*/
