/*------------------------------------------------------------------------*/
/* file: YAxesDrawerJavaMapper.cpp                                        */
/* Copyright INRIA 2008                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing java methods needed by YAxesDrawerJoGL         */
/*------------------------------------------------------------------------*/

#include "YAxesDrawerJavaMapper.hxx"

extern "C"
{
#include "getScilabJavaVM.h"
}

namespace sciGraphics
{

/*--------------------------------------------------------------------------*/
YAxesDrawerJavaMapper::YAxesDrawerJavaMapper(void)
{
  m_pJavaObject = new org_scilab_modules_renderer_axesDrawing::YAxesDrawerGL(getScilabJavaVM());
}
/*--------------------------------------------------------------------------*/
YAxesDrawerJavaMapper::~YAxesDrawerJavaMapper(void)
{
  delete m_pJavaObject;
  m_pJavaObject = NULL;
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::display(void)
{
  m_pJavaObject->display();
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::initializeDrawing(int figureIndex)
{
  m_pJavaObject->initializeDrawing(figureIndex);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::endDrawing(void)
{
  m_pJavaObject->endDrawing();
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::show(int figureIndex)
{
  m_pJavaObject->show(figureIndex);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::destroy(int parentFigureIndex)
{
  m_pJavaObject->destroy(parentFigureIndex);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setFigureIndex(int figureIndex)
{
  m_pJavaObject->setFigureIndex(figureIndex);
}
/*--------------------------------------------------------------------------*/
double YAxesDrawerJavaMapper::drawTicks(const double ticksPositions[], char * ticksLabels[],
                                         int nbTicks, const double subticksPositions[], int nbSubticks)
{
  return m_pJavaObject->drawTicks((double *)ticksPositions, nbTicks,
                                  ticksLabels, nbTicks,
                                  (double *)subticksPositions, nbSubticks);
}
/*--------------------------------------------------------------------------*/
bool YAxesDrawerJavaMapper::checkTicks(const double ticksPositions[], char * ticksLabels[], int nbTicks)
{
  return m_pJavaObject->checkTicks((double *)ticksPositions, nbTicks,
                                   ticksLabels, nbTicks);
}
/*--------------------------------------------------------------------------*/
double YAxesDrawerJavaMapper::drawTicks(const double ticksPositions[], char * ticksLabels[],
                                         char * labelsExponents[], int nbTicks,
                                         const double subticksPositions[], int nbSubticks)
{
  return m_pJavaObject->drawTicks((double *)ticksPositions, nbTicks,
                                  ticksLabels, nbTicks,
                                  labelsExponents, nbTicks,
                                 (double *)subticksPositions, nbSubticks);
}
/*--------------------------------------------------------------------------*/
bool YAxesDrawerJavaMapper::checkTicks(const double ticksPositions[], char * ticksLabels[],
                                        char * labelsExponents[], int nbTicks)
{

  return m_pJavaObject->checkTicks((double *)ticksPositions, nbTicks,
                                   ticksLabels, nbTicks,
                                   labelsExponents, nbTicks);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setAxesBounds(double xMin, double xMax,
                                           double yMin, double yMax,
                                           double zMin, double zMax)
{
  m_pJavaObject->setAxesBounds(xMin, xMax, yMin, yMax, zMin, zMax);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setAxisParamerters(int lineStyle, float lineWidth, int lineColor,
                                                int fontType, double fontSize, int fontColor)
{
  m_pJavaObject->setAxisParameters(lineStyle, lineWidth, lineColor,
                                   fontType, fontSize, fontColor);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setConstantCoordinates(double xCoordinate, double zCoordinate)
{
  m_pJavaObject->setConstantCoordinates(xCoordinate, zCoordinate);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setTicksDirection(char dir)
{
  // giws doesn't not support char yet.
  // so create a C string with 1 character
  char dirString[2] = {dir, 0};
  m_pJavaObject->setTicksDirection(dirString);
}
/*--------------------------------------------------------------------------*/
void YAxesDrawerJavaMapper::setAxisLineDrawing(bool drawAxisLine)
{
  m_pJavaObject->setAxisLineDrawing(drawAxisLine);
}
/*--------------------------------------------------------------------------*/
}
