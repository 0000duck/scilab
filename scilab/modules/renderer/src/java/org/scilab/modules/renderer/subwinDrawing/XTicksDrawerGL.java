/*------------------------------------------------------------------------*/
/* file: XTicksDrawerGL.java                                              */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Class drawing ticks for the X axis                              */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.subwinDrawing;

import javax.media.opengl.GL;

import org.scilab.modules.renderer.utils.CoordinateTransformation;
import org.scilab.modules.renderer.utils.geom3D.Vector3D;


/**
 * Class drawing ticks for the X axis
 * @author Jean-Baptiste Silvy
 */
public abstract class XTicksDrawerGL extends TicksDrawerGL {
	
	/**
	 * Default consturctor.
	 */
	public XTicksDrawerGL() {
		super();
	}
	
	
	
	
	/**
	 * Compute the Y coordinate of the X axis segment
	 * Select the one wich is in front of the camera
	 * @param zCoordinate Z coordinate of the X axis segment alredy computed by findZCoordinate
	 * @return Y coordinate of the segment to draw
	 */
	protected double findFrontYCoordinate(double zCoordinate) {
		GL gl = getGL();
		
		// same processus as for Z coordinate
		Vector3D pointYmin = new Vector3D(getXmin(), getYmin(), zCoordinate);
		Vector3D pointYmax = new Vector3D(getXmin(), getYmax(), zCoordinate);
		
		// find the one which is upper in term of pixels
		CoordinateTransformation transform = CoordinateTransformation.getTransformation(gl);
		
		pointYmin = transform.getCanvasCoordinates(gl, pointYmin);
		pointYmax = transform.getCanvasCoordinates(gl, pointYmax);
		
		// get the lowest one
		if (pointYmax.getY() > pointYmin.getY()) {
			return getYmin();
		} else {
			return getYmax();
		}
		
	}
	
	/**
	 * Compute the Y coordinate of the X axis segment
	 * Select the one which on the back of the screen
	 * @param zCoordinate Z coordinate of the X axis segment alredy computed by findZCoordinate
	 * @return Y coordinate of the segment to draw
	 */
	protected double findBackYCoordinate(double zCoordinate) {
		if (findFrontYCoordinate(zCoordinate) == getYmin()) {
			return getYmax();
		} else {
			return getYmin();
		}
	}
	
	/**
	 * Compute the Y coordinate of the X axis segment
	 * @param zCoordinate Z coordinate of the X axis segment alredy computed by findZCoordinate
	 * @return Y coordinate of the segment to draw
	 */
	protected double findMiddleYCoordinate(double zCoordinate) {
		// find if 0 is in the range of Y coordinates
		// if so then one of yMax or yMax is <= 0 and the other is not
		if (getYmin() * getYmax() <= 0.0) {
			return 0.0;
		} else if (getYmax() < 0.0) {
			// both bounds are negative
			return getYmax();
		} else {
			// both bounds are positive
			return getYmin();
		}
	}
	
	/**
	 * @param yCoordinate Y coordinate of the X axis
	 * @param zCoordinate Z coordinate of the X axis
	 * @return one of the axis segment edge
	 */
	protected Vector3D getAxisSegmentStart(double yCoordinate, double zCoordinate) {
		return new Vector3D(getXmin(), yCoordinate, zCoordinate);
	}
	
	/**
	 * @param yCoordinate Y coordinate of the X axis
	 * @param zCoordinate Z coordinate of the X axis
	 * @return the other axis segment edge
	 */
	protected Vector3D getAxisSegmentEnd(double yCoordinate, double zCoordinate) {
		return new Vector3D(getXmax(), yCoordinate, zCoordinate);
	}
	
