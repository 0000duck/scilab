// <-- Non-regression test for bug 610 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=610
//
// <-- Short Description -->
//    In a function with a varargout list I want to call another
//    function having a varargout list.  How should I code it
//    (this is simple in Matlab)?    The following is my example
//    which does not work.  Any suggestions?



// exec("bug610.sci");

 

function varargout = mysum(a, b)
  varargout = list(a + b, a - b, a * b);
endfunction

iCodeError= execstr('function [y, varargout] = MyNew(a,b) ..
   [y, varargout] = mysum(a,b) ..
   endfunction' ..
,'errcatch' );

//lasterror()
 
if iCodeError   then
disp("-----------------------");
lasterror()
disp("-----------------------");
affich_result(%T,610)
else
affich_result(%F,610)

end;
 
