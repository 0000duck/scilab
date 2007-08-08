/*------------------------------------------------------------------------*/
/* file: sci_fec.c                                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for sci_fec routine                                   */
/*------------------------------------------------------------------------*/

#include <string.h>

#include "sci_fec.h"
#include "sci_demo.h"
#include "stack-c.h"
#include "GetCommandArg.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "DestroyObjects.h"
#include "sciCall.h"
#include "GetProperty.h"
#include "DefaultCommandArg.h"
#include "sciprint.h"

/*-----------------------------------------------------------------------------------*/
int sci_fec(char *fname,unsigned long fname_len)
{
  integer m1,n1,l1,m2,n2,l2,m3,n3,l3,m4,n4,l4, mn1;

  static rhs_opts opts[]= { {-1,"colminmax","?",0,0,0},
                            {-1,"colout","?",0,0,0},
                            {-1,"leg","?",0,0,0},
                            {-1,"mesh","?",0,0,0},
                            {-1,"nax","?",0,0,0},
                            {-1,"rect","?",0,0,0},
                            {-1,"strf","?",0,0,0},
                            {-1,"zminmax","?",0,0,0},
                            {-1,NULL,NULL,0,0}        } ;

  char * strf = NULL ;
  char * legend = NULL ;
  double * rect = NULL ;
  double * zminmax = NULL ;
  int * colminmax = NULL ;
  int * nax = NULL ;
  int * colOut = NULL ;
  BOOL flagNax = FALSE ;
  BOOL withMesh = FALSE ;


  if (Rhs <= 0)
  {
    int one = 1 ;
    sci_demo (fname," exec(\"SCI/modules/graphics/demos/fec/fec.ex1\");",&one);
    return 0;
  }

  CheckRhs(4,12);

  if ( get_optionals(fname,opts) == 0) return 0;
  if ( FirstOpt() < 5) {
    sciprint("%s: misplaced optional argument, first must be at position %d \r\n",
      fname,5);
    Error(999); 
    return(0);
  }
  GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1);
  GetRhsVar(2,MATRIX_OF_DOUBLE_DATATYPE,&m2,&n2,&l2);
  CheckSameDims(1,2,m1,n1,m2,n2);

  GetRhsVar(3,MATRIX_OF_DOUBLE_DATATYPE,&m3,&n3,&l3);
  if (n3 != 5) {
    Scierror(999,"%s: triangles have %d columns,expecting 5\r\n",fname,n3);
    return 0;
  }

  GetRhsVar(4,MATRIX_OF_DOUBLE_DATATYPE,&m4,&n4,&l4);

  if (m1 * n1 == 0 || m3 == 0) { LhsVar(1)=0;     return 0;} 

  GetStrf(fname,5,opts,&strf);
  GetLegend(fname,6,opts,&legend);
  GetRect(fname,7,opts,&rect);
  GetNax(8,opts,&nax,&flagNax);
  GetZminmax(fname,9,opts,&zminmax);
  GetColminmax(fname,10,opts,&colminmax);
  GetColOut(fname,11,opts,&colOut);
  GetWithMesh(fname,12,opts,&withMesh);

  SciWin();
  SciGerase() ;

  if ( isDefStrf ( strf ) ) {
    char strfl[4];

    strcpy(strfl,DEFSTRFN);
    
    strf = strfl;
    if ( !isDefRect( rect ))
    {
      strfl[1]='7';
    }
    if ( !isDefLegend( legend ) )
    {
      strfl[0]='1';
    }
  }
  mn1 = m1 * n1;

  Objfec (stk(l1),stk(l2),stk(l3),stk(l4),&mn1,&m3,strf,legend,rect,nax,zminmax,colminmax,colOut,withMesh,flagNax);

  LhsVar(1)=0;
  return 0;
}

/*-----------------------------------------------------------------------------------*/
