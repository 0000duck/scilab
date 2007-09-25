/*------------------------------------------------------------------------*/
/* file: DrawableTextJavaMapper.hxx                                       */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Contains mapping of java method used by DrawableText            */
/*------------------------------------------------------------------------*/

#ifndef _DRAWABLE_TEXT_JAVA_MAPPER_HXX_
#define _DRAWABLE_TEXT_JAVA_MAPPER_HXX_

#include "DrawableClippedObjectJavaMapper.hxx"
#include "DrawableTextGL.hxx"

namespace sciGraphics
{

class DrawableTextJavaMapper : public virtual DrawableClippedObjectJavaMapper
{
public:

  DrawableTextJavaMapper(void) ;

  virtual ~DrawableTextJavaMapper(void);

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
  // Specific to texts

  /*----------------------------------------------------------------------*/



private:

  /**
   * Giws generated wrapper
   */
  org_scilab_modules_renderer_textDrawing::DrawableTextGL * m_pJavaObject;

};

}

#endif /* _DRAWABLE_TEXT_JAVA_MAPPER_HXX_ */
