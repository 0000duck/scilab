/*------------------------------------------------------------------------*/
/* file: DrawMarkTools.java                                               */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class used to draw different kinds of marks                     */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.utils.MarkDrawing;

import org.scilab.modules.renderer.DrawableObjectGL;
import javax.media.opengl.GL;

/**
 * Utility class to draw marks
 * @author Jean-Baptiste Silvy
 */
public class MarkDrawer extends DrawableObjectGL {

	
	/**
	 * The two kinds of markSize unit
	 */
	private static enum SizeUnit { POINT, TABULATED };
	
	/**
	 * Mapping between tabulated sizes and point sizes
	 */ 
	private static final int[] TABULATED_SIZE = {8, 10, 12, 14, 18, 24};
	
	/** To know the type of unit */
	private SizeUnit unit; 
	/** background color of marks */
	private int markBackground;
	/** outline color of marks */
	private int markForeground;
	/** Size of the mark */
	private int markSize;
	/** drawer of dots */
	private MarkDrawingStrategy drawer;
	
	
	/**
	 * Default constructor
	 */
	public MarkDrawer() {
		unit = SizeUnit.POINT;
		markBackground = -1;
		markForeground = -1;
		markSize       = -1;
		drawer         = null;
	}
	
	
	
	/**
	 * @param background index of new background color
	 */
	public void setBackground(int background) {
		markBackground = background;
	}
	
	/**
	 * @param foreground index of new background color
	 */
	public void setForeground(int foreground) {
		markForeground = foreground;
	}
	
	/**
	 * Specify that size unit is tabulated.
	 */
	public void setTabulatedUnit() {
		unit = SizeUnit.TABULATED;
	}
	
	/**
	 * Specify that size unit is point.
	 */
	public void setPointUnit() {
		unit = SizeUnit.POINT;
	}
	
	/**
	 * Specify a new size for marks
	 * @param markSize new size
	 */
	public void setMarkSize(int markSize) {
		this.markSize = markSize;
	}
	
	/**
	 * Specify the kind of mark to draw
	 * @param markStyleIndex index of the kind of mark
	 */
	public void setMarkStyle(int markStyleIndex) {
		drawer = MarkDrawingStrategy.create(markStyleIndex);
	}
	
	
	/**
	 * Get the size of marks in pixel wether it is tabulated or not.
	 * @return size in pixel
	 */
	protected int getMarkPixelSize() {
		
		// point
		if (unit == SizeUnit.POINT) {
			return markSize;
		}
		
		// tabulated
		if (markSize >= 0 && markSize < TABULATED_SIZE.length) {
			return TABULATED_SIZE[markSize];
		} else if (markSize < 0) {
			return 0;
		} else {
			return TABULATED_SIZE[TABULATED_SIZE.length - 1];
		}
		
	}
	
	/**
	 * Unused
	 * @param parentFigureIndex unused
	 */
	public void show(int parentFigureIndex) { }
	
	/**
	 * Draw a mark at the specified postion
	 * @param posX X coordinate of the mark
	 * @param posY Y coordinate of the mark
	 * @param posZ Z coordinate of the mark
	 */
	public void drawMark(double posX, double posY, double posZ) {
		if (drawer != null) {
			GL gl = getGL();
			gl.glPushMatrix();
			gl.glTranslated(posX, posY, posZ);
			if (isDLInit()) {
				displayDL();
			} else {
				startRecordDL();
				int realMarkSize = getMarkPixelSize();
				gl.glScaled(realMarkSize, realMarkSize, realMarkSize);
				drawer.drawMark(gl, getColorMap().getColor(markBackground), getColorMap().getColor(markForeground));
				endRecordDL();
			}
			gl.glPopMatrix();
		}
	}
	
	
}
