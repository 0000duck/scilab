/*------------------------------------------------------------------------
 *    Graphic library 
 *    Copyright INRIA
 *    newGraph Library header
 *    Matthieu PHILIPPE,   INRIA 2001-2002
 *    Djalel ABDEMOUCHE,   INRIA 2002-2004
 *    Fabrice Leray,       INRIA 2004-2006
 *    Jean-Baptiste SILVY, INRIA 2005-xxxx
 *    Comment:
 *    -This file contains all functions used to SET the properties of graphics
 *    objects.
 *    - there are two kinds of functions : the sciInit*** which only set an object
 *      property and sciSet*** which do the same work but check before if it is
 *      necessary to do so.
 *    - The returning status of each functions is as follow :
 *      0 for correct execution, 1 if no change was made
 *      and -1 if an error occured.
 --------------------------------------------------------------------------*/


#include "ObjectStructure.h"
#include "HandleManagement.h"


#ifndef __SCI_SET_PROPERTY__
#define __SCI_SET_PROPERTY__

void Obj_RedrawNewAngle(sciPointObj *psubwin,double theta,double alpha); /* SET  */

int sciSetEntityType (sciPointObj * pobj, sciEntityType value); /* SET */
int sciSetColormap (sciPointObj * pobj, double *rgbmat,
			   integer m, integer n); /* SET */
int sciInitNumColors( sciPointObj * pobj, int numcolors ) ; /* SET */
int sciSetNumColors ( sciPointObj * pobj, int numcolors ) ; /* SET */

int sciSetGoodIndex(sciPointObj * pobj, int colorindex);  /* SET */
void sciRecursiveUpdateBaW(sciPointObj *pobj, int old_m, int m);  /* SET */
int sciUpdateBaW (sciPointObj * pobj, int flag, int value ) ; /* SET */

int  sciInitMdlBackground( sciPointObj * pobj, int colorIndex ) ;
int sciInitBackground( sciPointObj * pobj, int colorindex ) ;
int sciSetBackground ( sciPointObj * pobj, int colorindex ) ; /* SET */

int sciInitMdlForeground( sciPointObj * pObj, int colorIndex ) ;
int sciInitForeground( sciPointObj * pobj, int colorindex ) ;
int sciSetForeground ( sciPointObj * pobj, int colorindex ) ; /* SET */

int sciInitLineWidth( sciPointObj * pobj, int linewidth ) ;
int sciSetLineWidth ( sciPointObj * pobj, int linewidth ) ;  /* SET */

int sciInitIsLine(sciPointObj * pobj, BOOL isline);
int sciSetIsLine (sciPointObj * pobj, BOOL isline);  /* SET */

int sciInitLineStyle( sciPointObj * pobj, int linestyle ) ;
int sciSetLineStyle ( sciPointObj * pobj, int linestyle ) ; /* SET */

int sciInitIsMark(sciPointObj * pobj, BOOL ismark);  /* SET */
int sciSetIsMark (sciPointObj * pobj, BOOL ismark);  /* SET */

int sciInitIsFilled(sciPointObj * pobj, BOOL isfilled);
int sciSetIsFilled (sciPointObj * pobj, BOOL isfilled);  /* SET */

int sciInitMarkStyle(sciPointObj * pobj, int markstyle);
int sciSetMarkStyle (sciPointObj * pobj, int markstyle); /* SET */

int sciInitMarkSize(sciPointObj * pobj, int marksize);
int sciSetMarkSize (sciPointObj * pobj, int marksize); /* SET */

int sciInitMarkSizeUnit(sciPointObj * pobj, int marksizeunit);
int sciSetMarkSizeUnit (sciPointObj * pobj, int marksizeunit); /* SET */

int sciInitMarkBackground(sciPointObj * pobj, int colorindex);
int sciSetMarkBackground (sciPointObj * pobj, int colorindex);  /* SET */

int sciInitMarkForeground(sciPointObj * pobj, int colorindex);
int sciSetMarkForeground (sciPointObj * pobj, int colorindex);  /* SET */

int sciInitBoxType( sciPointObj * pobj, EAxesBoxType type ) ;
int sciSetBoxType ( sciPointObj * pobj, EAxesBoxType type ) ; /* SET */

int sciInitIsBoxed(sciPointObj * pobj, BOOL isboxed);
int sciSetIsBoxed (sciPointObj * pobj, BOOL isboxed); /* SET */

/* Text Functions */
int sciInitFontSize(sciPointObj * pobj, double fontSize); /* SET */
int sciSetFontSize (sciPointObj * pobj, double fontSize); /* SET */

int sciInitFontOrientation(sciPointObj * pobj, double textorientation); /* SET */
int sciSetFontOrientation (sciPointObj * pobj, double textorientation); /* SET */

