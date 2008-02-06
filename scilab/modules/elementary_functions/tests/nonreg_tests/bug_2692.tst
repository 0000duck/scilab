// <-- Non-regression test for bug 2692 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=2692
//
// <-- Short Description -->
//   bitand( int8(x) , int8(y) ) doesn't return an int8 object.

// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2008
// Date : Feb 2008


// uint8
// =============================================================================

a = uint8(77);
b = uint8(89);

c = bitand(a,b);
if inttype(c) <> 11 then pause, end

c = bitor(a,b);
if inttype(c) <> 11 then pause, end

c = bitxor(a,b);
if inttype(c) <> 11 then pause, end

// uint16
// =============================================================================

a = uint16(58);
b = uint16(24);

c = bitand(a,b);
if inttype(c) <> 12 then pause, end

c = bitor(a,b);
if inttype(c) <> 12 then pause, end

c = bitxor(a,b);
if inttype(c) <> 12 then pause, end

// uint32
// =============================================================================

a = uint32(44);
b = uint32(56);

c = bitand(a,b);
if inttype(c) <> 14 then pause, end

c = bitor(a,b);
if inttype(c) <> 14 then pause, end

c = bitxor(a,b);
if inttype(c) <> 14 then pause, end
