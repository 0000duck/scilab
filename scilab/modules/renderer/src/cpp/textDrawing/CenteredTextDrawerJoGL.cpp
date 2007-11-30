/*------------------------------------------------------------------------*/
/* file: CenteredTextDrawerJoGL.hxx                                       */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class Drawing the text content of a text object with centered   */
/*        text box mode option                                            */
/*------------------------------------------------------------------------*/

#include "CenteredTextDrawerJoGL.hxx"
#include "CenteredTextDrawerJavaMapper.hxx"

extern "C"
{
#include "GetProperty.h"
#include "StringMatrix.h"
}

namespace sciGraphics
{
/*---------------------------------------------------------------------------------*/
CenteredTextDrawerJoGL::CenteredTextDrawerJoGL(DrawableText * text)
  : TextContentDrawerJoGL(text)
{
  setJavaMapper(new CenteredTextDrawerJavaMapper());
}
/*---------------------------------------------------------------------------------*/
CenteredTextDrawerJoGL::~CenteredTextDrawerJoGL(void)
{

}
/*---------------------------------------------------------------------------------*/
void CenteredTextDrawerJoGL::setDrawerParameters(void)
{
  sciPointObj * pObj = m_pDrawed->getDrawedObject();
  

  // get text position.
  double textPos[3];
  sciGetTextPos(pObj, textPos);

  // get box size in user coordinates
  double boxWidth;
  double boxHeight;
  sciGetUserSize(pObj, &boxWidth, &boxHeight);

  // convert the user lengths to pixel ones.
  int pixWidth;
  int pixHeight;
  getPixelLength(sciGetParentSubwin(pObj), textPos, boxWidth, boxHeight, &pixWidth, &pixHeight);

  getCenteredTextDrawerJavaMapper()->setTextParameters(sciGetAlignment(pObj), sciGetFontContext(pObj)->foregroundcolor,
                                                       sciGetFontStyle(pObj), sciGetFontSize(pObj), sciGetFontOrientation(pObj),
                                                       pixWidth, pixHeight);

  StringMatrix * textMatrix = sciGetText(pObj);
  getCenteredTextDrawerJavaMapper()->setTextContent(getStrMatData(textMatrix), getMatNbRow(textMatrix), getMatNbCol(textMatrix));

  getTextDisplayPos(textPos);
  getCenteredTextDrawerJavaMapper()->setCenterPosition(textPos[0], textPos[1], textPos[2]);
}
/*---------------------------------------------------------------------------------*/
CenteredTextDrawerJavaMapper * CenteredTextDrawerJoGL::getCenteredTextDrawerJavaMapper(void)
{
  return dynamic_cast<CenteredTextDrawerJavaMapper *>(getJavaMapper());
}
/*---------------------------------------------------------------------------------*/

}
