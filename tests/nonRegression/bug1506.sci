// <-- Non-regression test for bug 1506 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=1506
//
// <-- Short Description -->
//    datevec(datenum()) gives wrong result.
//
//    datevec(datenum()) is supposed to give the actual time, right?
//    On my box (Redhat Linux x86) it now gives
//    !   2005.    7.    27.    15.    10.    50.249993 !
//
//    where the date on a unix shell gives:
//    Wed Jul 27 12:02:16 CEST 2005
//
//    So the date is correct but not the time
//
//    Fabian

// Copyright INRIA
// Scilab Project - Pierre MARECHAL
// Copyright INRIA 2005
// Date : 28 d�cembre 2005

now = getdate();

one_sec = datenum(now(1),now(2),now(6),now(7),now(8),30) -  datenum(now(1),now(2),now(6),now(7),now(8),29);
one_sec_ref = 1/(3600*24);
test1  = (abs( (one_sec - one_sec_ref) / one_sec ) < 1e-5);

one_min = datenum(now(1),now(2),now(6),now(7),18,now(9)) -  datenum(now(1),now(2),now(6),now(7),17,now(9));
one_min_ref = 1/(60*24);
test2  = (abs( (one_min - one_min_ref) / one_min ) < 1e-6);

one_hour = datenum(now(1),now(2),now(6),18,now(8),now(9)) -  datenum(now(1),now(2),now(6),17,now(8),now(9));
one_hour_ref = 1/24;
test3  = (abs( (one_hour - one_hour_ref) / one_hour ) < 1e-8);

if ( test1 & test2 & test3 ) then
	affich_result(%T,1506);
else
	affich_result(%F,1506);
end
