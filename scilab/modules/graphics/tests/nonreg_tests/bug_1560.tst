// <-- TEST WITH GRAPHIC -->

// <-- Non-regression test for bug 1560 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1560
//
// <-- Short Description -->
//    (Following of bug 1558)
//    In a 3D representation, under the rotation angles [0,270], the third 
//    coordinate z1 of the first point of a segment is ignored, while the 
//    third coordinate z2 of the second point is considered.
//
//    Jacques-Deric

// Copyright INRIA
// Scilab Project - Jean-Baptiste Silvy
// Copyright INRIA 2006
// Date : 11 janvier 2006

hf = scf (1);
ha = hf.children;
ha.axes_visible = "on";
ha.view = "3d";
ha.box = "on";

xsegs ([0.0,0.0], [1.0,1.0]); 
hs10 = gce ();
hs10.data (1,1) = 1.00;  // x1
hs10.data (1,2) = 0.60;  // y1
hs10.data (2,1) = 0.70;  // x2
hs10.data (2,2) = 0.45;  // y2
hs10.data,

ha.rotation_angles = [0,270];
hs10.data (1,3) =-0.30;  // z1 
hs10.data (2,3) =-0.40;  // z2
hs10.data,	

ha.rotation_angles = [0,0];

reference = [ 1, 0.6, -0.3 ; 0.7, 0.45, -0.4 ] ;

// check that the segment z coordinates are modified
if hs10.data <> referenceif then pause,end
