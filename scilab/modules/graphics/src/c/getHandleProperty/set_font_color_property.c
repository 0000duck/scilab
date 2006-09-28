/*------------------------------------------------------------------------*/
/* file: set_font_color_property.c                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the font_color field of            */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "GetProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_font_color_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  int value = (int) getDoubleFromStack( stackPointer ) ;
  if ( sciGetEntityType(pobj) != SCI_AXES )
  {
    pAXES_FEATURE (pobj)->textcolor = value ;
    return 0 ;
  }
  else if ( sciGetEntityType(pobj) == SCI_SUBWIN || sciGetEntityType(pobj) == SCI_FIGURE )
  {
    return sciSetFontForeground( pobj,value ) ;
  } /* F.Leray 08.04.04 */
  else
  {
    sciprint( "font_color property does not exist for this handle.\n" ) ;
    return -1 ;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/
