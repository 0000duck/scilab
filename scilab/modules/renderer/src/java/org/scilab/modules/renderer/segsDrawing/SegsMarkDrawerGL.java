/*------------------------------------------------------------------------*/
/* file: SegsMarkDrawerGL.java                                            */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class drawing marks on the ends of segments                     */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.segsDrawing;

import org.scilab.modules.renderer.drawers.MarkDrawerGL;
import org.scilab.modules.renderer.utils.geom3D.Vector3D;

/**
 * Class drawing marks on the ends of segments
 * @author Jean-Baptiste Silvy
 */
public class SegsMarkDrawerGL extends MarkDrawerGL {

	private Vector3D[] marksPositions;
	
	/**
	 * default constructor
	 */
	public SegsMarkDrawerGL() {
		super();
		marksPositions = null;
	}
	
	/**
	 * Display the object by displaying the already stored data
	 * @param parentFigureIndex index of the parent figure in which the object will be drawn
	 */
	@Override
	public void show(int parentFigureIndex) {
		initializeDrawing(parentFigureIndex);
		drawSegs();
		endDrawing();
	}
	
	/**
	 * Draw a set of segment knowing their positions and colors
	 * @param startXCoords X coordinate of segments first point
	 * @param endXCoords X coordinate of segments end point
	 * @param startYCoords Y coordinate of segments first point
	 * @param endYCoords Y coordinate of segments end point
	 * @param startZCoords Z coordinate of segments first point
	 * @param endZCoords Z coordinate of segments end point
	 */
	public void drawSegs(double[] startXCoords, double[] endXCoords, double[] startYCoords, double[] endYCoords,
						 double[] startZCoords, double[] endZCoords) {
		int nbSegs = startXCoords.length;
		
		// we draw marks on both ends of segments
		marksPositions = new Vector3D[2 * nbSegs];
		
		for (int i = 0; i < nbSegs; i++) {
			marksPositions[2 * i] = new Vector3D(startXCoords[i], startYCoords[i], startZCoords[i]);
			marksPositions[2 * i + 1] = new Vector3D(endXCoords[i], endYCoords[i], endZCoords[i]);
		}
		
		drawSegs();
		
	}
	
	/**
	 * Draw the segments
	 */
	public void drawSegs() {
		drawMarks(marksPositions);
	}

}
