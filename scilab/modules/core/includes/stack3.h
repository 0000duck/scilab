#ifndef STACK3_H 
#define STACK3_H 
#include "machine.h"

/**
 * Read a matrix in scilab's internal stack 
 * calling sequence 
 *     logic=creadmat('matrixname',m,n,scimat)
 * @example
 *    Amat is a real 2 x 3 scilab matrix 
 *    your subroutine should be as follows: 
 *    subroutine mysubr(...) 
 *    ... 
 * @code
 *    call readmat('Amat',m,n,scimat) 
 *    => m=3 , n=2, and scimat(1)=Amat(1,1) 
 *                      scimat(2)=Amat(2,1) 
 *                      scimat(3)=Amat(3,1) 
 *                      scimat(4)=Amat(1,2) ... 
 *                      scimat(5)=Amat(3,2) 
 *                      scimat(6)=Amat(3,2) 
 * @endcode
 * @param name__ character string; name of the scilab variable. 
 * @param m number of rows
 * @param n number of columns
 * @param scimat  matrix entries stored columnwise
 * @param name_len
 * @return if the operation successed (true) or not (false)
 */
int C2F(readmat)  __PARAMS((char *name__, integer *m, integer *n, double *scimat, unsigned long name_len));


int C2F(creadmat)  __PARAMS((char *name__, integer *m, integer *n, double *scimat, unsigned long name_len));
int C2F(creadcmat)  __PARAMS((char *name__, integer *m, integer *n, double *scimat, unsigned long name_len));
int C2F(creadsmat)  __PARAMS((char *name__, integer *m, integer *n, double *scimat, unsigned long name_len));

/**
 * cwritemat writes vector/matrix in scilab's internal stack
 * logic=cwritemat('matrixname'//char(0),m,n,mat)
 * @param name__ character string; name of the scilab variable ( null terMinated) 
 * @param m number of rows 
 * @param n number of columns 
 * @param mat matrix entries stored columnwise in Scilab object
 * @param name_len strlen of name__ (Fortran needs it)
 * @return if the operation successed (true) or not (false)
 */
int C2F(cwritemat)  __PARAMS((char *name__, integer *m, integer *n, double *mat, unsigned long name_len));
int C2F(cwritecmat)  __PARAMS((char *name__, integer *m, integer *n, double *mat, unsigned long name_len));
int C2F(readchain)  __PARAMS((char *name__, integer *itslen, char *chai, unsigned long name_len, unsigned long chai_len));
int C2F(creadchain)  __PARAMS((char *name__, integer *itslen, char *chai, unsigned long name_len, unsigned long chai_len));
int C2F(creadchains)  __PARAMS((char *name__, integer *ir, integer *ic, integer *itslen, char *chai, unsigned long name_len, unsigned long chai_len));
int C2F(cwritechain)  __PARAMS((char *name__, integer *m, char *chai, unsigned long name_len, unsigned long chai_len));
int C2F(matptr)  __PARAMS((char *name__, integer *m, integer *n, integer *lp, unsigned long name_len));
int C2F(cmatptr)  __PARAMS((char *name__, integer *m, integer *n, integer *lp, unsigned long name_len));
int C2F(cmatcptr)  __PARAMS((char *name__, integer *m, integer *n, integer *lp, unsigned long name_len));
int C2F(cmatsptr)  __PARAMS((char *name__, integer *m, integer *n, integer *ix, integer *j, integer *lp, integer *nlr, unsigned long name_len));

/** 
read a boolean matrix in scilab stack
*/
int C2F(creadbmat)(char *namex, integer *m, integer *n, int *scimat, unsigned long name_len);

/**
write a boolean matrix in scilab stack
*/
int C2F(cwritebmat)(char *namex, integer *m, integer *n, int *mat, unsigned long name_len);

/**
get pointer on a named boolean matrix 
*/
int C2F(cmatbptr)(char *namex, integer *m,integer *n,integer *lp, unsigned long name_len);

int C2F(str2name)  __PARAMS((char *name__, integer *id, unsigned long name_len));
int C2F(objptr)  __PARAMS((char *name__, integer *lp, integer *fin, unsigned long name_len));
int C2F(putvar) __PARAMS((int *number, char *namex, unsigned long name_len ));


/**
 * returns length of a "chain variable" in scilab
 * example :
 * in scilab --> str = "abcdefghijklmnopqrstuvwxyz";
 * in C getlengthchain("str") returns 26
 * @param namex
 * @return  -1 if error
*/ 
int getlengthchain(char *namex);

#endif 


