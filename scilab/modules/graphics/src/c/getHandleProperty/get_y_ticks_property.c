/*------------------------------------------------------------------------*/
/* file: get_y_ticks_property.c                                           */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the y_ticks field of             */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "get_ticks_utils.h"
#include "Format.h"
#include "MALLOC.h"
#include "BasicAlgos.h"

/*------------------------------------------------------------------------*/
int get_y_ticks_property( sciPointObj * pobj )
{
  sciSubWindow * ppSubWin = NULL ;
  char c_format[5];
  if ( sciGetEntityType( pobj ) != SCI_SUBWIN )
  {
    sciprint("y_ticks property does not exists for this label.\n") ;
    return -1 ;
  }

  ppSubWin = pSUBWIN_FEATURE( pobj ) ;

  /* compute the c_format used for convert double to char (for labels) */
  ChooseGoodFormat( c_format, ppSubWin->logflags[1], ppSubWin->axes.ygrads, ppSubWin->axes.nygrads ) ;

  if( ppSubWin->axes.auto_ticks[1] )
  {
    int       nbtics        = ppSubWin->axes.nygrads ;
    char   ** ticklabel     = NULL                   ;
    double *  ticksPosition = NULL                   ;

    ticksPosition = ReBuildTicksLog2Lin( ppSubWin->logflags[1], nbtics, ppSubWin->axes.ygrads ) ;

    /* convert double to strings */
    ticklabel = copyFormatedArray( ticksPosition, nbtics, c_format, 100 ) ;

    /* construction de la tlist */
    buildTListForTicks( ticksPosition, ticklabel, nbtics ) ;

    /* free ticklabel */
    destroyStringArray( ticklabel, nbtics ) ;
    FREE( ticksPosition ) ;
    return 0 ;
  }
  else /* we display the x tics specified by the user*/
  {
    int      nbtics        = ppSubWin->axes.u_nygrads ;
    double * ticksPosition = ReBuildTicksLog2Lin( ppSubWin->logflags[1], nbtics, ppSubWin->axes.u_ygrads ) ;

    buildTListForTicks( ticksPosition, ppSubWin->axes.u_ylabels, nbtics ) ;

    FREE( ticksPosition ) ;
    return 0 ;
  }

  return -1 ;
}
/*------------------------------------------------------------------------*/
