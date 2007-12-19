/*------------------------------------------------------------------------*/
/* file: set_y_location_property.c                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the y_location field of            */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "localization.h"

/*------------------------------------------------------------------------*/
int set_y_location_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{

  if ( !isParameterStringMatrix( valueType ) )
  {
    sciprint(_("Incompatible type for property %s.\n"),"y_location") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint(_("%s property does not exist for this handle.\n"),"y_location") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( isStringParamEqual( stackPointer, "left" ) )
  {
    pSUBWIN_FEATURE(pobj)->axes.ydir = 'l' ;
  }
  else if ( isStringParamEqual( stackPointer, "right" ) )
  {
    pSUBWIN_FEATURE(pobj)->axes.ydir = 'r' ;
  }
  else if ( isStringParamEqual( stackPointer, "middle" ) )
  {
    pSUBWIN_FEATURE(pobj)->axes.ydir = 'c' ;
  }
  else  
  {
    sciprint(_("%s: Wrong type for second input argument: '%s', '%s' or '%s' expected.\n"), "set_y_location_property","left","right","middle") ;
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_SUCCEED ;
}
/*------------------------------------------------------------------------*/
