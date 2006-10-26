/*------------------------------------------------------------------------*/
/* file: xs2file.c                                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Jean-Philippe Chancelier,                                    */
/*           Fabrice Leray,                                               */
/*           Jean-Baptiste Silvy                                          */
/* desc : interface for xs2file routine                                   */
/*------------------------------------------------------------------------*/

#include "xs2file.h"
#include "stack-c.h"
#include "Xcall1.h"
#include "GetProperty.h"
#include "SetProperty.h"
#include "periScreen.h"
#include "graphicSession.h"
#include "DrawObjects.h"
#include "Rec.h"
#include "ColorMapManagement.h"
#include "MALLOC.h"

/*-----------------------------------------------------------------------------------*/
int xs2file( char * fname, char * dr, unsigned long fname_len, unsigned long dr_len )
{
  integer m1,n1,l1,m2,n2,l2,m3,n3,l3,flagx = -1,iwin;
  CheckRhs(2,3);

  /* the window number */ 
  GetRhsVar(1,"d",&m1,&n1,&l1) ;
  CheckScalar(1,m1,n1) ;
  iwin = (integer) *stk(l1) ;
  /* the file name */ 
  GetRhsVar(2,"c",&m2,&n2,&l2);
  /* color or n & b */ 
  if ( Rhs >= 3 )
  {
    GetRhsVar(3,"d",&m3,&n3,&l3) ;
    CheckScalar(3,m3,n3) ;
    flagx = (integer) *stk(l3) ;
  }
  /* nouveau graphique ?????*/
  C2F(xg2psofig)(cstk(l2),&m2,&iwin,&flagx,dr,bsiz,dr_len);
  LhsVar(1)=0;
  return 0;
}
/*-----------------------------------------------------------------------------------*/
int scig_toPs( integer win_num, integer colored, char * bufname, char * driver )
{
//  char name[4];
//  integer zero=0,un=1,ierr;
//  integer verb=0,cur,na,screenc;
//  BOOL save_xinitxend_flag = isGraphicSessionOpened() ;
//
//  ierr = 0;
//  GetDriver1(name,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0);
//  C2F(dr)("xget","window",&verb,&cur,&na,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);  
//  C2F(dr)("xset","window",&win_num,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);
//  if (version_flag() == 0) {
//    sciPointObj *curFig=sciGetCurrentFigure ();
//    integer bg;
//
//    if(curFig == (sciPointObj *) NULL){
//      Scierror(999,"No current graphic window %d found for exporting to %s\r\n",win_num,driver);
//      C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//      C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//      /* to force a reset in the graphic scales for the graphic window number cur */
//      if(GetDriverId() == 1) { SwitchWindow(&cur) ; }
//      return ierr;
//    }
//
//    C2F(dr)("xget","background",&verb,&bg,&na,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,11L);
//    /* Rajout F.Leray 06.04.04 */
//    bg = sciGetBackground(curFig);
//    C2F(dr)("xsetdr",driver,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    /* xinit from screen (for the colormap definition) */
//    C2F(dr)("xinit2",bufname,&win_num,&ierr,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    if (ierr != 0) goto bad;
//    set_version_flag(0);
//    sciSetCurrentFigure(curFig);
//    C2F(dr)("xset","background",&bg,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);
//    closeGraphicSession() ; /* we force to draw */
//    sciDrawObj(curFig);
//  }
//  else {
//    struct BCG * XGC = (struct BCG *) NULL;
//    C2F(dr)("xsetdr",driver,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    /* xinit from screen (for the colormap definition) */
//    C2F(dr)("xinit2",bufname,&win_num,&ierr,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    if (ierr != 0)  goto bad;
//    if (colored==1) 
//      C2F(dr)("xset","use color",&un,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    else
//      C2F(dr)("xset","use color",&zero,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    getcolordef(&screenc);
//    /** we set the default screen color to the value of colored 
//    because we don't want that recorded events such as xset("default") could 
//    change the color status .
//    and we set the UseColorFlag to 1 not to replay xset("use color",..) events 
//    **/
//    setcolordef(colored);
//    UseColorFlag(1);
//
//    /* we want to draw something with a driver in old style */
//    /* I force the current ScilabXgc.graphicsversion = 1 */ /* F.Leray 18.05.05 */
//    XGC=(struct BCG *) sciGetCurrentScilabXgc ();
//    XGC->graphicsversion = 1;
//
//    C2F(dr)("xreplay","v",&win_num,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//    /** back to default values **/
//    UseColorFlag(0);
//    setcolordef(screenc);
//  }
//  C2F(dr)("xend","v",PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//  if(version_flag() == 0) 
//  {
//    if ( save_xinitxend_flag )
//    {
//      openGraphicSession() ;
//    }
//    else
//    {
//      closeGraphicSession() ;
//    }
//  }
//bad:
//  C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//  C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
//  /* to force a reset in the graphic scales */
//  SwitchWindow(&cur);
//  return ierr;
  char name[4];
  integer zero=0,un=1,ierr;
  integer verb=0,cur,na,screenc;
  int save_xinitxend_flag = isGraphicSessionOpened();

  ierr = 0;
  GetDriver1(name,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0);
  C2F(dr)("xget","window",&verb,&cur,&na,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);  
  C2F(dr)("xset","window",&win_num,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);
  
  if (version_flag() == 0)
  {
    sciPointObj * curFig=sciGetCurrentFigure ();
    integer bg ;
    double * curColorMap = NULL ;
    double * bwColorMap  = NULL ; /* allocated if black and white needed */
    int colorMapSize = sciGetNumColors( curFig ) ;

    if( curFig == (sciPointObj *) NULL )
    {
      Scierror(999,"No current graphic window %d found for exporting to %s\r\n",win_num,driver);
      C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      /* to force a reset in the graphic scales for the graphic window number cur */
      if(GetDriverId() == 1) { SwitchWindow(&cur); }
      return ierr;
    }

    C2F(dr)("xget","background",&verb,&bg,&na,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,11L);
    /* Rajout F.Leray 06.04.04 */
    bg = sciGetBackground(curFig);
    C2F(dr)("xsetdr",driver,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    /* xinit from screen (for the colormap definition) */
    C2F(dr)("xinit2",bufname,&win_num,&ierr,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);

    if (ierr != 0)
    {
      C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      /* to force a reset in the graphic scales */
      SwitchWindow(&cur);
      return ierr ;
    }

    set_version_flag(0);
    sciSetCurrentFigure(curFig);

    if ( colored == 0 )
    {
      /* change the colormap to a bw one */
      curColorMap = MALLOC( 3 * colorMapSize * sizeof(double) ) ;
      bwColorMap  = MALLOC( 3 * colorMapSize * sizeof(double) ) ;
      sciGetColormap( curFig, curColorMap ) ;
      convertColorMap2BW( bwColorMap, curColorMap, colorMapSize ) ;
      sciSetColormap( curFig, bwColorMap, colorMapSize, 3 ) ;
      FREE( bwColorMap ) ;
      bwColorMap = NULL ;
    }

    C2F(dr)("xset","background",&bg,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,5L,7L);
    closeGraphicSession() ; /* we force to draw */
    sciDrawObj(curFig);


    C2F(dr)("xend","v",PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    if ( save_xinitxend_flag )
    {
      openGraphicSession() ;
    }
    else
    {
      closeGraphicSession() ;
    }
    C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);

    if ( colored == 0 )
    {
      sciSetColormap( curFig, curColorMap, colorMapSize, 3 ) ;
      FREE( curColorMap ) ;
      curColorMap = NULL ;
    }
  }
  else {
    struct BCG * XGC = (struct BCG *) NULL;
    C2F(dr)("xsetdr",driver,PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    /* xinit from screen (for the colormap definition) */
    C2F(dr)("xinit2",bufname,&win_num,&ierr,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    if ( ierr != 0 )
    {
      C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
      /* to force a reset in the graphic scales */
      SwitchWindow(&cur);
      return ierr ;
    }
    if (colored==1) 
      C2F(dr)("xset","use color",&un,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    else
      C2F(dr)("xset","use color",&zero,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    getcolordef(&screenc);
    /** we set the default screen color to the value of colored 
    because we don't want that recorded events such as xset("default") could 
    change the color status .
    and we set the UseColorFlag to 1 not to replay xset("use color",..) events 
    **/
    setcolordef(colored);
    UseColorFlag(1);

    /* we want to draw something with a driver in old style */
    /* I force the current ScilabXgc.graphicsversion = 1 */ /* F.Leray 18.05.05 */
    XGC=(struct BCG *) sciGetCurrentScilabXgc ();
    XGC->graphicsversion = 1;

    C2F(dr)("xreplay","v",&win_num,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    /** back to default values **/
    UseColorFlag(0);
    setcolordef(screenc);
    C2F(dr)("xend","v",PI0,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
    C2F(dr)("xsetdr",name, PI0, PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
  }

  C2F(dr)("xset","window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
  /* to force a reset in the graphic scales */
  SwitchWindow(&cur);
  return ierr;
}
/*-----------------------------------------------------------------------------------*/
int C2F(xg2psofig)(char *fname, integer *len, integer *iwin, integer *color, char *driver, long int l1, long int l2)
{
  int sc;
  if ( *color == -1 ) 
    getcolordef(&sc);
  else 
    sc= *color;
  /*scig_toPs(*iwin,sc,fname,driver);*/
  return scig_toPs(*iwin,sc,fname,driver); /* why twice ???? */
}
/*-----------------------------------------------------------------------------------*/
