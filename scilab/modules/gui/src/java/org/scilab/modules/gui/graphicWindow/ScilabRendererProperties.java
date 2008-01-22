/*------------------------------------------------------------------------*/
/* file: ScilabRendererProperties.java                                    */
/* Copyright INRIA 2007                                                   */
/* Authors : Jean-Baptiste Silvy, Vincent COUVERT                         */
/* desc : Properties needed by a figure from its rendering canvas         */
/*------------------------------------------------------------------------*/

package org.scilab.modules.gui.graphicWindow;

import javax.media.opengl.GL;
import org.scilab.modules.gui.canvas.Canvas;
import org.scilab.modules.gui.tab.Tab;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.renderer.figureDrawing.RendererProperties;


/**
 * Main class for renderers in Scilab
 */
public class ScilabRendererProperties implements RendererProperties {

	/** Rendering canvas */
	private Canvas parentCanvas;
	/** Enclosing tab */
	private Tab parentTab;
	
	/**
	 * Default constructor
	 * @param parentTab the parent tab of this renderer
	 * @param parentCanvas the parent canvas of this renderer
	 */
	public ScilabRendererProperties(Tab parentTab, Canvas parentCanvas) {
		this.parentCanvas = parentCanvas;
		this.parentTab = parentTab;
	}
	
	/**
	 * Force the parent Canvas to bve displayed
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#forceDisplay()
	 */
	public void forceDisplay() {
		parentCanvas.display();
	}

	/**
	 * Get the parent canvas height
	 * @return the height of the parent canvas
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getCanvasHeight()
	 */
	public int getCanvasHeight() {
		return parentCanvas.getDims().getHeight();
	}

	/**
	 * Get the parent canvas width
	 * @return the width of the parent canvas
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getCanvasWidth()
	 */
	public int getCanvasWidth() {
		return parentCanvas.getDims().getWidth();
	}

	/**
	 * Get the GL pipeline of the parent canvas
	 * @return the GL of the parent canvas
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getGLPipeline()
	 */
	public GL getGLPipeline() {
		return parentCanvas.getGL();
	}

	/**
	 * Get the name of the parent tab
	 * @return the name of the parent tab
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getInfoMessage()
	 */
	public String getInfoMessage() {
		return parentTab.getName();
	}

	/**
	 * Get the height of the parent window
	 * @return the height of the parent window
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getWindowHeight()
	 */
	public int getWindowHeight() {
		return parentTab.getParentWindow().getDims().getHeight();
	}

	/**
	 * Get the x-coordinate of the parent window
	 * @return the x-coordinate of the parent window
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getWindowPosX()
	 */
	public int getWindowPosX() {
		return parentTab.getParentWindow().getPosition().getX();
	}

	/**
	 * Get the y-coordinate of the parent window
	 * @return the y-coordinate of the parent window
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getWindowPosY()
	 */
	public int getWindowPosY() {
		return parentTab.getParentWindow().getPosition().getY();
	}

	/**
	 * Get the width of the parent window
	 * @return the width of the parent window
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getWindowWidth()
	 */
	public int getWindowWidth() {
		return parentTab.getParentWindow().getDims().getWidth();
	}

	/**
	 * Set the size of the parent canvas
	 * @param width the width to set to the parent
	 * @param height the height to set to the parent
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#setCanvasSize(int, int)
	 */
	public void setCanvasSize(int width, int height) {
		parentCanvas.setDims(new Size(width, height));
	}

	/**
	 * Set the name of the parent tab
	 * @param infoMessage the name of the parent tab
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getInfoMessage()
	 */
	public void setInfoMessage(String infoMessage) {
		parentTab.setName(infoMessage);
	}

	/**
	 * Set the position of the parent window
	 * @param posX the x-coordinate of the parent window
	 * @param posY the yx-coordinate of the parent window
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#setWindowPosition(int, int)
	 */
	public void setWindowPosition(int posX, int posY) {
		parentTab.getParentWindow().setPosition(new Position(posX, posY));
	}

	/**
	 * Set the size of the parent window
	 * @param width the width to set to the parent
	 * @param height the height to set to the parent
	 * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#setWindowSize(int, int)
	 */
	public void setWindowSize(int width, int height) {
		parentTab.getParentWindow().setDims(new Size(width, height));
		
	}

    /**
     * Set the pixmap mode
     * @param onOrOff true ("on" for Scilab) to set auto swap buffer off
     * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getPixmapMode()
     */
	public void setPixmapMode(boolean onOrOff) {
		// pixmap "on" means auto swap buffer off.
		parentCanvas.setAutoSwapBufferMode(!onOrOff);
	}
    
    /**
     * Get the pixmap mode
     * @return true ("on" for Scilab) if auto swap buffer is off
     * @see org.scilab.modules.renderer.figureDrawing.RendererProperties#getPixmapMode()
     */
    public boolean getPixmapMode() {
    	return !(parentCanvas.getAutoSwapBufferMode());
    }

	/**
	 * Get the parent tab
	 * @return the parent tab
	 */
	public Tab getParentTab() {
		return parentTab;
	}
	
	/**
     * Close the rendering canvas
     */
   public void closeCanvas() {
	   parentTab.close();
   }
   
	
}
