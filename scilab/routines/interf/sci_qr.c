/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "../stack-c.h"
/*-----------------------------------------------------------------------------------*/
#define SCI_DOUBLE 1
#define STRING  10
#define REAL 0
#define COMPLEX 1
#define FUNCTION 13
#define STRINGREAL 27
#define STRINGCOMPLEX 12
#define YES 1
#define NO 0
/*-----------------------------------------------------------------------------------*/
int C2F(intqr)(char *fname,unsigned long fname_len)
{
	int *header1;int *header2;
	int Cmplx;int ret; double *snd; double tol;

	extern int C2F(intdgeqpf3) __PARAMS((char *fname, unsigned long fname_len));
	extern int C2F(intzgeqpf3) __PARAMS((char *fname, unsigned long fname_len));
	extern int C2F(intdgeqpf4) __PARAMS((char *fname, unsigned long fname_len));
	extern int C2F(intzgeqpf4) __PARAMS((char *fname, unsigned long fname_len));
	extern int C2F(doldqr) __PARAMS((double *tol,char *fname, unsigned long fname_len));
	extern int C2F(zoldqr) __PARAMS((double *tol,char *fname, unsigned long fname_len));

	if (GetType(1)!=1) {
		OverLoad(1);
		return 0;
	}
	header1 = (int *) GetData(1);
	Cmplx=header1[3];

	if (header1[0] == 10) Cmplx=10;

	if (Lhs==4) {   /* obsolete : [Q,R,rk,E]=qr(A) or = qr(A,tol)   */
		if (Rhs==2) {
			snd = (double *) GetData(2);
			tol = snd[2];
		}
		else {
			tol = -1;Rhs=1;
		}
		switch (Cmplx) {
	case REAL :
		ret = C2F(doldqr)(&tol,"qr",2L);
		break;
	case COMPLEX :
		ret = C2F(zoldqr)(&tol,"qr",2L); 
		break;
	default :
		Scierror(999,"%s: Invalid input! \r\n",fname);
		return 0;
		}
		return 0;
	}
	switch (Rhs) {
  case 1:   /*   qr(A)   */
	  switch (Cmplx) {
  case REAL :
	  ret = C2F(intdgeqpf3)("qr",2L);
	  break;
  case COMPLEX :
	  ret = C2F(intzgeqpf3)("qr",2L);
	  break;
  default :
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  break;
	  }
	  break;
  case 2 :   /*   qr(A, something)   */
	  header2 = (int *) GetData(2);
	  switch (header2[0]) {
  case STRING  :
	  /* Economy size:  ...=qr(A,"e")  */
	  switch (Cmplx) {
  case REAL :
	  ret = C2F(intdgeqpf4)("qr",2L);
	  break;
  case COMPLEX :
	  ret = C2F(intzgeqpf4)("qr",2L);  
	  break;
  default :
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  break;
	  }
	  break;
  default:
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  break;
	  }
	  return 0;
  default :
	  Scierror(999,"%s: Invalid call! \r\n",fname);
	  break;
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
