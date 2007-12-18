/*------------------------------------------------------------------------*/
/* file: get_labels_font_size_property.c                                  */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the labels_font_size field of    */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"
#include "localization.h"

/*------------------------------------------------------------------------*/
int get_labels_font_size_property( sciPointObj * pobj )
{
  if ( sciGetEntityType (pobj) == SCI_AXES)
  {
    return sciReturnDouble( pAXES_FEATURE (pobj)->fontsize ) ;
  }
  else if (sciGetEntityType (pobj) == SCI_SUBWIN || sciGetEntityType (pobj) == SCI_FIGURE)
  {
    return sciReturnDouble( sciGetFontSize(pobj) ) ; /* F.Leray 08.04.04 */
  }
  else
  {
    sciprint(_("%s does not exist for this handle.\n"), "labels_font_size property");
    return -1;
  }

}
/*------------------------------------------------------------------------*/
