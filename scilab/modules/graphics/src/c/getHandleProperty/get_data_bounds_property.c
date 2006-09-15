/*------------------------------------------------------------------------*/
/* file: get_data_bounds_property.c                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the data_bounds field of         */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int get_data_bounds_property( sciPointObj * pobj )
{

  if ( sciGetEntityType(pobj) == SCI_SUBWIN )
  {
    /**DJ.Abdemouche 2003**/
    if ( sciGetIs3d( pobj ) )
    {
      return sciReturnRowVector( pSUBWIN_FEATURE (pobj)->SRect, 6 ) ;
    }
    else
    {
      return sciReturnRowVector( pSUBWIN_FEATURE (pobj)->SRect, 4 ) ;
    }
  }
  else if ( sciGetEntityType (pobj) == SCI_SURFACE )
  {
    /* used for what ? F.Leray 20.04.05 */
    return sciReturnMatrix( pSURFACE_FEATURE (pobj)->ebox, 3, 2 ) ;
  }
  else
  {
    sciprint("data_bounds property does not exist for this handle.\n");
    return -1;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/
