/*------------------------------------------------------------------------*/
/* file: sci_draw.h                                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for draw routine                                      */
/*------------------------------------------------------------------------*/

#include "sci_draw.h"
#include "GetProperty.h"
#include "SetProperty.h"
#include "DrawObjects.h"
#include "Graphics.h"
#include "BuildObjects.h"
#include "HandleManagement.h"

/*-----------------------------------------------------------------------------------*/
int sci_draw( char * fname, unsigned long fname_len )
{ 
  unsigned long hdl;
  sciPointObj *pobj, *psubwin, *tmpsubwin;
  integer m,n,l,lw;


  SciWin() ;
  CheckRhs(0,1) ;
  CheckLhs(0,1) ;
  if ( version_flag() == 0 )
  {
    if (Rhs == 0)
    {
      pobj = sciGetCurrentObj() ;
    }
    else
    {
      GetRhsVar( 1, "h", &m, &n, &l ) ; 
      if (m!=1||n!=1)
      {
        lw = 1 + Top - Rhs ;
        C2F(overload)(&lw,"draw",4);
        return 0;
      }
      hdl = (unsigned long)*hstk(l);            /* Puts the value of the Handle to hdl */ 
      pobj = sciGetPointerFromHandle(hdl);   
    }
    if (pobj != NULL )
    {  
      tmpsubwin = sciGetSelectedSubWin (sciGetCurrentFigure ()); 
      psubwin = sciGetParentSubwin(pobj);
      if ( psubwin != NULL )
      {
        sciSetSelectedSubWin(psubwin); 
        set_scale ("tttftt", pSUBWIN_FEATURE (psubwin)->WRect, 
                             pSUBWIN_FEATURE (psubwin)->FRect,
                             NULL, pSUBWIN_FEATURE (psubwin)->logflags, 
                             pSUBWIN_FEATURE (psubwin)->ARect); 

        sciDrawObj(pobj); 
        sciSetSelectedSubWin(tmpsubwin);
      }
      else
      {
        Scierror(999,"%s: object has no parent !!",fname);
        return 0;
      }
    }
  }
  LhsVar(1) = 0;
  return 0;
}
/*-----------------------------------------------------------------------------------*/
