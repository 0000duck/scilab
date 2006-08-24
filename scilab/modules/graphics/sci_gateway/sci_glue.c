/*------------------------------------------------------------------------*/
/* file: sci_glue.h                                                       */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for glue routine                                      */
/*------------------------------------------------------------------------*/

#include "sci_glue.h"
#include "stack-c.h"
#include "BuildObjects.h"
#include "MALLOC.h"
#include "GetProperty.h"
#include "../../elementaries_functions/includes/calelm.h"

/*-----------------------------------------------------------------------------------*/
int sci_glue( char * fname, unsigned long fname_len )
{
  integer numrow,numcol,l1,l2,lind,n,cx1=1,ret ;
  unsigned long hdl, parenthdl;
  long *handelsvalue;
  int outindex,i;
  sciPointObj *pobj;

  CheckRhs(1,1);
  CheckLhs(0,1);

  /*  set or create a graphic window */
  SciWin();
  GetRhsVar(1,"h",&numrow,&numcol,&l1); /* We get the scalar value if it is ones */
  n=numrow*numcol;
  CreateVar(Rhs+1,"d",&numrow,&numcol,&l2);
  CreateVar(Rhs+2,"i",&numrow,&numcol,&lind);
  if (n>1) {
    C2F(dcopy)(&n, stk(l1), &cx1, stk(l2), &cx1);
    C2F(dsort)(stk(l2),&n,istk(lind));
    for (i = 1; i < n;i++) {
      if (*stk(l2+i) == *stk(l2+i-1)) {
        Scierror(999,"%s :each handle should not appear twice\r\n",fname);
        return 0;
      }
    }
  }
  /* we must change the pobj to the Compound type */
  handelsvalue = MALLOC(n*sizeof(long));
  for (i = 0; i < n;i++)
  {
    handelsvalue[i] = (unsigned long) (hstk(l1))[i];
    pobj = sciGetPointerFromHandle(handelsvalue[i]);
    if (pobj == NULL) {
      Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
      return 0;
    }
    parenthdl = (unsigned long ) sciGetHandle(sciGetParent (pobj));
    if (i == 0)
      hdl=parenthdl;
    if  (parenthdl != hdl)
    {
      Scierror(999,"%s: Objects must have the same parent\r\n",fname);
      return 0;
    }

  }
  ret = CheckForCompound (handelsvalue, n);
  if (ret>0) {
    Scierror(999,"%s: handle %d cannot be glued (invalid parent)\r\n",fname,ret);
    return 0;
  }
  if (ret<0) {
    Scierror(999,"%s: handle %d cannot be glued (invalid type)\r\n",fname,-ret);
    return 0;
  }
  sciSetCurrentObj ((sciPointObj *)ConstructCompound (handelsvalue, n));

  numrow = 1;
  numcol = 1;
  CreateVar(Rhs+3,"h",&numrow,&numcol,&outindex);
  hstk(outindex)[0] = sciGetHandle((sciPointObj *) sciGetCurrentObj());
  LhsVar(1) = Rhs+3;
  FREE(handelsvalue);
  return 0;
}
/*-----------------------------------------------------------------------------------*/