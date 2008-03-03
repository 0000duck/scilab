/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Jean-Baptiste Silvy 
 * desc : Contains mapping of java method used by DrawableFigure
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef _DRAWABLE_FIGURE_JAVA_MAPPER_HXX_
#define _DRAWABLE_FIGURE_JAVA_MAPPER_HXX_

#include "DrawableObjectJavaMapper.hxx"
#include <string>
#include "DrawableFigureGL.hxx"

namespace sciGraphics
{

class DrawableFigureJavaMapper : public virtual DrawableObjectJavaMapper
{
public:

  DrawableFigureJavaMapper( void ) ;

  virtual ~DrawableFigureJavaMapper( void ) ;

  /*----------------------------------------------------------------------*/
  // Inherited From DrawableObjectJavaMapper
  virtual void display(void);

  virtual void initializeDrawing(int figureIndex);
  virtual void endDrawing(void);

  virtual void show(int figureIndex);

  virtual void destroy(int parentFigureIndex);

  virtual void setFigureIndex(int figureIndex);
  /*----------------------------------------------------------------------*/
  // specific for figures
  virtual void drawCanvas(void);

  virtual void closeRenderingCanvas(void);

  virtual void drawBackground(int colorIndex);
  
  virtual void setLogicalOp(int logicOpIndex);


  virtual void setColorMapData(const double rgbmat[], int nbColor);
  virtual void getColorMapData(double rgbmat[]);
  virtual int getColorMapSize(void);

  virtual int getCanvasWidth(void);
  virtual int getCanvasHeight(void);
  virtual void setCanvasSize(int width, int height);

  virtual int getWindowPosX(void);
  virtual int getWindowPosY(void);
  virtual void setWindowPosition(int posX, int posY);

  virtual int getWindowWidth(void);
  virtual int getWindowHeight(void);
  virtual void setWindowSize(int width, int height);

  virtual void setInfoMessage(char * infoMessage);

  virtual void setPixmapMode(bool onOrOff);
  virtual bool getPixmapMode(void);

  virtual void setRenderingEnable(bool isEnable);

  virtual void setAutoResizeMode(bool onOrOff);
  virtual bool getAutoResizeMode(void);

  virtual void getViewport(int viewport[4]);
  virtual void setViewport(const int viewport[4]);
  /*----------------------------------------------------------------------*/

protected:

  /** giws generated file */
  org_scilab_modules_renderer_figureDrawing::DrawableFigureGL * m_pJavaObject;

};

}

#endif /* _DRAWABLE_FIGURE_JAVA_MAPPER_HXX_ */

