// <-- Non-regression test for bug 1933 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1933
//
// <-- Short Description -->
//    log and log2 doesn't work on vectors with %nan under windows. They work 
//    nicely
//    under linux.

// A.C
// Copyright INRIA 2006

A             = [0 0 2 2 0 0];
A(find(A==0)) = %nan;
B             = log(A);

if ~(isnan(B(1))) then pause,end
if ~(isnan(B(2))) then pause,end
if ~(isnan(B(5))) then pause,end
if ~(isnan(B(6))) then pause,end

