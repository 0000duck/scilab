/*------------------------------------------------------------------------*/
/* file: DrawableText.h                                                   */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing the drawing routine for a text object          */
/*------------------------------------------------------------------------*/

#ifndef _DRAWABLE_TEXT_H_
#define _DRAWABLE_TEXT_H_


#include "../DrawableClippedObject.h"

namespace sciGraphics
{

class DrawableText : public DrawableClippedObject
{

public:

  DrawableText( sciPointObj * pObj ) : DrawableClippedObject( pObj ) {}

  virtual ~DrawableText( void ) {}

  /**
   * Get the 4 corners of the text bounding rectangle (the text lies within a plane).
   * Used to draw the rectangle around the text.
   */
  virtual void getBoundingRectangle(double corner1[3], double corner2[3], double corner3[3], double corner4[3]) = 0;

  /**
   * Get the bounding box of the displayed text in pixels. Used to detect overlapping text.
   */
  virtual void getScreenBoundingBox(int corner1[2], int corner2[2], int corner3[2], int corner4[2]) = 0;

  /**
   * To know if there is really some text to display.
   * Useful for labels objects which display text.
   */
  virtual bool isTextEmpty(void) = 0;

  /**
   * Update the text box of a text object
   */
  virtual void updateTextBox(void) = 0;

protected:

  /**
   * Draw the graphic handle and store it representation in memory
   * for later faster drawing.
   */
  virtual void draw( void ) ;

  /**
   * Fast draw of the graphic handle on the screen using the data created by draw.
   * Warning, be sure that draw is called before show each time the handle is modified.
   */
  virtual void show( void ) ;

  /**
   * Draw the rectangle surrounding the text.
   */
  virtual void drawBox(void) = 0;

  /**
   * Draw the text of the object.
   */
  virtual void drawTextContent(void) = 0;

  /**
   * Display the rectangle surrounding the text using display lists.
   */
  virtual void showBox(void) = 0;

  /**
   * Display the text using display lists.
   */
  virtual void showTextContent(void) = 0;


} ;

}

#endif /* _DRAWABLE_TEXT_H_  */
