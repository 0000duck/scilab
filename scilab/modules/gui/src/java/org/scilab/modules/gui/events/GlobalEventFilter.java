package org.scilab.modules.gui.events;

import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;

import org.scilab.modules.gui.bridge.canvas.SwingScilabCanvas;

/**
 * This class is to manage Events as Scilab used to.
 * Means we need a global overview for a little set of them
 * in particular "event waiting" functions.
 * 
 * @author bruno
 *
 */
public class GlobalEventFilter {

	private static final int SCILAB_CTRL_OFFSET = 1000;
	private static final int SCILAB_CALLBACK = -2;
	
	/**
	 * Update ClickInfos structure when a KeyEvent occurs.
	 * 
	 * @param keyPressed : the key pressed.
	 * @param isControlDown : is CTRL key modifier activated.
	 */
	public static void filterKey(int keyPressed, boolean isControlDown) {
		int keyCode = keyPressed;
		synchronized (ClickInfos.getInstance()) {
			if (isControlDown) {
				keyCode += SCILAB_CTRL_OFFSET;
			}
			ClickInfos.getInstance().setMouseButtonNumber(keyCode);
			ClickInfos.getInstance().notify();
		}
	}
	
	/**
	 * Update ClickInfos structure when some callback is about to be called.
	 * 
	 * @param event : the event caught.
	 * @param command : the callback that was supposed to be called.
	 */
	public static void filterCallback(ActionEvent event, String command) {
		synchronized (ClickInfos.getInstance()) {
			ClickInfos.getInstance().setMouseButtonNumber(SCILAB_CALLBACK);
			ClickInfos.getInstance().setMenuCallback(command);
			ClickInfos.getInstance().notify();
		}
	}	
	
	/**
	 * Update ClickInfos structure when a mouse event occurs on a Canvas.
	 * 
	 * @param mouseEvent : the event caught.
	 * @param source : the canvas where the event occurs.
	 * @param buttonCode : the Scilab button code.
	 */
	public static void filterMouse(MouseEvent mouseEvent, SwingScilabCanvas source, int buttonCode) {
		synchronized (ClickInfos.getInstance()) {
			ClickInfos.getInstance().setXCoordinate(mouseEvent.getPoint().getX());
			ClickInfos.getInstance().setYCoordinate(mouseEvent.getPoint().getY());
			if (mouseEvent.isControlDown()) {
				ClickInfos.getInstance().setMouseButtonNumber(buttonCode + mouseEvent.getButton() + SCILAB_CTRL_OFFSET);
			} else {
				ClickInfos.getInstance().setMouseButtonNumber(buttonCode + mouseEvent.getButton());
			}
			// @TODO : Find a way to get the ID.
			ClickInfos.getInstance().setWindowID(0);
			ClickInfos.getInstance().notify();
		}
	}
}
