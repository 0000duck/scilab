// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2006-2008 - INRIA - Serge STEER <serge.steer@inria.fr>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 1772 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1772
//
// <-- Short Description -->
//    There is a problem while inserting an object of type list in an undefined struct
//    field

S.x=1;
ok=%t
try
  S.y.z=list()	
catch
  ok=%f
end
if ok then ok=S.y.z==list(),end
affich_result(ok,1772);
