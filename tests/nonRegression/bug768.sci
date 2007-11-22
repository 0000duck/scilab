// <-- Non-regression test for bug 768 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=768
//
// <-- Short Description -->
//    as on Scilab 2.7.2, the "window" function still has a bug 
//    when choosing the "chebychev" type with its corresponding 
//    parameter vector. SAys the parameters are out of bounds 
//    whereas it is wrong

// Copyright INRIA
// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2005
// Date : 6 fevrier 2005

err_number  = execstr('window(''ch'',128,[0.25 0.1])','errcatch');
err_message = lasterror();

if( err_message == 'Parameter par should be [dp,df] where one of dp, df is equal to -1             ') then
	affich_result(%T,768);
else
	affich_result(%F,768);
end
