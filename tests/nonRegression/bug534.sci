// <-- Non-regression test for bug 534 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=534
//
// <-- Short Description -->
//    Bug Report Id: 030132003929164110
//    In order to correct error in command "geomean" it is necessary to 
//    1) take the place of
//    gm=prod(x)^(1/length(a)) 
//    on
//    gm=prod(x)^(1/length(x)) 
//    and
//    2)  take the place of 
//    gm=prod(x,orien).^(1/size(a,orien)) 
//    on
//    gm=prod(x,orien).^(1/size(x,orien)) 
//
//
//    On Scilab 2.7.2 with " statistics " function
//    The Error Messages are:
//       !--error     4
//    undefined variable : a
//    at line      25 of function geomean                  called by :
//    g=geomean(x);
//    Commands:  x=[3 1 5];
// ...

x=[3 1 5];

iErrorCode=execstr("geomean(x)","errcatch");

if iErrorCode==0 then
	affich_result(%T,534);
else
	affich_result(%F,534);
end