int sciSetStrings( sciPointObj * pobj, const StringMatrix * pStrings ) ; /* SET */
int sciSetText (   sciPointObj * pobj, char ** text, int nbRow, int nbCol ) ; /* SET */

int sciInitFontBackground(sciPointObj * pobj, int color);
int sciSetFontBackground (sciPointObj * pobj, int color); /* SET */

int sciInitFontForeground(sciPointObj * pobj, int colorindex ) ;
int sciSetFontForeground (sciPointObj * pobj, int colorindex ) ; /* SET */

int sciInitFontStyle(sciPointObj * pobj, int iAttributes ) ;
int sciSetFontStyle (sciPointObj * pobj, int iAttributes ) ; /* SET */

int sciSetFontName (sciPointObj * pobj, char pfontname[], int n); /* SET */

/*Title Functions */
int sciSetTitlePos (sciPointObj * pobj, int x, int y); /* SET */
int sciSetTitlePlace (sciPointObj * pobj, sciTitlePlace place); /* SET */

/* Legend */
int sciInitLegendPlace(sciPointObj * pobj, sciLegendPlace place);
int sciSetLegendPlace (sciPointObj * pobj, sciLegendPlace place); /* SET */

int sciInitLegendPos(sciPointObj * pobj, int x, int y);
int sciSetLegendPos (sciPointObj * pobj, int x, int y); /* SET */

/* GMODE */
int sciInitIsClipping(sciPointObj * pobj, int value) ;
int sciSetIsClipping (sciPointObj * pobj, int value); /* SET */

int sciSetClipping (sciPointObj * pobj, double pclip[4] ); /* SET */

int sciInitHighLight(sciPointObj * pobj, BOOL value);
int sciSetHighLight (sciPointObj * pobj, BOOL value); /* SET */

int sciInitAddPlot (sciPointObj * pobj, BOOL value);
int sciSetAddPlot (sciPointObj * pobj, BOOL value); /* SET */

int sciInitAutoScale(sciPointObj * pobj, BOOL value);
int sciSetAutoScale (sciPointObj * pobj, BOOL value); /* SET */

int sciInitZooming(sciPointObj * pobj, BOOL value);
int sciSetZooming (sciPointObj * pobj, BOOL value); /* SET */

int sciInitXorMode(sciPointObj * pobj, int value);
int sciSetXorMode (sciPointObj * pobj, int value); /* SET */

int sciInitVisibility (sciPointObj * pobj, BOOL value);
int sciSetVisibility (sciPointObj * pobj, BOOL value); /* SET */

int sciInitResize(sciPointObj * pobj, BOOL value);
int sciSetResize (sciPointObj * pobj, BOOL value); /* SET */

int sciSetDefaultValues (void); /* SET */


/* Window Functions */
int sciSetName (sciPointObj * pobj, char *pvalue, int length); /* SET */
int sciInitNum( sciPointObj * pobj, int value ) ;
int sciSetNum ( sciPointObj * pobj, int value ) ; /* SET */

int sciInitDimension( sciPointObj * pobj, int newWidth, int newHeight ) ;
int sciSetDimension(  sciPointObj * pobj, int newWidth, int newHeight ) ; /* SET */

int sciInitWindowDim( sciPointObj * pobj, int newWidth, int newHeight ) ;
int sciSetWindowDim(  sciPointObj * pobj, int newWidth, int newHeight ) ; /* SET */

int sciInitScreenPosition(sciPointObj * pobj, int pposx, int pposy);
int sciSetScreenPosition( sciPointObj * pobj, int pposx, int pposy); /* SET */

int sciInitFigureIconify(sciPointObj * pobj, BOOL value);
int sciSetFigureIconify( sciPointObj * pobj, BOOL value); /* SET */

int sciInitSubWindowPos(sciPointObj * pobj, int *x, int *y);
int sciSetSubWindowPos( sciPointObj * pobj, int *x, int *y); /* SET */

void sciSelectFirstSubwin( sciPointObj * parentFigure ) ; /* SET */

int sciInitSelectedSubWin (sciPointObj * psubwinobj);
int sciSetSelectedSubWin (sciPointObj * psubwinobj); /* SET */

int sciSetOriginalSubWin (sciPointObj * pfigure, sciPointObj * psubwin); /* SET */

int sciSetReplay (BOOL value); /* SET */
/* int sciSetHDC (sciPointObj * pobj); /\* SET *\/ /\* unused?? *\/ */
int sciSetPoint(sciPointObj * pthis, double *tab, int *numrow, int *numcol); /* SET */

int sciSetdrawmode(BOOL mode); /* SET */
int sciSwitchWindow(int winnum); /* SET */

int sciInitUsedWindow( int winNum ) ; /* SET */
int sciSetUsedWindow( int winNum ) ; /* SET */

