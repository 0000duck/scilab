/* Copyright INRIA 2007 */
/* Vincent COUVERT */
/* Sets the font angle of an uicontrol object */

#include "SetUicontrolFontAngle.hxx"

using namespace org_scilab_modules_gui_bridge;

int SetUicontrolFontAngle(sciPointObj* sciObj, int stackPointer, int valueType, int nbRow, int nbCol)
{
  /* Font angle can be normal, italic or oblique */

  char * fontAngle = NULL; 

  if (valueType == sci_strings)
    {
      if(nbCol != 1 || nbRow == 0)
        {
          /* Wrong string size */
          sciprint(_("FontAngle property value must be a single string: normal, italic or oblique.\n"));
          return SET_PROPERTY_ERROR;
        }
      
      fontAngle = getStringFromStack(stackPointer);

      if (strcmp(fontAngle, "normal") == 0)
        {
          pUICONTROL_FEATURE(sciObj)->fontAngle = NORMAL_FONT;
        }
      else if(strcmp(fontAngle, "italic") == 0)
        {
          pUICONTROL_FEATURE(sciObj)->fontAngle = ITALIC_FONT;
        }
      else if(strcmp(fontAngle, "oblique") == 0)
        {
          pUICONTROL_FEATURE(sciObj)->fontAngle = OBLIQUE_FONT;
        }
      else
        {
          /* Wrong string format */
          sciprint(_("FontAngle property value must be a single string: normal, italic or oblique.\n"));
          return SET_PROPERTY_ERROR;
        }
      
      switch(pUICONTROL_FEATURE(sciObj)->style)
        {
        case SCI_PUSHBUTTON:
          CallScilabBridge::setPushButtonFontAngle(getScilabJavaVM(), pUICONTROL_FEATURE(sciObj)->hashMapIndex, fontAngle);
          return SET_PROPERTY_SUCCEED;
        default:
          /* Unimplmented uicontrol style */
          sciprint(_("No %s property for uicontrols of style: %s.\n"), "FontAngle", UicontrolStyleToString(pUICONTROL_FEATURE(sciObj)->style));
          return SET_PROPERTY_ERROR;
        }
    }
  else
    {
      /* Wrong datatype */
      sciprint(_("FontAngle property value must be a single string: normal, italic or oblique.\n"));
      return SET_PROPERTY_ERROR;
    }

}

