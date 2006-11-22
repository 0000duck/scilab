/*------------------------------------------------------------------------*/
/* file: set_current_axes_property.c                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the current_axes field of          */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "GetProperty.h"
#include "getPropertyAssignedValue.h"
#include "sciprint.h"
#include "Xcall1.h"
#include "SetPropertyStatus.h"

/*------------------------------------------------------------------------*/
int set_current_axes_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{
  sciPointObj * curAxes   = NULL ;
  sciPointObj * parentFig = NULL ;
  int num = -1 ;
  int status1 = 1 ;
  int status2 = 1 ;
  
  if ( !isParameterHandle( valueType ) )
  {
    sciprint("Incompatible type for property current_axes.\n") ;
    return SET_PROPERTY_ERROR ;
  }

  curAxes = sciGetPointerFromHandle( getHandleFromStack( stackPointer ) ) ;

  if ( curAxes == NULL)
  {
    sciprint("Object is not valid.\n") ;
    return -1 ;
  }
  if ( sciGetEntityType( curAxes ) != SCI_SUBWIN )
  {
    sciprint("Object is not an Axes Entity.\n") ;
    return -1 ;
  }

  status1 = sciSetSelectedSubWin( curAxes ) ;
  /* F.Leray 11.02.05 : if the new selected subwin is not inside the current figure, */
  /* we must also set the current figure to subwin->parent */
  parentFig = sciGetParentFigure( curAxes );

  num  = sciGetNum( parentFig ) ;

  status2 = sciSetUsedWindow( num ) ;

  /* End modif. on the 11.02.05 */
  return sciSetFinalStatus( status1, status2 ) ;

}
/*------------------------------------------------------------------------*/
