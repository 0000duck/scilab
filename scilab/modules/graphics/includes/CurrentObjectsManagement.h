/*------------------------------------------------------------------------*/
/* file: CurrentObjectsManagement.h                                       */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Set of functions to set and get current objects                 */
/*------------------------------------------------------------------------*/

#ifndef _GET_CURRENT_OBJECTS_H_
#define _GET_CURRENT_OBJECTS_H_

#include "ObjectStructure.h"
#include "bcg.h"

/**
* To know if the current figure is a graphic one.
*/
int  get_cf_type( void ) ;
void set_cf_type( int val ) ;
/*-----------------------------------------------------------------------------*/
/**
 * Returns the pointer to the current selected figure. 
 */
sciPointObj * sciGetCurrentFigure( void ) ;

int sciInitCurrentFigure( sciPointObj * mafigure ) ;
int sciSetCurrentFigure(  sciPointObj * mafigure ) ;

/**
 * as sciGetCurrentFigure but do not create any figure if none exists.
 */
sciPointObj * sciGetCurPointedFigure( void ) ;
/*-----------------------------------------------------------------------------*/
/**
 * Return the Bcg of the currently selected figure
 */
struct BCG * sciGetCurrentScilabXgc( void ) ;
/*-----------------------------------------------------------------------------*/
/**
 * Get the current Object
 */
sciPointObj * sciGetCurrentObj( void ) ;

void sciSetCurrentObj( sciPointObj * pobj ) ;

/**
 * Return the handle on the current object
 */
long sciGetCurrentHandle( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentFrame( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentWindow( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentWindowFrame( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentScreen( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentSubWin( void ) ;
/*-----------------------------------------------------------------------------*/
sciPointObj * sciGetCurrentConsole( void ) ;
/*-----------------------------------------------------------------------------*/

#endif /* _GET_CURRENT_OBJECTS_H_ */
