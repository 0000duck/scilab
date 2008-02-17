// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2006-2008 - INRIA - Serge STEER <serge.steer@inria.fr>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 1768 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1768
//
// <-- Short Description -->
//    I just downloaded Scilab-4.0rc1.
//    Whenever I write a new function and try to write the relative help 
//    file, xmltohtml crashes. Apparently, it does not found the whatis file 
//    even if it was just created successfully

function y=foo1(a,b)
	y=a+b
endfunction

T=help_skeleton('foo1')
mputl(strsubst(T,"<LINK> add a key here</LINK>", ..
	"<LINK>abs</LINK>"), ..
	TMPDIR+"/foo1.xml");

try
	xmltohtml(TMPDIR)
catch
	if %T then pause,end
end

try
	xmltohtml('SCI/modules/elementary_functions/help/'+getlanguage())
catch
	if %T then pause,end
end
