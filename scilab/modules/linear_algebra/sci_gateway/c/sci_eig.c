/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stack-c.h"
#include "issymmetric.h"
#include "gw_linear_algebra.h"
#include "Scierror.h"
/*-----------------------------------------------------------------------------------*/
extern int C2F(complexify)  __PARAMS((int *num));

/* Gonna kill all externs with clear definition !!! */
/* extern int C2F(issymmetric)  __PARAMS((int *num)); */

extern int C2F(intdgeev) __PARAMS((char *fname, unsigned long fname_len));
extern int C2F(intdsyev) __PARAMS((char *fname, unsigned long fname_len));
extern int C2F(intzgeev) __PARAMS((char *fname, unsigned long fname_len));
extern int C2F(intzheev) __PARAMS((char *fname, unsigned long fname_len));

extern int C2F(intdggev) __PARAMS((char *fname, unsigned long fname_len));
extern int C2F(intzggev) __PARAMS((char *fname, unsigned long fname_len));

/*-----------------------------------------------------------------------------------*/
int C2F(inteig)(char *fname,unsigned long fname_len);
/*-----------------------------------------------------------------------------------*/
int C2F(inteig)(char *fname,unsigned long fname_len)
{
  int *header1, *header2;
  int CmplxA, CmplxB;
  int ret;int Symmetric;int X;

  switch (Rhs) {
  case 1:   /* spec(A)   */
    if (GetType(1)!=sci_matrix) {
      OverLoad(1);
      return 0;
    }
    header1 = (int *) GetData(1);
    CmplxA=header1[3];
    Symmetric = C2F(issymmetric)((X=1,&X));
    switch (CmplxA) {
    case REAL:
      switch (Symmetric) {
      case NO :
	ret = C2F(intdgeev)("spec",4L);
	break;
      case YES :
	ret = C2F(intdsyev)("spec",4L);
	break;
      }
      break;
    case COMPLEX:
      switch (Symmetric) {
      case NO :
	ret = C2F(intzgeev)("spec",4L);
	break;
      case YES:
	ret = C2F(intzheev)("spec",4L);
	break;
      }
      break;
    default:
      Scierror(999,"%s: Invalid input! \n",fname);
      break;
    } /* end switch  (CmplxA) */
    break; /* end case 1 */
  case 2: /* gspec(A,B) */
    if (GetType(1)!=sci_matrix) {
      OverLoad(1);
      return 0;
    }
    if (GetType(2)!=sci_matrix) {
      OverLoad(2);
      return 0;
    }
    header1 = (int *) GetData(1);
    header2 = (int *) GetData(2);
    CmplxA=header1[3];
    CmplxB=header2[3];
    switch (CmplxA) {
    case REAL:
      switch (CmplxB) {
      case REAL :
	/* A real, Breal */
	ret = C2F(intdggev)("gspec",5L);
	break;
      case COMPLEX :
	/* A real, B complex : complexify A */
	C2F(complexify)((X=1,&X));
	ret = C2F(intzggev)("gspec",5L);
	break;
      default:
	Scierror(999,"%s: Invalid input! \n",fname);
	break;
      }
      break;
    case COMPLEX :
      switch (CmplxB) {
      case REAL :
	/* A complex, B real : complexify B */
	C2F(complexify)((X=2,&X));
	ret = C2F(intzggev)("gspec",5L);
	break;
      case COMPLEX :
	/* A complex, B complex */
	ret = C2F(intzggev)("gspec",5L);
	break;
      default:
	Scierror(999,"%s: Invalid input! \n",fname);
	break;
      }
      break;
    default :
      Scierror(999,"%s: Invalid input! \n",fname);
      break;
    } /*end  switch (CmplxA) */
    break;/* end case 2 */
  }/* end switch (Rhs) */
  return 0;
}
/*-----------------------------------------------------------------------------------*/
