
/* Copyright INRIA 2007 */

package org.scilab.modules.gui.menu;

import org.scilab.modules.gui.bridge.ScilabBridge;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.widget.ScilabWidget;

/**
 * Class for Scilab Menus in GUIs
 * @author Marouane BEN JELLOUL
 */
public class ScilabMenu extends ScilabWidget implements Menu {

	private SimpleMenu component;
	
	/**
	 * Constructor
	 */
	protected ScilabMenu() {
		component = ScilabBridge.createMenu();
	}
	
	/**
	 * Creates a Scilab Menu object
	 * @return the created Menu
	 */
	public static Menu createMenu() {
		return new ScilabMenu();
	}
	
	/**
	 * Gets this Bridge component object
	 * @return this Bridge component object
	 */
	public SimpleMenu getAsSimpleMenu() {
		return component;
	}
	
	/**
	 * Append a MenuItem to a Scilab Menu
	 * @param newMenuItem the MenuItem to add to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#add(org.scilab.modules.gui.MenuItem)
	 */
	public void add(MenuItem newMenuItem) {
		ScilabBridge.add(this, newMenuItem);
	}
	
	/**
	 * Append a subMenu to a Scilab Menu
	 * @param newSubMenu the subMenu to append to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#add(org.scilab.modules.gui.Menu)
	 */
	public void add(Menu newSubMenu) {
		ScilabBridge.add(this, newSubMenu);
	}
	
	/**
	 * Sets the text of a Scilab Menu
	 * @param newText the Text to set to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#setText(java.lang.String)
	 */
	public void setText(String newText) {
		ScilabBridge.setText(this, newText);
	}
	
	/**
	 * Gets the text of a Scilab Menu
	 * @return the Text to set to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#getText(java.lang.String)
	 */
	public String getText() {
		return ScilabBridge.getText(this);
	}
	
	/**
	 * set a mnemonic to a Menu
	 * @param mnemonic the mnemonic to add to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#setMnemonic(org.scilab.modules.gui.widget.int)
	 */
	public void setMnemonic(int mnemonic) {
		ScilabBridge.setMnemonic(this, mnemonic);
	}
	
	/**
	 * Add a Separator to the Menu
	 * @see org.scilab.modules.gui.menu.Menu#addSeparator(org.scilab.modules.gui..)
	 */
	public void addSeparator() {
		ScilabBridge.addSeparator(this);
	}
	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 */
	public void draw() {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @return nothing
	 */
	public Size getDims() {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @return nothing
	 */
	public Position getPosition() {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @return nothing
	 */
	public boolean isVisible() {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @param newSize is not used
	 */
	public void setDims(Size newSize) {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @param newPosition is not used
	 */
	public void setPosition(Position newPosition) {
		throw new UnsupportedOperationException();
	}

	/**
	 * Should not be used, just here to implemeent org.scilab.modules.gui.UIElement#draw()
	 * @param newVisibleState is not used
	 */
	public void setVisible(boolean newVisibleState) {
		throw new UnsupportedOperationException();
	}
}
