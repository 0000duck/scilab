/*------------------------------------------------------------------------*/
/* file: getHandleDrawer.cpp                                              */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Contains the function to retrieve a the drawer of a graphic     */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleDrawer.h"
#include "DrawableObjectFactory.h"

extern "C"
{
#include "GetProperty.h"
}

namespace sciGraphics
{

/*---------------------------------------------------------------------------------*/
DrawableObject * getHandleDrawer( sciPointObj * pObj )
{
  if ( pObj->pDrawer != NULL )
  {
    return getHandleDrawerPointer( pObj ) ;
  }
  
  /* We need to create the drawer */

  DrawableObjectFactory creator ;
  creator.setGraphicObj( pObj ) ;

  DrawableObject * drawer = creator.create() ;

  setHandleDrawerPointer( pObj, drawer ) ;

  return drawer ;
}
/*---------------------------------------------------------------------------------*/
DrawableObject * getHandleDrawerPointer( sciPointObj * pObj )
{
  if ( pObj->pDrawer == NULL ) { return NULL ; }
  return ((DrawableObjectWrapper *)(pObj->pDrawer))->drawer ;
}
/*---------------------------------------------------------------------------------*/
void setHandleDrawerPointer( sciPointObj * pObj, DrawableObject * drawer )
{
  if ( pObj->pDrawer == NULL )
  {
    pObj->pDrawer = new DrawableObjectWrapper() ;
  }
  ((DrawableObjectWrapper *)(pObj->pDrawer))->drawer = drawer ;
}
/*---------------------------------------------------------------------------------*/
DrawableFigure * getFigureDrawer( sciPointObj * pFigure )
{
  if ( sciGetEntityType(pFigure) != SCI_FIGURE )
  {
    return NULL;
  }

  return dynamic_cast<DrawableFigure *>(getHandleDrawer(pFigure));
}
/*---------------------------------------------------------------------------------*/
DrawableRectangle * getRectangleDrawer( sciPointObj * pRectangle )
{
  if ( sciGetEntityType(pRectangle) != SCI_RECTANGLE )
  {
    return NULL;
  }

  return dynamic_cast<DrawableRectangle *>(getHandleDrawer(pRectangle));
}
/*---------------------------------------------------------------------------------*/
DrawableArc * getArcDrawer( sciPointObj * pArc )
{
  if ( sciGetEntityType(pArc) != SCI_ARC )
  {
    return NULL;
  }

  return dynamic_cast<DrawableArc *>(getHandleDrawer(pArc));
}
/*---------------------------------------------------------------------------------*/
DrawablePolyline * getPolylineDrawer( sciPointObj * pPolyline )
{
  if ( sciGetEntityType(pPolyline) != SCI_POLYLINE )
  {
    return NULL;
  }

  return dynamic_cast<DrawablePolyline *>(getHandleDrawer(pPolyline));
}
/*---------------------------------------------------------------------------------*/
DrawableText * getTextDrawer( sciPointObj * pText )
{
  if ( sciGetEntityType(pText) != SCI_TEXT )
  {
    return NULL;
  }

  return dynamic_cast<DrawableText *>(getHandleDrawer(pText));
}
/*---------------------------------------------------------------------------------*/
DrawableSubwin * getSubwinDrawer( sciPointObj * pSubwin )
{
  if ( sciGetEntityType(pSubwin) != SCI_SUBWIN )
  {
    return NULL;
  }

  return dynamic_cast<DrawableSubwin *>(getHandleDrawer(pSubwin));
}
/*---------------------------------------------------------------------------------*/
DrawableLabel * getLabelDrawer( sciPointObj * pLabel )
{
  if ( sciGetEntityType(pLabel) != SCI_LABEL )
  {
    return NULL;
  }

  return dynamic_cast<DrawableLabel *>(getHandleDrawer(pLabel));
}
/*---------------------------------------------------------------------------------*/
DrawableSurface * getSurfaceDrawer( sciPointObj * pSurface )
{
  if ( sciGetEntityType(pSurface) != SCI_SURFACE )
  {
    return NULL;
  }

  return dynamic_cast<DrawableSurface *>(getHandleDrawer(pSurface));
}
/*---------------------------------------------------------------------------------*/
}
