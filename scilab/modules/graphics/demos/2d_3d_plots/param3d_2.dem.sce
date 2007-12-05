// =============================================================================
// Scilab Project
// Copyright INRIA 2007
// =============================================================================

my_plot_desc          = "param3d : parametric curves in R3 (t.sin(t),t.cos(t),t.|t|/50.%pi)";

my_handle             = scf(100001);
my_handle.figure_name = my_plot_desc;

t = -50*%pi:0.1:50*%pi;
x = t.*sin(t);
y = t.*cos(t);
z = t.*abs(t)/(50*%pi);

param3d(x,y,z,45,60);
xtitle(my_plot_desc," "," "," ");
