// <-- Non-regression test for bug 2637 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2637
//
// <-- Short Description -->
// The isnum function had got some strange behaviour...
// 
// =============================================================================
// unit tests for isnum function
// Author : Pierre MARECHAL
// Scilab Project
// Copyright INRIA 2007
// =============================================================================

if isnum('e') then pause,end
if isnum('d') then pause,end

