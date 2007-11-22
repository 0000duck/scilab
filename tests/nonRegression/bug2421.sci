// <-- Non-regression test for bug 2421 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2421
//
// <-- Short Description -->
//    colon (all elements) assignment from output arguments of a function beyond the
//    first not possible

// Scilab Project - Serge Steer
// Copyright INRIA 2007
// Date : June 2007

BugNumber=2421
T=execstr('[a(:), v(1)] = (1, 2)','errcatch')==0
affich_result(T,BugNumber) ;
