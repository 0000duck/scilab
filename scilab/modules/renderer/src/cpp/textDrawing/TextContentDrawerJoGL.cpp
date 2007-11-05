/*------------------------------------------------------------------------*/
/* file: TextContentDrawerJoGL.hxx                                        */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Abstract class for text drawing                                 */
/*------------------------------------------------------------------------*/

#include "TextContentDrawerJoGL.hxx"
#include "GetJavaProperty.h"

namespace sciGraphics
{
/*------------------------------------------------------------------------------------------*/
TextContentDrawerJoGL::TextContentDrawerJoGL(DrawableText * drawer)
 : DrawableObjectJoGL(drawer), DrawTextContentStrategy(drawer)
{

}
/*------------------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getBoundingRectangle(double corner1[3], double corner2[3], double corner3[3], double corner4[3])
{
  setDrawerParameters();
  double * rect = getTextContentDrawerJavaMapper()->getBoundingRectangle();

  corner1[0] = rect[0];
  corner1[1] = rect[1];
  corner1[2] = rect[2];

  corner2[0] = rect[3];
  corner2[1] = rect[4];
  corner2[2] = rect[5];

  corner3[0] = rect[6];
  corner3[1] = rect[7];
  corner3[2] = rect[8];

  corner4[0] = rect[9];
  corner4[1] = rect[10];
  corner4[2] = rect[11];

  delete[] rect;
}
/*------------------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::getScreenBoundingBox(int corner1[2], int corner2[2], int corner3[2], int corner4[2])
{
  setDrawerParameters();
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

}
/*------------------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::drawTextContent(void)
{
  initializeDrawing();
  setDrawerParameters();

  getTextContentDrawerJavaMapper()->drawTextContent();
  endDrawing();
}
/*------------------------------------------------------------------------------------------*/
void TextContentDrawerJoGL::showTextContent(void)
{
  show();
}
/*------------------------------------------------------------------------------------------*/
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
  *pixelHeight = extremeYPix[1] - textPosPix[1];
}
/*------------------------------------------------------------------------------------------*/
TextContentDrawerJavaMapper * TextContentDrawerJoGL::getTextContentDrawerJavaMapper(void)
{
  return dynamic_cast<TextContentDrawerJavaMapper *>(getJavaMapper());
}
/*------------------------------------------------------------------------------------------*/
}