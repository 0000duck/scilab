
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.window;

import org.scilab.modules.gui.bridge.ScilabBridge;
import org.scilab.modules.gui.uielement.ScilabUIElement;
import org.scilab.modules.gui.tab.Tab;
import org.scilab.modules.gui.textbox.TextBox;
import org.scilab.modules.gui.toolbar.ToolBar;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.utils.UIElementMapper;
import org.scilab.modules.gui.menubar.MenuBar;

/**
 * Class for Scilab Windows in GUIs
 * @author Vincent COUVERT
 * @author Bruno JOFRET
 */
public class ScilabWindow extends ScilabUIElement implements Window {
	
	private SimpleWindow component;
		
	private TextBox infoBar;
	
	/**
	 * Constructor
	 */
	protected ScilabWindow() {
		component = ScilabBridge.createWindow();
		component.setElementId(UIElementMapper.add(this));

		super.addMenuBar(null);
		super.addToolBar(null);
		// FIXME : infoBar must not be null when creating a Window !!
		// Setter should not exists as used in java.
		// Just think Scilab...
		this.infoBar = null;
		
		setMenuBarId(UIElementMapper.getDefaultId());
		setToolBarId(UIElementMapper.getDefaultId());
	}
	
	/**
	 * Creates a Scilab window object
	 * @return the created window
	 */
	public static Window createWindow() {
		return new ScilabWindow();
	}

	/**
	 * Gets the GUI Window.
	 * @return the GUI dummy window.
	 */
	public SimpleWindow getAsSimpleWindow() {
		return component;
	}
	
	/**
	 * Draw a Scilab window
	 * @see org.scilab.modules.gui.ScilabUIElement#draw()
	 */
	public void draw() {
		ScilabBridge.draw(this);
	}

	/**
	 * Gets the dimensions (width and height) of a Scilab window
	 * @return the dimensions of the window
	 * @see org.scilab.modules.gui.UIElement#getDims()
	 */
	public Size getDims() {
		return ScilabBridge.getDims(this);
	}

	/**
	 * Sets the dimensions of a Scilab window
	 * @param newWindowSize the size we want to set to the window
	 * @see org.scilab.modules.gui.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public void setDims(Size newWindowSize) {
		ScilabBridge.setDims(this, newWindowSize);
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab window
	 * @return the position of the window
	 * @see org.scilab.modules.gui.UIElement#getPosition()
	 */
	public Position getPosition() {
		return ScilabBridge.getPosition(this);
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab window
	 * @param newWindowPosition the position we want to set to the window
	 * @see org.scilab.modules.gui.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public void setPosition(Position newWindowPosition) {
		ScilabBridge.setPosition(this, newWindowPosition);
	}

	/**
	 * Gets the title of a Scilab window
	 * @return the title of the window
	 * @see org.scilab.modules.gui.window.Window#getTitle()
	 */
	public String getTitle() {
		return ScilabBridge.getTitle(this);
	}

	/**
	 * Sets the title of a Scilab window
	 * @param newWindowTitle the title to set to the window
	 * @see org.scilab.modules.gui.window.Window#setTitle(java.lang.String)
	 */
	public void setTitle(String newWindowTitle) {
		ScilabBridge.setTitle(this, newWindowTitle);
	}

	/**
	 * Gets the visibility status of a Scilab window
	 * @return the visibility status of the window (true if the window is visible, false if not)
	 * @see org.scilab.modules.gui.UIElement#isVisible()
	 */
	public boolean isVisible() {
		return ScilabBridge.isVisible(this);
	}

	/**
	 * Sets the visibility status of a Scilab window
	 * @param newVisibleState the visibility status we want to set to the window (true to set the window visible, false else)
	 * @see org.scilab.modules.gui.UIElement#setVisible(boolean)
	 */
	public void setVisible(boolean newVisibleState) {
		ScilabBridge.setVisible(this, newVisibleState);
	}

	/**
	 * Add a tab to a Scilab window
	 * @param newTab the tab to add to the window
	 * @see org.scilab.modules.gui.window.Window#addTab(org.scilab.modules.gui.tab.Tab)
	 */
	public void addTab(Tab newTab) {
		ScilabBridge.addTab(this, newTab);
	}

	/**
	 * Sets a MenuBar to a Scilab window
	 * @param newMenuBar the tab to add to the window
	 * @see org.scilab.modules.gui.window.Window#setMenuBar(org.scilab.modules.gui.widget.MenuBar)
	 */
	public void addMenuBar(MenuBar newMenuBar) {
		super.addMenuBar(newMenuBar);
		ScilabBridge.addMenuBar(this, newMenuBar);
	}
	
	/**
	 * Sets a Scilab ToolBar to a Scilab window
	 * @param newToolBar the Scilab ToolBar to set to the Scilab window
	 * @see org.scilab.modules.gui.window.Window#setToolBar(org.scilab.modules.gui.toolbar.ToolBar)
	 */
	public void addToolBar(ToolBar newToolBar) {
		super.addToolBar(newToolBar);
		ScilabBridge.addToolBar(this, newToolBar);
	}
	
	/**
	 * Sets a Scilab InfoBar to a Scilab window
	 * @param newInfoBar the Scilab InfoBar to set to the Scilab window
	 * @see org.scilab.modules.gui.window.Window#setInfoBar(org.scilab.modules.gui.textbox.TextBox)
	 */
	public void addInfoBar(TextBox newInfoBar) {
		this.infoBar = newInfoBar;
		ScilabBridge.addInfoBar(this, newInfoBar);
	}
	
	/**
	 * Get a Scilab InfoBar from this Scilab window
	 * @return this window InfoBar
	 */
	public TextBox getInfoBar() {
		return this.infoBar;
	}
}
