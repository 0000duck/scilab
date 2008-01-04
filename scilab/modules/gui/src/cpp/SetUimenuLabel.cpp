/* Copyright INRIA 2007 */
/* Vincent COUVERT */
/* Set the label of anuimenu */

#include "SetUimenuLabel.hxx"

using namespace org_scilab_modules_gui_bridge;

int SetUimenuLabel(sciPointObj* sciObj, int stackPointer, int valueType, int nbRow, int nbCol)
{
  // Label must be only one character string
  if (valueType != sci_strings) {
    sciprint(_("%s property value must be a single string.\n"), "Label");
    return SET_PROPERTY_ERROR;
  }
  if (nbCol != 1) {
    sciprint(_("%s property value must be a single string.\n"), "Label");
    return SET_PROPERTY_ERROR;
  }

  if (nbRow == 0) {
    // This case should never happen beacause if nbRow==0 then nbCol is also 0
    sciprint(_("%s property value must be a single string.\n"), "Label");
    return SET_PROPERTY_ERROR;
  }

  if (sciGetEntityType( sciObj ) == SCI_UIMENU)
    {
      // Send the label to Java
      CallScilabBridge::setWidgetText(getScilabJavaVM(), pUIMENU_FEATURE(sciObj)->hashMapIndex, getStringFromStack(stackPointer));
      return SET_PROPERTY_SUCCEED;
    }
  else
    {
      sciprint(_("No %s property for this object.\n"), "Label");
      return SET_PROPERTY_ERROR;
    }
}

