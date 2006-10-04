/*------------------------------------------------------------------------*/
/* file: set_surface_color_property.c                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the surface_color field of         */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "ColorMapManagement.h"
#include "MALLOC.h"
#include "BasicAlgos.h"

/*------------------------------------------------------------------------*/
int set_surface_color_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{

  if ( !isParameterDoubleMatrix( valueType ) )
  {
    sciprint("Incompatible type for property surface_color.\n") ;
    return SET_PROPERTY_ERROR ;
  }

  if (sciGetEntityType (pobj) != SCI_SURFACE)
  {
    sciprint( "surface_color property does not exist for this handle.\n" ) ;
    return SET_PROPERTY_ERROR ;
  }

  if ( pSURFACE_FEATURE(pobj)->typeof3d == SCI_PARAM3D1 )
  {
    if (pSURFACE_FEATURE (pobj)->dimzy != nbRow * nbCol )
    {
      sciprint( "Second argument must have %d elements.\n", pSURFACE_FEATURE (pobj)->dimzy);
      return SET_PROPERTY_ERROR ;
    }
    copyDoubleVectorFromStack( stackPointer, pSURFACE_FEATURE(pobj)->zcol, pSURFACE_FEATURE (pobj)->dimzy ) ;
  }
  else if ( pSURFACE_FEATURE (pobj)->typeof3d == SCI_FAC3D && pSURFACE_FEATURE (pobj)->flagcolor >= 2 )
  {
    int N;
    if ( pSURFACE_FEATURE(pobj)->flagcolor == 2 )
    {
      N = pSURFACE_FEATURE (pobj)->dimzy ;
    }
    else
    {
      N = pSURFACE_FEATURE(pobj)->dimzy * pSURFACE_FEATURE (pobj)->dimzx;
    }
    if ( nbRow * nbCol != N)
    {
      sciprint("Second argument must have %d elements.\n",N) ;
      return SET_PROPERTY_ERROR ;
    }
    copyDoubleVectorFromStack( stackPointer, pSURFACE_FEATURE (pobj)->zcol, N ) ;
  }
  else
  {
    sciprint( "surface_color cannot be set in this case.\n" ) ;
    return SET_PROPERTY_ERROR ;
  }

  return SET_PROPERTY_SUCCEED ;

}
/*------------------------------------------------------------------------*/
