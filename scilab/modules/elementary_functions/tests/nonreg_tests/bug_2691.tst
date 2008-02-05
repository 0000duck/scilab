// <-- Non-regression test for bug 2691 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2691
//
// <-- Short Description -->
//    bitand doesn't complain when it's called with only one argument.

// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2008
// Date : Feb 2008

if execstr("bitand(1);","errcatch") == 0 then pause,end
if execstr("bitor(1);" ,"errcatch") == 0 then pause,end
if execstr("bitxor(1);","errcatch") == 0 then pause,end
