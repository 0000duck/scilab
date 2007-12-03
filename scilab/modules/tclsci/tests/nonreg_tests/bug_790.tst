// <-- Non-regression test for bug 790 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=790
//
// <-- Short Description -->
//    Scilab crashes when you enter findobj().
//    I know that it is not usefull but, the bug exists.

// Author : Allan CORNET
// Copyright INRIA

 // Modified by Pierre MARECHAL
// Copyright INRIA
// Date : 23 Mar 2005

if execstr('findobj() == []','errcatch') <> 77 then pause,end
if execstr('findobj(''test'') == []','errcatch') <> 77 then pause,end
if execstr('findobj(''Param1'',''Param2'') == []','errcatch') <> 0 then pause,end
