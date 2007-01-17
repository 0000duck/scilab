/*-----------------------------------------------------------------------------------*/
/* INRIA 2005 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __INTGRAPHICS__
#define __INTGRAPHICS__

#ifdef _MSC_VER
#include <windows.h>
#include <stdio.h>
#endif

#include "machine.h"
#include "stack-c.h"
#include "sciprint.h"

typedef int (*des_interf) __PARAMS((char *fname,unsigned long l));

typedef struct table_struct {
	des_interf f;    /** function **/
	char *name;      /** its name **/
} MatdesTable;

int C2F(gw_graphics)(void);

/*-----------------------------------------------------------------------------------*/ 
extern int sci_champ                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_param3d                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot3d                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot2d                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot2d1_1                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot2d1_2                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot2d1_3                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_plot2d1_4                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_grayplot                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_driver                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xarc                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xarcs                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xrects                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xarrows                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xsegs                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_drawaxis                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xchange                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xclea                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xrect                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xclear                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xclick                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xend                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xfpoly                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xfpolys                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xget                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xinit                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xlfont                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xpoly                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xpolys                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xselect                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xset                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xstring                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xstringl                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_StringBox                  _PARAMS((char *fname, unsigned long fname_len)) ;
extern int sci_xtape                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xsetech                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xgetech                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_geom3d                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_fec                        _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xgetmouse                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xtitle                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xgrid                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xfarcs                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_champ1                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xdel                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xg2ps                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2ps                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2fig                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xsort                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_winsid                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_param3d1                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xstringb                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_matplot                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_contour2di                 _PARAMS((char *fname, unsigned long fname_len));
extern int sci_matplot1                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xgraduate                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xname                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xaxis                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_seteventhandler            _PARAMS((char *fname, unsigned long fname_len));
extern int sci_help_gtk                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_set                        _PARAMS((char *fname, unsigned long fname_len));
extern int sci_get                        _PARAMS((char *fname, unsigned long fname_len));
extern int sci_delete                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_addcb                      _PARAMS((char *fname, unsigned long fname_len));
extern int sci_copy                       _PARAMS((char *fname, unsigned long subwinparenttarget));
extern int sci_move                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_glue                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_unglue                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_drawnow                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_drawlater                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_draw                       _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2gif                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2ppm                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_set_posfig_dim             _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xsnative                   _PARAMS((char *fname, unsigned long fname_len));
extern int sci_zoom_rect                  _PARAMS((char *fname, unsigned long fname_len));
extern int sci_unzoom                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2bmp                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_xs2emf                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_UImenu                     _PARAMS((char *fname, unsigned long fname_len));
extern int sci_newaxes                    _PARAMS((char *fname, unsigned long fname_len));
extern int sci_showalluimenushandles      _PARAMS(( char * fname, unsigned long fname_len ) ) ;
extern int sci_relocate_handle            _PARAMS(( char * fname, unsigned long fname_len ) ) ;
extern int sci_swap_handles               _PARAMS(( char * fname, unsigned long fname_len ) ) ;
extern int sci_readxbm	                  _PARAMS(( char * fname, unsigned long fname_len ) ) ;
extern int sci_readgif	                  _PARAMS(( char * fname, unsigned long fname_len ) ) ;


#endif /* __INTGRAPHICS__ */
/*-----------------------------------------------------------------------------------*/ 
