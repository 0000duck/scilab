// <-- Non-regression test for bug 570 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=570
//
// <-- Short Description -->
//    missing overload for string hypermatrix insertion?
//    See bug 566


if execstr('a(2,3,2)=''x''','errcatch') == 0 then pause,end
