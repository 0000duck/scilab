package org.scilab.modules.gui.events.callback;

import java.awt.event.ActionEvent;

import org.scilab.modules.action_binding.InterpreterManagement;
import org.scilab.modules.gui.events.GlobalEventFilter;
import org.scilab.modules.gui.events.GlobalEventWatcher;

/**
 * ScilabCallback abstract class to easily manage callbacks
 * that throws commands to Scilab.
 * 
 * @author bruno
 *
 */
public abstract class ScilabCallBack extends CallBack {

	/**
	 * @param command : the command to execute.
	 * @param type : the type of this command. 
	 */
	public ScilabCallBack(String command, int type) {
		this.command = command;
		this.type = type;
	}
	
	/**
	 * Callback Factory to easily create a callback
	 * just like in scilab. 
	 * @param command : the command to execute.
	 * @param type : the type of this command.
	 * @return a usable Java callback
	 */
	public static ScilabCallBack create(String command, int type) {
		return (new ScilabCallBack(command, type) {
				public void callBack() {
					this.storeCommand(this.getCommand(), this.getType());
				}
		});
	}
	
	/**
	 * To match the standard Java Action management.
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 * @param e The event that launch the callback.
	 */
	public void actionPerformed(ActionEvent e) {
		if (!GlobalEventWatcher.isActivated()) { 
				callBack();
		}
		else {
			if (this.command != null) {
				GlobalEventFilter.filter(e, this.command);
			}
		}
	}
	
	/**
	 * Put the command recieved through the callback.
	 * 
	 * @param command : The command to throw to Scilab
	 * @param type : The type of the command, C or Fortran compiled code, Scilab instruction...
	 */
	public void storeCommand(String command, int type) {
		//System.out.println("Store Command  Command="+command+" Type="+type);
		InterpreterManagement.putCommandInScilabQueue(command);
	}

	/**
	 * @return the command if it's a Scilab instruction.
	 */
	public String getCommand() {
		return command;
	}
	
	/**
	 * @return The type of the Scilab callback
	 */
	public int getType() {
		return type;
	}
	
	private String command;
	private int type;
}
