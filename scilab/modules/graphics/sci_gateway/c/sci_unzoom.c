/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - ENPC - Jean-Philipe Chancelier
 * Copyright (C) 2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: sci_unzoom.h                                                     */
/* desc : interface for unzoom routine                                    */
/*------------------------------------------------------------------------*/

#include "sci_unzoom.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "MALLOC.h"
#include "gw_graphics.h"
#include "SetProperty.h"
#include "axesScale.h"
#include "localization.h"
#include "CurrentObjectsManagement.h"
#include "sciprint.h"
#include "getPropertyAssignedValue.h"

/*--------------------------------------------------------------------------*/
int sci_unzoom(char *fname,unsigned long fname_len)
{
  sciPointObj ** unzoomedSubwins = NULL;
  int nbUnzoomedSubwins = 0;
  CheckRhs(0,1) ;
  CheckLhs(0,1) ;
  if ( Rhs == 0 )
  {
    sciPointObj * curSubwin = sciGetCurrentSubWin();
    unzoomedSubwins = &curSubwin;
    nbUnzoomedSubwins = 1;
  }
  else
  {
    int m,n,i;
    int stackPointer;
    GetRhsVar(1,GRAPHICAL_HANDLE_DATATYPE,&m,&n,&stackPointer);
    
    nbUnzoomedSubwins = m * n;

    unzoomedSubwins = MALLOC( nbUnzoomedSubwins * sizeof(sciPointObj *));
    
    if (unzoomedSubwins == NULL)
    {
      sciprint(_("%s: no more memory.\n"),fname);
      LhsVar(1)=0; 
      return 0;
    }

    for ( i = 0 ; i < nbUnzoomedSubwins ; i++ )
    {
      unzoomedSubwins[i] = sciGetPointerFromHandle(getHandleFromStack(stackPointer + i));
      if (sciGetEntityType(unzoomedSubwins[i]) != SCI_SUBWIN)
      {
        sciprint(_("%s: Wrong type for input argument: vector of axes handles expected.\n"),fname);
        FREE(unzoomedSubwins);
        LhsVar(1)=0; 
        return 0;
      }
      //sciSetZooming(sciGetPointerFromHandle(getHandleFromStack(stackPointer + i)), FALSE); /** Correction Bug 1476 + Warning Windows **/
    }
    
    

  }

  sciUnzoom(unzoomedSubwins, nbUnzoomedSubwins);

  if (Rhs != 0) 
  {
    FREE(unzoomedSubwins);
  }
  

  LhsVar(1)=0; 
  return 0;
}
/*--------------------------------------------------------------------------*/
