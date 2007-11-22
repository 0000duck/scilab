// <-- Non-regression test for bug 2333 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2333
//
// <-- Short Description -->
//    I am trying to convert a large number of Matlab files to Scilab. Either 
//    by using translatepath or a loop with mfile2sci I get the same error 
//    message when converting specific .m files. It appears in recursive mode 
//    only when calling another matlab function.


// Non-regression test file for bug 2333
// Vincent COUVERT - Scilab Project
// Copyright INRIA
// 15/03/2007

mode(-1);
clear;

load("SCI/modules/m2sci/macros/kernel/lib");
r=exists("mfile_path");

affich_result(r,2322);
clear
