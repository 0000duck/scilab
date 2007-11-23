/*--------------------------------------------------------------------------*/
/* INRIA 2007 */
/* @author Sylvestre LEDRU */
/*--------------------------------------------------------------------------*/ 

/**
 * This function is a wrapper / fake when Scilab is compiled without thegraphic
 * graphic Interface
 *
 * @return 0
 */
int C2F(gw_gui)(void);

/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 *
 * @return TRUE
 */
BOOL TerminateGUI(void);

/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param fname unused (just reproduce the profile)
 * @return 0
 */
int XClearScreenConsole(char *fname);

/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param string unused (just reproduce the profile)
 * @param nbytes unused (just reproduce the profile)
 */
void str_to_xterm ( register char * string, int nbytes);


/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param n unused (just reproduce the profile)
 */
void Click_menu(int n);


/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param prop unused (just reproduce the profile)
 * @param value unused (just reproduce the profile)
 * @return 0
 */
int GetScreenProperty(char *prop, char *value);


/**
 * Read the next character
 * This function is really used here !
 * @param interrupt  unused (just reproduce the profile)
 * @return the result of getchar
 */
int Xorgetchar(int interrupt);


/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param interrupt  unused (just reproduce the profile)
 * @return 0
 */
int XEvorgetchar(int interrupt);

/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 * @param startup   unused (just reproduce the profile)
 * @param lstartup  unused (just reproduce the profile)
 * @param memory    unused (just reproduce the profile)
 */
void main_sci (char *startup, int lstartup,int memory);

/**
 * This function is a wrapper when /fake Scilab is compiled without the 
 * graphic Interface
 */
void InitXsession(void);