int sciSetInterpVector(sciPointObj * pobj, int size, int * value);

int sciInitAutoRotation( sciPointObj * pObj, BOOL value ) ;
int sciSetAutoRotation ( sciPointObj * pObj, BOOL value ) ;

int sciInitAutoPosition( sciPointObj * pObj, BOOL value ) ;
int sciSetAutoPosition ( sciPointObj * pObj, BOOL value ) ;

int sciInitAutoSize( sciPointObj * pObj, BOOL autoSize ) ;
int sciSetAutoSize(  sciPointObj * pObj, BOOL autoSize ) ;

int sciInitAlignment( sciPointObj * pObj, sciTextAlignment align ) ;
int sciSetAlignment(  sciPointObj * pObj, sciTextAlignment align ) ;

int sciInitUserSize( sciPointObj * pObj, double width, double height ) ;
int sciSetUserSize(  sciPointObj * pObj, double width, double height ) ;

int sciInitCenterPos( sciPointObj * pObj, BOOL newCP ) ;
int sciSetCenterPos(  sciPointObj * pObj, BOOL newCP ) ;

int sciInitIs3d( sciPointObj * pObj, BOOL is3d ) ;
int sciSetIs3d(  sciPointObj * pObj, BOOL is3d ) ;

int sciInitSelectedObject( sciPointObj * pObj ) ;
int sciSetSelectObject(    sciPointObj * pObj ) ;

int sciInitHiddenColor( sciPointObj * pObj, int newColor ) ;
int sciSetHiddenColor(  sciPointObj * pObj, int newColor ) ;

int sciInitHiddenAxisColor( sciPointObj * pObj, int newColor ) ;
int sciSetHiddenAxisColor( sciPointObj * pObj, int newColor ) ;

int setSubWinAngles( sciPointObj *psubwin, double theta, double alpha );
int sciInitdrawmode( BOOL mode );

int sciInitGraphicsStyle( sciPointObj * pobj, BOOL value );

int sciInitGridStyle( sciPointObj * pObj, int xStyle, int yStyle, int zStyle ) ; 
int sciSetGridStyle( sciPointObj * pObj, int xStyle, int yStyle, int zStyle ) ; /* SET */

int sciInitViewport( sciPointObj * pObj, int xSize, int ySize ) ;
int sciSetViewport(  sciPointObj * pObj, int xSize, int ySize ) ; /* SET */

int sciSetInfoMessage( sciPointObj * pObj, const char * newMessage ) ; /* SET */

int sciInitEventHandler( sciPointObj * pObj, char * name ) ;
int sciSetEventHandler(  sciPointObj * pObj, char * name ) ;

int sciInitIsEventHandlerEnable( sciPointObj * pObj, BOOL enable ) ;
int sciSetIsEventHandlerEnable(  sciPointObj * pObj, BOOL enable ) ;

int sciSetSelectedObject( sciPointObj * pObj ) ;
int sciSetDataBounds( sciPointObj * pObj, double bounds[6] ) ; /* SET */
int sciSetRealDataBounds(sciPointObj * pObj, const double bounds[6]); /* SET */

int sciInitViewingAngles( sciPointObj * pObj, double alpha, double theta) ;
int sciSetViewingAngles( sciPointObj * pObj, double alpha, double theta); /* SET */

int setInfoMessageWithRotationAngles(sciPointObj * pFigure, double alpha, double theta);

int sciInitPixmapMode(sciPointObj * pObj, BOOL onOrOff);
int sciSetPixmapMode(sciPointObj * pObj, BOOL onOrOff); /* SET */

int sciInitTextPos( sciPointObj * pObj, double posX, double posY, double posZ);
int sciSetTextPos( sciPointObj * pObj, double posX, double posY, double posZ);

int sciInitLogFlags(sciPointObj * pObj, char logFlags[3]);
int sciSetLogFlags(sciPointObj * pObj, char logFlags[3]) ; /* SET */

int sciInitAutoTicks(sciPointObj * pObj, BOOL autoTicksX, BOOL autoTicksY, BOOL autoTicksZ);
int sciSetAutoTicks(sciPointObj * pObj, BOOL autoTicksX, BOOL autoTicksY, BOOL autoTicksZ); /* SET */

int sciSetRenderingEnable(sciPointObj * pObj, BOOL enable); /* SET */

int sciSetZoomBox(sciPointObj * pObj, const double zoomBox[6]); /* SET */

BOOL sciCheckColorIndex(sciPointObj * pObj, int colorIndex);

/*---------------------------------------------------------------------------*/
/* return 0 if the string contains any % character, 1 if a %d has been found */
/* and -1 otherwise. */
int checkPercent( char * string ) ;
/*---------------------------------------------------------------------------*/

#endif /* __SCI_SET_PROPERTY__ */
