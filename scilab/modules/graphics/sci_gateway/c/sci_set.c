/*------------------------------------------------------------------------*/
/* file: sci_set.h                                                        */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : interface for sci_set routine                                   */
/*------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
#include "sci_set.h"
#include "bcg.h"
#include "stack-c.h"
#include "HandleManagement.h"
#include "GetProperty.h"
#include "ObjectStructure.h"
#include "InitObjects.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "DrawObjects.h"
#include "Xcall1.h"
#include "CurrentObjectsManagement.h"
#include "GraphicSynchronizerInterface.h"

#include "getHandleProperty/SetHashTable.h"
#include "getHandleProperty/setHandleProperty.h"
#include "getHandleProperty/SetPropertyStatus.h"


#include "MALLOC.h" /* MALLOC */
#include "DrawingBridge.h"
/*-----------------------------------------------------------------------------------*/
static int sciSet(sciPointObj *pobj, char *marker, int *value, int valueType, int *numrow, int *numcol) ;
/*-----------------------------------------------------------------------------------*/
/**@name int sciset(sciPointObj *pobj,char *marker, long *x, long *y, long *w, long *h)
* Sets the value to the object
*/
static int sciSet(sciPointObj *pobj, char *marker, int *value, int valueType, int *numrow, int *numcol)
{

  /*createScilabSetHashTable() ;*/

  return callSetProperty( pobj, *value, valueType, *numrow, *numcol, marker ) ;

}
/*-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------
 * sciset(choice-name,x1,x2,x3,x4,x5)
 * or   xset()
 *-----------------------------------------------------------*/
