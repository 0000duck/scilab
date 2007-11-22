// <-- Non-regression test for bug 1794 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1794
//
// <-- Short Description -->
//    Problem encountered when redefining builtin function


// Non-regression test file for bug 1794
// Copyright INRIA
// Scilab Project - Serge Steer
// Copyright INRIA 2005
// Date : 30 janvier 2006

mode(-1);
clear
beta=5;
try
  beta
  ok1=%t;
catch
  ok1=%f;
end

function y=foo()
  beta;
  y=beta+1
endfunction

try
 foo()
  ok2=%t;
catch
  ok2=%f;
end

affich_result(ok1&ok2,1794);
clear
