
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.bridge.console;

import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.StyledDocument;

import org.scilab.modules.console.OneCharKeyEventListener;
import org.scilab.modules.console.SciConsole;
import org.scilab.modules.gui.console.SimpleConsole;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;

import com.artenum.rosetta.interfaces.ui.InputCommandView;
import com.artenum.rosetta.util.StringConstants;

/**
 * Swing implementation for Scilab Console in GUIs
 * This implementation uses JyConsole package
 * @author Vincent COUVERT
 */
public class SwingScilabConsole extends SciConsole implements SimpleConsole {

	private static final long serialVersionUID = 1L;
	
	/**
	 * Constructor
	 */
	public SwingScilabConsole() {
		super();
	}
	
	/**
	 * Displays data in the console
	 * @param dataToDisplay the data to be displayed
	 * @see fr.scilab.console.Console#display(java.lang.String)
	 */
	public void display(String dataToDisplay) {
		//System.out.println("[JAVA - SwingScilabConsole] --> Call ConsolePrint :");
		//System.out.println(dataToDisplay);
		this.getConfiguration().getOutputView().append(dataToDisplay);
	}

	/**
	 * This method is used to display the prompt
	 */
	public void displayPrompt() {
		
		InputCommandView inputCmdView = this.getConfiguration().getInputCommandView();
		// Show the prompt
		this.getConfiguration().getPromptView().setVisible(true);

		// Show the input command view and its hidden components
		inputCmdView.setEditable(true);

		((JTextPane) inputCmdView).setCaretColor(Color.black);
		
		// Remove last line returned given by Scilab (carriage return)
		try {
			StyledDocument outputStyledDoc = this.getConfiguration().getOutputViewStyledDocument();			
			int lastEOL = outputStyledDoc.getText(0, outputStyledDoc.getLength()).lastIndexOf(StringConstants.NEW_LINE);

			if (lastEOL > 1) { // To avoid a "javax.swing.text.BadLocationException: Invalid remove" exception
				outputStyledDoc.remove(lastEOL, outputStyledDoc.getLength() - lastEOL);
			}
		} catch (BadLocationException e) {
			e.printStackTrace();
		}
		
		// Gets the focus to have the caret visible
		((JTextPane) inputCmdView).grabFocus();

		updateScrollPosition();
	}

	/**
	 * Reads one user input char
	 * @return the data entered by the user
	 * @see fr.scilab.console.Console#getCharWithoutOutput()
	 */
	public int getCharWithoutOutput() {
		int retChar;
		
		// Gives the focus to the console to avoid having a blinking caret in the not-editable input command view
		this.requestFocus();
		
		updateScrollPosition();
		
		// Avoids reading of an empty buffer
		try {
			((SciConsole) this).getCanReadUserInputValue().acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Add a keylistener which will set the returned char
		OneCharKeyEventListener keyListener = new OneCharKeyEventListener(this);
		this.addKeyListener(keyListener);
		
		// Reads the buffer
		retChar = this.getUserInputValue();
		((SciConsole) this).getCanReadUserInputValue().release();

		// Remove the "more" message and replace it by an empty line
		this.clear(-1);
		this.display(StringConstants.NEW_LINE);

		this.removeKeyListener(keyListener);

		return retChar;
	}

	/**
	 * Draw a console
	 */
	public void draw() {
		super.setVisible(true);
		super.doLayout();
	}

	/**
	 * Gets the dimensions (width and height) of a Scilab console
	 * @return the size of the console
	 */
	public Size getDims() {
		return new Size(super.getWidth(), super.getHeight());
	}

	/**
	 * Gets the position (X-coordinate and Y-coordinates) of a Scilab console
	 * @return the position of the console
	 */
	public Position getPosition() {
		return new Position(this.getX(), this.getY());
	}

	/**
	 * Gets the visibility status of a console
	 * @return the visibility status of the console (true if the console is visible, false if not)
	 */
	public boolean isVisible() {
		return super.isVisible();
	}

	/**
	 * Sets the dimensions (width and height) of a Scilab console
	 * @param newSize the size we want to set to the console
	 */
	public void setDims(Size newSize) {
		this.setPreferredSize(new Dimension(newSize.getWidth(), newSize.getHeight()));
	}

	/**
	 * Sets the position (X-coordinate and Y-coordinate) of a Scilab console
	 * @param newPosition the position we want to set to the console
	 */
	public void setPosition(Position newPosition) {
		this.setLocation(newPosition.getX(), newPosition.getY());
	}

	/**
	 * Sets the visibility status of a Scilab console
	 * @param newVisibleState the visibility status we want to set to the console
	 */
	public void setVisible(boolean newVisibleState) {
		super.setVisible(newVisibleState);
	}

	/**
	 * Clears the Console
	 */
	public void clear() {
		super.clear();
	}

	/**
	  * Sets the prompt displayed in the console
	  * @param prompt the prompt to be displayed in the console
	  */
	public void setPrompt(String prompt) {
		this.getConfiguration().getPromptView().setDefaultPrompt(prompt);
	}
	
}
