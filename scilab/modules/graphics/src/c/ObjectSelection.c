/*------------------------------------------------------------------------*/
/* file: ObjectSelection.c                                                */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Set of functions to select children of an object                */
/*------------------------------------------------------------------------*/

#include "ObjectSelection.h"
#include "MALLOC.h"
#include "GetProperty.h"

/*-----------------------------------------------------------------------------------*/
int sciAddSelectedSon( sciPointObj * pParent, sciPointObj * pObj )
{
  sciEntityType sonType = sciGetEntityType( pObj ) ;
  /* first search if there are already objects with the specified type */
  TypedSonsList * typedList = sciGetTypedList( pParent, sonType ) ;

  if ( typedList == NULL )
  {
    /* first item with this type to be inserted */
    DoublyLinkedList * newTypedList = NULL ;
    TypedSonsList    * newItem      = NULL ;

    /* first create the list of objects with the son type */
    newTypedList = DoublyLinkedList_new() ;
    newTypedList = List_append( newTypedList, pObj ) ;

    /* then create a new entry in the main list for this type */
    newItem = newTypedSonList( sonType, newTypedList ) ;

    /* add it to the main list */
    sciGetRelationship(pParent)->pSelectedSon = List_append( sciGetRelationship(pParent)->pSelectedSon, newItem ) ;

  }
  else
  {
    typedList->typedSons = List_append( typedList->typedSons, pObj ) ;
  }
  return 0 ;

}
/*-----------------------------------------------------------------------------------*/
int sciAddUniqueSelectedSon( sciPointObj * pParent, sciPointObj * pObj )
{
  sciUnselectTypedSons( pParent, sciGetEntityType(pObj) ) ;
  return sciAddSelectedSon( pParent, pObj ) ;
}
/*-----------------------------------------------------------------------------------*/
void sciInitSelectedSons( sciPointObj * pObj )
{
  sciGetRelationship(pObj)->pSelectedSon = DoublyLinkedList_new() ;
}
/*-----------------------------------------------------------------------------------*/
sciPointObj * sciGetFirstSelectedSon( sciPointObj * pObj )
{
  return (sciPointObj *) List_data(((TypedSonsList*)List_data(sciGetRelationship(pObj)->pSelectedSon))->typedSons ) ;
}
/*-----------------------------------------------------------------------------------*/
sciPointObj * sciGetFirstTypedSelectedSon( sciPointObj * pObj, sciEntityType objType )
{
  return (sciPointObj *) List_data( sciGetTypedSelectedSons( pObj, objType ) ) ;
}
/*-----------------------------------------------------------------------------------*/
DoublyLinkedList * sciGetTypedSelectedSons( sciPointObj * pObj, sciEntityType objType )
{
  return sciGetTypedList( pObj, objType )->typedSons ;
}
/*-----------------------------------------------------------------------------------*/
int sciRemoveSelectedSon( sciPointObj * pParent, sciPointObj * pObj )
{
  TypedSonsList * curList = sciGetTypedList( pParent, sciGetEntityType(pObj) ) ;
  curList->typedSons = List_free_item( curList->typedSons, pObj ) ;
  return 0 ;
}
/*-----------------------------------------------------------------------------------*/
void sciUnselectSons( sciPointObj * pParent )
{
  List_free_full( sciGetRelationship(pParent)->pSelectedSon, deleteTypedSonList ) ;
  sciGetRelationship(pParent)->pSelectedSon = DoublyLinkedList_new() ;
}
/*-----------------------------------------------------------------------------------*/
void sciUnselectTypedSons( sciPointObj * pParent, sciEntityType sonsType )
{
  /* first search if there are already objects with the specified type */
  TypedSonsList * typedList = sciGetTypedList( pParent, sonsType ) ;

  if ( typedList == NULL ) { return ; } /* no item with this type */

  /* remove the input for this type in the main list */
  sciGetRelationship(pParent)->pSelectedSon = List_free_item( sciGetRelationship(pParent)->pSelectedSon, typedList ) ;

  /* free the input and the list of object with this type */
  deleteTypedSonList( typedList ) ;

}
/*-----------------------------------------------------------------------------------*/
BOOL sciGetIsSelected( sciPointObj * pObj )
{
  DoublyLinkedList * curList = sciGetTypedSelectedSons( sciGetParent(pObj), sciGetEntityType(pObj) ) ;
  return ( List_find( curList, pObj ) != NULL ) ;
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/**
* Just check if the two typedSonsList has same type.
* To be used with List_find_full.
*/
static BOOL hasSameType( void * typedSonsList1, void * typedSonsList2 )
{
  return ( ((TypedSonsList*)typedSonsList1)->sonType == ((TypedSonsList*)typedSonsList2)->sonType ) ;
}
/*-----------------------------------------------------------------------------------*/
TypedSonsList * sciGetTypedList( sciPointObj * pObj, sciEntityType objType )
{
  TypedSonsList refType = { objType, NULL } ; /* just for comparison with type */
  return (TypedSonsList *) List_data(List_find_full( sciGetRelationship(pObj)->pSelectedSon, &refType, hasSameType ) ) ;
}
/*-----------------------------------------------------------------------------------*/
TypedSonsList * newTypedSonList( sciEntityType type, DoublyLinkedList * typedSons )
{
  TypedSonsList * newList = MALLOC(sizeof(TypedSonsList)) ;
  newList->sonType   = type ;
  newList->typedSons = typedSons ;

  return newList ;
}
/*-----------------------------------------------------------------------------------*/
void deleteTypedSonList( void * typedSonsList )
{
  if ( ((TypedSonsList *)typedSonsList)->typedSons != NULL )
  {
    List_free( ((TypedSonsList *)typedSonsList)->typedSons ) ;
  }
  FREE(typedSonsList) ;
}
/*-----------------------------------------------------------------------------------*/
