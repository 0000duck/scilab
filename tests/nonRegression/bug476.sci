// <-- Non-regression test for bug 476 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=476
//
// <-- Short Description -->
//    Bug Report Id: 120442003624185651
//
//
//    On Scilab CVS with " %hm_find " function
//    The Error Messages are:
//      wrong result
//    Commands:  -->a=hypermat([3,3,1],int8(1:9));
//
//    -->[i,j]=find(a==5)   
//     j  =
//
//        1.  
//     i  =
//
//        0.  
//
//    -->[i,j,k]=find(a==5)
//     k  =
//
//        1.  
// ...

//correct=%F
a=hypermat([3,3,1],int8(1:9))
[i,j]=find(a==5) 
[k,l,m]=find(a==5)

affich_result((m==1)&((i==k)==(j==l)), 476)
