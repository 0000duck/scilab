/*------------------------------------------------------------------------*/
/* file: MovableClipPlane3DManager.java                                   */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Store all clipped planes and change everyone of them            */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.utils.glTools;

import java.util.Iterator;
import java.util.LinkedList;

import javax.media.opengl.GL;

/**
 * Store all cliped planes and change everyone of them
 * @author Jean-Baptiste Silvy
 */
public final class ClipPlane3DManager {
	
	/**
	 * List of clipplane. So every one can access the clipped planes
	 */
	private static class ClipPlaneList extends LinkedList<MovableClipPlane3D> {
		
		/**
		 * Needed
		 */
		private static final long serialVersionUID = 2435315256366L;

		/**
		 * Default constructor
		 */
		public ClipPlaneList() {
			super();
		}
	}
	
	/** List of all active clip planes */
	private static ClipPlaneList activeClipPlanes = new ClipPlaneList();
	
	/**
	 * Default constructor should not be used
	 */
	private ClipPlane3DManager() { }
	
	/**
	 * Add a new plane to the list of clipped planes
	 * @param plane plane to add
	 */
	public static void addClippedPlane(MovableClipPlane3D plane) {
		activeClipPlanes.add(plane);
	}
	
	/**
	 * Remove a plane from the list of clipped planes
	 * @param plane plane to remove
	 */
	public static void removeClippedPlane(MovableClipPlane3D plane) {
		activeClipPlanes.remove(plane);
	}
	
	/**
	 * @return Iterator on the list of currently active clip planes
	 */
	public static Iterator<MovableClipPlane3D> getActiveClipPlanes() {
		return activeClipPlanes.listIterator();
	}
	
	/**
	 * Push all planes.
	 * @param gl current GL pipeline
	 */
	public static void pushPlanes(GL gl) {
		Iterator<MovableClipPlane3D> curPlaneIt = activeClipPlanes.iterator();
		while (curPlaneIt.hasNext()) {
			curPlaneIt.next().pushPlane(gl);
		}
	}
	
	/**
	 * Pop all planes.
	 * @param gl current GL pipeline
	 */
	public static void popAllPlanes(GL gl) {
		Iterator<MovableClipPlane3D> curPlaneIt = activeClipPlanes.iterator();
		while (curPlaneIt.hasNext()) {
			curPlaneIt.next().popPlane(gl);
		}
	}
	
	/**
	 * Change frame for all clipped planes
	 * @param gl current GL pipeline
	 */
	public static void changeAllPlanesFrame(GL gl) {
		Iterator<MovableClipPlane3D> curPlaneIt = activeClipPlanes.iterator();
		while (curPlaneIt.hasNext()) {
			curPlaneIt.next().changeFrame(gl);
		}		
	}
	
	/**
	 * @return string representation of the class.
	 */
	public static String getStringRepresentation() {
		String res = "";
		Iterator<MovableClipPlane3D> curPlaneIt = activeClipPlanes.iterator();
		while (curPlaneIt.hasNext()) {
			res += curPlaneIt.next().toString() + "\n";
		}
		return res;
	}
}
