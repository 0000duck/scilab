// <-- Non-regression test for bug H -->
//
// <-- OLD BUG -->
//
// Une option de contour2d a ete oubliee dans la version 2.7

result = execstr("contour2d(1:10,1:10,rand(10,10),[0.1 0.5 0.9])","errcatch","n");
xdel();
if result <> 0 then pause,end
