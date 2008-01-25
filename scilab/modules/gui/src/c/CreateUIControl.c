/*------------------------------------------------------------------------*/
/* file: CreateUicontrol.c                                                */
/* Copyright INRIA 2007                                                   */
/* Authors : Vincent COUVERT                                              */
/* Create Java object matching Scilab uicontrol                           */
/*------------------------------------------------------------------------*/

#include "CreateUIControl.h"
#include "BuildObjects.h"
#include "ObjectStructure.h"
#include "PushButton.h"
#include "EditBox.h"
#include "Label.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "Slider.h"
#include "PopupMenu.h"
#include "ListBox.h"
#include "Frame.h"

/**CreateUIControl
 * This function creates Uicontrol structure.
 * @param char style[]: the type of the uicontrol object
 * @return  : pointer sciPointObj if ok , NULL if not
 */
sciPointObj * CreateUIControl(char *style)
{
  sciPointObj *pobj = (sciPointObj *) NULL;

  if ((pobj = MALLOC (sizeof (sciPointObj))) == NULL)	return (sciPointObj *) NULL;

  sciSetEntityType (pobj, SCI_UICONTROL);

  if ((pobj->pfeatures = MALLOC ((sizeof (sciUicontrol)))) == NULL)
    {
      FREE(pobj);
      return (sciPointObj *) NULL;
    }

  if ((pUICONTROL_FEATURE (pobj)->callback = CALLOC(1,sizeof(char))) == NULL )
    {
      sciprint(_("No more place to allocates text string, try a shorter string.\n"));
      return (sciPointObj *) NULL;
    }

  strcpy(pUICONTROL_FEATURE (pobj)->callback,"");
  pUICONTROL_FEATURE (pobj)->callbacklen = 0;
  pUICONTROL_FEATURE (pobj)->CallbackType = 0;
  pUICONTROL_FEATURE (pobj)->Enable = TRUE;

  /* Tag is set to NULL as default */
  /* The getter for tag returns "" is tag is NULL */
  pUICONTROL_FEATURE (pobj)->tag = NULL;

  /* Value is set to NULL as default */
  pUICONTROL_FEATURE (pobj)->value = NULL;
  pUICONTROL_FEATURE (pobj)->valueSize = 0;

  /* ListboxTop is set to NULL as default */
  /* The getter for ListboxTop returns [] is ListboxTop is NULL */
  pUICONTROL_FEATURE (pobj)->listboxTop = NULL;

  /* Min/Max default values */
  pUICONTROL_FEATURE (pobj)->max = 1;
  pUICONTROL_FEATURE (pobj)->min = 0;

  /* Font default */
  if ((pUICONTROL_FEATURE (pobj)->fontName = CALLOC(1,sizeof(char))) == NULL )
    {
      sciprint(_("No more place to allocates text string, try a shorter string.\n"));
      return (sciPointObj *) NULL;
    }
  strcpy(pUICONTROL_FEATURE (pobj)->fontName, "");
  pUICONTROL_FEATURE(pobj)->fontWeight = NORMAL_FONT;
  pUICONTROL_FEATURE(pobj)->fontUnits = POINTS_UNITS;
  pUICONTROL_FEATURE(pobj)->fontAngle = NORMAL_FONT;

  /* Units default */
  pUICONTROL_FEATURE(pobj)->units = POINTS_UNITS;

  /* Relief default */
  if (style == NULL || strcmp(style,"pushbutton")==0)
    {
      pUICONTROL_FEATURE(pobj)->relief = RAISED_RELIEF;
    }
  else if (strcmp(style,"edit")==0)
    {
      pUICONTROL_FEATURE(pobj)->relief = SUNKEN_RELIEF;
    }
  else
    {
      pUICONTROL_FEATURE(pobj)->relief = FLAT_RELIEF;
    }

  /* Alignment default */
  pUICONTROL_FEATURE(pobj)->horizontalAlignment = CENTER_ALIGNMENT;
  pUICONTROL_FEATURE(pobj)->verticalAlignment = MIDDLE_ALIGNMENT;

  /* Slider Step default */
  if ((pUICONTROL_FEATURE (pobj)->sliderStep = CALLOC(2,sizeof(double))) == NULL )
    {
      sciprint(_("No more place to allocates default SliderStep default value."));
      return (sciPointObj *) NULL;
    }
  pUICONTROL_FEATURE(pobj)->sliderStep[0] = 0.01;
  pUICONTROL_FEATURE(pobj)->sliderStep[1] = 0.1;

  sciStandardBuildOperations(pobj, NULL);
      
  /* Default Style is PushButton */
  if (style == NULL || strcmp(style,"pushbutton")==0)
    {
      createPushButton((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_PUSHBUTTON;
    }
  else if (strcmp(style,"edit")==0)
    {
      createEditBox((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_EDIT;
    }
  else if (strcmp(style,"text")==0)
    {
      createLabel((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_UITEXT;
    }
  else if (strcmp(style,"checkbox")==0)
    {
      createCheckBox((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_CHECKBOX;
    }
  else if (strcmp(style,"radiobutton")==0)
    {
      createRadioButton((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_RADIOBUTTON;
    }
  else if (strcmp(style,"slider")==0)
    {
      createSlider((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_SLIDER;
    }
  else if (strcmp(style,"popupmenu")==0)
    {
      createPopupMenu((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_POPUPMENU;
    }
  else if (strcmp(style,"listbox")==0)
    {
      createListBox((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_LISTBOX;
    }
  else if (strcmp(style,"frame")==0)
    {
      createFrame((sciPointObj *) pobj);
      pUICONTROL_FEATURE (pobj)->style = SCI_UIFRAME;
    }
  else
    {
      sciprint(_("Could not create uicontrol of type %s."), style);
    }
      
  return (sciPointObj *) pobj;
}
/*----------------------------------------------------------------------------*/

