/*------------------------------------------------------------------------*/
/* file: sci_UImenu.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Allan Cornet, Fabrice Leray, Jean-Baptiste Silvy             */
/* desc : interface for sci_UImenu routine                                */
/*------------------------------------------------------------------------*/

#include <stdio.h> 
#include <string.h> 
/*--------------------------------------------------------------------------*/
#include "sci_UImenu.h"
#include "MALLOC.h" /* MALLOC */
#include "ObjectStructure.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "localization.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "CurrentObjectsManagement.h"
#include "SetPropertyStatus.h"
#include "SetHashTable.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
int sci_UImenu( char *fname,unsigned long fname_len )
{
  int nbRow = 0, nbCol = 0, stkAdr = 0;

  int setStatus = SET_PROPERTY_SUCCEED;

  int inputIndex = 0, beginIndex = 0;

  char *labelmenu=NULL;
  char *callbackmenu=NULL;
  char *propertyName=NULL;

  sciPointObj *pParent=NULL;

  unsigned long GraphicHandle = 0;

  /* Create a new menu */
  GraphicHandle=sciGetHandle(ConstructUimenu (pParent,labelmenu,callbackmenu,TRUE));

  /**
   * Odd number of input arguments
   * First input is the parent ID
   * All event inputs are property names
   * All odd (except first) inputs are property values
   */
  if (Rhs%2==1)
    {
      if (VarType(1) != sci_handles)
        {
          Scierror(999,_("%s: Wrong type for first input argument: Graphic handle expected.\n"),fname);
          return FALSE;
        }
      else /* Get parent ID */
        {
	  GetRhsVar(1,GRAPHICAL_HANDLE_DATATYPE, &nbRow, &nbCol, &stkAdr);

          if (nbRow*nbCol != 1)
            {
	      Scierror(999,_("%s: Wrong size for first input argument: Single handle expected.\n"),fname);
	      return FALSE;
            }
	  pParent=sciGetPointerFromHandle((long)*hstk(stkAdr));
	  if ( (sciGetEntityType (pParent) != SCI_FIGURE) && (sciGetEntityType (pParent) != SCI_UIMENU) )
	    {
	      Scierror(999,_("%s: Wrong type for parent: Figure or uimenu expected.\n"),fname);
	      return FALSE;
	    }

          // Set the parent property
          callSetProperty((sciPointObj*) GraphicHandle, 1, sci_handles, nbRow, nbCol, "parent");
          return TRUE;

        }

      // First input parameter which is a property name
      beginIndex = 2;
    }
  /**
   * Even number of input arguments
   * All odd inputs are property names
   * All even inputs are property values
   */
  else
    {
      // First input parameter which is a property name
      beginIndex = 1;
    }

  /* Read and set all properties */
  for(inputIndex = beginIndex; inputIndex<Rhs; inputIndex = inputIndex+2)
    {
      /* Read property name */
      if (VarType(inputIndex) != sci_strings)
        {
          Scierror(999, _("%s: Wrong type for property name: String expected.\n"));
          return FALSE;
        }
      else
        {
          GetRhsVar(inputIndex,STRING_DATATYPE, &nbRow, &nbCol, &stkAdr);
          propertyName = cstk(stkAdr); 
        }
      
      /* Read property value */
      switch (VarType(inputIndex + 1)) {
      case sci_matrix:
        GetRhsVar(inputIndex + 1,MATRIX_OF_DOUBLE_DATATYPE,&nbRow,&nbCol,&stkAdr);
        setStatus = callSetProperty((sciPointObj*) GraphicHandle, stkAdr, sci_matrix, nbRow, nbCol, propertyName);
        break;
      case sci_strings:
        GetRhsVar(inputIndex + 1,STRING_DATATYPE,&nbRow,&nbCol,&stkAdr);
        setStatus = callSetProperty((sciPointObj*) GraphicHandle, stkAdr, sci_strings, nbRow, nbCol, propertyName);
        break;
      case sci_handles:
        GetRhsVar(inputIndex + 1,GRAPHICAL_HANDLE_DATATYPE,&nbRow,&nbCol,&stkAdr);
        setStatus = callSetProperty((sciPointObj*) GraphicHandle, stkAdr, sci_handles, nbRow, nbCol, propertyName);
        break;
      default:
        setStatus = SET_PROPERTY_ERROR;
        break;
      }
      if (setStatus == SET_PROPERTY_ERROR)
        {
          Scierror(999, _("Could not set property %s.\n"), propertyName);              
          return FALSE;
        }
    }

  /* Create return variable */
  nbRow = 1;
  nbCol = 1;
  CreateVar(Rhs+1, GRAPHICAL_HANDLE_DATATYPE, &nbRow, &nbCol, &stkAdr);
  *hstk(stkAdr) = GraphicHandle;

  LhsVar(1)=Rhs+1;

  return TRUE;
}
/*--------------------------------------------------------------------------*/
