/*------------------------------------------------------------------------*/
/* file: set_mark_foreground_property.c                                   */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to modify in Scilab the mark_foreground field of       */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
int set_mark_foreground_property( sciPointObj * pobj, int stackPointer, int nbRow, int nbCol )
{
  /*    sciSetIsMark((sciPointObj *) pobj, TRUE); */
  /* F.Leray 27.01.05 commented because mark_size is automatically launched */
  /* in tcl/tk editor (which causes marks appearance even when unwanted). */
  return sciSetMarkForeground( pobj, (int) getDoubleFromStack( stackPointer ) ) ;
}
/*------------------------------------------------------------------------*/
