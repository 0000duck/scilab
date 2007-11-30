/*------------------------------------------------------------------------*/
/* file: TextContentDrawerJoGL.hxx                                        */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Abstract class for text drawing                                 */
/*------------------------------------------------------------------------*/

#ifndef _TEXT_CONTENT_DRAWER_JOGL_
#define _TEXT_CONTENT_DRAWER_JOGL_

#include "DrawableObjectJoGL.h"
#include "DrawTextContentStrategy.hxx"
#include "TextContentDrawerJavaMapper.hxx"

namespace sciGraphics
{

class TextContentDrawerJoGL : public DrawTextContentStrategy, public DrawableObjectJoGL
{
public:

  TextContentDrawerJoGL(DrawableText * drawer) ;

  virtual ~TextContentDrawerJoGL( void ) {}

  /**
   * Get the 4 corners of the text bounding rectangle (the text lies within a plane).
   * Used to draw the rectangle around the text.
   */
  virtual void getBoundingRectangle(double corner1[3], double corner2[3], double corner3[3], double corner4[3]);

  /**
   * Get the bounding box of the displayed text. Used to detect overlapping text.
   */
  virtual void getScreenBoundingBox(int corner1[2], int corner2[2], int corner3[2], int corner4[2]);

  /**
   * Draw the rectangle surrounding the text.
   */
  virtual void drawTextContent(void);

  /**
   * Display the text using display lists.
   */
  virtual void showTextContent(void);

protected:

  virtual void setDrawerParameters(void) = 0;

  /**
   * Convert distance in user mode to pixel.
   * Since it can be used with logarithmic mode, one edge of the segment must be specified.
   */
  void getPixelLength(sciPointObj * parentSubwin, const double startingPoint[3],
                      double userWidth, double userHeight,
                      int * pixelWidth, int * pixelHeight );

  /**
   * Get position of the text to display.
   */
  void getTextDisplayPos(double pos[3]);

  /**
   * Get the display size of text box specified by user.
   */
  void getTextBoxDisplaySize(double * width, double * height);

  /**
   * Get the object performing mapping with Java class.
   */
  TextContentDrawerJavaMapper * getTextContentDrawerJavaMapper(void);

};

}

#endif /* _TEXT_CONTENT_DRAWER_JOGL_ */
