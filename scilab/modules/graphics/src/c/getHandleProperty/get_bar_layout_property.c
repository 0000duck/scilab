/*------------------------------------------------------------------------*/
/* file: get_bar_layout_property.c                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the bar_layout field of a        */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_bar_layout_property( sciPointObj * pobj )
{
  if ( sciGetEntityType (pobj) == SCI_POLYLINE )
  {
    if( pPOLYLINE_FEATURE (pobj)->bar_layout == 0 )
    {
      /* 0 grouped; 1 stacked */
      return sciReturnString( "grouped" ) ;
    }
    else
    {
      return sciReturnString( "stacked" ) ;
    }
  }
  else
  {
    sciprint( "bar_layout property does not exist for this handle.\n" ) ;
    return -1 ;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/
