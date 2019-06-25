// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2019 - Stéphane MOTTELET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 15248 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15248
//
// <-- Short Description -->
// lsq() is leaking memory

m1 = getmemory();
a = rand(100,100);
b = rand(100,100);
for i=1:20000
    x = lsq(a,b);
end
clear i a b x
m2 = getmemory();
assert_checktrue((m1-m2)/m1 <= 0);