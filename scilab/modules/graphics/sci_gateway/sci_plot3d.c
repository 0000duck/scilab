/*------------------------------------------------------------------------*/
/* file: sci_plot3d.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for plot3d (and plot3d1) routine                      */
/*------------------------------------------------------------------------*/

#include <stdio.h>

#include "sci_plot3d.h"
#include "stack-c.h"
#include "Plo3d.h"
#include "sci_demo.h"
#include "BuildObjects.h"
#include "GetProperty.h"
#include "GetCommandArg.h"
#include "DestroyObjects.h"
#include "MALLOC.h"
#include "sciCall.h"
#include "dr1Call.h"

/*-----------------------------------------------------------------------------------*/
int sci_plot3d( char * fname, unsigned long fname_len )
{
  static double  ebox_def [6]= { 0,1,0,1,0,1};
  double *ebox = ebox_def ;
  static integer iflag_def[3]={2,2,4};
  integer *iflag = iflag_def;
  double  alpha_def=35.0 , theta_def=45.0 ;
  double *alpha=&alpha_def, *theta=&theta_def;
  integer m1, n1, l1, m2, n2, l2, m3, n3, l3;
  integer m3n = 0, n3n = 0, l3n, m3l, n3l, l3l; /*F.Leray 19.03.04 m3n and n3n set to 0.*/

  integer izcol,  isfac;
  double *zcol=NULL;

  static rhs_opts opts[]= { {-1,"alpha","?",0,0,0},
  {-1,"ebox","?",0,0,0},
  {-1,"flag","?",0,0,0},
  {-1,"leg","?",0,0,0},
  {-1,"theta","?",0,0,0},
  {-1,NULL,NULL,0,0}};

  char * legend = NULL ;

  if (Rhs <= 0)
  {
    int one = 1 ;
    sprintf(C2F(cha1).buf,"t=-%%pi:0.3:%%pi;%s(t,t,sin(t)'*cos(t),35,45,'X@Y@Z',[2,2,4]);",fname);
    sci_demo(fname,C2F(cha1).buf, &one);
    return 0;
  }

  CheckRhs(3,8);

  if ( get_optionals(fname,opts) == 0) return 0;
  if ( FirstOpt() < 4) {
    sciprint("%s: misplaced optional argument, first must be at position %d \r\n",
      fname,4);
    Error(999); 
    return(0);
  }

  GetRhsVar(1, "d", &m1, &n1, &l1);
  GetRhsVar(2, "d", &m2, &n2, &l2);
  if (m1 * n1 == 0) 	{ LhsVar(1) = 0; return 0;}

  if (Rhs >= 3) {
    /*     third argument can be a matrix z or a list list(z,zcol) */
    switch ( VarType(3) ) 
    {
    case 1 : 
      GetRhsVar(3, "d", &m3, &n3, &l3);
      izcol = 0;
      break;
    case 15 : 
      izcol = 1;
      /* z = list(z,colors) */
      GetRhsVar(3,"l",&m3l,&n3l,&l3l);
      if ( m3l != 2 ) 
      {
        Scierror(999,"%s: second argument has a wrong size (%d), expecting a list of size %d\r\n",
          fname,m3l,2);
        return 0;
      }
      GetListRhsVar(3,1,"d",&m3,&n3,&l3);
      GetListRhsVar(3,2,"d",&m3n,&n3n,&l3n);
      zcol  = stk(l3n);
      if (m3n * n3n != n3 &&  m3n*n3n != m3*n3)
      {
        Scierror(999,"%s: third argument: color specification has wrong size, expecting %d or %d \r\n",fname,n3,m3*n3);
        return 0;
      }
      /* 
      *   Added by E Segre 4/5/4000. In the case where zcol is a 
      *   matrix of the same size as z, we set izcol to 2. This
      *   value is later transmitted to the C2F(fac3dg) routine,
      *   which has been modified to do the interpolated shading 
      *    (see the file SCI/routines/graphics/Plo3d.c 
      */
      if (   m3n*n3n == m3*n3 ) { izcol=2  ; }
      break ;
    default : 
      OverLoad(3);
      return 0;
    }
  }
  SciWin();
  if (version_flag() == 0) { iflag_def[1]=8; }
  else { iflag_def[1]=2; /* F.Leray 15.06.04 : if switching back to old graphic style */ }

  GetOptionalDoubleArg(fname,4,"theta",&theta,1,opts);
  GetOptionalDoubleArg(fname,5,"alpha",&alpha,1,opts);
  GetLabels(fname,6,opts,&legend);
  GetOptionalIntArg(fname,7,"flag",&iflag,3,opts);
  GetOptionalDoubleArg(fname,8,"ebox",&ebox,6,opts);

  if (m1 * n1 == m3 * n3 && m1 * n1 == m2 * n2 && m1 * n1 != 1) {
    if (! (m1 == m2 && m2 == m3 && n1 == n2 && n2 == n3)) {
      Scierror(999,"%s: The three first arguments have incompatible length \r\n",fname);
      return 0;
    }
  } else {
    if (m2 * n2 != n3) {
      Scierror(999,"%s: second and third arguments have incompatible length\r\n",fname);
      return 0;
    }
    if (m1 * n1 != m3) {
      Scierror(999,"%s: first and third arguments have incompatible length\r\n",fname);
      return 0;
    }
    if ( m1*n1 <= 1 || m2*n2 <= 1 ) 
    {
      Scierror(999,"%s: first and second arguments should be of size >= 2\r\n",fname);
      return 0;
    }
  }

  if (m1 * n1 == 0 || m2 * n2 == 0 || m3 * n3 == 0) { LhsVar(1)=0; return 0;} 
  SciWin();
  SciGerase() ;

  /******************** 24/015/2002 ********************/
  if (m1 * n1 == m3 * n3 && m1 * n1 == m2 * n2 && m1 * n1 != 1) /* NG beg */
  {
    isfac=1;
  }
  else
  {
    isfac=0;
  }

  if (version_flag() == 0)
  {
    Objplot3d (fname,&isfac,&izcol,stk(l1),stk(l2),stk(l3),zcol,&m3,&n3,theta,alpha,legend,iflag,ebox,&m1,&n1,&m2,&n2,&m3,&n3,&m3n,&n3n);/*Adding F.Leray 12.03.04 and 19.03.04*/
  }
  else
  {
    integer *cvect = NULL,i;
    if((m3n)*(n3n) != 0){
      if((cvect=MALLOC((m3n)*(n3n)*sizeof(integer)))==NULL){
        Scierror(999,"Allocation failed for color matrix in %s\r\n",fname);
        return 0;
      }
    }

    for( i = 0 ; i < m3n * n3n ; i++ )
    {
      cvect[i] = (int) zcol[i];
    }

    Xplot3d (fname,&isfac,&izcol,stk(l1),stk(l2),stk(l3),cvect,&m3,&n3,theta,alpha,legend,iflag,ebox) ;
    FREE( cvect ) ;
    cvect = NULL;
  }
  /* NG end */
  LhsVar(1)=0;
  return 0;

}
/*-----------------------------------------------------------------------------------*/
