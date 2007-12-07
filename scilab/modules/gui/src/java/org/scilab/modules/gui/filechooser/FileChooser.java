
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.filechooser;

import org.scilab.modules.gui.uielement.UIElement;

/**
 * Interface for file chooser used by Scilab function such as uigetfile 
 * @author Vincent COUVERT
 */
public interface FileChooser extends UIElement {
	
	/**
	 * Gets this Bridge component object
	 * @return this Bridge component object
	 */
	SimpleFileChooser getAsSimpleFileChooser();
	
	/**
	 * Set the title of the file chooser
	 * @param title the title to set
	 */
	void setTitle(String title);
	
	/**
	 * Set the mask for files to choose
	 * @param mask the mask to set
	 */
	void setMask(String mask);
	
	/**
	 * Set the initial directory used for file search
	 * @param path the default path
	 */
	void setInitialDirectory(String path);
	
	/**
	 * Display this chooser and wait for user selection 
	 */
	void displayAndWait();
	
	/**
	 * Get the number of files selected
	 * @return the number of files selected
	 */
	int getSelectionSize();
	
	/**
	 * Get the names of selected files
	 * @return the names of selected files
	 */
	String[] getSelection();
}
