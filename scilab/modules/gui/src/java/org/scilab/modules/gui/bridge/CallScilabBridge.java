
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.bridge;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.checkbox.CheckBox;
import org.scilab.modules.gui.checkbox.ScilabCheckBox;
import org.scilab.modules.gui.console.ScilabConsole;
import org.scilab.modules.gui.editbox.EditBox;
import org.scilab.modules.gui.editbox.ScilabEditBox;
import org.scilab.modules.gui.filechooser.FileChooser;
import org.scilab.modules.gui.filechooser.ScilabFileChooser;
import org.scilab.modules.gui.frame.Frame;
import org.scilab.modules.gui.frame.ScilabFrame;
import org.scilab.modules.gui.graphicWindow.ScilabRendererProperties;
import org.scilab.modules.gui.label.Label;
import org.scilab.modules.gui.label.ScilabLabel;
import org.scilab.modules.gui.listbox.ListBox;
import org.scilab.modules.gui.listbox.ScilabListBox;
import org.scilab.modules.gui.menu.Menu;
import org.scilab.modules.gui.menu.ScilabMenu;
import org.scilab.modules.gui.menubar.MenuBar;
import org.scilab.modules.gui.menubar.ScilabMenuBar;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.menuitem.ScilabMenuItem;
import org.scilab.modules.gui.messagebox.MessageBox;
import org.scilab.modules.gui.messagebox.ScilabMessageBox;
import org.scilab.modules.gui.popupmenu.PopupMenu;
import org.scilab.modules.gui.popupmenu.ScilabPopupMenu;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;
import org.scilab.modules.gui.radiobutton.RadioButton;
import org.scilab.modules.gui.radiobutton.ScilabRadioButton;
import org.scilab.modules.gui.slider.ScilabSlider;
import org.scilab.modules.gui.slider.Slider;
import org.scilab.modules.gui.tab.Tab;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.ScilabRelief;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.utils.UIElementMapper;
import org.scilab.modules.gui.widget.Widget;
import org.scilab.modules.gui.window.ScilabWindow;
import org.scilab.modules.gui.window.Window;
import org.scilab.modules.renderer.FigureMapper;

/**
 * This class is used to call Scilab GUIs objects from Scilab
 * @author Vincent COUVERT
 */
public class CallScilabBridge {
	
	private static final int NB_COLORS = 3;
	
	private static final int POSITION_SIZE = 4;
	
	private static final int X_INDEX = 0;
	private static final int Y_INDEX = 1;
	private static final int WIDTH_INDEX = 2;
	private static final int HEIGHT_INDEX = 3;
	
	private static final String NORMALFONT = "normal";
	private static final String OBLIQUEFONT = "oblique";
	private static final String ITALICFONT = "italic";
	private static final String BOLDFONT = "bold";
	private static final int DEFAULTFONTSIZE = 12;
	private static final String DEFAULTFONTNAME = "helvetica";

	private static final double DEFAULT_RED_BACKGROUND = 0.8 * 255;
	private static final double DEFAULT_GREEN_BACKGROUND = 0.8 * 255;
	private static final double DEFAULT_BLUE_BACKGROUND = 0.8 * 255;
	
	private static final double BUTTON_RED_BACKGROUND = 0.6 * 255;
	private static final double BUTTON_GREEN_BACKGROUND = 0.6 * 255;
	private static final double BUTTON_BLUE_BACKGROUND = 0.6 * 255;
	
	private static final double DEFAULT_RED_FOREGROUND = 0;
	private static final double DEFAULT_GREEN_FOREGROUND = 0;
	private static final double DEFAULT_BLUE_FOREGROUND = 0;
	/**
	 * Constructor
	 */
	protected CallScilabBridge() {
		throw new UnsupportedOperationException(); /* Prevents calls from subclass */
	}
	
	/******************/
	/*                */  
	/* CONSOLE BRIDGE */
	/*                */  
	/******************/
	
	/**
	 * Read a line from the Console
	 * @return the line read
	 */
	public static String readLine() {
		return ScilabConsole.getConsole().readLine();
	}
	
	/**
	 * Display a line in the Console
	 * @param dataToDisplay the line to display
	 */
	public static void display(String dataToDisplay) {
		ScilabConsole.getConsole().display(dataToDisplay);
	}
	
	/**
	 * Get the status of the Console
	 * @return true if the console is at the prompt
	 */
	public static boolean isWaitingForInput() {
		return ScilabConsole.getConsole().isWaitingForInput();
	}

	/**
	 * Update the number of lines and columns that Scilab use to format data to display
	 */
	public static void scilabLinesUpdate() {
		ScilabConsole.getConsole().scilabLinesUpdate();
	}
	
	/**
	 * Clear the Console
	 */
	public static void clear() {
		ScilabConsole.getConsole().clear();
	}
	
	/**
	 * Clear some lines in the Console
	 * @param nbLines the number of lines to clear
	 */
	public static void clear(int nbLines) {
		ScilabConsole.getConsole().clear(nbLines);
	}
	
	/**
	 * Get a char to know if the user wants more data to be displayed
	 * @return the user answer
	 */
	public static int getCharWithoutOutput() {
		return ScilabConsole.getConsole().getAsSimpleConsole().getCharWithoutOutput();
	}
	
	/**
	 * Put the prompt on the top left corner
	 */
	public static void toHome() {
		ScilabConsole.getConsole().toHome();
	}
	
	/**
	 * Set the contents of the prompt
	 * @param prompt the content to set (default is -->)
	 */
	public static void setPrompt(String prompt) {
		ScilabConsole.getConsole().setPrompt(prompt);
	}
	
	/**************************/
	/*                        */
	/* OBJECT CREATION BRIDGE */
	/*                        */
	/**************************/
	
