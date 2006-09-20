/*------------------------------------------------------------------------*/
/* file: returnProperty.c                                                 */
/* Copyright INRIA 2006                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : a set of functions used to return a tList in Scilab             */
/*------------------------------------------------------------------------*/

#include "returnPropertyList.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "sciprint.h"

/*------------------------------------------------------------------------*/
returnedList * createReturnedList( int nbElements, const char * elementName[] )
{
  returnedList * newList = NULL ;
  int nbRow = 1 ;

  newList = MALLOC( sizeof(returnedList) ) ;
  if ( newList == NULL )
  {
    sciprint("Error returning tlist, memory full.\n") ;
    return NULL ;
  }

  newList->nbElements = nbElements + 1 ;

  /* create the tlist in the stack and get the stack pointer in newList->stackPointer */
  CreateVar( Rhs+1, "t", &(newList->nbElements), &nbRow, &(newList->stackPointer) ) ;

  /* create the first element : names of properties */
  CreateListVarFromPtr( Rhs+1, 1, "S", &nbRow, &(newList->nbElements), elementName ) ;
  
  newList->curElement = 1 ;

  return newList ;
}
/*------------------------------------------------------------------------*/
int destroyReturnedList( returnedList * list )
{
  /* safe test to know if the list has been correctly filled */
  if ( list->curElement != list->nbElements )
  {
    sciprint( "tList not completely filled.\n" ) ;
    FREE( list ) ;
    return 1 ;
  }

  FREE( list ) ;
  return 0 ;
}
/*------------------------------------------------------------------------*/
int addRowVectorToReturnedList( returnedList * list, const double vector[], int nbValues )
{
  int nbRow = 1 ;
  /* check we are not using all the allocated space for the list */
  if ( list->curElement >= list->nbElements )
  {
    sciprint("list full.\n") ;
    return 1 ;
  }

  /* add a new element */
  list->curElement++ ;
  CreateListVarFromPtr( Rhs+1, list->curElement, "d", &nbRow, &nbValues, &vector ) ;

  return 0 ;
}
/*------------------------------------------------------------------------*/
int addColVectorToReturnedList( returnedList * list, const double vector[], int nbValues )
{
  int nbCol = 1 ;
  /* check we are not using all the allocated space for the list */
  if ( list->curElement >= list->nbElements )
  {
    sciprint("list full.\n") ;
    return 1 ;
  }

  /* add a new element */
  list->curElement++ ;
  CreateListVarFromPtr( Rhs+1, list->curElement, "d", &nbValues, &nbCol, &vector ) ;

  return 0 ;
}
/*------------------------------------------------------------------------*/
int addMatrixToReturnedList( returnedList * list, const double matrix[], int nbRow, int nbCol )
{
  /* check we are not using all the allocated space for the list */
  if ( list->curElement >= list->nbElements )
  {
    sciprint("list full.\n") ;
    return 1 ;
  }

  /* add a new element */
  list->curElement++ ;
  CreateListVarFromPtr( Rhs+1, list->curElement, "d", &nbRow, &nbCol, &matrix ) ;

  return 0 ;
}
/*------------------------------------------------------------------------*/
int addStringColVectorToReturnedList( returnedList * list, const char * vector[], int nbValues )
{
  int nbCol = 1 ;
  /* check we are not using all the allocated space for the list */
  if ( list->curElement >= list->nbElements )
  {
    sciprint("list full.\n") ;
    return 1 ;
  }

  /* add a new element */
  list->curElement++ ;
  CreateListVarFromPtr( Rhs+1, list->curElement, "S", &nbValues, &nbCol, vector ) ;

  return 0 ;
}
/*------------------------------------------------------------------------*/
