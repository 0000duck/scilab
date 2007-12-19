
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.textbox;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.bridge.textbox.SwingScilabTextBox;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

/**
 * Bridge for Scilab TextBox in GUIs
 * @author Marouane BEN JELLOUL
 */
public class ScilabTextBoxBridge {

	/**
	 * Constructor
	 */
	protected ScilabTextBoxBridge() {
		throw new UnsupportedOperationException(); /* Prevents calls from subclass */
	}

	/**
	 * Creates a Scilab TextBox
	 * @return the created TextBox
	 */
	public static SimpleTextBox createTextBox() {
		return new SwingScilabTextBox();
	}
	
	/**
	 * Sets the Text of a Scilab TextBox
	 * @param textBox the TextBox we want to set the Text of
	 * @param newText the Text we want to set to the TextBox
	 */
	public static void setText(TextBox textBox, String newText) {
		textBox.getAsSimpleTextBox().setText(newText);
	}
	
	/**
	 * Sets the Text of a Scilab TextBox
	 * @param textBox the TextBox we want to get the Text of
	 * @return the text of the TextBox
	 */
	public static String getText(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getText();
	}
	
	/**
	 * Draws a Scilab textBox
	 * @param textBox the textBox to draw
	 * @see org.scilab.modules.gui.UIElement#draw()
	 */
	public static void draw(TextBox textBox) {
		textBox.getAsSimpleTextBox().draw();
	}

	/**
	 * Gets the dimensions (width and height) of a Scilab TextBox
	 * @param textBox the textBox we want to get the dimensions of
	 * @return the size of the textBox
	 * @see org.scilab.modules.gui.UIElement#getDims()
	 */
	public static Size getDims(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getDims();
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab textBox
	 * @param textBox the textBox we want to get the position of
	 * @return the position of the textBox
	 * @see org.scilab.modules.gui.UIElement#getPosition()
	 */
	public static Position getPosition(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getPosition();
	}

	/**
	 * Gets the visibility status of a Scilab TextBox
	 * @param textBox the textBox we want to get the visiblity status of
	 * @return the visibility status of the textBox (true if the textBox is visible, false if not)
	 * @see org.scilab.modules.gui.UIElement#isVisible()
	 */
	public static boolean isVisible(TextBox textBox) {
		return textBox.getAsSimpleTextBox().isVisible();
	}

	/**
	 * Sets the dimensions (width and height) of a Scilab TextBox
	 * @param textBox the textBox we want to set the dimensions of
	 * @param newSize the size we want to set to the textBox
	 * @see org.scilab.modules.gui.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public static void setDims(TextBox textBox, Size newSize) {
		textBox.getAsSimpleTextBox().setDims(newSize);
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab textBox
	 * @param textBox the textBox we want to set the position of
	 * @param newPosition the position we want to set to the textBox
	 * @see org.scilab.modules.gui.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public static void setPosition(TextBox textBox, Position newPosition) {
		textBox.getAsSimpleTextBox().setPosition(newPosition);
	}

	/**
	 * Sets the visibility status of a Scilab TextBox
	 * @param textBox the textBox we want to set the visiblity status of
	 * @param newVisibleState the visibility status we want to set to the textBox (true to set the textBox visible, false else)
	 * @see org.scilab.modules.gui.UIElement#setVisible(boolean)
	 */
	public static void setVisible(TextBox textBox, boolean newVisibleState) {
		textBox.getAsSimpleTextBox().setVisible(newVisibleState);
	}

	/**
	 * Set the Background color of a Scilab TextBox
	 * @param textBox the textbox we want to set the background of
	 * @param color the Color
	 */
	public static void setBackground(TextBox textBox, Color color) {
		textBox.getAsSimpleTextBox().setBackground(color);
	}

	/**
	 * Get the Background color of the textbox
	 * @param textBox the textbox we want to get the background of
	 * @return the Color
	 */
	public static Color getBackground(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getBackground();
	}

	/**
	 * Set the Foreground color of a Scilab TextBox
	 * @param textBox the textbox we want to set the foreground of
	 * @param color the Color
	 */
	public static void setForeground(TextBox textBox, Color color) {
		textBox.getAsSimpleTextBox().setForeground(color);
	}

	/**
	 * Get the Foreground color of the textbox
	 * @param textBox the textbox we want to get the foreground of
	 * @return the Color
	 */
	public static Color getForeground(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getForeground();
	}

	/**
	 * Set the font of the textbox.
	 * @param textBox the textbox we want to set the font of
	 * @param font the font
	 */
	public static void setFont(TextBox textBox, Font font) {
		textBox.getAsSimpleTextBox().setFont(font);
	}
	
	/**
	 * Get the font of the textbox.
	 * @param textBox the textbox we want to get the font of
	 * @return the font
	 */
	public static Font getFont(TextBox textBox) {
		return textBox.getAsSimpleTextBox().getFont();
	}
}
