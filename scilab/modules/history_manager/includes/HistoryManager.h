/*------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*------------------------------------------------------------------------*/
#ifndef __HISTORYMANAGER_C_H__
#define __HISTORYMANAGER_C_H__
#include "machine.h" /* BOOL */
/*------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------*/
	/**
	* add a line to History manager
	* @param a line to add
	* line isn't added if it is the same as previous (FALSE)
	* @return TRUE or FALSE
	*/
	BOOL appendLineToScilabHistory(char *line);

	/**
	* append lines to History manager
	* @param array of string
	* @param size of the array of string
	* @return TRUE or FALSE
	*/
	BOOL appendLinesToScilabHistory(char **lines,int numberoflines);

	/**
	* Display history
	*/
	void displayScilabHistory(void);

	/**
	* save history in a file
	* @param a filename if NULL saves in default filename
	* default filename --> SCIHOME/history.scilab
	* @return TRUE or FALSE
	*/
	BOOL writeScilabHistoryToFile(char *filename);

	/**
	* load history from a file
	* @param a filename if NULL load from default filename
	* default filename --> SCIHOME/history.scilab
	* @return TRUE or FALSE
	*/
	BOOL loadScilabHistoryFromFile(char *filename);

	/**
	* set filename of history
	* @param filename of history
	* @return TRUE or FALSE
	*/
	BOOL setFilenameScilabHistory(char *filename);

	/**
	* get filename of history
	* @return a filename
	*/
	char *getFilenameScilabHistory(void);

	/**
	* set default filename of history
	* @return TRUE or FALSE
	*/
	BOOL setDefaultFilenameScilabHistory(void);

	/**
	* reset history manager
	*/
	void resetScilabHistory(void);

	/**
	* Get all lines in history
	* @return a array of string
	*/
	char **getAllLinesOfScilabHistory(void);

	/**
	* Get numbers of lines in history
	* size of array returned by getAllLinesOfScilabHistory
	* @return int 
	*/
	int getSizeAllLinesOfScilabHistory(void);

	/**
	* set new token to search in history
	* @param token (a string)
	* @return TRUE or FALSE
	*/
	BOOL setSearchedTokenInScilabHistory(char *token);

	/**
	* reset search in history
	* @return TRUE or FALSE
	*/
	BOOL resetSearchedTokenInScilabHistory(void);

	/**
	* get token searched in history
	* @return token (a string)
	*/
	char *getSearchedTokenInScilabHistory(void);

	/**
	* Get the previous line in Scilab history
	* @return a line or NULL
	* after a appendLine iterator go to end
	*/
	char *getPreviousLineInScilabHistory(void);

	/**
	* Get the next line in Scilab history
	* @return a line or NULL
	* after a appendLine iterator go to end
	*/
	char *getNextLineInScilabHistory(void);

	/**
	* Get numbers of lines in history
	* @return number of lines
	*/
	int getNumberOfLinesInScilabHistory(void);

	/**
	* set consecutive duplicate lines are added
	* @param doit (TRUE or FALSE)
	*/
	void setSaveConsecutiveDuplicateLinesInScilabHistory(BOOL doit);

	/**
	* indicate if consecutive duplicate lines are added
	* @return TRUE or FALSE
	*/
	BOOL getSaveConsecutiveDuplicateLinesInScilabHistory(void);

	/**
	* Set after how many lines history is saved
	* @param number between 0 and Max
	* default value is 0 (disabled)
	*/
	void setAfterHowManyLinesScilabHistoryIsSaved(int num);

	/**
	* Get after how many lines history is saved
	* @return number between 0 and Max
	* default value is 0 (disabled)
	*/
	int getAfterHowManyLinesScilabHistoryIsSaved(void);

	/**
	* Get the Nth Line in history
	* @param N
	* @return the Nth Line
	*/
	char *getNthLineInScilabHistory(int N);

	/**
	* delete the Nth Line in history
	* @param N
	* @return TRUE or FALSE
	*/
	BOOL deleteNthLineScilabHistory(int N);

	/**
	* get number of lines of history
	* @return a number >= 0
	*/
	int getSizeScilabHistory(void);
	

/*------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
/*------------------------------------------------------------------------*/
#endif /* __HISTORYMANAGER_C_H__ */
/*------------------------------------------------------------------------*/
