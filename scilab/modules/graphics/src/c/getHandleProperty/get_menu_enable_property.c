/*------------------------------------------------------------------------*/
/* file: get_menu_enable_property.c                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the menu_enable field of         */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_menu_enable_property( sciPointObj * pobj )
{
  if (sciGetEntityType (pobj) != SCI_UIMENU)
  {
    sciprint("menu_enable property does not exist for this handle.\n");
    return -1;
  }
  if ( pUIMENU_FEATURE(pobj)->Enable )
  {
    return sciReturnString( "on" ) ;
  }
  else 
  {
    return sciReturnString( "off" ) ;
  }
}
/*------------------------------------------------------------------------*/