int sci_set(char *fname, unsigned long fname_len)
{
  int lw = 0;
  CheckRhs(2,3);
  CheckLhs(0,1);


  if (VarType(1) == sci_matrix) /* tclsci handle */
  {
	  lw = 1 + Top - Rhs;
	  /* call "set" for tcl/tk see tclsci/sci_gateway/c/sci_set.c */
	  C2F(overload)(&lw,"set",3);
	  return 0;
  }
  else /* others types */
  {
	  integer m1,n1,l1,m2,n2,l2,num,cur,na,verb=0;
	  integer numrow3 = 0 ;
	  integer numcol3 = 0 ;
	  integer l3 = 0 ;
	  unsigned long hdl;
	  int t2;
	  BOOL vis_save = FALSE ;
	  sciPointObj *pobj = NULL;

	  int valueType = 0 ; /* type of the rhs */

	  int numrow[4],i;
	  int numcol[4], lxyzcol[4];
	  int ptrindex[2];
	  int setStatus = 0 ; 
	  /* after the call to sciSet get the status : 0 <=> OK,          */ 
	  /*                                          -1 <=> Error,       */
	  /*                                           1 <=> nothing done */

	  /* F.Leray Init. to 0*/
	  for(i=0;i<4;i++)
	  {
		  numrow[i] = 0;
		  numcol[i] = 0;
		  lxyzcol[i] = 0;
	  }
	  ptrindex[0] = 0;
	  ptrindex[1] = 0;

	  startGraphicDataWriting();

	  /*  set or create a graphic window */
	  switch(VarType(1)) 
	  {
		case sci_handles: 
			/* first is a scalar argument so it's a gset(hdl,"command",[param]) */
			/* F.Leray; INFO: case 9 is considered for a matrix of graphic handles*/
			CheckRhs(3,3);
			GetRhsVar(1,GRAPHICAL_HANDLE_DATATYPE,&m1,&n1,&l1); /* Gets the Handle passed as argument */
			if ( *hstk(l1) != sciGetHandle(getFigureModel()) && *hstk(l1) != sciGetHandle(getAxesModel())
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_title)
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_x_label)
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_y_label) /* Addings here F.Leray 10.06.04 */
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_z_label))
				{
					if (m1!=1||n1!=1) 
					{ 
						Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
						endGraphicDataWriting();
						return 0;
					}

					hdl = (unsigned long)*hstk(l1); /* Puts the value of the Handle to hdl */ 

					if (hdl == (unsigned long)0 )
					{
						pobj = (sciPointObj *) NULL;
					}
					else
					{
						pobj = sciGetPointerFromHandle(hdl);
					}
				} 
				else 
				{
					hdl = (unsigned long)*hstk(l1);
					pobj = sciGetPointerFromHandle(hdl);
				}

			GetRhsVar(2,STRING_DATATYPE,&m2,&n2,&l2); /* Gets the command name */  
			if ( *hstk(l1) != sciGetHandle(getFigureModel()) && *hstk(l1) != sciGetHandle(getAxesModel())
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_title)
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_x_label)
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_y_label) 
			  &&  *hstk(l1) != sciGetHandle(pSUBWIN_FEATURE(getAxesModel())->mon_z_label))
			{
				if ((strcmp(cstk(l2),"old_style") !=0) 
				  &&(strcmp(cstk(l2),"default_figure") !=0) 
				  && (strcmp(cstk(l2),"default_axes") !=0) ) SciWin();
			}

			valueType = VarType(3) ;

			if ( valueType == 1 )
			{
				GetRhsVar(3,MATRIX_OF_DOUBLE_DATATYPE,&numrow3,&numcol3,&l3);
			}
			else if ( valueType == 9 )
			{
				GetRhsVar(3,GRAPHICAL_HANDLE_DATATYPE,&numrow3,&numcol3,&l3);
			}
			else if ( valueType == 10 ) 
			{ 
				if (    strcmp( cstk(l2), "tics_labels"  ) != 0
				  && strcmp( cstk(l2), "auto_ticks"   ) != 0
				  && strcmp( cstk(l2), "axes_visible" ) != 0
				  && strcmp( cstk(l2), "axes_reverse" ) != 0
				  && strcmp( cstk(l2), "text"         ) != 0 )
				{
					GetRhsVar(3,STRING_DATATYPE,&numrow3,&numcol3,&l3);
				} 
				else
				{
					GetRhsVar(3,MATRIX_OF_STRING_DATATYPE,&numrow3,&numcol3,&l3);
				}
		  }
		  break;

		case sci_strings:/* first is a string argument so it's a gset("command",[param]) */ 
			CheckRhs(2,2);
			GetRhsVar(1,STRING_DATATYPE,&m2,&n2,&l2);
			if (strcmp(cstk(l2),"default_figure") !=0 && strcmp(cstk(l2),"default_axes") !=0 )
			{
				if ((strcmp(cstk(l2),"old_style") ==0) || (strcmp(cstk(l2),"current_figure") ==0)) 
				{
					hdl = (unsigned long)0;
					pobj = (sciPointObj *) NULL;
				}
				else
				{
					SciWin();
					if ((strcmp(cstk(l2),"zoom_") !=0) && 
					  (strcmp(cstk(l2),"auto_") !=0) && 
					  (strcmp(cstk(l2),"clip_box") !=0) )   
					{
						hdl = (unsigned long ) sciGetHandle(sciGetCurrentObj ()) ;
					}
					else
					{
						hdl = (unsigned long ) sciGetHandle(sciGetCurrentSubWin());
					}

					if (hdl == (unsigned long)0 )
					{
					  pobj = (sciPointObj *) NULL;
					}
					else
					{
					  pobj = sciGetPointerFromHandle(hdl);
					}
				}
			}
			else
			{
				hdl = (unsigned long)0;
				pobj = (sciPointObj *) NULL;
			}
			valueType = VarType(2) ;
			t2=sciType(cstk(l2),pobj);
			if (t2<0) 
			{
				Scierror(999,"%s: unknown property name '%s' \r\n",fname,cstk(l2));
				return 0;
			} 
			if ( valueType != t2 ) if(strcmp(cstk(l2),"current_figure") != 0 && VarType(2) !=1 )
			{  
				/* F.Leray : special unique case here set("current_figure", HANDLE);*/
				/* HANDLE type is 9 */
				Scierror(999,"%s: uncompatible values for property type  '%s' \r\n",fname,cstk(l2));
				return 0;
			}

			if (valueType == sci_matrix )
			{
				GetRhsVar(2,MATRIX_OF_DOUBLE_DATATYPE,&numrow3,&numcol3,&l3);
			}
			else if ( valueType == sci_handles )
			{
				GetRhsVar(2,GRAPHICAL_HANDLE_DATATYPE,&numrow3,&numcol3,&l3);
			}
			else if ( valueType == sci_strings )
			{
				if (strcmp( cstk(l2), "tics_labels"  ) != 0
				  && strcmp( cstk(l2), "auto_ticks"   ) != 0
				  && strcmp( cstk(l2), "axes_visible" ) != 0
				  && strcmp( cstk(l2), "axes_reverse" ) != 0
				  && strcmp( cstk(l2), "text"      ) != 0 )
				{
					GetRhsVar(2,STRING_DATATYPE,&numrow3,&numcol3,&l3);
				} 
				else
				{
					GetRhsVar(2,MATRIX_OF_STRING_DATATYPE,&numrow3,&numcol3,&l3);
				}
			}
			break;

	  default:
		  Scierror(999,"%s : invalid parameter(s).\r\n",fname);
		  endGraphicDataWriting();
		  return 0;
		  break;
	 }

	 if ( (hdl != (unsigned long)0) ) 
	 { 
		 /* F.Leray 16.03.04*/
		 pobj = sciGetPointerFromHandle(hdl);
		 if ( pobj == NULL )
		 {
			 Scierror(999,"%s :the handle is not or no more valid\r\n",fname);
			 endGraphicDataWriting();
			 return 0;
		 }
		 vis_save = sciGetVisibility(pobj) ; /*used not to redraw the figure is object remains invisible SS 20.04.04*/
		 if ( (setStatus = sciSet(pobj, cstk(l2), &l3, valueType, &numrow3, &numcol3)) < 0 )
		 {
			 endGraphicDataWriting();
			 LhsVar(1)=0;
			 return 0 ;
		 }

		 if ( !( vis_save == 0 && sciGetVisibility(pobj)==0 ) && setStatus == 0 ) 
		 {
			 /* do not redraw figure if object remains invisible */
			 if ((strcmp(cstk(l2),"figure_style") !=0) &&
				 (strcmp(cstk(l2),"old_style") !=0 ) && 
				 (strcmp(cstk(l2),"current_axes") !=0) &&
				 (strcmp(cstk(l2),"default_figure") !=0) && 
				 (strcmp(cstk(l2),"default_axes") !=0) &&
				 (pobj != getFigureModel()) && (pobj != getAxesModel())
				 && pobj != pSUBWIN_FEATURE(getAxesModel())->mon_title
				 && pobj != pSUBWIN_FEATURE(getAxesModel())->mon_x_label
				 && pobj != pSUBWIN_FEATURE(getAxesModel())->mon_y_label
				 && pobj != pSUBWIN_FEATURE(getAxesModel())->mon_z_label )
			 { 
				 /* Addings F.Leray 10.06.04 */
				 num= sciGetNumFigure (pobj);    
				 C2F (dr) ("xget", "window",&verb,&cur,&na,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
				 C2F (dr) ("xset", "window",&num,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);  

				 //sciDrawObj(sciGetParentFigure(pobj)); /* F.Leray we redraw here */
				 sciDrawObj(pobj) ;

				 C2F (dr) ("xset", "window",&cur,PI0,PI0,PI0,PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
			 }
		 }
	 }
	 else if ( ( setStatus = sciSet( NULL, cstk(l2), &l3, valueType, &numrow3, &numcol3) ) < 0 )
	 {
		// endGraphicDataWriting();
		// return 0;
	 }

	 endGraphicDataWriting();
	 LhsVar(1)=0;
  }
    return 0;
}
/*-----------------------------------------------------------------------------------*/
