// <-- Non-regression test for bug 1732 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1732
//
// <-- Short Description -->
//    The field Axes.sub_tics does not correctly works under Linux, but correctly
//    works un Windows.
//
//    Jacques-Deric

// Copyright INRIA
// Scilab Project - Jean-Baptiste Silvy
// Copyright INRIA 2006
// Date : 18 janvier 2006

ref                = [1,0,5] ;
ha                 = gca () ;
ha.axes_visible    = "on" ;
ha.view            = "3d" ;
ha.sub_ticks       = ref ;
res1               = ha.sub_ticks ;

// mask Z axis
ha.rotation_angles = [1,30];
res2               = ha.sub_ticks ;

// check the sub_ticks were not modified

if or(res1<>ref) then pause,end
if or(res2<>ref) then pause,end