	/**
	 * @param yCoordinate Y coordinate of the X axis
	 * @param zCoordinate Z coordinate of the X axis
	 * @return direction in which to draw the ticks
	 */
	public Vector3D findTicksDirection(double yCoordinate, double zCoordinate) {
		Vector3D res;
		if (Math.abs(yCoordinate - getYmin()) <= Math.abs(yCoordinate - getYmax())) {
			// yCoordinate is closer to Ymin
			res = new Vector3D(0.0, getYmin() - getYmax(), 0.0);
		} else {
			res = new Vector3D(0.0, getYmax() - getYmin(), 0.0);
		}
		
		// if angle is too small then use Z direction
		if (!checkTicksDirection(res, getAxisSegmentStart(yCoordinate, zCoordinate), getAxisSegmentEnd(yCoordinate, zCoordinate))) {
			if (Math.abs(zCoordinate - getZmin()) < Math.abs(zCoordinate - getZmax())) {
				// yCoordinate is closer to Ymin
				res = new Vector3D(0.0, 0.0, getZmin() - getZmax());
			} else {
				res = new Vector3D(0.0, 0.0, getZmax() - getZmin());
			}
		}
		
		return setTicksDirectionLength(res);
		
	}
	
	/**
	 * Compute ticks positions from an array of X coordinates
	 * @param xCoordinates X coordinates of ticks
	 * @param yCoordinate Y coordinate common for all ticks
	 * @param zCoordinate Z coordinate common for all ticks
	 * @return array of vector with only displayable ticks
	 */
	private Vector3D[] getTicksPosition(double[] xCoordinates, double yCoordinate, double zCoordinate) {
		int nbTicks = xCoordinates.length;
		Vector3D[] res = new Vector3D[nbTicks];
		
		for (int i = 0; i < nbTicks; i++) {
			double xCoordinate = xCoordinates[i];
			// remove ticks wich are out of bounds
			if (xCoordinate <= getXmax() && xCoordinate >= getXmin()) {
				res[i] = new Vector3D(xCoordinate, yCoordinate, zCoordinate);
			} else {
				res[i] = null;
			}
		}

		return res;
	}
	
	/**
	 * Get the base of each ticks segment.
	 * @param yCoordinate Y coordinate of the X axis
	 * @param zCoordinate Z coordinate of the X axis
	 * @return array containing the base of each ticks
	 */
	protected Vector3D[] getTicksPositions(double yCoordinate, double zCoordinate) {
		return getTicksPosition(getTicksPositions(), yCoordinate, zCoordinate);
	}
	
	/**
	 * Get the base of each ticks segment.
	 * @param yCoordinate Y coordinate of the X axis
	 * @param zCoordinate Z coordinate of the X axis
	 * @return array containing the base of each subticks
	 */
	protected Vector3D[] getSubTicksPositions(double yCoordinate, double zCoordinate) {
		return getTicksPosition(getSubTicksPositions(), yCoordinate, zCoordinate);
	}
	

	/**
	 * Draw ticks from the recorded data.
	 */
	public void drawTicks() {
		
		double zCoordinate = findZCoordinate();
		double yCoordinate = findYCoordinate(zCoordinate);
		
		Vector3D[] ticksPosition = getTicksPositions(yCoordinate, zCoordinate);
		Vector3D[] subticksPosition = getSubTicksPositions(yCoordinate, zCoordinate);
		Vector3D ticksDirection = findTicksDirection(yCoordinate, zCoordinate);
		drawTicksLines(ticksPosition, subticksPosition, ticksDirection,
					   getAxisSegmentStart(yCoordinate, zCoordinate),
					   getAxisSegmentEnd(yCoordinate, zCoordinate));
		
		drawLabels(ticksPosition, ticksDirection);
		
	}
	
	/**
	 * Check if labels can be displayed has if.
	 * @return true if ticks can be displayed or false if we need to reduc number of ticks.
	 */
	public boolean checkTicks() {
		double zCoordinate = findZCoordinate();
		double yCoordinate = findYCoordinate(zCoordinate);
		
		Vector3D[] ticksPosition = getTicksPositions(yCoordinate, zCoordinate);
		Vector3D ticksDirection = findTicksDirection(yCoordinate, zCoordinate);
		
		return checkLabels(ticksPosition, ticksDirection);
	}
	
	/**
	 * Find the Z coordinate of the X axis segment.
	 * X axis segment is always displayed on the bottom of tyhe box.
	 * @return Z coordinate of the segment to draw
	 */
	public abstract double findZCoordinate();
	
	/**
	 * Compute the Y coordinate of the X axis segment
	 * @param zCoordinate Z coordinate of the X axis segment already computed by findZCoordinate
	 * @return Y coordinate of the segment to draw
	 */
	public abstract double findYCoordinate(double zCoordinate);

}
