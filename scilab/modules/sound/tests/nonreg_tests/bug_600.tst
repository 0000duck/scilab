// <-- INTERACTIVE TEST -->
//
// <-- Non-regression test for bug 600 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=600
//
// <-- Short Description -->
//    I am not able to hear the sounds using either the 'Sound'
//    or 'playsnd' functions.
//
//       The sound card is working properly with all other
//    softwares.all other wave funstions are working such as
//    wavread loadwave etc...

disp("activate your sound card, and run this file");
disp("if you hear something, that means the playsnd & PlaySnd work");

y=wavread("SCI/demos/signal/sound/chimes.wav");
playsnd(y);

PlaySound("SCI/demos/signal/sound/chimes.wav");
