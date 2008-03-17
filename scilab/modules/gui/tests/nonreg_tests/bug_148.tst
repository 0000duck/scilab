// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Vincent COUVERT
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 148 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=148
//
// <-- Short Description -->
//    plot() plots fullscreen despite the xsetech() restriction.

// <-- INTERACTIVE TEST -->

xbasc();

xsetech([0 .5 .5 .5]);

plot2d(1:10,1:10)
