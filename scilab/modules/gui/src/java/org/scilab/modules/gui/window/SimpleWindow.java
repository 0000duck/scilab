
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.window;

import org.scilab.modules.gui.menubar.MenuBar;
import org.scilab.modules.gui.tab.Tab;
import org.scilab.modules.gui.textbox.TextBox;
import org.scilab.modules.gui.toolbar.ToolBar;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

/**
 * Interface for SimpleWindow the associated object to Scilab GUIs Window
 * @author Marouane BEN JELLOUL
 */
public interface SimpleWindow {
	
	/**
	 * Gets the title of a window
	 * @return the title of the window
	 */
	String getTitle();

	/**
	 * Sets the title of a window
	 * @param newWindowTitle the title we want to set for the window
	 */
	void setTitle(String newWindowTitle);

	/**
	 * Add a tab to a window
	 * @param newTab the tab to add to the window
	 */
	void addTab(Tab newTab);
	
	/**
	 * Remove a tab from a window
	 * @param tab tab to remove
	 */
	void removeTab(Tab tab);
	
	/**
	 * Sets a InfoBar to a window
	 * @param newInfoBar the Scilab InfoBar to set to the Scilab window
	 */
	void addInfoBar(TextBox newInfoBar);
	
	/**
	 * Gets the size of an Window (width and height)
	 * @return the size of the Window
	 */
	Size getDims();

	/**
	 * Sets the size of an Window (width and height)
	 * @param newSize the size we want to set to the Window
	 */
	void setDims(Size newSize);

	/**
	 * Gets the position of an Window (X-coordinate and Y-corrdinate)
	 * @return the position of the Window
	 */
	Position getPosition();

	/**
	 * Sets the position of an Window (X-coordinate and Y-corrdinate)
	 * @param newPosition the position we want to set to the Window
	 */
	void setPosition(Position newPosition);

	/**
	 * Gets the visibility status of an Window
	 * @return the visibility status of the Window (true if the Window is visible, false if not)
	 */
	boolean isVisible();

	/**
	 * Sets the visibility status of an Window
	 * @param newVisibleState the visibility status we want to set for the Window
	 * 			(true if the Window is visible, false if not)
	 */
	void setVisible(boolean newVisibleState);

	/**
	 * Draws an Window
	 */
	void draw();
	
	/**
	 * Sets a MenuBar to a window
	 * @param newMenuBar the MenuBar to add to the window
	 */
	void addMenuBar(MenuBar newMenuBar);

	/**
	 * Sets a ToolBar to a window
	 * @param newToolBar the ToolBar to set to the window
	 */
	void addToolBar(ToolBar newToolBar);
	
	/**
	 * Set the element id for this window
	 * @param id the id of the corresponding window object
	 */
	void setElementId(int id);
	
	/**
	 * Get the element id for this window
	 * @return id the id of the corresponding window object
	 */
	int getElementId();
}
