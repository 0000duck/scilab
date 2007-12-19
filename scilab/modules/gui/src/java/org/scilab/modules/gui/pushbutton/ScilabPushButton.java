
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.pushbutton;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.widget.ScilabWidget;
import org.scilab.modules.gui.bridge.ScilabBridge;

/**
* Class for Scilab PushButtons in GUIs
* @author Marouane BEN JELLOUL
*/
public class ScilabPushButton extends ScilabWidget implements PushButton {

	private SimplePushButton component;
	
	/**
	 * Constructor
	 */
	protected ScilabPushButton() {
		component = ScilabBridge.createPushButton();
	}

	/**
	 * Creates a Scilab PushButton object
	 * @return the created PushButton
	 */
	public static PushButton createPushButton() {
		return new ScilabPushButton();
	}
	
	/**
	 * Gets this Bridge component object
	 * @return this Bridge component object
	 */
	public SimplePushButton getAsSimplePushButton() {
		return component;
	}
	
	/**
	 * Sets the text of a PushButton
	 * @param newText the text to set to the PushButton
	 */
	public void setText(String newText) {
		ScilabBridge.setText(this, newText);
	}
	
	/**
	 * Gets the text of a PushButton
	 * @return the text of the PushButton
	 */
	public String getText() {
		return ScilabBridge.getText(this);
	}

	/**
	 * Draws a PushButton
	 */
	public void draw() {
		ScilabBridge.draw(this);
	}
	
	/**
	 * Sets the dimensions (width and height) of a swing Scilab PushButton
	 * @param newSize the dimensions to set to the PushButton
	 * @see org.scilab.modules.gui.uielement.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public void setDims(Size newSize) {
		ScilabBridge.setDims(this, newSize);
	}
	
	/**
	 * Gets the dimensions (width and height) of a swing Scilab Menu
	 * @return the dimensions (width and height) of the window
	 * @see org.scilab.modules.gui.uielement.UIElement#getDims(org.scilab.modules.gui.utils.Size)
	 */
	public Size getDims() {
		return ScilabBridge.getDims(this); 
	}
	
	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab Menu
	 * @return the position of the Menu
	 * @see org.scilab.modules.gui.uielement.UIElement#getPosition()
	 */
	public Position getPosition() {
		return ScilabBridge.getPosition(this); 
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab Menu
	 * @param newPosition the position we want to set to the Menu
	 * @see org.scilab.modules.gui.uielement.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public void setPosition(Position newPosition) {
		ScilabBridge.setPosition(this, newPosition); 
	}

	/**
	 * Gets the visibility status of an UIElement
	 * @return the visibility status of the UIElement (true if the UIElement is visible, false if not)
	 */
	public boolean isVisible() {
		return ScilabBridge.isVisible(this); 
	}
	
	/**
	 * Sets the visibility status of a Menu
	 * @param newVisibleState the visibility status we want to set for the UIElement
	 * 			(true if the UIElement is visible, false if not)
	 */
	public void setVisible(boolean newVisibleState) {
		ScilabBridge.setVisible(this, newVisibleState);
	}
	
	/**
	 * Sets the icon of a PushButton
	 * @param filename the path to the icon image to set to the PushButton
	 */
	public void setIcon(String filename) {
		ScilabBridge.setIcon(this, filename);
	}

	/**
	 * Add a callback to the pushbutton, this callback is a Scilab command
	 * @param command the Scilab command to execute when the pushbutton is activated
	 * @param commandType the type of the command that will be executed.
	 */
	public void setCallback(String command, int commandType) {
		ScilabBridge.setCallback(this, command, commandType);
	}

	/**
	 * Set if the pushbutton is enabled or not
	 * @param status true if the pushbutton is enabled
	 */
	public void setEnabled(boolean status) {
		ScilabBridge.setEnabled(this, status);
	}

	/**
	 * To set the Background color of the pushbutton
	 * @param color the Color
	 */
	public void setBackground(Color color) {
		ScilabBridge.setBackground(this, color);
	}

	/**
	 * Get the Background color of the pushbutton
	 * @return the Color
	 */
	public Color getBackground() {
		return ScilabBridge.getBackground(this);
	}
	
	/**
	 * To set the Foreground color of the pushbutton
	 * @param color the Color
	 */
	public void setForeground(Color color) {
		ScilabBridge.setForeground(this, color);
	}

	/**
	 * Get the Foreground color of the pushbutton
	 * @return the Color
	 */
	public Color getForeground() {
		return ScilabBridge.getForeground(this);
	}

	/**
	 * Set the font of the pushbutton.
	 * @param font the font
	 */
	public void setFont(Font font) {
		ScilabBridge.setFont(this, font);
	}
	
	/**
	 * Get the font of the pushbutton.
	 * @return the font
	 */
	public Font getFont() {
		return ScilabBridge.getFont(this);
	}

	//	/**
//	 * Sets a MenuBar to an element
//	 * @param newMenuBar the MenuBar to set to the element
//	 */
//	public void addMenuBar(MenuBar newMenuBar) {
//		// TODO Auto-generated method stub
//		
//	}
//
//	/**
//	 * Sets a ToolBar to an element
//	 * @param newToolBar the ToolBar to set to the element
//	 */
//	public void addToolBar(ToolBar newToolBar) {
//		// TODO Auto-generated method stub
//		
//	}
	
}
