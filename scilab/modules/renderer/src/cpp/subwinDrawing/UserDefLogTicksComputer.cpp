/*------------------------------------------------------------------------*/
/* file: UserDefLogTicksComputer.cpp                                      */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Compute ticks from ticks given by the user in logarithmic mode  */
/*------------------------------------------------------------------------*/

#include <math.h>

#include "UserDefLogTicksComputer.hxx"
#include "BasicAlgos.hxx"

namespace sciGraphics
{
/*------------------------------------------------------------------------------------------*/
UserDefLogTicksComputer::UserDefLogTicksComputer(DrawableSubwin * subwin)
 : UserDefinedTicksComputer(subwin)
{

}
/*------------------------------------------------------------------------------------------*/
UserDefLogTicksComputer::~UserDefLogTicksComputer(void)
{

}
/*------------------------------------------------------------------------------------------*/
void UserDefLogTicksComputer::getTicksPosition(double positions[], char * labels[], char * labelsExponents[])
{
  for (int i = 0; i < m_iNbUserTicks; i++)
  {
    positions[i] = m_aUserTicksPositions[i];
  }
  BasicAlgos::stringArrayCopy(labels, m_aUserTicksLabels, m_iNbUserTicks);
}
/*------------------------------------------------------------------------------------------*/
void UserDefLogTicksComputer::getSubticksPosition(const double ticksPositions[], int nbTicks,
                                                  double subTickspositions[])
{
  /*    |              |              |    */
  /* ___|____|____|____|____|____|____|___ */
  /*   t0             t1             t2   */

  // draw only between two ticks, so skip last one
  for (int i = 0; i < nbTicks - 1; i++)
  {
    // decompose interval in nbsubtics parts
    double prevTick = ticksPositions[i];
    double nextTick = ticksPositions[i + 1];
    for (int j = 0; j < m_iNbSubticks; j++)
    {
      // positions are given in logarithmic mode
      // so we need to switch ticks positions in normal mode
      // and then come back to log mode
      // the expression is then s = log(exp(t[i]) + (exp(t[i+1]) - exp(t[i])) * (j+1) / (nb+1)
      // and simplified
      subTickspositions[j + m_iNbSubticks * i]
         = prevTick + log10(1.0 + (exp10(nextTick - prevTick) - 1.0) * (j + 1.0) / (m_iNbSubticks + 1.0));
    }
  }
}
/*------------------------------------------------------------------------------------------*/
}