	/**
	 * Create a new Window in Scilab GUIs
	 * @return the ID of the window in the UIElementMapper
	 */
	public static int newWindow() {
		Window window = ScilabWindow.createWindow();
		return UIElementMapper.add(window);
	}

	/**
	 * Create a new Menubar in Scilab GUIs
	 * @return the ID of the Menubar in the UIElementMapper
	 */
	public static int newMenuBar() {
		MenuBar menuBar = ScilabMenuBar.createMenuBar();
		return UIElementMapper.add(menuBar);
	}

	/**
	 * Create a new Menu in Scilab GUIs
	 * @return the ID of the menu in the UIElementMapper
	 */
	public static int newMenu() {
		MenuItem menuItem = ScilabMenuItem.createMenuItem();
		return UIElementMapper.add(menuItem);
	}
	
	/**
	 * Create a new File Chooser in Scilab GUIs
	 * @return the ID of the File Chooser in the UIElementMapper
	 */
	public static int newFileChooser() {
		FileChooser fileChooser = ScilabFileChooser.createFileChooser();
		return UIElementMapper.add(fileChooser);
	}
	
	/**
	 * Create a new MessageBox in Scilab GUIs
	 * @return the ID of the MessageBox in the UIElementMapper
	 */
	public static int newMessageBox() {
		MessageBox messageBox = ScilabMessageBox.createMessageBox();
		return UIElementMapper.add(messageBox);
	}
	
