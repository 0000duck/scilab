/*--------------------------------------------------------------------------*/
/* Allan CORNET INRIA 2006 */
/* Vincent COUVERT INRIA 2007 */
/*--------------------------------------------------------------------------*/ 
#include "gw_gui.h"
#include "machine.h"
#include "machine.h"
#include "stack-c.h"
#include "localization.h"
#include "Scierror.h"
#include "InitUIMenu.h"
#include "scilabmode.h"
/*--------------------------------------------------------------------------*/
int sci_unsetmenu(char *fname,unsigned long fname_len)
{
  int nbRow=0, nbCol=0, stkAdr=0;
  int nbRow1=0, nbCol1=0, stkAdr1=0;

  // Check parameter number
  CheckRhs(1,2);
  CheckLhs(1,1);

  if (Rhs == 1)
    {
      // Error message in not in standard mode
      if(getScilabMode() != SCILAB_STD)
        {
          Scierror(999,_("%s: figure number must be given when used in no window mode."),"delmenu");
        }

      // Unset a Menu of Scilab Main Window
      if (VarType(1) != sci_strings)
        {
          Scierror(999, _("%s: Wrong type for first input argument: String expected.\n"),fname);
          return FALSE;
        }

      GetRhsVar(1, STRING_DATATYPE, &nbRow, &nbCol, &stkAdr);

      if (nbCol != 1)
        {
          Scierror(999, _("%s: Wrong type for first input argument: Single string expected.\n"),fname);
          return FALSE;
        }
     EnableRootMenu(cstk(stkAdr), FALSE);
    }
  else
    {
      // Unset a Menu a Scilab Graphic Window
      if (VarType(1) != sci_matrix)
        {
          Scierror(999, _("%s: Wrong type for first input argument: Double value expected.\n"),fname);
          return FALSE;
        }
      GetRhsVar(1, MATRIX_OF_DOUBLE_DATATYPE, &nbRow, &nbCol, &stkAdr);
      
      if (nbRow*nbCol != 1)
        {
          Scierror(999, _("%s: Wrong type for first input argument: Scalar expected.\n"),fname);
          return FALSE;
        }

      if (VarType(2) != sci_strings)
        {
          Scierror(999, _("%s: Wrong type for second input argument: String expected.\n"),fname);
          return FALSE;
        }
      GetRhsVar(2, STRING_DATATYPE, &nbRow1, &nbCol1, &stkAdr1);

      EnableFigureMenu((int)*stk(stkAdr), cstk(stkAdr1), FALSE);
    }
  
  LhsVar(1)=0;
  C2F(putlhsvar)();
  return 0;
}
/*--------------------------------------------------------------------------*/
