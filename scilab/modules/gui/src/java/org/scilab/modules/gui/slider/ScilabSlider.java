
/* Copyright INRIA 2008 */

package org.scilab.modules.gui.slider;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.bridge.ScilabBridge;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.widget.ScilabWidget;

/**
 * Class for Scilab Sliders in GUIs
 * @author Vincent COUVERT
 */
public class ScilabSlider extends ScilabWidget implements Slider {

	private SimpleSlider component;
	
	/**
	 * Constructor
	 */
	protected ScilabSlider() {
		component = ScilabBridge.createSlider();
	}

	/**
	 * Creates a Scilab Slider object
	 * @return the created Slider
	 */
	public static Slider createSlider() {
		return new ScilabSlider();
	}
	
	/**
	 * Gets this Bridge component object
	 * @return this Bridge component object
	 */
	public SimpleSlider getAsSimpleSlider() {
		return component;
	}
	
	/**
	 * Sets the text of a Slider
	 * @param newText the text to set to the Slider
	 */
	public void setText(String newText) {
		ScilabBridge.setText(this, newText);
	}
	
	/**
	 * Gets the text of a Slider
	 * @return text of the Slider
	 */
	public String getText() {
		return ScilabBridge.getText(this);
	}
	
	/**
	 * Draws a Slider
	 */
	public void draw() {
		ScilabBridge.draw(this);
	}
	
	/**
	 * Sets the dimensions (width and height) of a swing Scilab element
	 * @param newSize the dimensions to set to the element
	 * @see org.scilab.modules.gui.uielement.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public void setDims(Size newSize) {
		ScilabBridge.setDims(this, newSize); 
	}
	
	/**
	 * Gets the dimensions (width and height) of a swing Scilab element
	 * @return the dimensions (width and height) of the element
	 * @see org.scilab.modules.gui.uielement.UIElement#getDims(org.scilab.modules.gui.utils.Size)
	 */
	public Size getDims() {
		return ScilabBridge.getDims(this);
	}
	
	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab element
	 * @return the position of the element
	 * @see org.scilab.modules.gui.uielement.UIElement#getPosition()
	 */
	public Position getPosition() {
		return ScilabBridge.getPosition(this);
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab element
	 * @param newPosition the position we want to set to the element
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
	 * To get the Background color of the element.
	 * @return color the Color
	 */
	public Color getBackground() {
		return ScilabBridge.getBackground(this);
	}

	/**
	 * To get the Font of the element.
	 * @return font the Font
	 */
	public Font getFont() {
		return ScilabBridge.getFont(this);
	}

	/**
	 * To get the Foreground color of the element.
	 * @return color the Color
	 */
	public Color getForeground() {
		return ScilabBridge.getForeground(this);
	}

	/**
	 * To set the Background color of the element.
	 * @param color the Color
	 */
	public void setBackground(Color color) {
		ScilabBridge.setBackground(this, color);
	}

	/**
	 * To set the Font of the element.
	 * @param font the Font
	 */
	public void setFont(Font font) {
		ScilabBridge.setFont(this, font);
	}

	/**
	 * To set the Foreground color of the element.
	 * @param color the Color
	 */
	public void setForeground(Color color) {
		ScilabBridge.setForeground(this, color);
	}
	
	/**
	 * Add a callback to the Slider
	 * @param command the Scilab command to execute when the Slider is activated
	 * @param commandType the type of the command that will be executed.
	 */
	public void setCallback(String command, int commandType) {
		ScilabBridge.setCallback(this, command, commandType);
	}
	
	/**
	 * Set if the Slider is enabled or not
	 * @param status true if the Slider is enabled
	 */
	public void setEnabled(boolean status) {
		ScilabBridge.setEnabled(this, status);
	}

	/**
	 * Set the horizontal alignment for the Slider text
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public void setHorizontalAlignment(String alignment) {
		ScilabBridge.setHorizontalAlignment(this, alignment);
	}

	/**
	 * Set the vertical alignment for the Slider text
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public void setVerticalAlignment(String alignment) {
		ScilabBridge.setVerticalAlignment(this, alignment);
	}

	/**
	 * Set the minor tick spacing for a Slider
	 * @param space the increment value
	 */
	public void setMinorTickSpacing(int space) {
		ScilabBridge.setMinorTickSpacing(this, space);	
	}

	/**
	 * Set the major tick spacing for a Slider
	 * @param space the increment value
	 */
	public void setMajorTickSpacing(int space) {
		ScilabBridge.setMinorTickSpacing(this, space);	
	}

	/**
	 * Set the minimum value of a Slider
	 * @param value the minimum value
	 */
	public void setMinimumValue(int value) {
		ScilabBridge.setMinimumValue(this, value);	
	}

	/**
	 * Set the maximum value of a Slider
	 * @param value the maximum value
	 */
	public void setMaximumValue(int value) {
		ScilabBridge.setMinimumValue(this, value);	
	}

}
