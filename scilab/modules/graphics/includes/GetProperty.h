/*------------------------------------------------------------------------
 *    Graphic library 
 *    Copyright INRIA
 *    newGraph Library header
 *    Matthieu PHILIPPE,   INRIA 2001-2002
 *    Djalel ABDEMOUCHE,   INRIA 2002-2004
 *    Fabrice Leray,       INRIA 2004-2006
 *    Jean-Baptiste Silvy, INRIA 2005-xxxx
 *    Comment:
 *    This file contains all functions used to GET the properties of graphics
 *    objects.
 --------------------------------------------------------------------------*/



#ifndef __SCI_GET_PROPERTY__
#define __SCI_GET_PROPERTY__



#include "ObjectStructure.h"
#include "HandleManagement.h"
#include "StringMatrix.h"

void *sciGetPointerToFeature (sciPointObj * pobj); /* GET */
void sciGetPointerToUserData (sciPointObj * pobj,int ***user_data_ptr, int **size_ptr); /* GET */
sciEntityType sciGetEntityType (sciPointObj * pobj);  /* GET */
char *sciGetCharEntityType (sciPointObj * pobj);  /* GET */

/* Graphic Context Functions */
sciGraphicContext *sciGetGraphicContext (sciPointObj * pobj); /* GET */
int sciGetNumColors (sciPointObj * pobj); /* GET */
int sciGetColormap (sciPointObj * pobj, double rgbmat[] ); /* GET */
int sciGetNumColors( sciPointObj * pobj ) ; /* GET */
int sciGetGoodIndex(sciPointObj * pobj, int colorindex);  /* GET */

int sciGetForegroundToDisplay (sciPointObj * pobj); /* GET */
int sciGetBackgroundToDisplay (sciPointObj * pobj); /* GET */

int sciGetBackground (sciPointObj * pobj); /* GET */
int sciGetForeground (sciPointObj * pobj); /* GET */
int sciGetLineWidth (sciPointObj * pobj); /* GET */
BOOL sciGetIsLine (sciPointObj * pobj); /* GET */
int sciGetLineStyle (sciPointObj * pobj); /* GET */
BOOL sciGetIsMark (sciPointObj * pobj); /* GET */
BOOL sciGetIsFilled (sciPointObj * pobj); /* GET */
EAxesBoxType sciGetBoxType( sciPointObj * pobj ) ; /* GET */
BOOL sciGetIsBoxed (sciPointObj * pobj); /* GET */
int sciGetMarkStyle (sciPointObj * pobj); /* GET */
int sciGetMarkSize (sciPointObj * pobj); /* GET */
int sciGetMarkSizeUnit (sciPointObj * pobj); /* GET */
int sciGetFillStyle (sciPointObj * pobj); /* GET */

/* Text Functions */
sciFont *sciGetFontContext (sciPointObj * pobj);  /* GET */
int sciGetFontDeciWidth (sciPointObj * pobj); /* GET */
int sciGetFontOrientation (sciPointObj * pobj); /* GET */
StringMatrix * sciGetText (sciPointObj * pobj); /* GET */
void sciGetTextSize( sciPointObj * pobj, int * nbRow, int * nbCol ) ; /* GET */
unsigned int sciGetTextLength (sciPointObj * pobj); /* GET */

int sciGetFontBackground (sciPointObj * pobj); /* GET */
int sciGetFontForeground (sciPointObj * pobj); /* GET */
int sciGetMarkBackground (sciPointObj * pobj); /* GET */
int sciGetMarkForeground (sciPointObj * pobj); /* GET */
/* F.Leray 09.04.04*/
int sciGetFontBackgroundToDisplay (sciPointObj * pobj); /* GET */
int sciGetFontForegroundToDisplay (sciPointObj * pobj); /* GET */
int sciGetMarkBackgroundToDisplay (sciPointObj * pobj); /* GET */
int sciGetMarkForegroundToDisplay (sciPointObj * pobj); /* GET */

int sciGetFontStyle (sciPointObj * pobj); /* GET */
char *sciGetFontName (sciPointObj * pobj); /* GET */
unsigned int sciGetFontNameLength (sciPointObj * pobj); /* GET */
double sciGetTextPosX (sciPointObj * pobj); /* GET */
double sciGetTextPosY (sciPointObj * pobj); /* GET */
double sciGetTextPosWidth (sciPointObj * pobj); /* GET */
double sciGetTextPosHeight (sciPointObj * pobj); /* GET */

/*Title Functions */
POINT2D sciGetTitlePos (sciPointObj * pobj); /* GET */
sciTitlePlace sciGetTitlePlace (sciPointObj * pobj); /* GET */

/* Legend */
sciLegendPlace sciGetLegendPlace (sciPointObj * pobj);
POINT2D sciGetLegendPos (sciPointObj * pobj);

/* Figure / Subwin main functions */
sciPointObj *sciGetParentFigure (sciPointObj * pobj); /* GET */
sciPointObj *sciGetParentSubwin (sciPointObj * pobj); /* GET */
int sciGetNumFigure (sciPointObj * pobj); /* GET */

/* GMODE */
scigMode *sciGetGraphicMode (sciPointObj * pobj);  /* GET */
int sciGetIsClipRegionValuated (sciPointObj * pobj);
int sciGetIsClipping (sciPointObj * pobj); /* GET */
double *sciGetClipping (sciPointObj * pobj); /* GET */
BOOL sciGetHighLight (sciPointObj * pobj);  /* GET */
BOOL sciGetAddPlot (sciPointObj * pobj);  /* GET */
BOOL sciGetAutoScale (sciPointObj * pobj);  /* GET */
BOOL sciGetZooming (sciPointObj * pobj);  /* GET */
int sciGetXorMode (sciPointObj * pobj);  /* GET */
BOOL sciGetRealVisibility (sciPointObj * pobj) ; /* GET */
BOOL sciGetVisibility (sciPointObj * pobj);  /* GET */
BOOL sciGetResize (sciPointObj * pobj);  /* GET */


