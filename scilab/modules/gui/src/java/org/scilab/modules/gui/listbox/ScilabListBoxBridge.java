
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.listbox;

import java.awt.Color;
import java.awt.Font;

import org.scilab.modules.gui.bridge.listbox.SwingScilabListBox;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

/**
 * Bridge for Scilab ListBox in GUIs
 * @author Vincent COUVERT
 * @author Marouane BEN JELLOUL
 */
public class ScilabListBoxBridge {
	
	/**
	 * Constructor
	 */
	protected ScilabListBoxBridge() {
		throw new UnsupportedOperationException(); /* Prevents calls from subclass */
	}


	/**
	 * Creates a Scilab ListBox
	 * @return the created ListBox
	 */
	public static SimpleListBox createListBox() {
		return new SwingScilabListBox();
	}
	
	/**
	 * Sets the Text of a Scilab ListBox
	 * @param listBox the ListBox we want to set the Text of
	 * @param newText the Text we want to set to the ListBox
	 */
	public static void setText(ListBox listBox, String newText) {
		listBox.getAsSimpleListBox().setText(newText);
	}
	
	/**
	 * Sets the Text of a Scilab ListBox
	 * @param listBox the ListBox we want to get the Text of
	 * @return the text of the ListBox
	 */
	public static String getText(ListBox listBox) {
		return listBox.getAsSimpleListBox().getText();
	}
	
	/**
	 * Draws a Scilab listBox
	 * @param listBox the listBox to draw
	 * @see org.scilab.modules.gui.UIElement#draw()
	 */
	public static void draw(ListBox listBox) {
		listBox.getAsSimpleListBox().draw();
	}

	/**
	 * Gets the dimensions (width and height) of a Scilab ListBox
	 * @param listBox the listBox we want to get the dimensions of
	 * @return the size of the listBox
	 * @see org.scilab.modules.gui.UIElement#getDims()
	 */
	public static Size getDims(ListBox listBox) {
		return listBox.getAsSimpleListBox().getDims();
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinate) of a Scilab listBox
	 * @param listBox the listBox we want to get the position of
	 * @return the position of the listBox
	 * @see org.scilab.modules.gui.UIElement#getPosition()
	 */
	public static Position getPosition(ListBox listBox) {
		return listBox.getAsSimpleListBox().getPosition();
	}

	/**
	 * Gets the visibility status of a Scilab ListBox
	 * @param listBox the listBox we want to get the visiblity status of
	 * @return the visibility status of the listBox (true if the listBox is visible, false if not)
	 * @see org.scilab.modules.gui.UIElement#isVisible()
	 */
	public static boolean isVisible(ListBox listBox) {
		return listBox.getAsSimpleListBox().isVisible();
	}

	/**
	 * Sets the dimensions (width and height) of a Scilab ListBox
	 * @param listBox the listBox we want to set the dimensions of
	 * @param newSize the size we want to set to the listBox
	 * @see org.scilab.modules.gui.UIElement#setDims(org.scilab.modules.gui.utils.Size)
	 */
	public static void setDims(ListBox listBox, Size newSize) {
		listBox.getAsSimpleListBox().setDims(newSize);
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab listBox
	 * @param listBox the listBox we want to set the position of
	 * @param newPosition the position we want to set to the listBox
	 * @see org.scilab.modules.gui.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
	 */
	public static void setPosition(ListBox listBox, Position newPosition) {
		listBox.getAsSimpleListBox().setPosition(newPosition);
	}

	/**
	 * Sets the visibility status of a Scilab ListBox
	 * @param listBox the listBox we want to set the visiblity status of
	 * @param newVisibleState the visibility status we want to set to the listBox (true to set the listBox visible, false else)
	 * @see org.scilab.modules.gui.UIElement#setVisible(boolean)
	 */
	public static void setVisible(ListBox listBox, boolean newVisibleState) {
		listBox.getAsSimpleListBox().setVisible(newVisibleState);
	}
	
	/**
	 * Add a callback to the ListBox
	 * @param listBox the ListBox we want to set the callback of
	 * @param command the Scilab command to execute when the contents of the listBox is validated
	 * @param commandType the type of the command that will be executed.
	 */
	public static void setCallback(ListBox listBox, String command, int commandType) {
		listBox.getAsSimpleListBox().setCallback(command, commandType);
	}
	
	/**
	 * To set the Background color of the ListBox
	 * @param listBox the ListBox we want to set the background of
	 * @param color the Color
	 */
	public static void setBackground(ListBox listBox, Color color) {
		listBox.getAsSimpleListBox().setBackground(color);
	}

	/**
	 * Get the Background color of the ListBox
	 * @param listBox the ListBox we want to get the background of
	 * @return the Color
	 */
	public static Color getBackground(ListBox listBox) {
		return listBox.getAsSimpleListBox().getBackground();
	}

	/**
	 * To set the Foreground color of the listBox
	 * @param listBox the ListBox we want to set the foreground of
	 * @param color the Color
	 */
	public static void setForeground(ListBox listBox, Color color) {
		listBox.getAsSimpleListBox().setForeground(color);
	}

	/**
	 * Get the Foreground color of the ListBox
	 * @param listBox the ListBox we want to get the foreground of
	 * @return the Color
	 */
	public static Color getForeground(ListBox listBox) {
		return listBox.getAsSimpleListBox().getForeground();
	}

	/**
	 * Set the font of the ListBox.
	 * @param listBox the ListBox we want to set the font of
	 * @param font the font
	 */
	public static void setFont(ListBox listBox, Font font) {
		listBox.getAsSimpleListBox().setFont(font);
	}
	
	/**
	 * Get the font of the ListBox.
	 * @param listBox the ListBox we want to get the font of
	 * @return the font
	 */
	public static Font getFont(ListBox listBox) {
		return listBox.getAsSimpleListBox().getFont();
	}
	
	/**
	 * Set if the ListBox is enabled or not
	 * @param listBox the ListBox we want to set the status of
	 * @param status true if the ListBox is enabled
	 */
	public static void setEnabled(ListBox listBox, boolean status) {
		listBox.getAsSimpleListBox().setEnabled(status);
	}
	
	/**
	 * Set the horizontal alignment for the ListBox text
	 * @param listBox the ListBox we want to set the alignment of
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setHorizontalAlignment(ListBox listBox, String alignment) {
		listBox.getAsSimpleListBox().setHorizontalAlignment(alignment);
	}

	/**
	 * Set the vertical alignment for the ListBox text
	 * @param listBox the ListBox we want to set the alignment of
	 * @param alignment the value for the alignment (See ScilabAlignment.java)
	 */
	public static void setVerticalAlignment(ListBox listBox, String alignment) {
		listBox.getAsSimpleListBox().setVerticalAlignment(alignment);
	}

}
