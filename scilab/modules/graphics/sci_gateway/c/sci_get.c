/*------------------------------------------------------------------------*/
/* file: sci_get.c                                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : interface for sci_get routine                                   */
/*------------------------------------------------------------------------*/
#include "sci_get.h"
/*--------------------------------------------------------------------------*/

#include "stack-c.h"
#include "GetProperty.h"
#include "HandleManagement.h"
#include "InitObjects.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "CurrentObjectsManagement.h"
#include "CurrentObjectsManagement.h"

#include "../src/c/getHandleProperty/GetHashTable.h"

#include "../src/c/getHandleProperty/getHandleProperty.h"

/*--------------------------------------------------------------------------*/
int sciGet(sciPointObj *pobj,char *marker);
/*--------------------------------------------------------------------------*/
int sciGet(sciPointObj *pobj,char *marker)
{
  /* get the hash_table to retrieve functions */
  createScilabGetHashTable() ;

  /* find the function in the hashtable relative to the property name */
  /* and call it */
  return callGetProperty( pobj, marker ) ;
}
/*--------------------------------------------------------------------------*/
static char error_message[128];
/*--------------------------------------------------------------------------*/
int sci_get(char *fname,unsigned long fname_len)
{
  integer m1,n1,numrow2,numcol2,l2 ;
  int l1;
  unsigned long hdl;

  int lw;
  sciPointObj *pobj;

  CheckRhs(1,2);
  CheckLhs(0,1);
  
  /*  set or create a graphic window */

  /* le premier argument peut etre soit un Id, ou un marker(auquel cas, get renvoi la valeur de 
     l'objet courant ) */
  switch(VarType(1))
    {
    case 1: /* tclsci handle */
      lw = 1 + Top - Rhs;
      C2F(overload)(&lw,"get",3);
      return 0;
      break;
    case sci_handles: /* scalar argument (hdl + string) */
      CheckRhs(2,2);
      GetRhsVar(1,GRAPHICAL_HANDLE_DATATYPE,&m1,&n1,&l1);
      if (m1!=1||n1!=1) { 
	lw = 1 + Top - Rhs;
	C2F(overload)(&lw,"get",3);
        return 0;
      }
      GetRhsVar(2,STRING_DATATYPE,&numrow2,&numcol2,&l2);
      if ( *hstk(l1) != sciGetHandle(getFigureModel()) && *hstk(l1) != sciGetHandle(getAxesModel())
	   &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_title)
	   &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_x_label)
	   &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_y_label) /* Addings here F.Leray 10.06.04 */
	   &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_z_label))
	{

	  hdl = (unsigned long)*hstk(l1); /* on recupere le pointeur d'objet par le handle */
          

	}/* DJ.A 08/01/04 */
      else
      {
	hdl = (unsigned long)*hstk(l1);
      }
      break;
    case sci_strings:/* string argument (string) */
      CheckRhs(1,1);
      GetRhsVar(1,STRING_DATATYPE,&numrow2,&numcol2,&l2);
      if (strcmp(cstk(l2),"default_figure") !=0 && strcmp(cstk(l2),"default_axes") !=0 )
	{
	  if (strcmp(cstk(l2),"old_style") == 0 || strcmp(cstk(l2),"current_figure") ==0) {
	    hdl = (unsigned long)0;
	  }
	  else
	    {
              sciPointObj * ppobj;

              /* Test debug F.Leray 13.04.04 */
              if ((strcmp(cstk(l2),"children") != 0) &&  
                (strcmp(cstk(l2),"zoom_") !=0) && 
                (strcmp(cstk(l2),"clip_box") !=0) && 
                (strcmp(cstk(l2),"auto_") !=0)) 
              {
                SciWin();
                ppobj = sciGetCurrentObj();
                hdl = (unsigned long) sciGetHandle(sciGetCurrentObj());
              }
              else
              {
                hdl = (unsigned long) sciGetHandle(sciGetCurrentSubWin());/* on recupere le pointeur d'objet par le handle */
              }

	    }/* DJ.A 08/01/04 */
	}
      else
      {
	hdl = (unsigned long)0;
      }
    
      break;
    default:
      lw = 1 + Top - Rhs;
      C2F(overload)(&lw,"get",3);
	  return 0;
      /*Scierror(999,"%s: Incorrect argument\n",fname);*/
      break;
    }
  /* cstk(l2) est la commande, l3 l'indice sur les parametres de la commande */
  CheckLhs(0,1);
  if (hdl == (unsigned long)0 ) {
    if (sciGet((sciPointObj *) NULL, cstk(l2))!=0) {
      Scierror(999,"%s: %s\n",fname,error_message);
      return 0;
    }
  }
  else
  {
    if ( (pobj = sciGetPointerFromHandle(hdl) ) )
    {

      if (sciGet(pobj, cstk(l2))!=0)
      {
        Scierror(999,"%s: %s\n",fname,error_message);
        return 0;
      }
    }
    else
    {
      Scierror(999,"%s :the handle is not or no more valid\n",fname);
    }
  }
  LhsVar(1)=Rhs+1;
  return 0;
}
/*--------------------------------------------------------------------------*/
