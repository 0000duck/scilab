
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.menuitem;

import org.scilab.modules.gui.widget.Widget;

/**
 * Interface for MenuItem associated to objects in Scilab GUIs
 * @author Vincent COUVERT
 * @author Marouane BEN JELLOUL
 */
public interface MenuItem extends Widget {
	
	/**
	 * Gets this Bridge component object
	 * @return this Bridge component object
	 */
	SimpleMenuItem getAsSimpleMenuItem();
	
	/**
	 * set a mnemonic to a MenuItem
	 * @param mnemonic the Mnemonic of the MenuItem
	 */
	void setMnemonic(int mnemonic);
	
	/**
	 * Add a callback to the menu, this callback is a Scilab command
	 * @param command the Scilab command to execute when the menu is activated
	 * @param commandType the type of the command that will be executed.
	 */
	void setCallback(String command, int commandType);
	
	/**
	 * Set if the menu item is enabled or not
	 * @param status true if the menu item is enabled
	 */
	void setEnabled(boolean status);
}
