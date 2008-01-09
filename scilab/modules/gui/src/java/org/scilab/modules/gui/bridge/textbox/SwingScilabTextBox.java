
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.bridge.textbox;

import javax.swing.JTextArea;

import org.scilab.modules.gui.menubar.MenuBar;
import org.scilab.modules.gui.textbox.SimpleTextBox;
import org.scilab.modules.gui.toolbar.ToolBar;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

/**
 * Swing implementation for Scilab TextBox in GUIs
 * @author Marouane BEN JELLOUL
 */
public class SwingScilabTextBox extends JTextArea implements SimpleTextBox {

	/**
	 * Constructor
	 */
	public SwingScilabTextBox() {
		super();
		setEditable(false);
	}

	/**
	 * Sets the text of a Text Widget
	 * @param newText the text to set to the Text Widget
	 */
	@Override
	public void setText(String newText) {
		super.setText(newText);
	}

	/**
	 * Gets the text of a Text Widget
	 * @return the text of the Text Widget
	 */
	@Override
	public String getText() {
		return super.getText();
	}
	
	/**
	 * Draws a swing Scilab TextBox
	 * @see org.scilab.modules.gui.uielement.UIElement#draw()
	 */
	public void draw() {
		this.setVisible(true);
		this.doLayout();
	}

	/**
	 * Gets the dimensions (width and height) of a swing Scilab TextBox
	 * @return the dimensions of the TextBox
	 * @see org.scilab.modules.gui.uielement.UIElement#getDims()
	 */
	public Size getDims() {
		return new Size(super.getSize().width, super.getSize().height);
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a swing Scilab TextBox
	 * @return the position of the TextBox
	 * @see org.scilab.modules.gui.uielement.UIElement#getPosition()
	 */
	public Position getPosition() {
		return new Position(super.getX(), super.getY());
	}
	
	/**
	 * Sets the dimensions (width and height) of a swing Scilab TextBox
	 * @param newSize the dimensions to set to the TextBox
	 * @see org.scilab.modules.gui.uielement.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public void setDims(Size newSize) {
		super.setSize(newSize.getWidth(), newSize.getHeight());
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a swing Scilab TextBox
	 * @param newPosition the position to set to the TextBox
	 * @see org.scilab.modules.gui.uielement.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public void setPosition(Position newPosition) {
		this.setLocation(newPosition.getX(), newPosition.getY());
	}
	

	/**
	 * Get the id of the menu bar associated to the TextBox
	 * @return the menubar
	 * @see org.scilab.modules.gui.uielement.UIElement#getMenuBar()
	 */
	public MenuBar getMenuBar() {
		// Must not be there...
		return null;
	}

	/**
	 * Get the id of the tool bar associated to the TextBox
	 * @return the toolbar
	 * @see org.scilab.modules.gui.uielement.UIElement#getToolBar()
	 */
	public ToolBar getToolBar() {
		// Must not be there...
		return null;
	}
	
	/**
	 * Add a Scilab MenuBar to a Scilab TextBox
	 * @param menuBarToAdd the Scilab MenuBar to add to the Scilab TextBox
	 * @see org.scilab.modules.gui.window.Window#setMenuBar(org.scilab.modules.gui.menubar.MenuBar)
	 */
	public void addMenuBar(MenuBar menuBarToAdd) {
		// TODO Auto-generated method stub
		
	}

	/**
	 * Add a Scilab Toolbar to a Scilab TextBox
	 * @param toolBarToAdd the Scilab ToolBar to add to the Scilab TextBox
	 * @see org.scilab.modules.gui.window.Window#setToolBar(org.scilab.modules.gui.menubar.ToolBar)
	 */
	public void addToolBar(ToolBar toolBarToAdd) {
		// TODO Auto-generated method stub
		
	}
	
	/**
	 * Add a callback to the TextBox
	 * @param command the Scilab command to execute when the contents of the TextBox is validated
	 * @param commandType the type of the command that will be executed.
	 */
	public void setCallback(String command, int commandType) {
		throw new UnsupportedOperationException();
	}


}
