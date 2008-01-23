// <-- Non-regression test for bug 2665 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2665
//
// <-- Short Description -->
// The example provided with the on-line help of grep crashes Scilab
// grep('2' ,'/2(]*)?$\1/' ,'r')
//
// =============================================================================
// Author : Pierre MARECHAL
// Scilab Project
// Copyright INRIA 2007
// =============================================================================
//

if grep("2" ,"/2(]*)?$\1/" ,"r")       <> 1      then pause, end
if or( regexp("xabyabbbz","/ab*/","r") <> [2 5]) then pause, end
if strindex("2","/2(]*)?$\1/" ,"r")    <> 1      then pause, end