/* Window Functions */
char *sciGetName (sciPointObj * pobj);  /* GET */
int sciGetNameLength (sciPointObj * pobj);  /* GET */
int sciGetNum (sciPointObj * pobj);  /* GET */
int sciGetWidth (sciPointObj * pobj);   /* GET */
int sciGetHeight (sciPointObj * pobj);  /* GET */
void sciGetDim( sciPointObj * pobj, int * pWidth, int * pHeight ) ; /* GET */
int sciGetWindowWidth(sciPointObj * pObj) ; /* GET */
int sciGetWindowHeight(sciPointObj * pObj) ; /* GET */
BOOL sciGetIsFigureIconified (sciPointObj * pobj);  /* GET */
int sciGetSubwindowPosX (sciPointObj * pobj);  /* GET */
int sciGetSubwindowPosY (sciPointObj * pobj);  /* GET */
sciPointObj *sciIsExistingSubWin (double *WRect); /* GET */ /* WARNING special case here */
int sciGetScrollPosV (sciPointObj * pobj);  /* GET */
int sciGetScrollPosH (sciPointObj * pobj);  /* GET */

BOOL sciGetReplay (void); /* GET */


double *sciGetPoint (sciPointObj * pthis, int *num, int *numco); /* GET */
sciPointObj *sciGetObjClicked (sciPointObj *pthis,int x, int y); /* GET */ /* unused */
BOOL sciIsClicked(sciPointObj *pthis,int x, int y);  /* GET */

BOOL sciGetdrawmode (sciPointObj *pobj); /* GET */
sciPointObj *sciGetAxes (sciPointObj *pparentfigure,sciPointObj *psubwin); /* GET */


int sciType (char *marker, sciPointObj *pobj); /* GET */

unsigned int sciGetFontNameLength (sciPointObj * pobj); /* GET */

sciPointObj *sciGetSurface(sciPointObj *psubwin); /* GET */

sciPointObj *CheckClickedSubwin(integer x, integer y); /* GET */

/* BOOL GetIsAxes(sciPointObj *psubwin); /\* GET *\/ */
BOOL GetIsAxes2D(sciPointObj *psubwin); /* GET */

int CheckForCompound (long *tabpointobj, int number); /* GET */

/* UNUSED ? */
sciPointObj *sciGetOriginalSubWin (sciPointObj * pfigure);
HMENU sciGethPopMenu (sciPointObj * pthis);

int *sciGetInterpVector(sciPointObj * pobj);
int sciGetPosition (sciPointObj * pobj, double *x, double *y);

BOOL sciGetAutoRotation ( sciPointObj * pObj ) ;
BOOL sciGetAutoPosition ( sciPointObj * pObj ) ;

BOOL sciGetCenterPos( sciPointObj * pObj ) ;

BOOL sciGetIs3d( sciPointObj * pObj ) ;

/**
 * for a subwindow object, return if the its labels (x,y,z) are all
 *       empty or not.
 * @param pObj the subwindow.
 */
BOOL sciGetLegendDefined( sciPointObj * pObj ) ;

BOOL sciGetAutoSize( sciPointObj * pObj ) ;
sciTextAlignment sciGetAlignment( sciPointObj * pObj ) ;
void sciGetUserSize( sciPointObj * pObj, double * width, double * height ) ;

int sciGetNbChildren( sciPointObj * pObj ) ; /* GET */

BOOL sciGetIsAccessibleChild( sciPointObj * pObj ) ; /* GET */

int sciGetNbAccessibleChildren( sciPointObj * pObj ) ; /* GET */

BOOL GetHandleVisibilityOnUimenu( sciPointObj * pobj ) ; /* GET */

int sciGetNbTypedObjects( sciPointObj * pObj, sciEntityType type ) ;

int sciGetHiddenColor( sciPointObj * pObj ) ;

BOOL sciGetIsAutoDrawable( sciPointObj * pobj ) ;

void sciGetGridStyle( sciPointObj * pObj, int * xStyle, int * yStyle, int * zStyle ) ;

void sciGetViewport( sciPointObj * pObj, int * xSize, int * ySize ) ;

char * sciGetInfoMessage( sciPointObj * pObj ) ;

int sciGetInfoMessageLength( sciPointObj * pObj ) ;

void sciGetScreenPosition( sciPointObj * pObj, int * posX, int * posY ) ;

BOOL sciGetIsEventHandlerEnable( sciPointObj * pObj ) ;
char * sciGetEventHandler( sciPointObj * pObj ) ;

double * sciGetAxesBounds( sciPointObj * pObj ) ;
double * sciGetMargins( sciPointObj * pObj ) ;

void sciGetRealDataBounds( sciPointObj * pObj, double bounds[6] ) ; /* GET */
void sciGetDataBounds( sciPointObj * pObj, double bounds[6] ) ; /* GET */

void sciGetViewingAngles( sciPointObj * pObj, double * alpha, double * theta) ; /* GET */

int sciGetWhiteColorIndex(sciPointObj * pObj); /* GET */
int sciGetBlackColorIndex(sciPointObj * pObj); /* GET */

void sciGetLogFlags(sciPointObj * pObj, char flags[3]); /* GET */

BOOL sciGetPixmapMode(sciPointObj * pObj); /* GET */

int sciGetNbPoints(sciPointObj * pObj); /* GET */

#endif /* __SCI_GET_PROPERTY__ */
