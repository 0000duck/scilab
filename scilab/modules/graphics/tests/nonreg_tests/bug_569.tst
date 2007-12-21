// <-- INTERACTIVE TEST -->
// <-- TEST WITH GRAPHIC -->
//
// <-- Non-regression test for bug 569 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=569
//
// <-- Short Description -->
//    contour2d does not work for me; however, contour works as
//    expected of contour2d: 2D plot of a set of level lines.


disp("check the result of the  graphic windows");

x  = 0:0.1:1;
f  = sin(2*%pi*x)'*cos(2*%pi*x);
nz = [0,0.1,0.2];
if execstr('contour(x,x,f,nz)','errcatch') <> 0 then pause,end
