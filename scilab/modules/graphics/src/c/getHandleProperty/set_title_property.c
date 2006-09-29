/*------------------------------------------------------------------------*/
/* file: set_title_property.c                                             */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the title field of                 */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "Interaction.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_title_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  if ( sciGetEntityType(pobj) != SCI_SUBWIN )
  {
    sciprint("title property undefined for this object.\n") ;
    return SET_PROPERTY_ERROR ;
  }
  else
  {
    sciprint("can not set directly a label object.\n") ;
    return SET_PROPERTY_ERROR ;
  }
  return SET_PROPERTY_ERROR ;
}
/*------------------------------------------------------------------------*/
