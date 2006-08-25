/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stack-c.h"
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
extern int C2F(complexify)  __PARAMS((int *num));
/*-----------------------------------------------------------------------------------*/
int C2F(intslash)(char *fname,unsigned long fname_len)
{
	int *header1;int *header2;
	int CmplxA;int CmplxB;int ret;int X;

	extern int C2F(intdgesv4) __PARAMS((char *fname, unsigned long fname_len));
	extern int C2F(intzgesv4) __PARAMS((char *fname, unsigned long fname_len));

	/*   X = slash(A,B) <=> X = A / B */
	header1 = (int *) GetData(1);    header2 = (int *) GetData(2);
	CmplxA=header1[3];   CmplxB=header2[3];
	if ((header1[2]!=header2[2])&(header1[1]*header1[2]==1)) {
		C2F(com).fun=0;
		C2F(com).fin=-C2F(com).fin;
		return 0;
	}
	switch (CmplxA) {
  case REAL:   
	  switch (CmplxB) {
  case REAL :
	  /* A real, Breal */
	  ret = C2F(intdgesv4)("slash",5L);
	  break;
  case COMPLEX :
	  /* A real, B complex : complexify A */
	  C2F(complexify)((X=1,&X));
	  ret = C2F(intzgesv4)("slash",5L);
	  break;
  default:
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  break;
	  }
	  return 0;
  case COMPLEX :
	  switch (CmplxB) {
  case REAL :
	  /* A complex, B real : complexify B */
	  C2F(complexify)((X=2,&X));
	  ret = C2F(intzgesv4)("slash",5L);
	  break;
  case COMPLEX :
	  /* A complex, B complex */
	  ret = C2F(intzgesv4)("slash",5L);
	  break;
  default:
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  break;
	  }
	  return 0;
  default :
	  Scierror(999,"%s: Invalid input! \r\n",fname);
	  return 0;
	}
	return 0;
}
/*-----------------------------------------------------------------------------------*/
