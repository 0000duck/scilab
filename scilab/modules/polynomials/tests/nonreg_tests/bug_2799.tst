// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2006-2008 - INRIA -Serge Steer
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 2799 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2799
//
// <-- Short Description -->
//    Failure to assign boolean values to a sub-matrix when the matrix does 
//    not exist
//    clear A;A(:,1) = [%s;%s+1];
clear A;A(:,1) = [%s;%s+1];
if or(A<>[%s;%s+1]) then pause,end
clear A;A(1,:) = [%s+1;%s];
if or(A<>[%s+1,%s]) then pause,end
