package org.scilab.modules.xpad.style;

import javax.swing.text.BadLocationException;

import org.scilab.modules.gui.dockable.ScilabDockable;

public class TabManager {
	private static String tabulation = "  ";
	
	public static String getTabulation() { 
		return tabulation;
		}
	
	/*
	 * Insert a tab just after the caret position
	 */
	public synchronized void insertTab(ScilabStyleDocument scilabDocument, int position) {
		try {
			scilabDocument.insertString(position, getTabulation(), null);
		}
		catch (BadLocationException e) 		{
			e.printStackTrace();
		}
	}
	
	/*
	 * Tabify a line
	 */
	public synchronized int tabifyLine(ScilabStyleDocument scilabDocument, int line) {
		insertTab(scilabDocument, scilabDocument.getDefaultRootElement().getElement(line).getStartOffset());	
		return getTabulation().length();
	}
	
	/*
	 * Tabify several lines
	 */
	public synchronized int tabifyLines(ScilabStyleDocument scilabDocument, int line_start, int line_end) {
		IndentManager indentManager = new IndentManager();
		ColorizationManager colorizationManager = new ColorizationManager();
		
		boolean indentMode = indentManager.getAutoIndent();
		boolean colorizeMode = colorizationManager.getColorize();
		boolean mergeEditsMode = scilabDocument.getUpdateManager().getShouldMergeEdits();
		
		indentManager.setAutoIndent(false);
		colorizationManager.setColorize(false);
		
		scilabDocument.getUpdateManager().setShouldMergeEdits(true);
		
		for (int currentLine = line_start; currentLine <= line_end; ++currentLine) { // tabifying should not insert/remove lines
			tabifyLine(scilabDocument, currentLine);
		}
		indentManager.setAutoIndent(indentMode);
		colorizationManager.setColorize(colorizeMode);
		scilabDocument.getUpdateManager().setShouldMergeEdits(mergeEditsMode);
		return getTabulation().length();
	}
		
	/**
	 * DOCUMENT UNTABIFY ACTION
	 */
	
	/*
	 * Delete a tab just after position if possible.
	 * returns the nb of deleted characters.
	 */
	public synchronized int deleteTab(ScilabStyleDocument scilabDocument, int position)	{
		String tab = getTabulation(); 
		int res = 0, tabLength = tab.length();
		try {
			String nextChars = scilabDocument.getText(position, tabLength);
			if(nextChars.equals(tab)){
				scilabDocument.remove(position, tabLength);
				res= tabLength;
			}
		}
		catch (BadLocationException e)
		{
			e.printStackTrace();
			res= 0;
		}
		
		return res;
	}
	
	/*
	 * Delete a tab at the beginning of the line "line" if there was one.
	 * returns the nb of deleted characters. 
	 */
	
	public synchronized int untabifyLine(ScilabStyleDocument scilabDocument, int line)
	{
		return this.deleteTab(scilabDocument, scilabDocument.getDefaultRootElement().getElement(line).getStartOffset());
	}
	
	/*
	 * Delete tabs at the beginning of several lines
	 */
	public boolean canUntabifyLines(ScilabStyleDocument scilabDocument, int line_start, int line_end)
	{
		boolean result = true;
		String tab = getTabulation();
		int tabLength = tab.length();
		try {
			for (int i = line_start; result && (i <= line_end); i++)
			{
				result = result && (tab.equals(scilabDocument.getText(scilabDocument.getDefaultRootElement().getElement(i).getStartOffset(), tabLength)));
			}
		}
		catch( javax.swing.text.BadLocationException e){
			System.err.println("untabifying lines "+line_start+" to "+line_end+" "+e);
		}
		return result;
	}
	/*
	 * remove one tabulation step from every line starting with tabulation in [line_start, line_end]
	 * returns an array of int containing the position delta for line start and line end.
	 * the first value is getTabulation().length() if the first line was starting with a tabulation, 0 otherwise
	 * the second value is the total nb of character removed in the region.   
	 */
	public synchronized int[] untabifyLines(ScilabStyleDocument scilabDocument, int line_start, int line_end)
	{	
		int []res={0,0};
        IndentManager indentManager = new IndentManager();
        ColorizationManager colorizationManager = new ColorizationManager();

		if(true || canUntabifyLines(scilabDocument, line_start, line_end)) // always untabify as much lines as possible from a selection
		{
			//boolean indentMode= getAutoIndent(), colorizeMode= getColorize(), mergeEditsMode= getShouldMergeEdits();
            boolean indentMode = indentManager.getAutoIndent();
            boolean colorizeMode = colorizationManager.getColorize();
            boolean mergeEditsMode = scilabDocument.getUpdateManager().getShouldMergeEdits();

			//setAutoIndent(false);
			//setColorize(false);
			//setShouldMergeEdits(true);
			for (int currentLine = line_start; currentLine <= line_end; ++currentLine) { // tabifying should not insert/remove lines
				res[1] += untabifyLine(scilabDocument, currentLine); // accumulate nb of deleted characters
				if (currentLine == line_start) {
					res[0] = res[1]; // nb of deleted characters in the first line
				}
			}
			
            indentManager.setAutoIndent(indentMode);
            colorizationManager.setColorize(colorizeMode);
            scilabDocument.getUpdateManager().setShouldMergeEdits(mergeEditsMode);
/*
			setAutoIndent(indentMode);
			setColorize(colorizeMode);
			setShouldMergeEdits(mergeEditsMode);
			*/
		}
		return res;
	}
	
}
