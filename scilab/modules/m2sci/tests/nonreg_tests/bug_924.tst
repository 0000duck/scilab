// <-- Non-regression test for bug 924 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=924
//
// <-- Short Description -->
//    Bad handling of variable display in functions.
//    Following Matlab code :
//    function test
//    a='milou'
//    a
//    sould be converted to Scilab code :
//    function test
//    a='milou'
//    disp(a)
//    but it is not....

// Copyright INRIA
// Scilab Project - V. Couvert

// Modified by Pierre MARECHAL
// Copyright INRIA
// Date : 18 Mar 2005

MFILECONTENTS=["function bug924";
		"a=''milou'';";
		"a=''milou'',";
		"a=''milou''";
		"a;";
		"a,";
		"a";
		"[c,d]=svd(1);";
		"[c,d]=svd(1),";
		"[c,d]=svd(1)";
		"b=a;";
		"b=a,";
		"b=a"]

MFILE=TMPDIR+"/bug924.m"
SCIFILE=TMPDIR+"/bug924.sci"

mputl(MFILECONTENTS,MFILE);
mfile2sci(MFILE,TMPDIR);
SCIFILECONTENTS=mgetl(SCIFILE);

SCIFILECONTENTSREF=["function [] = bug924()";
		"";
		"// Display mode";
		"mode(0);";
		"";
		"// Display warning for floating point exception";
		"ieee(1);";
		"";
		"a = ""milou"";";
		"a = ""milou"",";
		"a = ""milou""";
		"a;";
		"a,";
		"a";
		"[c,d] = svd(1);";
		"[c,d] = svd(1),";
		"[c,d] = svd(1)";
		"b = a;";
		"b = a,";
		"b = a";
		"endfunction"]

if or(SCIFILECONTENTSREF<>SCIFILECONTENTS) then pause,end
