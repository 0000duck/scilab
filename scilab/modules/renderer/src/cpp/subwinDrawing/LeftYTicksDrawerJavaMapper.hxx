/*------------------------------------------------------------------------*/
/* file: LeftYTicksDrawerJavaMapper.hxx                                   */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing java methods needed by YTicksDrawerJoGL        */
/*------------------------------------------------------------------------*/

#ifndef _LEFT_Y_TICKS_DRAWER_JAVA_MAPPER_HXX_
#define _LEFT_Y_TICKS_DRAWER_JAVA_MAPPER_HXX_

#include "TicksDrawerJavaMapper.hxx"
#include "LeftYTicksDrawerGL.hxx"


namespace sciGraphics
{

/**
* Contains mapping of java method used by YTicksDrawerJoGL 
*/
class LeftYTicksDrawerJavaMapper : public virtual TicksDrawerJavaMapper
{
public:

  LeftYTicksDrawerJavaMapper(void);

  virtual ~LeftYTicksDrawerJavaMapper(void);
  /*----------------------------------------------------------------------*/
  // Inherited from DrawableObjectJavaMapper
  virtual void display(void);

  virtual void initializeDrawing(int figureIndex);
  virtual void endDrawing(void);

  virtual void show(int figureIndex);

  virtual void destroy(int figureIndex);

  virtual void setFigureIndex(int figureIndex);
  /*----------------------------------------------------------------------*/
  // Inherited from TicksDrawer
  virtual double drawTicks(const double ticksPositions[], char * ticksLabels[],
                           int nbTicks, const double subticksPositions[], int nbSubticks);

  virtual bool checkTicks(const double ticksPositions[], char * ticksLabels[], int nbTicks);

  virtual double drawTicks(const double ticksPositions[], char * ticksLabels[], char * labelsExponents[],
                           int nbTicks, const double subticksPositions[], int nbSubticks);

  virtual bool checkTicks(const double ticksPositions[], char * ticksLabels[],
                          char * labelsExponents[], int nbTicks);

  virtual void setAxesBounds(double xMin, double xMax,
                             double yMin, double yMax,
                             double zMin, double zMax);

  virtual void setAxisParamerters(int lineStyle, float lineWidth, int lineColor,
                                  int fontType, double fontSize, int fontColor);
  /*----------------------------------------------------------------------*/

protected:

  /**
   * Giws generated wrapper
   */
  org_scilab_modules_renderer_subwinDrawing::LeftYTicksDrawerGL * m_pJavaObject;

};

}

#endif /* _LEFT_Y_TICKS_DRAWER_JAVA_MAPPER_HXX_ */
