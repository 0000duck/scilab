// Non-regression test file for bug 1720
// Copyright INRIA
// Scilab Project - Jean-Baptiste Silvy
// Copyright INRIA 2006
// Date : 11 janvier 2006

mode(-1);
clear;

hf = scf(1) ;
hf.figure_name = "4.13.22A1";
ha = hf.children;
ha.axes_visible = "on";
ha.box = "on";
xfrect (0,0.5,0.5,0.5);
hr = gce();
hr.background = 5;
xfarc (0.5,1,0.5,0.5,0,23040);
hc = gce();
hc.background = 6;

// check that xfarc fill the arc and don't draw the limit
if ( hc.line_mode == 'off' ) then
  affich_result(%T,1720);
else
  affich_result(%F,1720);
end

clear;

