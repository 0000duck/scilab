/*------------------------------------------------------------------------*/
/* file: get_info_message_property.c                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the info_message field of a       */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_info_message_property( sciPointObj * pobj )
{
  if ( sciGetEntityType(pobj) != SCI_FIGURE )
  {
    sciprint("info_message property undefined for this object") ;
    return -1;
  }
  return sciReturnString( sciGetInfoMessage( pobj ) ) ;

}
/*------------------------------------------------------------------------*/
