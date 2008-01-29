// <-- Non-regression test for bug 2674 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2674
//
// <-- Short Description -->
// regexp function return weird strings.
//
// =============================================================================
// Author : Pierre MARECHAL
// Scilab Project
// 29 janvier 2008
// =============================================================================

[ start_ind end_ind str_match ] = regexp('XABYABBBZ','/ab*/i','r');
if str_match <> ["AB";"ABBB"] then pause,end
