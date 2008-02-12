/*------------------------------------------------------------------------*/
/* file: sci_xset.c                                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for xset routine                                      */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "sci_xset.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "SetProperty.h"
#include "ObjectStructure.h"
#include "sci_demo.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "DrawObjects.h"
#include "InitObjects.h"
#include "XsetXgetParameters.h"
#include "CurrentObjectsManagement.h"
#include "sciprint.h"
#include "Format.h"
#include "ObjectSelection.h"
#include "msgs.h"
#include "localization.h"
#include "Scierror.h"
/*--------------------------------------------------------------------------*/
int C2F(xsetg)(char * str,char * str1,integer lx0,integer lx1) ;
/*--------------------------------------------------------------------------*/
int sci_xset( char *fname, unsigned long fname_len )
{
  integer m1,n1,l1,m2,n2,l2, xm[5],xn[5],x[5], i, v;
  integer lr;
  double fontSize = 0.0;
  double  xx[5];
  sciPointObj *subwin = NULL; 
  BOOL keyFound = FALSE ;

  if (Rhs <= 0) {int zero=0; sci_demo(fname,"xsetm();",&zero); return 0; }

  CheckRhs(1,6);
  CheckLhs(0,1);

  GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);

  for ( i = 0 ; i < NUMSETFONC ; i++ )
  {
    if ( strcmp(cstk(l1),KeyTab_[i]) == 0 )
    {
      keyFound = TRUE ;
      break ;
    }
  }

  if ( !keyFound )
  {
    i = 105;v=m1*n1;
    strncpy(C2F(cha1).buf,cstk(l1),v);
    C2F(msgs)(&i,&v);
    LhsVar(1)=0;
    return 0;
  }

  /* Allan CORNET Avril 2004 */
  /* Bloque la commande xset('window') sans numero de fenetre */
  if (Rhs == 1 && (strcmp(cstk(l1),"window") == 0) )
  {
    sciprint(_("%s : xset(\"window\",window-number): window-number must be set\n"),fname);
    LhsVar(1)=0; return 0;
  }

  if (Rhs == 2 && VarType(2) != sci_matrix) 
  {
    /* second argument is not a scalar it must be a string */ 
    GetRhsVar(2,STRING_DATATYPE,&m2,&n2,&l2);
    C2F(xsetg)(cstk(l1),cstk(l2),m1,m2);
    LhsVar(1)=0; return 0;
  }

  if (Rhs == 1 && strcmp(cstk(l1),"default") == 0) 
  {
    /* first treatment for xsetg : then we continue */
    C2F(xsetg)(cstk(l1),"void",m1,4L);
  }

  for ( i = 2 ; i <= Rhs ; i++ ) 
  {
    GetRhsVar(i,MATRIX_OF_DOUBLE_DATATYPE,&xm[i-2],&xn[i-2],&lr);
    x[i - 2] = (integer) *stk(lr); xx[i - 2] = *stk(lr);
  }
  if (strcmp(cstk(l1),"wdim") == 0 || strcmp(cstk(l1),"wpdim") == 0) {
    /* Xwindows limits dimensions to 2^16 */
    if ( (x[0]>65535)||(x[1]>65535)) {
      x[0]=Min(x[0],65535);
      x[1]=Min(x[1],65535);
      i = 106;v=0;
      C2F(msgs)(&i,&v);
    }
  }

  if (strcmp(cstk(l1),"clipping") == 0)
  {
    sciSetClipping(sciGetCurrentObj(),xx);
  }
  else if ( strcmp(cstk(l1),"colormap") == 0)
  {
    sciSetColormap (sciGetCurrentFigure(), stk(lr), *xm, *xn);
    sciRedrawFigure();
  }
  else if ( strcmp(cstk(l1),"mark size") == 0)
  {

    subwin = sciGetCurrentSubWin() ;
    sciSetMarkSizeUnit(subwin,2); /* force switch to tabulated mode : old syntax */
    subwin = sciGetCurrentSubWin();
    sciSetMarkSize(subwin,(int)xx[0]);
  }
  else if ( strcmp(cstk(l1),"mark") == 0)
  {
    subwin = sciGetCurrentSubWin();
    sciSetMarkSizeUnit(subwin,2); /* force switch to tabulated mode : old syntax */
    sciSetMarkStyle(subwin,(int) xx[0]);
    sciSetMarkSize(subwin,(int) xx[1]);

    // force mark drawing
    sciSetIsMark(subwin, TRUE);
    
  }
  else if ( strcmp(cstk(l1),"font size") == 0) {
    fontSize = xx[0];
    sciSetFontSize(sciGetCurrentSubWin(), fontSize);
    sciSetFontSize(sciGetParent(subwin), fontSize);
  } 
  /* NG beg */
  else if ( strcmp(cstk(l1),"old_style") == 0)
  {
    if (*stk(lr) == 1)
    {
      sciprint(_("Old graphic mode is no longer available. Please refer to the set help page.\n"));
    }
    else
    {
      Scierror(999,"%s: Value must be 1 or 0",fname);
    }
  }/* NG end */
  else if( strcmp(cstk(l1),"default") == 0 )
  {
    sciPointObj * pfigure = sciGetCurrentFigure();
    ResetFigureToDefaultValues(pfigure);

    /*special treatement for xset default and old_style off F.Leray 23.09.04 */
    /* mimic clf(gcf(),'reset') behaviour here */
    sciXbasc();
  }
  else if( strcmp(cstk(l1),"clipgrf") == 0 ) {
    /* special treatement for xset("cligrf") */
    sciPointObj * psubwin = sciGetCurrentSubWin();
    sciSetIsClipping(psubwin,0);
  }
  else if( strcmp(cstk(l1),"clipoff") == 0 ) {
    /* special treatement for xset("clipoff") */
    sciPointObj * psubwin = sciGetCurrentSubWin();
    sciSetIsClipping(psubwin,-1);
  }
  else if( strcmp(cstk(l1),"hidden3d") == 0 ) {
    /* special treatement for xset("hidden3d") */
    sciPointObj * psubwin = sciGetCurrentSubWin();
    pSUBWIN_FEATURE(psubwin)->hiddencolor = x[0];
  }
  else if ( strcmp(cstk(l1),"window") == 0 || strcmp(cstk(l1),"figure") == 0 )
  {
    if (sciSwitchWindow(x[0]) != 0){
      Scierror(999,_("%s: It was not possible to create the requested figure"),fname);
    }
  }
  else if ( strcmp(cstk(l1),"wshow") != 0 )
  {
    subwin = sciGetCurrentSubWin();
    if (( strcmp(cstk(l1),"foreground") == 0) || (strcmp(cstk(l1),"color") == 0) ||( strcmp(cstk(l1),"pattern") == 0) ) {
      sciSetForeground(subwin, x[0]); 
      if (sciGetSons((sciPointObj *) subwin) == (sciSons *)NULL) {/* added SS 20.04.04 */
        /* if subwin is empty, set also the ticscolor and fontforeground */
        pSUBWIN_FEATURE (subwin)->axes.ticscolor= x[0];
        sciSetFontForeground(subwin,x[0]); 
      }
    } 
    else if ( strcmp(cstk(l1),"background") == 0) {
      sciSetBackground(subwin, x[0]); 
    }  
    else if ( strcmp(cstk(l1),"thickness") == 0) {
      sciSetLineWidth(subwin, x[0]); 
      sciSetLineWidth(sciGetParent(subwin), x[0]);   
    } 
    else if ( strcmp(cstk(l1),"line style") == 0) {
      sciSetLineStyle(subwin, x[0]); 
      sciSetLineStyle(sciGetParent(subwin), x[0]);   
    }  
    else if ( strcmp(cstk(l1),"mark") == 0) {
      sciSetIsMark(subwin,1);                  /* A REVOIR F.Leray 21.01.05 */
      sciSetIsMark(sciGetParent(subwin),1);
      sciSetMarkStyle(subwin,x[0]); 
      sciSetMarkStyle(sciGetParent(subwin),x[0]);   
    } 
    else if ( strcmp(cstk(l1),"colormap") == 0) {
      sciSetColormap(sciGetParent(subwin), stk(lr),xm[0], xn[0]);
    }
    else if ( strcmp(cstk(l1),"font size") == 0) {
      sciSetFontSize(subwin, fontSize); 
      sciSetFontSize(sciGetParent(subwin), fontSize);
    }     
    else if ( strcmp(cstk(l1),"dashes") == 0) {
      sciSetLineStyle(subwin, x[0]); 
      sciSetLineStyle(sciGetParent(subwin), x[0]);   
    }  
    else if ( strcmp(cstk(l1),"font") == 0) {
      sciSetFontStyle(subwin, x[0]); 
      sciSetFontSize(subwin,  x[1]);  
      sciSetFontStyle(sciGetParent(subwin), x[0]); 
      sciSetFontSize(sciGetParent(subwin), x[1]);  
    } 
    else if ( strcmp(cstk(l1),"alufunction") == 0) {
      sciSetXorMode(subwin, x[0]); 
      sciSetXorMode(sciGetParent(subwin), x[0]);   
    }
    else if ( strcmp(cstk(l1),"auto clear") == 0) {
      if ( x[0] == 1 )
      {
        sciSetAddPlot(subwin, TRUE); 
        sciSetAddPlot(sciGetParent(subwin), TRUE);  
      }
      else  
      {
        sciSetAddPlot(subwin, FALSE); 
        sciSetAddPlot(sciGetParent(subwin), FALSE);  
      } 
    } 
    else if ( strcmp(cstk(l1),"auto scale") == 0) {
      if ( x[0] == 1 )
      {
        sciSetAutoScale(subwin, TRUE); 
        sciSetAutoScale(sciGetParent(subwin), TRUE);  
      }
      else  
      {
        sciSetAutoScale(subwin, FALSE); 
        sciSetAutoScale(sciGetParent(subwin), FALSE);  
      } 
    }
    else if ( strcmp(cstk(l1),"wresize") == 0) {
      if ( x[0] == 1 )
      {
        sciSetResize(subwin, TRUE); 
        sciSetResize(sciGetParent(subwin), TRUE);  
      }
      else  
      {
        sciSetResize(subwin, FALSE); 
        sciSetResize(sciGetParent(subwin), FALSE);  
      }
    }
    else if ( strcmp(cstk(l1),"wpos") == 0) {
      sciSetScreenPosition(sciGetParent(subwin), x[0], x[1]);

    }
    else if ( strcmp(cstk(l1),"wpdim") == 0) {
      sciSetWindowDim(sciGetParent(subwin), x[0], x[1] ) ;
    } 
    else if ( strcmp(cstk(l1),"wdim") == 0) {
      sciSetDimension(sciGetParent(subwin), x[0], x[1] ) ;

    } /*Ajout A.Djalel le 10/11/03 */
    else if ( strcmp(cstk(l1),"pixmap") == 0) {
      sciSetPixmapMode(sciGetParent(subwin), x[0]);
    }  
    else if ( strcmp(cstk(l1),"wshow") == 0) { /* a supprimer ce n'est pas une propriete mais une action */
      pFIGURE_FEATURE(sciGetParent(subwin))->wshow=1;
      sciSetVisibility (subwin, TRUE); 
    }
    else if (strcmp(cstk(l1),"viewport") == 0) {
      // TODO
    }
    else if (strcmp(cstk(l1),"wwpc") == 0) {
      // TODO
    }
    else if(strcmp(cstk(l1),"line mode") == 0)
    {
      if (x[0] == 0)
      {
        sciSetIsLine(subwin, FALSE);
      }
      else
      {
        sciSetIsLine(subwin, TRUE);
      }
    }
    else
    {
      sciprint(_("%s: Unrecognized input argument: \"%s\".\n"), fname, cstk(l1));
    }

    if(strcmp(cstk(l1),"window") != 0) sciRedrawFigure();   
  }
   
  LhsVar(1)=0;
  return 0;
}
/*--------------------------------------------------------------------------*/
int C2F(xsetg)(char * str,char * str1,integer lx0,integer lx1)
{
  if ( strcmp(str,"fpf") == 0) 
  {
    strncpy(getFPF(),str1,32);
  }
  else if ( strcmp(str,"auto clear")==0) 
  {
    sciPointObj * subwin = sciGetFirstTypedSelectedSon(sciGetCurrentFigure(), SCI_SUBWIN);
    if (strcmp(str1,"on")==0 )
    {
      sciSetAddPlot( subwin,FALSE);
    }
    else{
      sciSetAddPlot( subwin,TRUE);
    }
  }
  else if ( strcmp(str,"default")==0)
  {
    getFPF()[0]='\0';
  }
  else 
  {
    sciprint(_("xset(arg,<string>): Unrecognized arg: %s\n"),str);
  }
  return 0;
}
/*--------------------------------------------------------------------------*/
