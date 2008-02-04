/*------------------------------------------------------------------------*/
/* file: DrawableGrayplotGL.java                                          */
/* Copyright INRIA 2008                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing the driver dependant routines to draw a        */
/*        grayplot object with JoGL                                       */
/*------------------------------------------------------------------------*/

package org.scilab.modules.renderer.grayplotDrawing;

import javax.media.opengl.GL;

import org.scilab.modules.renderer.AutoDrawableObjectGL;

/**
 * Class containing functions called by DrawableGrayplotJoGL.cpp
 * @author Jean-Baptiste Silvy
 */
public class DrawableGrayplotGL extends AutoDrawableObjectGL {

	/**
	 * Default Constructor
	 */
	public DrawableGrayplotGL() {
		super();
	}
	
	/**
	 * Draw the grayplot or matplot object. The object is composed of set of facets.
	 * Each facet is a rectangle whose edges are between (xGrid[i], yGrid[j]) and
	 * (xGrid[i + 1], yGrid[j + 1]) and its color is color[i][j].
	 * @param xGrid array containing the abscissas of the grid
	 * @param yGrid array containing the ordinates of the grid
	 * @param zCoord zCoordinate used to draw the grayplot
	 * @param colors array considered as a matrix containing the color index for each facet
	 *               its size is (xGrid.length - 1) x (yGrid.length - 1)
	 */
	public void drawGrayplot(double[] xGrid, double[] yGrid, double zCoord, int[] colors) {
		GL gl  = getGL();
		
		int nbRow = xGrid.length - 1;
		int nbCol = yGrid.length - 1;
		
		// rectangles are used to render each pixel
		// Using textures would be much faster
		// hower it would not be compatible with GL2PS, so for now we keep th eslow version
		gl.glBegin(GL.GL_QUADS);
		for (int i = 0; i < nbRow; i++) {
			for (int j = 0; j < nbCol; j++) {
				double[] curColor = getColorMap().getColor(getColorMap().convertScilabToColorMapIndex(colors[j + nbCol * i]));
				gl.glColor3d(curColor[0], curColor[1], curColor[2]);
				gl.glVertex3d(xGrid[i], yGrid[j], zCoord);
				gl.glVertex3d(xGrid[i], yGrid[j + 1], zCoord);
				gl.glVertex3d(xGrid[i + 1], yGrid[j + 1], zCoord);
				gl.glVertex3d(xGrid[i + 1], yGrid[j], zCoord);
			}
		}
		gl.glEnd();
		
		
	}
	
}
