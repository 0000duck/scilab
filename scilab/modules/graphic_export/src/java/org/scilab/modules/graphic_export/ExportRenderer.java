package org.scilab.modules.graphic_export;

import javax.media.opengl.GLEventListener;
import com.sun.opengl.util.FileUtil;

/**
 * Main export class
 * @author Sylvestre Koumar
 *
 */
public abstract class ExportRenderer implements GLEventListener {

	/** Code-number for the function statue */
	public static final int SUCCESS = 0;
	public static final int GLEXCEPTION_ERROR = 1;
	public static final int IOEXCEPTION_ERROR = 2;
	public static final int INVALID_FILE = 3;

	/** Code-number for each bitmap format */
	public static final int BMP_EXPORT = 1;
	public static final int GIF_EXPORT = 2;
	public static final int JPG_EXPORT = 3;
	public static final int PNG_EXPORT = 4;
	public static final int PPM_EXPORT = 5;

	/** Code-number for each postscript format */
	public static final int EPS_EXPORT = 6;
	public static final int PDF_EXPORT = 7;
	public static final int SVG_EXPORT = 8;
	public static final int PS_EXPORT = 9;

	private static String fileName;
	private static int fileType;

	/**
	 * Constructor
	 * @param fileName name of the file
	 * @param fileType type of the file
	 */
	protected ExportRenderer(String fileName, int fileType) {
		this.fileName = fileName;
		this.fileType = fileType;	
		removeExtension();
	}	

	/**
	 * Choose which kind of filetype will be exported 
	 * @param figureIndex type of the file
	 * @param fileName name of the file
	 * @param fileType type of the file
	 * @return GL2PSRenderer export a postscript screen-shot
	 */
	public static ExportRenderer createExporter(int figureIndex, String fileName, int fileType) {
		
		GL2PS gl2ps = new GL2PS();
		
		/** Select in which type the file will be exported */		
		switch (fileType) {
		case BMP_EXPORT:  
		case GIF_EXPORT:
		case JPG_EXPORT:
		case PNG_EXPORT:
		case PPM_EXPORT:
			return new BitmapRenderer(fileName, fileType);
		case EPS_EXPORT:
		case PDF_EXPORT:
		case SVG_EXPORT:
		case PS_EXPORT:
			return new GL2PSRenderer(figureIndex, fileName, fileType);
		default: System.err.println(ExportRenderer.INVALID_FILE);
		}
		return null;			
	}

	/**
	 * getter 
	 * @return fileName get the file name
	 */
	public static String getFileName() {
		return fileName;
	}

	/**
	 * setter 
	 * @param fileName set the file name
	 */
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	/**
	 * getter
	 * @return fileType get the file type
	 */
	public static int getFileType() {
		return fileType;
	}

	/**
	 * setter 
	 * @param fileType set the file name
	 */
	public void setFileType(int fileType) {
		this.fileType = fileType;
	}

	/**
	 * Function allowing to format the extension of the screen-shot file  
	 */
	public void removeExtension() {		
		String suffix = FileUtil.getFileSuffix(this.fileName); //get the suffix(extension) of the file name
		int pos = this.fileName.lastIndexOf('.'); // position of the dot

		if (suffix != null) {
			suffix = suffix.toLowerCase();
			if (suffix.equalsIgnoreCase("bmp") && this.fileType == ExportRenderer.BMP_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("gif") && this.fileType == ExportRenderer.GIF_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("jpg") && this.fileType == ExportRenderer.JPG_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("png") && this.fileType == ExportRenderer.PNG_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("ppm") && this.fileType == ExportRenderer.PPM_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("eps") && this.fileType == ExportRenderer.EPS_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("pdf") && this.fileType == ExportRenderer.PDF_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("svg") && this.fileType == ExportRenderer.SVG_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			} else if (suffix.equalsIgnoreCase("ps") && this.fileType == ExportRenderer.PS_EXPORT) {
				this.fileName = this.fileName.substring(0, pos);
			}		
		}
	}
}
