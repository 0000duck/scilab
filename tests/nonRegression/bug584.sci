// <-- Non-regression test for bug 584 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=584
//
// <-- Short Description -->
//    logspace does not return good max value ! try this :
//    format('e',32);logspace( 3, 3, 1 )
//    ans  =
//
//        1.0000000000000007000000000E+03

// Copyright INRIA

// Modified by Pierre MARECHAL
// Copyright INRIA
// Date : 23 Mar 2005

format('e',32);
result=logspace( 3, 3, 1 );

trueValue=1.000000000000000000E+03;

if result == trueValue then ;
	format('v',10);
	affich_result(%T,584);
else
	format('v',10);
	affich_result(%F,584);
end

format('v',10);
