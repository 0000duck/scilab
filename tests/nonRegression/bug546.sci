// <-- Non-regression test for bug 546 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=546
//
// <-- Short Description -->
//    Bug Report Id: 031202003109143249
//    Wasn't also this fixed?
//    On Scilab CVS with " > with int " function
//    The Error Messages are:
//     none but wrong result
//    Commands: int8(ones(10,10))>2
//     ans  =
//
//    ! T T T T F F F F F F !
//    ! T T T T F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//    ! T T T F F F F F F F !
//
//    Enrico SEGRE on Linux version RH9 distribution  with   as window manager
// ...


//exec("bug546.sci")
 

a=int8(ones(10,10))>2;

b = [ 	%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ; ...
				%F  %F  %F  %F  %F  %F  %F  %F  %F  %F ]

 if a == b then
 
 affich_result(%T,546);
 
 else
 affich_result(%F,546);
 
 end;
    
