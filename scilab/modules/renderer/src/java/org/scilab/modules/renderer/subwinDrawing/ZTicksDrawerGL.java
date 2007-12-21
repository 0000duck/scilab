/*------------------------------------------------------------------------*/
/* file: ZTicksDrawerGL.java                                              */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class drawing ticks for the Z axis                              */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.subwinDrawing;

import org.scilab.modules.renderer.utils.geom3D.Vector3D;

/**
 * Class drawing ticks for the Z axis
 * @author Jean-Baptiste Silvy
 */
public class ZTicksDrawerGL extends TicksDrawerGL {

	/**
	 * Default constructor
	 */
	public ZTicksDrawerGL() {
		super();
	}
	
	/**
	 * @param xCoordinate X coordinate of the Z axis
	 * @param yCoordinate Y coordinate of the Z axis
	 * @return one of the axis segment edge
	 */
	protected Vector3D getAxisSegmentStart(double xCoordinate, double yCoordinate) {
		return new Vector3D(xCoordinate, yCoordinate, getZmin());
	}
	
	/**
	 * @param xCoordinate X coordinate of the Z axis
	 * @param yCoordinate Y coordinate of the Z axis
	 * @return the other axis segment edge
	 */
	protected Vector3D getAxisSegmentEnd(double xCoordinate, double yCoordinate) {
		return new Vector3D(xCoordinate, yCoordinate, getZmax());
	}
	
	/**
	 * @param xCoordinate X coordinate of the Z axis
	 * @param yCoordinate Y coordinate of the Z axis
	 * @return direction in which to draw the ticks
	 */
	public Vector3D findTicksDirection(double xCoordinate, double yCoordinate) {
		Vector3D res;
		
		// we must find wether Z axis ticks are directed by X axis or Y axis
		// Actually Z axis is direted by the axis with which it shares on edge
		// when X and Y axis are in defautl mode, ie bottom and left

		
		// get the three coordinates of the edge whuch is common for X and Y axis in default mode
		double zCoordFront = findLowerZCoordinate();
		
		if (isSharingEndWithXaxis(zCoordFront, xCoordinate)) {
			res = new Vector3D(xCoordinate - findFrontXCoordinate(zCoordFront), 0.0, 0.0);
		} else {
			res = new Vector3D(0.0, yCoordinate - findFrontYCoordinate(zCoordFront), 0.0);
		}
		
		return setTicksDirectionLength(res);
		
	}
	
	/**
	 * Compute ticks positions from an array of Y coordinates
	 * @param xCoordinate X coordinates common for all ticks
	 * @param yCoordinate Y coordinates common for all ticks
	 * @param zCoordinates Z coordinates of ticks
	 * @return array of vector with only displayable ticks
	 */
	private Vector3D[] getTicksPosition(double xCoordinate, double yCoordinate, double[] zCoordinates) {
		int nbTicks = zCoordinates.length;
		Vector3D[] res = new Vector3D[nbTicks];
		
		for (int i = 0; i < nbTicks; i++) {
			double zCoordinate = zCoordinates[i];
			// remove ticks wich are out of bounds
			if (yCoordinate <= getYmax() && yCoordinate >= getYmin()) {
				res[i] = new Vector3D(xCoordinate, yCoordinate, zCoordinate);
			} else {
				res[i] = null;
			}
		}

		return res;
	}
	
	/**
	 * Get the base of each ticks segment.
	 * @param xCoordinate X coordinate of the Z axis
	 * @param yCoordinate Y coordinate of the Z axis
	 * @return array containing the base of each ticks
	 */
	protected Vector3D[] getTicksPositions(double xCoordinate, double yCoordinate) {
		return getTicksPosition(xCoordinate, yCoordinate, getTicksPositions());
	}
	
	/**
	 * Get the base of each ticks segment.
	 * @param xCoordinate X coordinate of the Z axis
	 * @param yCoordinate Y coordinate of the Z axis
	 * @return array containing the base of each subticks
	 */
	protected Vector3D[] getSubTicksPositions(double xCoordinate, double yCoordinate) {
		return getTicksPosition(xCoordinate, yCoordinate, getSubTicksPositions());
	}
	
	/**
	 * Check if labels can be displayed has if.
	 * @return true if ticks can be displayed or false if we need to reduc number of ticks.
	 */
	public boolean checkTicks() {
		double yCoordinate = findLeftMostYCoordinate();
		double xCoordinate = findLeftMostXCoordinate();
		
		Vector3D[] ticksPosition = getTicksPositions(xCoordinate, yCoordinate);
		Vector3D ticksDirection = findTicksDirection(xCoordinate, yCoordinate);
		
		return checkLabels(ticksPosition, ticksDirection);
	}

	/**
	 * Draw ticks from the recorded data.
	 */
	public void drawTicks() {
		double yCoordinate = findLeftMostYCoordinate();
		double xCoordinate = findLeftMostXCoordinate();
		
		Vector3D[] ticksPosition = getTicksPositions(xCoordinate, yCoordinate);
		Vector3D[] subticksPosition = getSubTicksPositions(xCoordinate, yCoordinate);
		Vector3D ticksDirection = findTicksDirection(xCoordinate, yCoordinate);
		drawTicksLines(ticksPosition, subticksPosition, ticksDirection,
					   getAxisSegmentStart(xCoordinate, yCoordinate),
					   getAxisSegmentEnd(xCoordinate, yCoordinate));
		
		drawLabels(ticksPosition, ticksDirection);

	}

}
