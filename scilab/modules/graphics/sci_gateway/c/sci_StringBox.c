/*------------------------------------------------------------------------*/
/* file: sci_StringBox.c                                                  */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for StringBox routine                                 */
/*------------------------------------------------------------------------*/

#include "sci_StringBox.h"
#include "Scierror.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "BuildObjects.h"
#include "gw_graphics.h"
#include "DrawObjects.h"
#include "StringBox.h"

/*--------------------------------------------------------------------------*/
int sci_StringBox( char * fname, unsigned long fname_len )
{
  integer    two   = 2     ;
  integer    four  = 4     ;
  integer    m,n           ;
  integer    stackPointer  ;
  double     corners[4][2] ; /* the four edges of the boundingRect */
  sciPointObj * pText = NULL ;

  /* The function should be called with stringbox( handle ) */
  CheckRhs( 1, 1 ) ;
  CheckLhs( 0, 1 ) ;

  if ( VarType(1) != sci_handles )
  {
    Scierror(999,"Function StringBox works with only one text handle.\n") ;
    return 0 ;
  }

  /* get the handle */
  GetRhsVar( 1,GRAPHICAL_HANDLE_DATATYPE, &m, &n, &stackPointer );

  if ( m * n != 1 )
  {
    Scierror(999,"Function StringBox works with only one text handle.\n" ) ;
    return 0 ;
  }

  pText = sciGetPointerFromHandle( (unsigned long) *hstk( stackPointer ) ) ;

  if ( pText == NULL )
  {
    Scierror(999,"%s : The handle is not valid.\n",fname);
    return 0 ;
  }

  if ( sciGetEntityType( pText ) == SCI_LABEL )
  {
    pText = pLABEL_FEATURE( pText )->text ;
  }
  else if ( sciGetEntityType( pText ) != SCI_TEXT )
  {
    Scierror(999,"Function StringBox works with only one text handle.\n") ;
    return 0 ;
  }

  /* create a window if needed to initialize the X11 graphic context  */

  /* get the string box */
  getTextBoundingBox( pText, NULL, corners ) ;

  /* copy everything into the lhs */
  CreateVar( Rhs + 1,MATRIX_OF_DOUBLE_DATATYPE, &two, &four, &stackPointer );
  *stk( stackPointer     )  = corners[0][0] ; 
  *stk( stackPointer + 1 )  = corners[0][1] ;
  *stk( stackPointer + 2 )  = corners[1][0] ;
  *stk( stackPointer + 3 )  = corners[1][1] ;
  *stk( stackPointer + 4 )  = corners[2][0] ;
  *stk( stackPointer + 5 )  = corners[2][1] ;
  *stk( stackPointer + 6 )  = corners[3][0] ;
  *stk( stackPointer + 7 )  = corners[3][1] ;

  LhsVar( 1 ) = Rhs + 1 ;
  return 0;
}

/*--------------------------------------------------------------------------*/
