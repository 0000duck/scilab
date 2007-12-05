demopath = get_absolute_file_path("2d_3d_plots.dem.gateway.sce");

demolist = [                                       ..
	"plot2d"         , "plot2d.dem.sce"          ; ..
	"plot2d1 (1)"    , "plot2d1_1.dem.sce"       ; ..
	"plot2d3"        , "plot2d3.dem.sce"         ; ..
	"plot2d1 (2)"    , "plot2d1_2.dem.sce"       ; ..
	"histplot"       , "histplot.dem.sce"        ; ..
	"fplot2d"        , "fplot2d.dem.sce"         ; ..
	"param3d (1)"    , "param3d_1.dem.sce"       ; ..
	"param3d (2)"    , "param3d_2.dem.sce"       ; ..
	"plot3d"         , "plot3d.dem.sce"          ; ..
	"fplot3d"        , "fplot3d.dem.sce"         ; ..
	"plot3d1"        , "plot3d1.dem.sce"         ; ..
	"fplot3d1"       , "fplot3d1.dem.sce"        ; ..
	"contour"        , "contour.dem.sce"         ; ..
	"fcontour"       , "fcontour.dem.sce"        ; ..
	"contourf"       , "contourf.dem.sce"        ; ..
	"champ"          , "champ.dem.sce"           ; ..
	"fchamp"         , "fchamp.dem.sce"          ; ..
	"grayplot"       , "grayplot.dem.sce"        ; ..
	"fgrayplot"      , "fgrayplot.dem.sce"       ; ..
	"errbar"         , "errbar.dem.sce"          ; ..
	"abaque"         , "abaque.dem.sce"          ; ..
	"zgrid"          , "zgrid.dem.sce"           ; ..
	"xgeom"          , "xgeom.dem.sce"           ; ..
	"contour (3d) 2" , "contour_3d_2.dem.sce"    ; ..
	"contour (3d) 3" , "contour_3d_3.dem.sce"    ; ..
	"contour (3d) 4" , "contour_3d_4.dem.sce"    ; ..
	"subplot"        , "subplot.dem.sce"         ; ..
	"fac3d"          , "fac3d.dem.sce"           ; ..
	"fac3d1"         , "fac3d1.dem.sce"          ];
	
function xdemo(info,str)
	x_message([info;str]);
	xbasc();
	execstr(str);
endfunction

// exec('SCI/modules/graphics/demos/dessin-1.dem');

// nn=prod(size(str_l));
// 
// while %t then
// 	num=tk_choose(info_l,'Choose a demo    ');
// 	if num==0 then
// 		lines(oldln(1));
// 		set figure_style new;
// 		return;
// 	else
// 		xdemo(" ",str_l(num));
// 	end
// end
