/*------------------------------------------------------------------------*/
/* file: sci_showalluimenushandles.c                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Allan Cornet, Fabrice Leray, Jean-Baptiste Silvy             */
/* desc : interface for howalluimenushandles routine                      */
/*------------------------------------------------------------------------*/

#include "sci_showalluimenushandles.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "HandleManagement.h"

/*-----------------------------------------------------------------------------------*/
int sci_showalluimenushandles( char *fname, unsigned long fname_len )
{
  CheckRhs(1,1);
  CheckLhs(1,1);
	
  if ( version_flag() != 0 )
  {
    Scierror(999,"Not valid under old graphics mode.");
    return 0;
  }

  if (VarType(1) == sci_handles)
  {
    sciPointObj *pParent=NULL;
    int m1,n1,l1;

    GetRhsVar(1,"h",&m1,&n1,&l1);
    pParent = sciGetPointerFromHandle((long)*hstk(l1));

    if (sciGetEntityType (pParent) != SCI_FIGURE ) 
    {
      Scierror(999,"Invalid parameter. must be a Figure handle");
      return 0;
    }
    else
    {
      SciShowAllUimenus(pParent);
    }
  }
  else
  {
    Scierror(999,"Invalid parameter. must be a Figure handle");
  return 0;
  }
  LhsVar(1)=0;
  return 0;
}
/*-----------------------------------------------------------------------------------*/
int SciShowAllUimenus( sciPointObj * pparent )
{
  sciSons * psonstmp = sciGetLastSons(pparent) ;

  while(psonstmp != (sciSons *) NULL)
  {   
    if( sciGetEntityType(psonstmp->pointobj) == SCI_UIMENU )
    {
      pUIMENU_FEATURE(psonstmp->pointobj)->handle_visible = TRUE;
      SciShowAllUimenus(psonstmp->pointobj);
    }

    psonstmp = psonstmp->pprev;
  }
  return 0;
}
/*-----------------------------------------------------------------------------------*/
