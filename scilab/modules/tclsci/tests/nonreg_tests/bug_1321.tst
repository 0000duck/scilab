// <-- Non-regression test for bug 1321 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1321
//
// <-- Short Description -->
//    Function findobj does not work when property value contains
//    capital letters and is case sensitive for property name.

// Copyright INRIA
// Scilab Project - V. Couvert

h=figure(1);

t = uicontrol( h, "style","text", ...
  "string","This is a figure", ...
  "position",[50 70 100 100], ...
  "fontsize",15, ...
  "tag","Alabel");

correct = findobj("tag","Alabel")==t & ...
    isempty(findobj("tag","alabel")) & ...
    findobj("Tag","Alabel")==t & ...
    isempty(findobj("Tag","alabel"));

close(1);

if correct == %F then pause,end
