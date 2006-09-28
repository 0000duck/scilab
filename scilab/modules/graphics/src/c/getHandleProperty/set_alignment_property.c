/*------------------------------------------------------------------------*/
/* file: set_alignment_property.c                                         */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the alignment field of             */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_alignment_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  if ( sciGetEntityType( pobj ) != SCI_TEXT )
  {
    sciprint("alignment property does not exist for this handle.\n");
    return SET_PROPERTY_ERROR ;
  }

  if ( isStringParamEqual( stackPointer, "left" ) )
  {
    return sciSetAlignment( pobj, ALIGN_LEFT ) ;
  }
  else if ( isStringParamEqual( stackPointer, "center" ) )
  {
    return sciSetAlignment( pobj, ALIGN_CENTER ) ;
  }
  else if ( isStringParamEqual( stackPointer, "right" ) )
  {
    return sciSetAlignment( pobj, ALIGN_RIGHT ) ;
  }
  else
  {
    sciprint("Second argument must be 'left','center' or 'right'.\n");
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_ERROR ;

}
/*------------------------------------------------------------------------*/
