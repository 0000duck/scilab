
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.radiobutton;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.bridge.radiobutton.SwingScilabRadioButton;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

/**
 * Bridge for Scilab RadioButton in GUIs
 * @author Vincent COUVERT
 * @author Marouane BEN JELLOUL
 */
public class ScilabRadioButtonBridge {
	
	/**
	 * Constructor
	 */
	protected ScilabRadioButtonBridge() {
		throw new UnsupportedOperationException(); /* Prevents calls from subclass */
	}

	/**
	 * Creates a Scilab RadioButton
	 * @return the created RadioButton
	 */
	public static SimpleRadioButton createRadioButton() {
		return new SwingScilabRadioButton();
	}
	
	/**
	 * Sets the Text of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to set the Text of
	 * @param newText the Text we want to set to the RadioButton
	 */
	public static void setText(RadioButton radioButton, String newText) {
		radioButton.getAsSimpleRadioButton().setText(newText);
	}
	
	/**
	 * Sets the Text of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to get the Text of
	 * @return the text of the RadioButton
	 */
	public static String getText(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getText();
	}
	
	/**
	 * Draws a Scilab RadioButton
	 * @param radioButton the RadioButton to draw
	 * @see org.scilab.modules.gui.UIElement#draw()
	 */
	public static void draw(RadioButton radioButton) {
		radioButton.getAsSimpleRadioButton().draw();
	}

	/**
	 * Gets the dimensions (width and height) of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to get the dimensions of
	 * @return the size of the RadioButton
	 * @see org.scilab.modules.gui.UIElement#getDims()
	 */
	public static Size getDims(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getDims();
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to get the position of
	 * @return the position of the RadioButton
	 * @see org.scilab.modules.gui.UIElement#getPosition()
	 */
	public static Position getPosition(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getPosition();
	}

	/**
	 * Gets the visibility status of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to get the visiblity status of
	 * @return the visibility status of the RadioButton (true if the RadioButton is visible, false if not)
	 * @see org.scilab.modules.gui.UIElement#isVisible()
	 */
	public static boolean isVisible(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().isVisible();
	}

	/**
	 * Sets the dimensions (width and height) of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to set the dimensions of
	 * @param newSize the size we want to set to the RadioButton
	 * @see org.scilab.modules.gui.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public static void setDims(RadioButton radioButton, Size newSize) {
		radioButton.getAsSimpleRadioButton().setDims(newSize);
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to set the position of
	 * @param newPosition the position we want to set to the RadioButton
	 * @see org.scilab.modules.gui.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public static void setPosition(RadioButton radioButton, Position newPosition) {
		radioButton.getAsSimpleRadioButton().setPosition(newPosition);
	}

	/**
	 * Sets the visibility status of a Scilab RadioButton
	 * @param radioButton the RadioButton we want to set the visiblity status of
	 * @param newVisibleState the visibility status we want to set to the RadioButton (true to set the RadioButton visible, false else)
	 * @see org.scilab.modules.gui.UIElement#setVisible(boolean)
	 */
	public static void setVisible(RadioButton radioButton, boolean newVisibleState) {
		radioButton.getAsSimpleRadioButton().setVisible(newVisibleState);
	}
	
	/**
	 * Add a callback to the RadioButton
	 * @param radioButton the RadioButton we want to set the callback of
	 * @param command the Scilab command to execute when the contents of the RadioButton is validated
	 * @param commandType the type of the command that will be executed.
	 */
	public static void setCallback(RadioButton radioButton, String command, int commandType) {
		radioButton.getAsSimpleRadioButton().setCallback(command, commandType);
	}
	
	/**
	 * To set the Background color of the RadioButton
	 * @param radioButton the RadioButton we want to set the background of
	 * @param color the Color
	 */
	public static void setBackground(RadioButton radioButton, Color color) {
		radioButton.getAsSimpleRadioButton().setBackground(color);
	}

	/**
	 * Get the Background color of the RadioButton
	 * @param radioButton the RadioButton we want to get the background of
	 * @return the Color
	 */
	public static Color getBackground(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getBackground();
	}

	/**
	 * To set the Foreground color of the RadioButton
	 * @param radioButton the RadioButton we want to set the foreground of
	 * @param color the Color
	 */
	public static void setForeground(RadioButton radioButton, Color color) {
		radioButton.getAsSimpleRadioButton().setForeground(color);
	}

	/**
	 * Get the Foreground color of the RadioButton
	 * @param radioButton the RadioButton we want to get the foreground of
	 * @return the Color
	 */
	public static Color getForeground(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getForeground();
	}

	/**
	 * Set the font of the RadioButton.
	 * @param radioButton the RadioButton we want to set the font of
	 * @param font the font
	 */
	public static void setFont(RadioButton radioButton, Font font) {
		radioButton.getAsSimpleRadioButton().setFont(font);
	}
	
	/**
	 * Get the font of the RadioButton.
	 * @param radioButton the RadioButton we want to get the font of
	 * @return the font
	 */
	public static Font getFont(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().getFont();
	}
	
	/**
	 * Set if the RadioButton is enabled or not
	 * @param radioButton the RadioButton we want to set the status of
	 * @param status true if the RadioButton is enabled
	 */
	public static void setEnabled(RadioButton radioButton, boolean status) {
		radioButton.getAsSimpleRadioButton().setEnabled(status);
	}
	
	/**
	 * Set the horizontal alignment for the RadioButton text
	 * @param radioButton the RadioButton we want to set the alignment of
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setHorizontalAlignment(RadioButton radioButton, String alignment) {
		radioButton.getAsSimpleRadioButton().setHorizontalAlignment(alignment);
	}

	/**
	 * Set the vertical alignment for the RadioButton text
	 * @param radioButton the RadioButton we want to set the alignment of
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setVerticalAlignment(RadioButton radioButton, String alignment) {
		radioButton.getAsSimpleRadioButton().setVerticalAlignment(alignment);
	}

	/**
	 * Set if the RadioButton is checked or not
	 * @param radioButton the RadioButton we want to set the status of
	 * @param status true to set the RadioButon checked
	 */
	public static void setChecked(RadioButton radioButton, boolean status) {
		radioButton.getAsSimpleRadioButton().setChecked(status);
	}
	
	/**
	 * Get the status of the RadioButton
	 * @param radioButton the RadioButton we want to get the status of
	 * @return true if the RadioButton is checked
	 */
	public static boolean isChecked(RadioButton radioButton) {
		return radioButton.getAsSimpleRadioButton().isChecked();
	}

	/**
	 * Set the Relief of the RadioButton
	 * @param radioButton the RadioButton which we want to set the Relief of
	 * @param reliefType the type of the relief to set (See ScilabRelief.java)
	 */
	public static void setRelief(RadioButton radioButton, String reliefType) {
		radioButton.getAsSimpleRadioButton().setRelief(reliefType);
	}
}
