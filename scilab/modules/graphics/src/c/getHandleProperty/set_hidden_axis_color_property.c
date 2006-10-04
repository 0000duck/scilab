/*------------------------------------------------------------------------*/
/* file: set_hidden_axis_color_property.c                                 */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the hidden_axis_color field of     */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "sciprint.h"
#include "GetProperty.h"
#include "SetPropertyStatus.h"

/*------------------------------------------------------------------------*/
int set_hidden_axis_color_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{

  int haColor      = (int) getDoubleFromStack( stackPointer ) ;
  int colormapSize = sciGetNumColors( pobj ) ;

  if ( !isParameterDoubleMatrix( valueType ) )
  {
    sciprint("Incompatible type for property hidden_axis_color.\n") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( sciGetEntityType (pobj) != SCI_SUBWIN )
  {
    sciprint( "hidden_axis_color property does not exist for this handle.\n" ) ;
    return SET_PROPERTY_ERROR ;
  }

  if ( haColor >= -2 && haColor <= colormapSize + 1 )
  {
    pSUBWIN_FEATURE(pobj)->axes.hiddenAxisColor = haColor ;
    return SET_PROPERTY_SUCCEED ;
  }
  else
  {
    sciprint( "Color outside of color map boundaries.\n" ) ;
    return SET_PROPERTY_ERROR ;
  }

  return SET_PROPERTY_ERROR ;
}
/*------------------------------------------------------------------------*/
