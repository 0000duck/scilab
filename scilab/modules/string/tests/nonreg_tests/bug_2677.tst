// <-- Non-regression test for bug 2677 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2677


if grep(["at";"cat"],'/[hc]+at/','r')	 <>  2 then pause,end
if grep(["cat";"at"],'/[hc]+at/','r')	 <>  1 then pause,end



