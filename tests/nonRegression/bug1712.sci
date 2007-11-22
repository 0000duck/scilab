// <-- Non-regression test for bug 1712 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1712
//
// <-- Short Description -->
//    Logical binary operations &,| with hypermatrices fail, as shown in the 
//    following examples. (The unary operation ~ succeeds.)
//
//    -->hm=hypermat([2 2 2],1:8)
//
//    -->hm>min(hm) & hm<max(hm)
//                            !--error 4
//    undefined variable : %l_h_l
//
//    -->hm==min(hm) | hm==max(hm)
//                              !--error 4
//    undefined variable : %l_g_l
//
//    -->~(hm==min(hm))
//     ans  =
//
//    (:,:,1)
//
//    ! F T !
//    ! T T !
// ...

// Copyright INRIA
// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2005
// Date : 6 fevrier 2005

hm=hypermat([2 2 2],1:8);
test1 = execstr('hm>min(hm) & hm<max(hm)','errcatch');
test2 = execstr('hm==min(hm) | hm==max(hm)','errcatch');

if( (test1 == 0) & (test2 == 0) ) then
	affich_result(%T,1712);
else
	affich_result(%F,1712);
end
