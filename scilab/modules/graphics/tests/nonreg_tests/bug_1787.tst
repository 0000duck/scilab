// <-- Non-regression test for bug 1787 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1787
//
// <-- Short Description -->
//    Scilab 4.0 RC1
//    The calling of procedure xtitle bugs when the drawing of boxes is asked.
//
//    Jacques-Deric

// Copyright INRIA
// Scilab Project - Jean-Baptiste Silvy
// Copyright INRIA 2006
// Date : 10/02/2006

titleStr  = "Scilab P0W3R" ;
xLabelStr = "XXX" ;
yLabelStr = "YYY" ;

xtitle("Scilab P0W3R",'XXX','YYY',1) ;
a = gca() ;
title  = a.title   ;
xLabel = a.x_label ;
yLabel = a.y_label ;

// check that a box is drawn around the labels
// and that they have the rigth text

if ( title.text  <> titleStr  ) | ( title.fill_mode  <> 'on' ) then pause,end
if ( xLabel.text <> xLabelStr ) | ( xLabel.fill_mode <> 'on' ) then pause,end
if ( yLabel.text <> yLabelStr ) | ( yLabel.fill_mode <> 'on' ) then pause,end
