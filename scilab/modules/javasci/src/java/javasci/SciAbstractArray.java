package javasci;

/**
 * Defines the basic method that very ScilabXXXXArray should implement
 * @author Sylvestre LEDRU - INRIA 2007
 */
public abstract class SciAbstractArray {

	/** m number of rows */
	protected int m;

	/** n number of colons */
	protected int n;

	/** Name of the variable */
	protected String name;

	/**
	 * Initialize Scilab interface
	 */
	protected static native void Initialize();

	/**
	 * Internal method to know dim (Row) in scilab 
	 * @return The result of the operation (>= 0 OK, -1 if the name does not exist)
	 */
	protected native int getNumberOfRowsFromScilab(String name);

	/**
	 * internal method to know dim (Col) in scilab
	 * @return The result of the operation (>= 0 OK, -1 if the name does not exist)
	 */  
	protected native int getNumberOfColsFromScilab(String name);
	
	/**
	 * Execute a command in Scilab 
	 * Deprecated. Use Scilab.Exec instead.
	 * @param job the Scilab job 
	 * @return 
	 @deprecated
	 */
	public native boolean Job(String job);

	/**
	 * Get Matrix from Scilab
	 */
	public native void Get();

	/**
	 * Send Matrix to Scilab 
	 */
  	public native void Send();

	/**
	 * Return the number of rows
	 * @deprecated
	 * @see #getNumberOfRows()
	 * @return the number of rows
	 */
	public int getRow() 
	{
		return this.getNumberOfRows();
	}


	/**
	 * Return the number of rows
	 * @return the number of rows
	 */
	public int getNumberOfRows()
	{
		return m;
	}
	
	/**
	 * Return the number of columns
	 * @deprecated
	 * @see #getNumberOfCols()
	 * @return the number of columns
	 */
	public int getCol()
	{
		return this.getNumberOfCols();
	}



	/**
	 * Return the number of columns
	 * @return the number of columns
	 */
	public int getNumberOfCols()
	{
		return n;
	}

	/**
	 * Return the name of the variable
	 * @return the name
	 */
	public String getName()  {
		return name;
	}

	/**
	 * Display the Matrix (by calling the scilab disp() function
	 */
	public void disp(){
		Get();
		System.out.println("Matrix "+ getName() +"=");
		Scilab.Exec( "disp(" + getName() +");"); // Call the scilab command
	}

	/**
	 * Return the data
	 * @return the data
	 */
	//	abstract Object[] getData();

	static 
	{
		try {
			System.loadLibrary("javasci");
		} catch(SecurityException e){
			System.err.println("A security manager exists and does not allow the loading of the specified dynamic library :");
			e.printStackTrace(System.err);
		} catch(UnsatisfiedLinkError e){
			System.err.println("The native library javasci does not exist or cannot be found.");
			e.printStackTrace(System.err);
		}

		try {
			Initialize();		
		}catch(UnsatisfiedLinkError e){
			System.err.println("Cannot find method Initialize from the library.");
			e.printStackTrace(System.err);
			
		}
	}
}
