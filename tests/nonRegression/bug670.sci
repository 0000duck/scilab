// <-- Non-regression test for bug 670 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=670
//
// <-- Short Description -->
//    Stack problem in FUN2STRING. Occurs in many different 
//    situations, one situation can be reproduced using the code 
//    below.


// Non-regression test file for bug 670
// Copyright INRIA
// Scilab Project - Serge Steer
// Copyright INRIA 2006
// Date : 10 janvier 2006

mode(-1);
clear
deff('a = foo()', ...
     'b = tlist([''b''; ''c''], 0); ' + ...
     'a = tlist([''a''; ''b''], b); ' + ...
     'a.b.c = getText() + ''text 2'' ');
t=fun2string(foo);		
t_ref=["function a=ans";
"  b = tlist([''b'';''c''], 0);a = tlist([''a'';''b''], b);a.b.c = getText() + ''text 2''";
"endfunction"];
ok=and(t==t_ref);
affich_result(ok,670);
