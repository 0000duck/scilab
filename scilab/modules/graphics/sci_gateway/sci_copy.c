/*------------------------------------------------------------------------*/
/* file: sci_copy.h                                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy, Jean-Philipe Chancelier  */
/* desc : interface for copy routine                                      */
/*------------------------------------------------------------------------*/

#include "sci_copy.h"
#include "stack-c.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "ObjectStructure.h"
#include "DrawObjects.h"
#include "GetProperty.h"
#include "CloneObjects.h"

/*-----------------------------------------------------------------------------------*/
int sci_copy(char *fname,unsigned long fname_len)
{  
  unsigned long hdl, hdlparent;
  sciPointObj *pobj, *psubwinparenttarget, *pcopyobj;
  integer m1, n1, l1,l2;
  int numrow, numcol, outindex,lw;
  sciEntityType typ;

  CheckRhs(1,2);
  CheckLhs(0,1);

  /*  set or create a graphic window*/
  SciWin();
  lw = 1 + Top - Rhs;
  GetRhsVar(1,"h",&m1,&n1,&l1); /* Gets the Handle passed as argument*/
  if (m1!=1||n1!=1) {
    C2F(overload)(&lw,"copy",4);
    return 0;
  }

  if (Rhs == 1)
  {
    hdl = (unsigned long)*hstk(l1); /* on recupere le pointeur d'objet par le handle*/
    pobj = sciGetPointerFromHandle(hdl);
    if (pobj == NULL) {
      Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
      return 0;
    }
    typ=sciGetEntityType(pobj);
    if (typ!=SCI_TEXT&&typ!=SCI_ARC&&typ!=SCI_POLYLINE&&typ!=SCI_RECTANGLE) {
      C2F(overload)(&lw,"copy",4);
      return 0;
    }
    psubwinparenttarget = sciGetParentSubwin(sciGetPointerFromHandle(hdl));
  }
  else
  {
    hdl = (unsigned long)*hstk(l1); /* on recupere le pointeur d'objet par le handle*/
    pobj = sciGetPointerFromHandle(hdl);
    if (pobj == NULL) {
      Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
      return 0;
    }
    typ=sciGetEntityType(pobj);
    if (typ!=SCI_TEXT&&typ!=SCI_ARC&&typ!=SCI_POLYLINE&&typ!=SCI_RECTANGLE) {
      C2F(overload)(&lw,"copy",4);
      return 0;
    }
    GetRhsVar(2,"h",&m1,&n1,&l2); /* Gets the command name */
    hdlparent = (unsigned long)*hstk(l2); /* on recupere le pointeur d'objet par le handle*/
    psubwinparenttarget = sciGetPointerFromHandle(hdlparent);
    if ( psubwinparenttarget == NULL) {
      Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
      return 0;
    }
  }
  numrow   = 1;numcol   = 1;
  CreateVar(Rhs+1,"h",&numrow,&numcol,&outindex);
  *hstk(outindex) = sciGetHandle(pcopyobj = sciCopyObj((sciPointObj *)pobj,(sciPointObj *)psubwinparenttarget));
  sciDrawObj((sciPointObj *)sciGetParentFigure(pcopyobj));
  LhsVar(1) = Rhs+1;
  return 0;
}

/*-----------------------------------------------------------------------------------*/
