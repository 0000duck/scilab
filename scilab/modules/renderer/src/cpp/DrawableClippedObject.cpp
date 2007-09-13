/*------------------------------------------------------------------------*/
/* file: DrawableClippedObject.cpp                                        */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class which represent an object which can be clipped            */
/*------------------------------------------------------------------------*/

#include "DrawableClippedObject.h"

extern "C"
{
#include "GetProperty.h"
}

namespace sciGraphics
{

/*------------------------------------------------------------------------------------------*/
DrawableClippedObject::DrawableClippedObject( sciPointObj * drawed )
  : DrawableObject( drawed )
{
  m_bIsClipped = false ;
  m_bXClippingEnable = false ;
  m_bYClippingEnable = false ;
  m_bZClippingEnable = false ;
}
/*------------------------------------------------------------------------------------------*/
void DrawableClippedObject::setClipBox( void )
{
  // compute the real clipping of the object
  sciPointObj * pObj = getDrawedObject() ;

  switch(sciGetIsClipping(pObj))
  {
  case 0: // clipgrf state, use axes bounds
    {
      double clipBounds[6] ;
      sciGetRealDataBounds(sciGetParentSubwin(pObj), clipBounds) ;
      setClipBox(clipBounds[0], clipBounds[1], clipBounds[2],
                 clipBounds[3], clipBounds[4], clipBounds[5] ) ;
      m_bXClippingEnable = true ;
      m_bYClippingEnable = true ;
      m_bZClippingEnable = true ;
    }
    break;
  case 1: // on state, use its own bounds
    {
      double * clipBounds = sciGetClipping(pObj) ; // array (x,y,w,h)
      setClipBox( clipBounds[0], clipBounds[0] + clipBounds[2],
                  clipBounds[1], clipBounds[1] + clipBounds[3],
                  0.0, 0.0 ) ;
      m_bXClippingEnable = true ;
      m_bYClippingEnable = true ;
      m_bZClippingEnable = false ;
    }
    break;
  default: // clipping off
    m_bXClippingEnable = false ;
    m_bYClippingEnable = false ;
    m_bZClippingEnable = false ;
    return;
  }

}
/*------------------------------------------------------------------------------------------*/
void DrawableClippedObject::setClipBox( double xMin, double xMax,
                                        double yMin, double yMax,
                                        double zMin, double zMax )
{
  getClippedObjBridge()->setClipBox(xMin, xMax, yMin, yMax, zMin, zMax) ;
}
/*------------------------------------------------------------------------------------------*/
void DrawableClippedObject::clip( void )
{
  setClipBox();
  if ( m_bXClippingEnable )
  {
    getClippedObjBridge()->clipX();
  }

  if ( m_bYClippingEnable )
  {
    getClippedObjBridge()->clipY();
  }

  if ( m_bZClippingEnable )
  {
    getClippedObjBridge()->clipZ();
  }
  m_bIsClipped = true ;
}
/*------------------------------------------------------------------------------------------*/
void DrawableClippedObject::unClip( void )
{
  if ( m_bIsClipped )
  {
    getClippedObjBridge()->unClip();
    m_bIsClipped = false ;
  }
}
/*------------------------------------------------------------------------------------------*/
DrawableClippedObjectBridge * DrawableClippedObject::getClippedObjBridge( void )
{
  return dynamic_cast<DrawableClippedObjectBridge *>(m_pImp) ;
}
/*------------------------------------------------------------------------------------------*/

}
