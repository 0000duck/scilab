/*------------------------------------------------------------------------*/
/* file: TextGrid.java                                                    */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : Define the steps for text rendering                             */
/*------------------------------------------------------------------------*/


package org.scilab.modules.renderer.textDrawing;

import org.scilab.modules.renderer.utils.geom3D.Vector3D;

/**
 * Define the steps for text rendering
 * @author Jean-Bapiste Silvy
 */
public interface TextRenderingPipeline {

	/**
	 * Step 1: Compute a matrix with the size of every of its strings.
	 * @param renderer text renderer to display strings.
	 * @param inputMatrix matrix of text
	 * @return the new matrix filled.
	 */
	StringMatrixGL computeStringSizes(SciTextRenderer renderer, StringMatrixGL inputMatrix);
	
	/**
	 * Step 2: Compute the matrix containing the positions of all texts.
	 * @param text matrix of string with their size to draw
	 * @return matrix of positions
	 */
	TextGrid getStringsPositions(StringMatrixGL text);
	
	/**
	 * Step 3: Put the text grid at the righ tposition
	 * @param stringPositions Initial position of strings, centered on (0,0).
	 * @param textCenter position of the center in pixel coordinates
	 * @param rotationAngle angle in radian.
	 * @return the new text grid at at the right position.
	 */
	TextGrid placeTextGrid(TextGrid stringPositions, Vector3D textCenter, double rotationAngle);
	
	/**
	 * Step 4: Draw the text at the right position.
	 * @param renderer TextRenderer used to render the text.
	 * @param text Matrix of the string to display
	 * @param stringPositions positons of the strings
	 */
	void drawText(SciTextRenderer renderer, StringMatrixGL text, TextGrid stringPositions);
	
	/**
	 * Step 2 bis: Get the bounding box of the text matrix centerd at the origin.
	 * @param text matrix of strings with the size of each string already computed.
	 * @return 4 corners of the bounding box.
	 */
	Vector3D[] getBoundingBox(StringMatrixGL text);
	
	/**
	 * Step 3 bis:Move the bounding box to the right position.
	 * @param bbox intial bounding box centered at the origin.
	 * @param textCenter text center
	 * @param rotationAngle rotation angle around the text center
	 * @return new bouding box turned
	 */
	Vector3D[] placeBoundingBox(Vector3D[] bbox, Vector3D textCenter, double rotationAngle);
	
}
