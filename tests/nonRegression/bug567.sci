// <-- Non-regression test for bug 567 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=567
//
// <-- Short Description -->
//    When I accidentally closed scilab while scipad editor was
//    open, scipad did not ask to save the changes. This is a
//    serious bug since all unsaved changes were lost. The best
//    solution might be to leave the editor window open as a
//    separate application.


disp("start scilab");
disp("start scipad");
disp("write something in scipad");
disp("don''t save!");
disp("quit scilab");