	/**
	 * Create a new PushButton in Scilab GUIs
	 * @return the ID of the PushButton in the UIElementMapper
	 */
	public static int newPushButton() {
		PushButton pushButton = ScilabPushButton.createPushButton();
		int id = UIElementMapper.add(pushButton);
		
		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.RAISED);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) BUTTON_RED_BACKGROUND, (int) BUTTON_GREEN_BACKGROUND, (int) BUTTON_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new EditBox in Scilab GUIs
	 * @return the ID of the Edit in the UIElementMapper
	 */
	public static int newEditBox() {
		EditBox editBox = ScilabEditBox.createEditBox();
		int id = UIElementMapper.add(editBox);
		
		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.SUNKEN);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new Label in Scilab GUIs
	 * @return the ID of the Label in the UIElementMapper
	 */
	public static int newLabel() {
		Label label = ScilabLabel.createLabel();
		int id = UIElementMapper.add(label);
		
		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.FLAT);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new CheckBox in Scilab GUIs
	 * @return the ID of the CheckBox in the UIElementMapper
	 */
	public static int newCheckBox() {
		CheckBox checkBox = ScilabCheckBox.createCheckBox();
		int id = UIElementMapper.add(checkBox);
		
		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);

		setWidgetRelief(id, ScilabRelief.FLAT);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new RadioButton in Scilab GUIs
	 * @return the ID of the RadioButton in the UIElementMapper
	 */
	public static int newRadioButton() {
		RadioButton radioButton = ScilabRadioButton.createRadioButton();
		int id = UIElementMapper.add(radioButton);

		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);

		setWidgetRelief(id, ScilabRelief.FLAT);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new Slider in Scilab GUIs
	 * @return the ID of the Slider in the UIElementMapper
	 */
	public static int newSlider() {
		Slider slider = ScilabSlider.createSlider();
		int id = UIElementMapper.add(slider);

		/* Default font */
		/* Set a default font because is null when JScrollBar is created */
		slider.setFont(new Font(DEFAULTFONTNAME, Font.PLAIN, DEFAULTFONTSIZE));
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.FLAT);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		
		slider.setText(""); /* Because Name property is null at creation */
		slider.setMinimumValue(0);
		slider.setMaximumValue(1);
		slider.setValue(0);
		
		return id;
	}

	/**
	 * Create a new ListBox in Scilab GUIs
	 * @return the ID of the ListBox in the UIElementMapper
	 */
	public static int newListBox() {
		ListBox listBox = ScilabListBox.createListBox();
		int id = UIElementMapper.add(listBox);

		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.FLAT);

		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new PopupMenu in Scilab GUIs
	 * @return the ID of the PopupMenu in the UIElementMapper
	 */
	public static int newPopupMenu() {
		PopupMenu popupMenu = ScilabPopupMenu.createPopupMenu();
		int id = UIElementMapper.add(popupMenu);

		/* Default font */
		setWidgetFontName(id, DEFAULTFONTNAME);
		setWidgetFontWeight(id, NORMALFONT);
		setWidgetFontSize(id, DEFAULTFONTSIZE);
		
		setWidgetRelief(id, ScilabRelief.FLAT);
		
		/* Default colors */
		setWidgetBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setWidgetForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		return id;
	}

	/**
	 * Create a new Frame in Scilab GUIs
	 * @return the ID of the PopupMenu in the UIElementMapper
	 */
	public static int newFrame() {
		Frame frame = ScilabFrame.createFrame();
		int id = UIElementMapper.add(frame);

		/* Default font */
		setFrameFontName(id, DEFAULTFONTNAME);
		setFrameFontWeight(id, NORMALFONT);
		setFrameFontSize(id, DEFAULTFONTSIZE);
		
		setFrameRelief(id, ScilabRelief.RIDGE);
		
		/* Default colors */
		setFrameBackgroundColor(id, (int) DEFAULT_RED_BACKGROUND, (int) DEFAULT_GREEN_BACKGROUND, (int) DEFAULT_BLUE_BACKGROUND);
		setFrameForegroundColor(id, (int) DEFAULT_RED_FOREGROUND, (int) DEFAULT_GREEN_FOREGROUND, (int) DEFAULT_BLUE_FOREGROUND);
		
		frame.setText(""); /* Because Name property is null at creation */
		return id;
	}
	
	/**
	 * Destroy a Widget
	 * @param id the id of the Widget to destroy
	 */
	public static void destroyWidget(int id) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).destroy();
	}

	/**
	 * Destroy a Frame
	 * @param id the id of the Frame to destroy
	 */
	public static void destroyFrame(int id) {
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).destroy();
	}

	/****************************/
	/*                          */
	/* OBJECT DIMENSIONS BRIDGE */
	/*                          */
	/****************************/
	
	/**
	 * Set the dimensions of an object in Scilab GUIs
	 * @param objID the ID of the object in the UIElementMapper
	 * @param width the width of the object
	 * @param height the height of the object
	 */
	public static void setDims(int objID, int width, int height) {
		UIElementMapper.getCorrespondingUIElement(objID).setDims(new Size(width, height));
	}
	
	/**********************/
	/*                    */
	/* OBJECT TEXT BRIDGE */
	/*                    */
	/**********************/
	
	/**
	 * Set the text of a widget in Scilab GUIs
	 * @param objID the ID of the Widget in the UIElementMapper
	 * @param text the text to set to the widget
	 */
	public static void setWidgetText(int objID, String text) {
		((Widget) UIElementMapper.getCorrespondingUIElement(objID)).setText(text);
	}
	
	/**
	 * Get the text of a widget in Scilab GUIs
	 * @param objID the ID of the Widget in the UIElementMapper
	 * @return the text of the widget
	 */
	public static String getWidgetText(int objID) {
		return ((Widget) UIElementMapper.getCorrespondingUIElement(objID)).getText();
	}

	/**
	 * Set the text of a Frame in Scilab GUIs
	 * @param objID the ID of the Widget in the UIElementMapper
	 * @param text the text to set to the Frame
	 */
	public static void setFrameText(int objID, String text) {
		((Frame) UIElementMapper.getCorrespondingUIElement(objID)).setText(text);
	}
	
	/**
	 * Get the text of a Frame in Scilab GUIs
	 * @param objID the ID of the Frame in the UIElementMapper
	 * @return the text of the Frame
	 */
	public static String getFrameText(int objID) {
		return ((Frame) UIElementMapper.getCorrespondingUIElement(objID)).getText();
	}

	/******************/
	/*                */
	/* PARENT SETTING */
	/*                */
	/******************/

	/**
	 * Set a figure as parent for an UIElement
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the object in the UIElementMapper
	 */
	public static void setFigureAsParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();

		if (UIElementMapper.getCorrespondingUIElement(objID) instanceof Menu) {
			// Add the menu to the tab
			parentTab.getMenuBar().add((Menu) UIElementMapper.getCorrespondingUIElement(objID));
		} else {
			// obj is a MenuItem that has to be converted to a Menu
			MenuItem menuItem = (MenuItem) UIElementMapper.getCorrespondingUIElement(objID);
			
			Menu menuToAdd = ScilabMenu.createMenu();
			UIElementMapper.removeMapping(objID);
			UIElementMapper.addMapping(objID, menuToAdd);
			// Copy all properties from MenuItem to Menu
			menuToAdd.setText(menuItem.getText());
			// TODO Add other properties
			
			// Add the menu to the tab
			parentTab.getMenuBar().add(menuToAdd);
		}
	}
	
	/**
	 * Set a figure as parent for a PushButton
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setPushButtonParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		PushButton pushButton = (PushButton) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, pushButton);
	}

	/**
	 * Set a figure as parent for a EditBox
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setEditBoxParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		EditBox editBox = (EditBox) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, editBox);
	}

	/**
	 * Set a figure as parent for a Label
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setLabelParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		Label label = (Label) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, label);
	}

	/**
	 * Set a figure as parent for a CheckBox
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setCheckBoxParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		CheckBox checkBox = (CheckBox) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, checkBox);
	}

	/**
	 * Set a figure as parent for a RadioButton
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setRadioButtonParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		RadioButton radioButton = (RadioButton) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, radioButton);
	}

	/**
	 * Set a figure as parent for a Slider
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PushButton in the UIElementMapper
	 */
	public static void setSliderParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		Slider slider = (Slider) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, slider);
	}

	/**
	 * Set a figure as parent for a ListBox
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the ListBox in the UIElementMapper
	 */
	public static void setListBoxParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		ListBox listBox = (ListBox) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, listBox);
	}

	/**
	 * Set a figure as parent for a PopupMenu
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PopupMenu in the UIElementMapper
	 */
	public static void setPopupMenuParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		PopupMenu popupMenu = (PopupMenu) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, popupMenu);
	}

	/**
	 * Set a figure as parent for a Frame
	 * @param figureID the ID of the figure in the FigureMapper
	 * @param objID the ID of the PopupMenu in the UIElementMapper
	 */
	public static void setFrameParent(int figureID, int objID) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		Frame frame = (Frame) UIElementMapper.getCorrespondingUIElement(objID);
		ScilabBridge.addMember(parentTab, frame);
	}

	/**
	 * Set root Scilab object (the console tab) as the parent of the menu
	 * @param objID the id of the menu
	 */
	public static void setRootAsParent(int objID) {
		if (UIElementMapper.getCorrespondingUIElement(objID) instanceof Menu) {
			// Add the menu to the tab
			ScilabConsole.getConsole().getMenuBar().add((Menu) UIElementMapper.getCorrespondingUIElement(objID));
		} else {
			// obj is a MenuItem that has top be converted to a Menu
			MenuItem menuItem = (MenuItem) UIElementMapper.getCorrespondingUIElement(objID);
			
			Menu menuToAdd = ScilabMenu.createMenu();
			UIElementMapper.removeMapping(objID);
			UIElementMapper.addMapping(objID, menuToAdd);
			// Copy all properties from MenuItem to Menu
			menuToAdd.setText(menuItem.getText());
			// TODO Add other properties

			ScilabConsole.getConsole().getMenuBar().add(menuToAdd);
		}
	}
	
	/**
	 * Set an other menu as the parent of the menu
	 * @param menuID the id of the parent menu
	 * @param objID the id of the menu
	 */
	public static void setMenuAsParent(int menuID, int objID) {

		Menu parentMenu = null;
		if (UIElementMapper.getCorrespondingUIElement(menuID) instanceof Menu) {
			// Add the menu to the tab
			parentMenu = (Menu) UIElementMapper.getCorrespondingUIElement(menuID);
		} else {
			// obj is a MenuItem that has to be converted to a Menu
			MenuItem menuItem = (MenuItem) UIElementMapper.getCorrespondingUIElement(objID);
			
			parentMenu = ScilabMenu.createMenu();
			UIElementMapper.removeMapping(objID);
			UIElementMapper.addMapping(objID, parentMenu);
			
			// Copy all properties from MenuItem to Menu
			parentMenu.setText(menuItem.getText());
			// TODO Add other properties
			//((MenuItem) UIElementMapper.getCorrespondingUIElement(menuID)).add((Menu) UIElementMapper.getCorrespondingUIElement(objID));
		}
		
		if (UIElementMapper.getCorrespondingUIElement(objID) instanceof Menu) {
			parentMenu.add((Menu) UIElementMapper.getCorrespondingUIElement(objID));
		} else {
			parentMenu.add((MenuItem) UIElementMapper.getCorrespondingUIElement(objID));
		}
	}
	
	/*******************/
	/*                 */
	/* OBJECT CALLBACK */
	/*                 */
	/*******************/
	
	/**
	 * Set a callback for a Widget
	 * @param objID the ID of the object in the UIElementMapper
	 * @param callbackString the text of the callback
	 * @param callbackType the type of the callback
	 */
	public static void setWidgetCallback(int objID, String callbackString, int callbackType) {
		((Widget) UIElementMapper.getCorrespondingUIElement(objID)).setCallback(callbackString, callbackType);
	}
	
	/**
	 * Set a callback for a Frame
	 * @param objID the ID of the object in the UIElementMapper
	 * @param callback the text of the callback
	 */
	public static void setFrameCallback(int objID, String callback) {
		System.out.println("setFrameCallback is not implemented");
	}
	
	/************************/
	/*                      */
	/* ENABLE/DISABLE MENUS */
	/*                      */
	/************************/

	/**
	 * Disable a menu of a Scilab figure giving its name
	 * @param figureID the id of the figure
	 * @param menuName the name of the menu
	 * @param status true to set the menu enabled
	 */
	public static void setFigureMenuEnabled(int figureID, String menuName, boolean status) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		
		MenuBar figureMenuBar = parentTab.getMenuBar();
		
		figureMenuBar.getAsSimpleMenuBar().setMenuEnabled(menuName, status);
	}

	/**
	 * Disable a menu of a Scilab root window giving its name
	 * @param menuName the name of the menu
	 * @param status true to set the menu enabled
	 */
	public static void setRootMenuEnabled(String menuName, boolean status) {
		ScilabConsole.getConsole().getMenuBar().getAsSimpleMenuBar().setMenuEnabled(menuName, status);
	}
	
	/****************/
	/*              */
	/* REMOVE MENUS */
	/*              */
	/****************/

	/**
	 * Delete a menu of a Scilab figure giving its name
	 * @param figureID the id of the figure
	 * @param menuName the name of the menu
	 */
	public static void removeFigureMenu(int figureID, String menuName) {
		Tab parentTab = ((ScilabRendererProperties) FigureMapper.getCorrespondingFigure(figureID).getRendererProperties()).getParentTab();
		
		MenuBar figureMenuBar = parentTab.getMenuBar();
		
		figureMenuBar.getAsSimpleMenuBar().removeMenu(menuName);
	}

	/**
	 * Delete a menu of a Scilab root window giving its name
	 * @param menuName the name of the menu
	 */
	public static void removeRootMenu(String menuName) {
		ScilabConsole.getConsole().getMenuBar().getAsSimpleMenuBar().removeMenu(menuName);
	}
	
	/***********************/
	/*                     */
	/* FILE CHOOSER BRIDGE */
	/*                     */
	/***********************/
	
	/**
	 * Set the file chooser title 
	 * @param id the id of the fileChooser
	 * @param title the title of the fileChooser
	 */
	public static void setFileChooserTitle(int id, String title) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).setTitle(title);
	}
	
	/**
	 * Set the initial directory used for file search
	 * @param id the id of the fileChooser
	 * @param path the default path
	 */
	public static void setFileChooserInitialDirectory(int id, String path) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).setInitialDirectory(path);
	}

	/**
	 * Set the mask for files that can be selected
	 * @param id the id of the fileChooser
	 * @param mask the mask to apply
	 */
	public static void setFileChooserMask(int id, String mask) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).setMask(mask);
	}

	/**
	 * Display this chooser and wait for user selection 
	 * @param id the id of the fileChooser
	 */
	public static void fileChooserDisplayAndWait(int id) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).displayAndWait();
	}
	
	/**
	 * Get the number of files selected
	 * @param id the id of the fileChooser
	 * @return the number of files selected
	 */
	public static int getFileChooserSelectionSize(int id) {
		return ((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).getSelectionSize();
	}
	
	/**
	 * Get the names of selected files
	 * @param id the id of the fileChooser
	 * @return the names of selected files
	 */
	public static String[] getFileChooserSelection(int id) {
		return ((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).getSelection();
	}
	
	/**
	 * Set the flag indicating that we want only select directories
	 * @param id the id of the fileChooser
	 */
	public static void setFileChooserDirectorySelectionOnly(int id) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).setDirectorySelectionOnly();
	}

	/**
	 * Set the flag indicating that we want only select files
	 * @param id the id of the fileChooser
	 */
	public static void setFileChooserFileSelectionOnly(int id) {
		((FileChooser) UIElementMapper.getCorrespondingUIElement(id)).setFileSelectionOnly();
	}
	
	/**********************/
	/*                    */
	/* MESSAGE BOX BRIDGE */
	/*                    */
	/**********************/
	
	/**
	 * Set the MessageBox title 
	 * @param id the id of the messageBox
	 * @param title the title of the messageBox
	 */
	public static void setMessageBoxTitle(int id, String title) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setTitle(title);
	}
	
	/**
	 * Set the MessageBox message 
	 * @param id the id of the messageBox
	 * @param message the message of the messageBox
	 */
	public static void setMessageBoxMessage(int id, String message) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setMessage(message);
	}

	/**
	 * Set the MessageBox message (multi-line)
	 * @param id the id of the messageBox
	 * @param message the message of the messageBox
	 */
	public static void setMessageBoxMessage(int id, String[] message) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setMessage(message);
	}

	/**
	 * Display this chooser and wait for user selection 
	 * @param id the id of the messageBox
	 */
	public static void messageBoxDisplayAndWait(int id) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).displayAndWait();
	}
	
	/**
	 * Get the index of the selected button
	 * @param id the id of the messageBox
	 * @return the index of the selected button
	 */
	public static int getMessageBoxSelectedButton(int id) {
		return ((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).getSelectedButton();
	}

	/**
	 * Set the labels of the buttons in the MessageBox
	 * @param id the id of the MessageBox
	 * @param labels the labels of the buttons
	 */
	public static void setMessageBoxButtonsLabels(int id, String[] labels) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setButtonsLabels(labels);
	}

	/**
	 * Set the initial value for the editable part of the MessageBox
	 * @param id the id of the MessageBox
	 * @param value the initial value
	 */
	public static void setMessageBoxInitialValue(int id, String[] value) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setInitialValue(value);
	}

	/**
	 * Get the value of the editable zone in the MessageBox
	 * @param id the id of the MessageBox
	 * @return the value
	 */
	public static String[] getMessageBoxValue(int id) {
		return ((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).getValue();
	}
	
	/**
	 * Get the size of the value of the editable zone in the MessageBox
	 * @param id the id of the MessageBox
	 * @return the value size
	 */
	public static int getMessageBoxValueSize(int id) {
		return ((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).getValueSize();
	}

	/**
	 * Set the items of the listbox in the MessageBox
	 * @param id the id of the MessageBox
	 * @param items the items to set
	 */
	public static void setMessageBoxListBoxItems(int id, String[] items) {
		((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).setListBoxItems(items);
	}

	/**
	 * Get the index of the selected item in the listbox in the MessageBox
	 * @param id the id of the MessageBox
	 * @return the index
	 */
	public static int getMessageBoxSelectedItem(int id) {
		return ((MessageBox) UIElementMapper.getCorrespondingUIElement(id)).getSelectedItem();
	}
	
	/************************/
	/*                      */
	/* OBJECT COLORS BRIDGE */
	/*                      */
	/************************/
	
	/**
	 * Set the background color of a Widget
	 * @param id the id of the Widget
	 * @param red the red value for the color
	 * @param green the green value for the color
	 * @param blue the blue value for the color
	 */
	public static void setWidgetBackgroundColor(int id, int red, int green, int blue) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setBackground(new Color(red, green, blue));
	}
	
	/**
	 * Get the background color of a widget 
	 * @param id the id of the widget
	 * @return the color [R, G, B]
	 */
	public static int[] getWidgetBackgroundColor(int id) {
		Color tmpColor = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getBackground();
		int[] color = new int[NB_COLORS];
		color[0] = tmpColor.getRed();
		color[1] = tmpColor.getGreen();
		color[2] = tmpColor.getBlue();
		return color;
	}
	
	/**
	 * Set the foreground color of a Widget
	 * @param id the id of the Widget
	 * @param red the red value for the color
	 * @param green the green value for the color
	 * @param blue the blue value for the color
	 */
	public static void setWidgetForegroundColor(int id, int red, int green, int blue) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setForeground(new Color(red, green, blue));
	}
	
	/**
	 * Get the foreground color of a Widget 
	 * @param id the id of the Widget
	 * @return the color [R, G, B]
	 */
	public static int[] getWidgetForegroundColor(int id) {
		Color tmpColor = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getForeground();
		int[] color = new int[NB_COLORS];
		color[0] = tmpColor.getRed();
		color[1] = tmpColor.getGreen();
		color[2] = tmpColor.getBlue();
		return color;
	}

	/**
	 * Set the background color of a Frame
	 * @param id the id of the Frame
	 * @param red the red value for the color
	 * @param green the green value for the color
	 * @param blue the blue value for the color
	 */
	public static void setFrameBackgroundColor(int id, int red, int green, int blue) {
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setBackground(new Color(red, green, blue));
	}
	
	/**
	 * Get the background color of a Frame 
	 * @param id the id of the Frame
	 * @return the color [R, G, B]
	 */
	public static int[] getFrameBackgroundColor(int id) {
		Color tmpColor = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getBackground();
		int[] color = new int[NB_COLORS];
		color[0] = tmpColor.getRed();
		color[1] = tmpColor.getGreen();
		color[2] = tmpColor.getBlue();
		return color;
	}
	
	/**
	 * Set the foreground color of a Frame
	 * @param id the id of the Frame
	 * @param red the red value for the color
	 * @param green the green value for the color
	 * @param blue the blue value for the color
	 */
	public static void setFrameForegroundColor(int id, int red, int green, int blue) {
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setForeground(new Color(red, green, blue));
	}
	
	/**
	 * Get the foreground color of a Frame 
	 * @param id the id of the Frame
	 * @return the color [R, G, B]
	 */
	public static int[] getFrameForegroundColor(int id) {
		Color tmpColor = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getForeground();
		int[] color = new int[NB_COLORS];
		color[0] = tmpColor.getRed();
		color[1] = tmpColor.getGreen();
		color[2] = tmpColor.getBlue();
		return color;
	}

	/**********************/
	/*                    */
	/* OBJECT FONT BRIDGE */
	/*                    */
	/**********************/

	/**
	 * Set the name of a Widget font
	 * @param id the id of the Widget
	 * @param name the name of the Widget font
	 */
	public static void setWidgetFontName(int id, String name) {
		Font font = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont();
		font = new Font(name, font.getStyle(), font.getSize());
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}

	/**
	 * Get the name of a Widget font
	 * @param id the id of the Widget
	 * @return the name of the Widget font
	 */
	public static String getWidgetFontName(int id) {
		return ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont().getName();
	}

	/**
	 * Set the weight of a Widget font
	 * @param id the id of the Widget
	 * @param weight the weight of the Widget font
	 */
	public static void setWidgetFontWeight(int id, String weight) {
		Font font = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont();

		if (weight.equals(BOLDFONT)) {
			if (font.isItalic()) {
				font = new Font(font.getName(), Font.ITALIC + Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.BOLD, font.getSize());
			}
		} else {
			if (font.isItalic()) {
				font = new Font(font.getName(), Font.ITALIC, font.getSize());
			} else {
				font = new Font(font.getName(), Font.PLAIN, font.getSize());
			}
		}

		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}
	
	/**
	 * Set the angle of a Widget font
	 * @param id the id of the Widget
	 * @param angle the angle of the Widget font
	 */
	public static void setWidgetFontAngle(int id, String angle) {
		Font font = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont();

		if (angle.equals(ITALICFONT) || angle.equals(OBLIQUEFONT)) {
			if (font.isBold()) {
				font = new Font(font.getName(), Font.ITALIC + Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.ITALIC, font.getSize());
			}
		} else {
			if (font.isBold()) {
				font = new Font(font.getName(), Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.PLAIN, font.getSize());
			}
		}

		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}
	
	/**
	 * Set the size of a Widget font
	 * @param id the id of the Widget
	 * @param size the size of the Widget font
	 */
	public static void setWidgetFontSize(int id, int size) {
		Font font = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont();
		font = new Font(font.getName(), font.getStyle(), size);
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}

	/**
	 * Get the size of a Widget font
	 * @param id the id of the Widget
	 * @return the size of the Widget font
	 */
	public static int getWidgetFontSize(int id) {
		return ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getFont().getSize();
	}

	/**
	 * Set the weight of a Frame font
	 * @param id the id of the Frame
	 * @param weight the weight of the Frame font
	 */
	public static void setFrameFontWeight(int id, String weight) {
		Font font = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont();

		if (weight.equals(BOLDFONT)) {
			if (font.isItalic()) {
				font = new Font(font.getName(), Font.ITALIC + Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.BOLD, font.getSize());
			}
		} else {
			if (font.isItalic()) {
				font = new Font(font.getName(), Font.ITALIC, font.getSize());
			} else {
				font = new Font(font.getName(), Font.PLAIN, font.getSize());
			}
		}

		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}
	
	/**
	 * Set the angle of a Frame font
	 * @param id the id of the Frame
	 * @param angle the angle of the Frame font
	 */
	public static void setFrameFontAngle(int id, String angle) {
		Font font = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont();

		if (angle.equals(ITALICFONT) || angle.equals(OBLIQUEFONT)) {
			if (font.isBold()) {
				font = new Font(font.getName(), Font.ITALIC + Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.ITALIC, font.getSize());
			}
		} else {
			if (font.isBold()) {
				font = new Font(font.getName(), Font.BOLD, font.getSize());
			} else {
				font = new Font(font.getName(), Font.PLAIN, font.getSize());
			}
		}

		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}
	
	/**
	 * Set the size of a Frame font
	 * @param id the id of the Frame
	 * @param size the size of the Frame font
	 */
	public static void setFrameFontSize(int id, int size) {
		Font font = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont();
		font = new Font(font.getName(), font.getStyle(), size);
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}

	/**
	 * Get the size of a Frame font
	 * @param id the id of the Frame
	 * @return the size of the Frame font
	 */
	public static int getFrameFontSize(int id) {
		return ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont().getSize();
	}

	/**
	 * Set the name of a Frame font
	 * @param id the id of the Frame
	 * @param name the name of the Frame font
	 */
	public static void setFrameFontName(int id, String name) {
		Font font = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont();
		font = new Font(name, font.getStyle(), font.getSize());
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setFont(font);
	}

	/**
	 * Get the name of a Frame font
	 * @param id the id of the Frame
	 * @return the name of the Frame font
	 */
	public static String getFrameFontName(int id) {
		return ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getFont().getName();
	}

	/**************************/
	/*                        */
	/* OBJECT POSITION BRIDGE */
	/*                        */
	/**************************/
	
	/**
	 * Set the position (in Scilab terms) of a Widget 
	 * @param id the id of the Widget
	 * @param x the X-coordinate for the Widget
	 * @param y the Y-coordinate for the Widget
	 * @param width the width of the Widget
	 * @param height the height of the Widget
	 */
	public static void setWidgetPosition(int id, int x, int y, int width, int height) {
		UIElementMapper.getCorrespondingUIElement(id).setPosition(new Position(x, y));
		UIElementMapper.getCorrespondingUIElement(id).setDims(new Size(width, height));
	}
	
	/**
	 * Get the position (in Scilab terms) of a widget 
	 * @param id the id of the widget
	 * @return the position (X-coordinate, Y-coordinate, width, height) of the button
	 */
	public static int[] getWidgetPosition(int id) {
		int[] position = new int[POSITION_SIZE];
		
		position[X_INDEX] = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getPosition().getX();
		position[Y_INDEX] = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getPosition().getY();
		position[WIDTH_INDEX] = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getDims().getWidth();
		position[HEIGHT_INDEX] = ((Widget) UIElementMapper.getCorrespondingUIElement(id)).getDims().getHeight();
		
		return position;
	}
	
	/**
	 * Set the position (in Scilab terms) of a Frame 
	 * @param id the id of the Frame
	 * @param x the X-coordinate for the Frame
	 * @param y the Y-coordinate for the Frame
	 * @param width the width of the Frame
	 * @param height the height of the Frame
	 */
	public static void setFramePosition(int id, int x, int y, int width, int height) {
		UIElementMapper.getCorrespondingUIElement(id).setPosition(new Position(x, y));
		UIElementMapper.getCorrespondingUIElement(id).setDims(new Size(width, height));
	}
	
	/**
	 * Get the position (in Scilab terms) of a Frame 
	 * @param id the id of the Frame
	 * @return the position (X-coordinate, Y-coordinate, width, height) of the button
	 */
	public static int[] getFramePosition(int id) {
		int[] position = new int[POSITION_SIZE];
		
		position[X_INDEX] = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getPosition().getX();
		position[Y_INDEX] = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getPosition().getY();
		position[WIDTH_INDEX] = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getDims().getWidth();
		position[HEIGHT_INDEX] = ((Frame) UIElementMapper.getCorrespondingUIElement(id)).getDims().getHeight();
		
		return position;
	}
	
	/***************************/
	/*                         */
	/* OBJECT ALIGNMENT BRIDGE */
	/*                         */
	/***************************/

	/**
	 * Set the horizontal alignment for the Widget text
	 * @param id the id of the Widget
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setWidgetHorizontalAlignment(int id, String alignment) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setHorizontalAlignment(alignment);
	}

	/**
	 * Set the vertical alignment for the Widget text
	 * @param id the id of the Widget
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setWidgetVerticalAlignment(int id, String alignment) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setVerticalAlignment(alignment);
	}
	
	/**********************/
	/*                    */
	/* SLIDER STEP BRIDGE */
	/*                    */
	/**********************/

	/**
	 * Set the minor tick spacing for a Slider
	 * @param id the id of the Slider
	 * @param space the increment value
	 */
	public static void setSliderMinorTickSpacing(int id, int space) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setMinorTickSpacing(space);
	}

	/**
	 * Set the major tick spacing for a Slider
	 * @param id the id of the Slider
	 * @param space the increment value
	 */
	public static void setSliderMajorTickSpacing(int id, int space) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setMajorTickSpacing(space);
	}
	
	/*************************/
	/*                       */
	/* SLIDER MIN/MAX BRIDGE */
	/*                       */
	/*************************/

	/**
	 * Set the minimum value of a Slider
	 * @param id the id of the Slider
	 * @param value the minimum value
	 */
	public static void setSliderMinValue(int id, int value) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setMinimumValue(value);
	}

	/**
	 * Set the maximum value of a Slider
	 * @param id the id of the Widget
	 * @param value the maximum value
	 */
	public static void setSliderMaxValue(int id, int value) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setMaximumValue(value);
	}
	
	/*****************************/
	/*                           */
	/* SLIDER ORIENTATION BRIDGE */
	/*                           */
	/*****************************/
	
	/**
	 * Set the slider orientation to vertical
	 * @param id the id of the slider
	 */
	public static void setSliderVertical(int id) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setVertical();
	}

	/**
	 * Set the slider orientation to horizontal
	 * @param id the id of the slider
	 */
	public static void setSliderHorizontal(int id) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setHorizontal();
	}

	/******************/
	/*                */
	/* LISTBOX BRIDGE */
	/*                */
	/******************/

	/**
	 * Set if more than one item can be selected in a ListBox
	 * @param id the id of the ListBox
	 * @param status true if multiple selection is enabled
	 */
	public static void setListBoxMultipleSelectionEnabled(int id, boolean status) {
		((ListBox) UIElementMapper.getCorrespondingUIElement(id)).setMultipleSelectionEnabled(status);
	}

	/**
	 * Get the text of all the list items
	 * @param id the id of the ListBox
	 * @return the text items
	 * @see org.scilab.modules.gui.listbox.ListBox#getAllItemsText()
	 */
	public static String[] getListBoxAllItemsText(int id) {
		return ((ListBox) UIElementMapper.getCorrespondingUIElement(id)).getAllItemsText();
	}

	/**
	 * Get the number of items in the list
	 * @param id the id of the ListBox
	 * @return the number of items
	 * @see org.scilab.modules.gui.listbox.ListBox#getNumberOfItems()
	 */
	public static int getListBoxNumberOfItems(int id) {
		return ((ListBox) UIElementMapper.getCorrespondingUIElement(id)).getNumberOfItems();
	}

	/**
	 * Set the text of the list items
	 * @param id the id of the ListBox
	 * @param text the text of the items
	 * @see org.scilab.modules.gui.listbox.ListBox#setText(java.lang.String[])
	 */
	public static void setListBoxText(int id, String[] text) {
		((ListBox) UIElementMapper.getCorrespondingUIElement(id)).setText(text);
	}

	/********************/
	/*                  */
	/* POPUPMENU BRIDGE */
	/*                  */
	/********************/

	/**
	 * Get the text of all the PopupMenu items
	 * @param id the id of the PopupMenu
	 * @return the text items
	 * @see org.scilab.modules.gui.popupmenu.PopupMenu#getAllItemsText()
	 */
	public static String[] getPopupMenuAllItemsText(int id) {
		return ((PopupMenu) UIElementMapper.getCorrespondingUIElement(id)).getAllItemsText();
	}

	/**
	 * Get the number of items in the PopupMenu
	 * @param id the id of the PopupMenu
	 * @return the number of items
	 * @see org.scilab.modules.gui.popupmenu.PopupMenu#getNumberOfItems()
	 */
	public static int getPopupMenuNumberOfItems(int id) {
		return ((PopupMenu) UIElementMapper.getCorrespondingUIElement(id)).getNumberOfItems();
	}

	/**
	 * Set the text of the PopupMenu items
	 * @param id the id of the PopupMenu
	 * @param text the text of the items
	 * @see org.scilab.modules.gui.popupmenu.PopupMenu#setText(java.lang.String[])
	 */
	public static void setPopupMenuText(int id, String[] text) {
		((PopupMenu) UIElementMapper.getCorrespondingUIElement(id)).setText(text);
	}

	/****************/
	/*              */
	/* VALUE BRIDGE */
	/*              */
	/****************/

	/**
	 * Set the selected indices of the ListBox
	 * @param id the id of the ListBox
	 * @param indices the indices of the items to be selected
	 */
	public static void setListBoxSelectedIndices(int id, int[] indices) {
		System.out.println("CallScilabBridge.setListBoxSelectedIndices");
		((ListBox) UIElementMapper.getCorrespondingUIElement(id)).setSelectedIndices(indices);
	}
	
	/**
	 * Get the selected indices of the ListBox
	 * @param id the id of the ListBox
	 * @return the indices of the items selected
	 */
	public static int[] getListBoxSelectedIndices(int id) {
		return ((ListBox) UIElementMapper.getCorrespondingUIElement(id)).getSelectedIndices();
	}

	/**
	 * Get the number of items selected in the ListBox
	 * @param id the id of the ListBox
	 * @return the number of items selected
	 */
	public static int getListBoxSelectionSize(int id) {
		return ((ListBox) UIElementMapper.getCorrespondingUIElement(id)).getSelectionSize();
	}

	/**
	 * Set the selected index of the PopupMenu
	 * @param id the id of the PopupMenu
	 * @param index the index of the item to be selected
	 */
	public static void setPopupMenuSelectedIndex(int id, int index) {
		((PopupMenu) UIElementMapper.getCorrespondingUIElement(id)).setSelectedIndex(index);
	}
	
	/**
	 * Get the selected index of the PopupMenu
	 * @param id the id of the PopupMenu
	 * @return the index of the item selected
	 */
	public static int getPopupMenuSelectedIndex(int id) {
		return ((PopupMenu) UIElementMapper.getCorrespondingUIElement(id)).getSelectedIndex();
	}

	/**
	 * Get the current value of the Slider
	 * @param id the id of the Slider
	 * @return the current value of the Slider
	 */
	public static int getSliderValue(int id) {
		return ((Slider) UIElementMapper.getCorrespondingUIElement(id)).getValue();
	}
	
	/**
	 * Sets the current value of the Slider
	 * @param id the id of the Slider
	 * @param value the new value
	 */
	public static void setSliderValue(int id, int value) {
		((Slider) UIElementMapper.getCorrespondingUIElement(id)).setValue(value);		
	}

	/**
	 * Set if the RadioButton is checked or not
	 * @param id the id of the RadioButton
	 * @param status true to set the RadioButton checked
	 */
	public static void setRadioButtonChecked(int id, boolean status) {
		((RadioButton) UIElementMapper.getCorrespondingUIElement(id)).setChecked(status);
	}
	
	/**
	 * Get the status of the RadioButton
	 * @param id the id of the RadioButton
	 * @return true if the RadioButton is checked
	 */
	public static boolean isRadioButtonChecked(int id) {
		return ((RadioButton) UIElementMapper.getCorrespondingUIElement(id)).isChecked();
	}

	/**
	 * Set if the CheckBox is checked or not
	 * @param id the id of the CheckBox
	 * @param status true to set the CheckBox checked
	 */
	public static void setCheckBoxChecked(int id, boolean status) {
		((CheckBox) UIElementMapper.getCorrespondingUIElement(id)).setChecked(status);
	}
	
	/**
	 * Get the status of the CheckBox
	 * @param id the id of the CheckBox
	 * @return true if the CheckBox is checked
	 */
	public static boolean isCheckBoxChecked(int id) {
		return ((CheckBox) UIElementMapper.getCorrespondingUIElement(id)).isChecked();
	}
	
	/*****************/
	/*               */
	/* RELIEF BRIDGE */
	/*               */
	/*****************/

	/**
	 * Set the Relief of the Widget
	 * @param id the id of the Widget
	 * @param reliefType the type of the relief to set (See ScilabRelief.java)
	 */
	public static void setWidgetRelief(int id, String reliefType) {
		((Widget) UIElementMapper.getCorrespondingUIElement(id)).setRelief(reliefType);
	}

	/**
	 * Set the Relief of the Frame
	 * @param id the id of the Frame
	 * @param reliefType the type of the relief to set (See ScilabRelief.java)
	 */
	public static void setFrameRelief(int id, String reliefType) {
		((Frame) UIElementMapper.getCorrespondingUIElement(id)).setRelief(reliefType);
	}

}
