/*------------------------------------------------------------------------*/
/* file: get_callback_type_property.c                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the callback_type field of       */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_callback_type_property( sciPointObj * pobj )
{
  if (sciGetEntityType (pobj) != SCI_UIMENU)
  {
    sciprint("callback_type property does not exist for this handle.\n");
    return -1;
  }
  switch (pUIMENU_FEATURE(pobj)->CallbackType)
  {
  case -1:
    return sciReturnString( "disable" ) ;
    break;
  case 0:
    return sciReturnString( "string" ) ;
    break;
  case 1:
    return sciReturnString( "C" ) ;
    break;
  case 2:
    return sciReturnString( "internal" ) ;
    break;
  case 3:
    return sciReturnString( "addmenu" ) ;
    break;
  default:
    sciprint("unknow callbak type\n");
    return -1;
    break;
  }

}
/*------------------------------------------------------------------------*/
