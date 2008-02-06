/*------------------------------------------------------------------------*/
/* file: DrawableFec.h                                                    */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing the drawing routine for a fec object           */
/*------------------------------------------------------------------------*/

#ifndef _DRAWABLE_FEC_H_
#define _DRAWABLE_FEC_H_


#include "../DrawableClippedObject.h"

namespace sciGraphics
{

class DrawableFec : public DrawableClippedObject
{

public:

  DrawableFec( sciPointObj * pObj ) : DrawableClippedObject( pObj ) {}

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
   * Actually draw the fec objets
   */
  virtual void drawFec(void) = 0;

  /**
   * Actually show fec object
   */
  virtual void showFec(void) = 0;

} ;

}

#endif /* _DRAWABLE_FEC_H_  */
