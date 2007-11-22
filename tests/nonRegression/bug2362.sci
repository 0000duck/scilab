// <-- Non-regression test for bug 2362 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2362
//
// <-- Short Description -->
//    plot3d3 crash
//
//    plot3d3([0,0;10,10],[5,3;5,5],[0,2;0,2]);
//
//    badaboom!
//
//    Francois

// Copyright INRIA
// Scilab Project - Jean-Baptiste Silvy
// Copyright INRIA 2007
// Date : 5 avril 2007

// crashed before the bug fix
plot3d3([0,0;10,10],[5,3;5,5],[0,2;0,2]);
affich_result(%T,2362);
