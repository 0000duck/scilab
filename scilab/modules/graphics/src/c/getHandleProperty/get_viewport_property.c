/*------------------------------------------------------------------------*/
/* file: get_viewport_property.c                                          */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : function to retrieve in Scilab the viewport field of            */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_viewport_property( sciPointObj * pobj )
{
  int viewport[2] ;

  if( sciGetEntityType(pobj) != SCI_FIGURE )
  {
    sciprint("viewport does not exist for this handle.\n") ;
    return -1 ;
  }

  sciGetViewport( pobj, &viewport[0], &viewport[1] ) ;

  return sciReturnRowIntVector( viewport, 2 ) ;

}
/*------------------------------------------------------------------------*/
