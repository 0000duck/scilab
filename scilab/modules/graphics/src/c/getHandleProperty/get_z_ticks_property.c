/*------------------------------------------------------------------------*/
/* file: get_z_ticks_property.c                                           */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : function to retrieve in Scilab the z_ticks field of             */
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
int get_z_ticks_property( sciPointObj * pobj )
{
  sciSubWindow * ppSubWin = NULL ;
  char c_format[5];
  if ( sciGetEntityType( pobj ) != SCI_SUBWIN )
  {
    sciprint("z_ticks property does not exists for this label.\n") ;
    return -1 ;
  }

  ppSubWin = pSUBWIN_FEATURE( pobj ) ;

  /* compute the c_format used for convert double to char (for labels) */
  ChooseGoodFormat( c_format, ppSubWin->logflags[2], ppSubWin->axes.zgrads, ppSubWin->axes.nzgrads ) ;

  if( ppSubWin->axes.auto_ticks[2] )
  {
    int       nbtics        = ppSubWin->axes.nzgrads ;
    char   ** ticklabel     = NULL                   ;
    double *  ticksPosition = NULL                   ;

    ticksPosition = ReBuildTicksLog2Lin( ppSubWin->logflags[2], nbtics, ppSubWin->axes.zgrads ) ;

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
    int      nbtics        = ppSubWin->axes.u_nzgrads ;
    double * ticksPosition = ReBuildTicksLog2Lin( ppSubWin->logflags[2], nbtics, ppSubWin->axes.u_zgrads ) ;

    buildTListForTicks( ticksPosition, ppSubWin->axes.u_zlabels, nbtics ) ;

    FREE( ticksPosition ) ;
    return 0 ;
  }

  return -1 ;
}
/*------------------------------------------------------------------------*/
