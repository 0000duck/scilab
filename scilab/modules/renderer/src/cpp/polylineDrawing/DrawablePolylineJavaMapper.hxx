/*------------------------------------------------------------------------*/
/* file: DrawablePolylineJavaMapper.hxx                                   */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Contains mapping of java method used by DrawablePolyline        */
/*------------------------------------------------------------------------*/

#ifndef _DRAWABLE_POLYLINE_JAVA_MAPPER_HXX_
#define _DRAWABLE_POLYLINE_JAVA_MAPPER_HXX_

#include "DrawableClippedObjectJavaMapper.hxx"
#include "DrawablePolylineGL.hxx"

namespace sciGraphics
{

class DrawablePolylineJavaMapper : public virtual DrawableClippedObjectJavaMapper
{
public:

  DrawablePolylineJavaMapper(void) ;

  virtual ~DrawablePolylineJavaMapper(void);

  /*----------------------------------------------------------------------*/
  // Inherited From DrawableObjectJavaMapper
  virtual void display(void);

  virtual void initializeDrawing(int figureIndex);
  virtual void endDrawing(void);

  virtual void show(int figureIndex);

  virtual void destroy(int figureIndex);

  virtual void setFigureIndex(int figureIndex);
  /*----------------------------------------------------------------------*/
  // Inherited From DrawableClippedObjectJavaMapper
  virtual void clipX(double xMin, double xMax);
  virtual void clipY(double yMin, double yMax);
  virtual void clipZ(double zMin, double zMax);

  virtual void unClip(void);
  /*----------------------------------------------------------------------*/
  // Specific to polylines

  /*----------------------------------------------------------------------*/



private:

  /**
   * Giws generated wrapper
   */
  org_scilab_modules_renderer_polylineDrawing::DrawablePolylineGL * m_pJavaObject;

};

}

#endif /* _DRAWABLE_POLYLINE_JAVA_MAPPER_HXX_ */
