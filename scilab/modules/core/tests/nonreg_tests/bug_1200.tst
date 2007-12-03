// <-- Non-regression test for bug 1200 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1200
//
// <-- Short Description -->
//    Incoherence dans le format d'un nombre.
//    En prenant par exemple j=0.001, on obtient un affichage 
//    incoherent avec format :
//    format("v",6) => 0.001
//    format("v",7) => 1.E-3
//    format("v",8) => 0.001

// Pierre MARECHAL - Scilab Project
// Copyright INRIA
// 1er juin 2005

J=0.001;
format("v",7);
diary(TMPDIR+"/bug1200.dia");
disp(J);
diary(0);

DIAFILECONTENTS=mgetl(TMPDIR+"/bug1200.dia");

REFFILECONTENTS=[" ";
	"    0.001  ";]

if or(DIAFILECONTENTS<>REFFILECONTENTS) then pause,end
