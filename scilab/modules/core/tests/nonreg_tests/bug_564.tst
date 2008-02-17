// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Pierre MARECHAL <pierre.marechal@inria.fr>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 564 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=564
//
// <-- Short Description -->
//    CVS version of Scilab:
//    using break when it is not called for creates confusing
//    error messages. 
//    In the following code the breaks are useless, they should do
//    nothing
//    but they create uncomprehensible error messages (this code
//    is included
//    in a macro which is execed)
//      if ok then 
//          scs_m.objs(k)=XX
//          disp(1)
//          edited=%t;
//          disp(2)
//          needcompile=4
//          disp(3)
//          Cmenu='Replot';
//          disp(4),disp(Cmenu)
//          break
//        else
//          Cmenu='Open/Set' 
// ...

// Non-regression test file for bug 564

function foo()
	if ok then
 
		disp(1);
		edited=%t;
		disp(2);
		needcompile=4
		disp(3);
		Cmenu='Replot';
		disp(4);,disp(Cmenu);
		break
	else
		Cmenu='Open/Set'
		break
	end
endfunction

ok=%t;
diary(TMPDIR+"/bug564.txt");
foo();
exec(foo);
diary(0);

BUG564TXT = mgetl(TMPDIR+"/bug564.txt");
BUG564REF = mgetl(SCI+"/modules/core/nonreg_tests/bug_564.ref");

if or(BUG564TXT<>BUG564REF) then pause,end
mdelete(TMPDIR+"/bug564.txt");
