// <-- Non-regression test for bug 1786 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1786
//
// <-- Short Description -->
//    Scilab 4.0-RC1
//    Handle Label : rotation of the text
//
//    Changing field Label.auto_rotation to off does not causes the rotation of the
//    text. To force the rotation, it is necessary to re-affect the value of
//    Label.font_angle.
//
//    jacques-Deric

// Copyright INRIA
// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2005
// Date : 6 fevrier 2005

hf  = scf (1);
ha  = gca ();
hlt = ha.title;

hlt.text = "Titre/Title";

if hlt.auto_rotation <> "on" then pause,end
if hlt.auto_position <> "on" then pause,end

hlt.font_angle = 180;
if hlt.auto_rotation <> "off" then pause,end

hlt.position = [0.5,0.5];;
if hlt.auto_position == "off" then pause,end
