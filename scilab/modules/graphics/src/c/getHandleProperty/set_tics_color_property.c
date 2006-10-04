/*------------------------------------------------------------------------*/
/* file: set_tics_color_property.c                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the tics_color field of            */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_tics_color_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{

  if ( !isParameterDoubleMatrix( valueType ) )
  {
    sciprint("Incompatible type for property tics_color.\n") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( sciGetEntityType(pobj) == SCI_AXES )
  {
    pAXES_FEATURE (pobj)->ticscolor = (int) getDoubleFromStack( stackPointer ) ;
  }
  else if ( sciGetEntityType(pobj) == SCI_SUBWIN )
  {
    sciprint("Warning: tics_color use is deprecated and no more taken into account, use foreground property to edit Axes color\n");
    pSUBWIN_FEATURE (pobj)->axes.ticscolor = (int)getDoubleFromStack( stackPointer ) ;
  }
  else
  {
    sciprint( "tics_color property does not exist for this handle.\n" ) ;
    return SET_PROPERTY_SUCCEED ;
  }
  return SET_PROPERTY_SUCCEED ;
}
/*------------------------------------------------------------------------*/
