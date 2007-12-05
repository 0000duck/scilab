// =============================================================================
// Scilab Project
// Copyright INRIA 2007
// =============================================================================
	
	my_plot_desc          = "pie chart";
	
	my_handle             = scf(100001);
	my_handle.figure_name = my_plot_desc;

	"plot2d(0,0,[0],''032'',''leg'',[-1.5,-1.5 ,1.5,1.5]);"
	"a=gca(); t=a.title;"
	"t.text=""pie chart""; t.font_size=3;"
	"xclip(''clipgrf'');"
	"alls=[-1,1,2,2,0,64*90;"
	"    -1,1,2,2,64*90,64*(30);"
	"    -1,1,2,2,64*(120),64*(70);"
	"    -1,1,2,2,64*(190),64*(360-190)];"
	"xfarcs(alls'',[1,3,5,7]);xclip();"];
	x_message(["[VIII  Colored histogram]";expr]);
	
	execstr(expr);
	