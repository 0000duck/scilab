// <-- Non-regression test for bug 625 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=625
//
// <-- Short Description -->
//    xget does not recognise (anymore) some of its valid keys.
//    Side effect: getmark() is very verbose and does not show
//    scaled marks.

if execstr('xget(''mark size'')','errcatch')<>0 then pause,end
