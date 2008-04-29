/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Jean-Baptiste Silvy
 * desc : Abstract class for text drawing
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: TextContentDrawerJoGL.hxx                                        */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Abstract class for text drawing                                 */
/*------------------------------------------------------------------------*/

#include "TextContentDrawerJoGL.hxx"
#include "GetJavaProperty.h"

extern "C"
{
#include "GetProperty.h"
}

namespace sciGraphics
{
/*---------------------------------------------------------------------------------*/
TextContentDrawerJoGL::TextContentDrawerJoGL(DrawableText * drawer)
 :  DrawTextContentStrategy(drawer), DrawableObjectJoGL(drawer)
{

}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getBoundingRectangle(double corner1[3], double corner2[3], double corner3[3], double corner4[3])
{
  initializeDrawing();
  setDrawerParameters();

  // we got an array of size 12
  double * rect = getTextContentDrawerJavaMapper()->getBoundingRectangle();

  convertCornersArray(rect, corner1, corner2, corner3, corner4);

  delete[] rect;

  endDrawing();
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getScreenBoundingBox(int corner1[2], int corner2[2], int corner3[2], int corner4[2])
{
  initializeDrawing();
  setDrawerParameters();

  // we got an array of size 8
  long * rect = getTextContentDrawerJavaMapper()->getScreenBoundingBox();

  corner1[0] = rect[0];
  corner1[1] = rect[1];

  corner2[0] = rect[2];
  corner2[1] = rect[3];

  corner3[0] = rect[4];
  corner3[1] = rect[5];

  corner4[0] = rect[6];
  corner4[1] = rect[7];

  delete[] rect;
  endDrawing();
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::drawTextContent(double corner1[3], double corner2[3], double corner3[3], double corner4[3])
{
  initializeDrawing();
  setDrawerParameters();

  double * rect = getTextContentDrawerJavaMapper()->drawTextContent();
  convertCornersArray(rect, corner1, corner2, corner3, corner4);

  delete[] rect;
  endDrawing();
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::showTextContent(void)
{
  show();
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getPixelLength(sciPointObj * parentSubwin, const double startingPoint[3],
                                           double userWidth, double userHeight,
                                           int * pixelWidth, int * pixelHeight )
{
  // get the extreme bound along X axis
  double extremeX[3];
  extremeX[0] = startingPoint[0] + userWidth;
  extremeX[1] = startingPoint[1];
  extremeX[2] = startingPoint[2];

  // get the extreme bound along Y axis
  double extremeY[3];
  extremeY[0] = startingPoint[0];
  extremeY[1] = startingPoint[1] + userHeight;
  extremeY[2] = startingPoint[2];

  // convert every one in pixel coordinates
  int textPosPix[2];
  sciGetJava2dViewPixelCoordinates(parentSubwin, startingPoint, textPosPix);

  int extremeXPix[2];
  sciGetJava2dViewPixelCoordinates(parentSubwin, extremeX, extremeXPix);

  int extremeYPix[2];
  sciGetJava2dViewPixelCoordinates(parentSubwin, extremeY, extremeYPix);

  // compute lengths accordingly
  *pixelWidth = extremeXPix[0] - textPosPix[0];
  *pixelHeight = textPosPix[1] - extremeYPix[1]; // Y axis is inverted
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getTextDisplayPos(double pos[3])
{
  sciGetTextPos(m_pDrawed->getDrawedObject(), pos);
  m_pDrawed->pointScale(pos[0], pos[1], pos[2], &(pos[0]), &(pos[1]), &(pos[2]) );
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getTextBoxDisplaySize(double * width, double * height)
{
  // get user size
  sciGetUserSize(m_pDrawed->getDrawedObject(), width, height);

  // get text position
  double textPos[3];
  sciGetTextPos(m_pDrawed->getDrawedObject(), textPos);
  
  // apply log scale if needed
  m_pDrawed->directionScale(*width, *height, 0.0,
                            textPos[0], textPos[1], textPos[2],
                            width, height, NULL);
}
/*---------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::convertCornersArray(const double corners[12],
                                                double corner1[3],
                                                double corner2[3],
                                                double corner3[3],
                                                double corner4[3])
{
  // we got an array of size 12

  corner1[0] = corners[0];
  corner1[1] = corners[1];
  corner1[2] = corners[2];

  corner2[0] = corners[3];
  corner2[1] = corners[4];
  corner2[2] = corners[5];

  corner3[0] = corners[6];
  corner3[1] = corners[7];
  corner3[2] = corners[8];

  corner4[0] = corners[9];
  corner4[1] = corners[10];
  corner4[2] = corners[11];

  // use logarithmic scale if needed.
  m_pDrawed->inversePointScale(corner1[0], corner1[1], corner1[2],
    &(corner1[0]), &(corner1[1]), &(corner1[2]));
  m_pDrawed->inversePointScale(corner2[0], corner2[1], corner2[2],
    &(corner2[0]), &(corner2[1]), &(corner2[2]));
  m_pDrawed->inversePointScale(corner3[0], corner3[1], corner3[2],
    &(corner3[0]), &(corner3[1]), &(corner3[2]));
  m_pDrawed->inversePointScale(corner4[0], corner4[1], corner4[2],
    &(corner4[0]), &(corner4[1]), &(corner4[2]));
}
/*---------------------------------------------------------------------------------*/
TextContentDrawerJavaMapper * TextContentDrawerJoGL::getTextContentDrawerJavaMapper(void)
{
  return dynamic_cast<TextContentDrawerJavaMapper *>(getJavaMapper());
}
/*---------------------------------------------------------------------------------*/
}
