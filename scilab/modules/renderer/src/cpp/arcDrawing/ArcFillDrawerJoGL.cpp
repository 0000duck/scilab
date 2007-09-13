/*------------------------------------------------------------------------*/
/* file: ArcFillDrawerJoGL.hxx                                            */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Strategy drawing the inside of an arc object                    */
/*------------------------------------------------------------------------*/

#include "ArcFillDrawerJoGL.hxx"

extern "C"
{
#include "GetProperty.h"
}

namespace sciGraphics
{

/*------------------------------------------------------------------------------------------*/
ArcFillDrawerJoGL::ArcFillDrawerJoGL( DrawableArc * arc )
  : DrawArcStrategy(arc), DrawableObjectJoGL(arc)
{
  
}
/*------------------------------------------------------------------------------------------*/
ArcFillDrawerJoGL::~ArcFillDrawerJoGL(void)
{
  
}
/*------------------------------------------------------------------------------------------*/
void ArcFillDrawerJoGL::drawArc( void )
{
  sciPointObj * pObj = m_pDrawed->getDrawedObject();
  initializeDrawing() ;

  // set the line parameters
  getFillDrawerJavaMapper()->setBackColor(sciGetGraphicContext(pObj)->backgroundcolor) ;

  // get the data of thar arc
  double center[3];
  double semiMinorAxis[3];
  double semiMajorAxis[3];
  double startAngle;
  double endAngle;

  m_pDrawed->getArcRepresentation(center, semiMinorAxis, semiMajorAxis, startAngle, endAngle ) ;

  // display the rectangle
  getFillDrawerJavaMapper()->drawArc(center[0]       , center[1]       , center[2]       ,
                                     semiMinorAxis[0], semiMinorAxis[1], semiMinorAxis[2],
                                     semiMajorAxis[0], semiMajorAxis[1], semiMajorAxis[2],
                                     startAngle      , endAngle);
  endDrawing() ;
}
/*------------------------------------------------------------------------------------------*/
void ArcFillDrawerJoGL::showArc( void )
{
  show();
}
/*------------------------------------------------------------------------------------------*/
ArcFillDrawerJavaMapper * ArcFillDrawerJoGL::getFillDrawerJavaMapper(void)
{
  return dynamic_cast<ArcFillDrawerJavaMapper *>(getJavaMapper());
}
/*------------------------------------------------------------------------------------------*/

}
