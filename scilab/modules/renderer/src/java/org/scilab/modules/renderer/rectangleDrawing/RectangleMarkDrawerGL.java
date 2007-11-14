/*------------------------------------------------------------------------*/
/* file: RectangleMarkDrawerJoGL.java                                     */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class containing the driver dependant routines to draw marks    */
/*        on the corners of a rectangle                                   */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.rectangleDrawing;

import org.scilab.modules.renderer.drawers.MarkDrawerGL;
import org.scilab.modules.renderer.utils.geom3D.Vector3D;

/**
 * Class containing functions called by RectangleMarkDrawerJoGL.cpp
 * @author Jean-Baptiste Silvy
 */
public class RectangleMarkDrawerGL extends MarkDrawerGL implements RectangleDrawerStrategy {
	
	private static final int NB_CORNERS = 4;
	
	
	/** position of corners, needed to retrive pixels coordinates */
	private Vector3D[] cornersPos;
	
	/**
	 * Default Constructor
	 */
	public RectangleMarkDrawerGL() {
		super();
		cornersPos = new Vector3D[NB_CORNERS];
	}
	
	
	/**
	 * Display the object by displaying its display list
	 * @param parentFigureIndex index of the parent figure in which the object will be drawn
	 */
	public void show(int parentFigureIndex) {
		initializeDrawing(parentFigureIndex);
		drawRectangle();
		endDrawing();
	}
	
	/**
	 * Draw the marks on the corners of a rectangle
	 * using data stored in cornersPos
	 */
	public void drawRectangle() {
		drawMarks(cornersPos);
	}
	
	/**
	 * create the display list for the rectangle
	 * @param corner1X first corner X coordinate
	 * @param corner1Y first corner Y coordinate
	 * @param corner1Z first corner Z coordinate
	 * @param corner2X second corner X coordinate
	 * @param corner2Y second corner Y coordinate
	 * @param corner2Z second corner Z coordinate
	 * @param corner3X third corner X coordinate
	 * @param corner3Y third corner Y coordinate
	 * @param corner3Z third corner Z coordinate
	 * @param corner4X last corner X coordinate
	 * @param corner4Y last corner Y coordinate
	 * @param corner4Z last corner Z coordinate
	 */
	public void drawRectangle(double corner1X, double corner1Y, double corner1Z,
							  double corner2X, double corner2Y, double corner2Z,
							  double corner3X, double corner3Y, double corner3Z,
							  double corner4X, double corner4Y, double corner4Z) {

		
		
		// save rectangle coordinates
		cornersPos[0] = new Vector3D(corner1X, corner1Y, corner1Z);
		cornersPos[1] = new Vector3D(corner2X, corner2Y, corner2Z);
		cornersPos[2] = new Vector3D(corner3X, corner3Y, corner3Z);
		cornersPos[NB_CORNERS - 1] = new Vector3D(corner4X, corner4Y, corner4Z);
		
		drawRectangle();
		
	}
	
}
