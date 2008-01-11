/*------------------------------------------------------------------------*/
/* file: set_position_property.c                                          */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the position field of              */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "localization.h"
#include "SetUicontrolPosition.h"
/*------------------------------------------------------------------------*/
int set_position_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{

  if(sciGetEntityType(pobj) == SCI_UICONTROL)
  {
    SetUicontrolPosition(pobj, stackPointer, valueType, nbRow, nbCol);
    return SET_PROPERTY_SUCCEED ;
  }

  if ( !isParameterDoubleMatrix( valueType ) )
  {
    sciprint(_("Incompatible type for property %s.\n"),"position") ;
    return SET_PROPERTY_ERROR ;
  }

  if ( sciGetAutoPosition( pobj ) )
  {
    sciSetAutoPosition( pobj, FALSE ) ;
  }

  if ( sciGetEntityType(pobj)== SCI_UIMENU )
  {
    pUIMENU_FEATURE(pobj)->MenuPosition = (int) getDoubleFromStack( stackPointer ) ;
    return SET_PROPERTY_SUCCEED ;
  }
  else if( sciGetEntityType(pobj) == SCI_LABEL )
  {
    double * values = getDoubleMatrixFromStack( stackPointer ) ;
    double curPos[3];
    sciGetTextPos(pobj, curPos);
    return sciSetTextPos( pobj, values[0], values[1], curPos[2] ) ;
  }
  else if( sciGetEntityType(pobj) == SCI_FIGURE ) /* Added for compatibility with old TK figure */
  {
    double * values = getDoubleMatrixFromStack( stackPointer ) ;
    return (sciInitScreenPosition(pobj, values[0], values[1]) & sciSetWindowDim(pobj, values[2], values[3]));
  }
  else
  {
    sciprint(_("%s does not exist for this handle.\n"), "position") ;
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_ERROR ;
}
/*------------------------------------------------------------------------*/
