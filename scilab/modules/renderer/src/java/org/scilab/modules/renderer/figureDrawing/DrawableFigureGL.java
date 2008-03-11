/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Jean-Baptiste Silvy
 * desc : Class containing the driver dependant routines to draw a 
 * figure object with JoGL
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.renderer.figureDrawing;

import java.awt.Font;

import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.Threading;
import javax.swing.SwingUtilities;

import org.scilab.modules.renderer.ObjectGL;
import org.scilab.modules.renderer.FigureMapper;
import org.scilab.modules.renderer.arcDrawing.ArcRendererFactory;
import org.scilab.modules.renderer.arcDrawing.NurbsArcRendererFactory;
import org.scilab.modules.renderer.textDrawing.SciTextRenderer;
import org.scilab.modules.renderer.utils.TexturedColorMap;
import org.scilab.modules.renderer.ObjectGLCleaner;




/**
 * Class containing functions called by DrawableFigureJoGL.cpp
 * @author Jean-Baptiste Silvy
 */
public class DrawableFigureGL extends ObjectGL {
	
	/** Mapping between scilab pixel drawing mode and OpenGL ones */
	private static final int[] LOGICAL_OPS = {GL.GL_CLEAR,
											  GL.GL_AND,
											  GL.GL_AND_REVERSE,
											  GL.GL_COPY,
											  GL.GL_AND_INVERTED,
											  GL.GL_NOOP,
											  GL.GL_XOR,
											  GL.GL_OR,
											  GL.GL_NOR,
											  GL.GL_EQUIV,
											  GL.GL_INVERT,
											  GL.GL_OR_REVERSE,
											  GL.GL_COPY_INVERTED,
											  GL.GL_OR_INVERTED,
											  GL.GL_NAND,
											  GL.GL_SET};
	
	/** Canvas to draw the figure */
	private RendererProperties guiProperties;
	/** store the figureIndex */
	private int figureId;
	/** To get all the objects which needs to be destroyed */
	private ObjectGLCleaner destroyedObjects;
	
	/** To know if the figure can be displayed */
	private boolean isReadyForRendering;
	
	private boolean pixmapModeOn;
	
	private SciTextRenderer textWriter;
	
	/** Keep a pointer on the OpenGL rendering target (Canvas, pBuffer, ...). */
	private GLAutoDrawable renderingTarget;
	
	/** Default TextRenderer */
	private TextRendererFactory textRendererFactory;

	/** Default ArcRenderer */
	private ArcRendererFactory arcRendererFactory;
	
	/** index of the background color */
	private int backGroundColorIndex;
	
	/**
	 * Default Constructor
	 */
	public DrawableFigureGL() {
		super();
      	guiProperties = null;
      	setColorMap(TexturedColorMap.create());
      	figureId = -1; // figure ids should be greater than 0.
      	destroyedObjects = new ObjectGLCleaner();
      	isReadyForRendering = false;
      	pixmapModeOn = true;
      	renderingTarget = null;
      	setDefaultTextRenderer();
      	setDefaultArcRendererFactory();
      	backGroundColorIndex = 0;
      	textWriter = null;
    }
	
	/**
	 * Set the default TextRenderer
	 */
	public void setDefaultTextRenderer() {
		textRendererFactory = new JOGLTextRendererFactory();
	}
	
	/**
	 * Set the default ArcRenderer Factory
	 */
	public void setDefaultArcRendererFactory() {
		arcRendererFactory = new NurbsArcRendererFactory();
	}
	/**
	 * Specify a new state for the rendering enable mode
	 * @param isEnalbe if true figure can no be rendered
	 */
	public synchronized void setIsRenderingEnable(boolean isEnalbe) {
		isReadyForRendering = isEnalbe;
	}
	
	/**
	 * @return true if the figure can be rendered, false otherwise
	 */
	public synchronized boolean getIsRenderingEnable() {
		return isReadyForRendering;
	}
	
	/**
	 * Set figureId property
	 * @param figureId new figure Id
	 */
	public void setFigureIndex(int figureId) {
		// a chack will be performed to see if the figure is alredy here
		FigureMapper.addMapping(figureId, this);
		this.figureId = figureId;
	}
	
	/**
	 * Specify a new object to access canvas and other gui related properties.
	 * @param prop new object to access gui properties
	 */
	public void setRendererProperties(RendererProperties prop) {
		guiProperties = prop;
	}
	
	/**
	 * Function called before beginning to use OpenGL methods.
	 * @param parentFigureIndex index of the parent figure.
	 *                          Needed to get the GL context to draw in.
	 */
	public void initializeDrawing(int parentFigureIndex) {
		// destroy all the objects stored in the destroy list
		destroyedObjects.destroyAll(parentFigureIndex);
		
		super.initializeDrawing(parentFigureIndex);
		
		GL gl = getGL();
		// don't clear the color buffer as usual, we may need to keep it
		// depending on the pixel mode
		gl.glClear(GL.GL_DEPTH_BUFFER_BIT);
		gl.glClearDepth(1.0f);
	}
	
	/**
	 * Function called at the end of the OpenGL use.
	 */
	public void endDrawing() {
		super.endDrawing();
	}
  
	/**
   	 * Get the info message used by the figure
   	 * @return the info message
   	 */
	public String getInfoMessage() {
		return guiProperties.getInfoMessage();
	}
	
	/**
	 * Display the info message of the figure
	 * @param infoMessage string to display describing the figure
	 */
	public void setInfoMessage(String infoMessage) {
		guiProperties.setInfoMessage(infoMessage);
	}

	/**
	 * Force the display of the canvas
	 * Called from C to be sure to be in the right context
	 */
	public void drawCanvas() {
		guiProperties.forceDisplay();
	}

  	/**
  	 * Destroyr the rendering context
  	 */
  	public void closeRenderingCanvas() {
  		guiProperties = null;
   	}
  
  /**
   * Set a new colormap to the figure.
   * @param rgbMat matrix containing the new data. This is a nbColor x 3 matrix
   *               where 3 is the number of color in the colormap
   */
  	public void setColorMapData(double[] rgbMat) {
  		getColorMap().setData(rgbMat);
  	}
  	
  	/**
  	 * Get the raw data of the figure colormap
  	 * Should only be used by C code
  	 * @return colormap data
  	 */
  	public double[] getColorMapData() {
  		return getColorMap().getData();
  	}
  
  /**
   * Get the size of te colormap
   * @return number of color in the colorMap
   */
  public int getColorMapSize() {
    return getColorMap().getSize();
  }
  	
  	/**
  	 * Get the raw data of the figure colormap
  	 * Should only be used by C code
  	 * @param data matrix filled with the colormap data
  	 */
  	public void getColorMapData(double[] data) {
  		getColorMap().getData(data);
  	}
  	
  	/**
  	 * @return object used to destroy JoGL objects
  	 */
  	public ObjectGLCleaner getObjectCleaner() {
  		return destroyedObjects;
  	}
  	
  	/**
  	 * Get the canvas in which the figure is drawn
  	 * @return canvas in x=which the figur eis drawn or null if none exists
  	 */
  	public RendererProperties getRendererProperties() { return guiProperties; }
  	
  	
  	/**
  	 * Set the background of the canvas
  	 * @param colorIndex color index in the colormap
  	 */
  	public void setBackgroundColor(int colorIndex) {
  		backGroundColorIndex = colorIndex;
  		double[] color = getBackgroundColor();
  		getRendererProperties().setBackgroundColor(color[0], color[1], color[2]);
  	}
  	
  	/**
  	 * @return 3 channels of the background color
  	 */
  	public double[] getBackgroundColor() {
  		return getColorMap().getColor(backGroundColorIndex);
  	}
  	
  	/**
  	 * Set the background color of the figure
  	 */
  	public void drawBackground() {
  		GL gl = getGL();
  		double[] color = getBackgroundColor();
  		// not really needed actually
  		gl.glClearColor((float) color[0], (float) color[1], (float) color[2], 1.0f); // alpha is set to 1
  		gl.glClear(GL.GL_COLOR_BUFFER_BIT);
  	}
  	
  	
  	/**
     * Set the pixel drawing mode of the figure.
  	 * @param logicOpIndex Scilab value of pixel drawing mode
  	 */
  	public void setLogicalOp(int logicOpIndex) {
  		// convert to OpenGL value
  		GL gl = getGL();
		gl.glEnable(GL.GL_COLOR_LOGIC_OP); // to use pixel drawing mode
		gl.glLogicOp(LOGICAL_OPS[logicOpIndex]);
  	}
  	
  	/**
	 * Called when the object is destroyed from C code
	 * @param parentFigureIndex index of parent figure
	 */
  	@Override
	public void destroy(int parentFigureIndex) {
  		setIsRenderingEnable(false);
  		FigureMapper.removeMapping(figureId);
  		
  		// destroy context
  		// destroy it here otherwise it crashes Scilab if Scilab quit
  		if (Threading.isOpenGLThread()) {
  			getRenderingTarget().getContext().destroy();
  		} else {
  			Threading.invokeOnOpenGLThread(new Runnable() {
  				public void run() {
  					getRenderingTarget().getContext().destroy();
  				}
  			});
  		}

  		// then destroy canvas
  		// call it on an other thread to avoid deadlocks
  		Thread destroyThread = new Thread(new Runnable() {
  			public void run() {

  				if (SwingUtilities.isEventDispatchThread()) {
  					getRendererProperties().closeCanvas();
  				} else {
  					SwingUtilities.invokeLater(new Runnable() {
  						public void run() {
  							getRendererProperties().closeCanvas();
  						}
  					});
  				}

  			}
  		});

  		destroyThread.start();
	}
	
	
	/**
	 * @return width of the rendering canvas
	 */
	public int getCanvasWidth() {
		return guiProperties.getCanvasWidth();
	}
	
	/**
	 * @return height of the rendering canvas
	 */
	public int getCanvasHeight() {
		return guiProperties.getCanvasHeight();
	}
	
	/**
	 * Set the rendering canvas size.
	 * @param width new width in pixels
	 * @param height new height in pixels
	 */
	public void setCanvasSize(int width, int height) {
		guiProperties.setCanvasSize(width, height);
	}
	
	/**
	 * @return width of the rendering window
	 */
	public int getWindowWidth() {
		return guiProperties.getWindowWidth();
	}
	
	/**
	 * @return height of the rendering window
	 */
	public int getWindowHeight() {
		return guiProperties.getWindowHeight();
	}
	
	/**
	 * Set the rendering window size.
	 * @param width new width in pixels
	 * @param height new height in pixels
	 */
	public void setWindowSize(int width, int height) {
		guiProperties.setWindowSize(width, height);
	}
	
	/**
	 * Get the position of the window enclosing the figure
	 * @return X coordinate in pixels of the window
	 */
	public int getWindowPosX() {
		return guiProperties.getWindowPosX();
	}
	
	/**
	 * Get the position of the window enclosing the figure
	 * @return Y coordinate in pixels of the window
	 */
	public int getWindowPosY() {
		return guiProperties.getWindowPosY();
	}
	
	/**
	 * Get the position of the window enclosing the figure
	 * @param posX X coordinate in pixels of the window
	 * @param posY Y coordinate in pixels of the window
	 */
	public void setWindowPosition(int posX, int posY) {
		guiProperties.setWindowPosition(posX, posY);
	}
	
	/**
	 * Get the current GL pipeline associated with the rendering context
	 * @return current GL pipeline
	 */
	@Override
	public GL getGL() {
		return guiProperties.getGLPipeline();
	}
	
	
	/**
	 * @param onOrOff specify if we set the pixmap on or off
	 */
	public void setPixmapMode(boolean onOrOff) {
		pixmapModeOn = onOrOff;
	}
	
	/**
	 * @return wether the pixmap mode is on ar off.
	 */
	public boolean getPixmapMode() {
		return pixmapModeOn;
	}
	
	/**
     * Specify wether the canvas should fit the parent tab size
     * (and consequently the scrollpane size) or not
     * @param onOrOff true to enable autoresize mode
     */
    public void setAutoResizeMode(boolean onOrOff) {
    	getRendererProperties().setAutoResizeMode(onOrOff);
    }
    
    /**
     * @return wether the resize mode is on or off
     */
    public boolean getAutoResizeMode() {
    	return getRendererProperties().getAutoResizeMode();
    }
    
    /**
	 * Get the part of the canvas which is currently viewed
	 * @return [x,y,w,h] array
	 */
   public int[] getViewport() {
	   return getRendererProperties().getViewport();
   }
   
   /**
	 * Specify a new viewport for the canvas
	 * For SwingScilabCanvas viewport can not be modified
	 * since it match the parent tab size
	 * @param posX X coordinate of upper left point of the viewport within the canvas
	 * @param posY Y coordinate of upper left point of the viewport within the canvas
	 * @param width width of the viewport
	 * @param height height of the viewport
	 */
	public void setViewport(int posX, int posY, int width, int height) {
		getRendererProperties().setViewport(posX, posY, width, height);
	}
	
	/**
	 * Specify the default target on which the figure is rendered.
	 * @param target pointer on the target
	 */
	public void setRenderingTarget(GLAutoDrawable target) {
		this.renderingTarget = target;
	}
	
	/**
	 * @return Default target on which the figure is rendered.
	 */
	public GLAutoDrawable getRenderingTarget() {
		return renderingTarget;
	}
	
	/**
	 * setTextRendererFactory
	 * @param textRendererFactory TextRendererFactory
	 */
	public void setTextRendererFactory(TextRendererFactory textRendererFactory) {
		this.textRendererFactory = textRendererFactory;
	}
	
	/**
	 * getTextRendererFactory
	 * @return TextRendererFactory
	 */
	public TextRendererFactory getTextRendererFactory() {
		return textRendererFactory;
		
	}	
	
	/**
	 * setArcRendererFactory
	 * @param arcRendererFactory ArcRendererFactory
	 */
	public void setArcRendererFactory(ArcRendererFactory arcRendererFactory) {
		this.arcRendererFactory = arcRendererFactory;
	}
	
	/**
	 * getArcRendererFactory
	 * @return ArcRendererFactory
	 */
	public ArcRendererFactory getArcRendererFactory() {
		return arcRendererFactory;
		
	}
	
	/**
	 * Get a text renderer with the specified color and font
	 * @param font specified font
	 * @param color 3 color channels
	 * @return text renderer to use
	 */
	public SciTextRenderer getTextWriter(Font font, double[] color) {
		// check if we need to recreate a new one
		if (textWriter == null || !textWriter.hasFont(font)) {
			if (textWriter != null) {
				// free resources used by the current one if exists
				textWriter.flush();
				textWriter.dispose();
			}
			textWriter = (SciTextRenderer) getTextRendererFactory().createTextRenderer(font, color);
		} else {
			textWriter.setColor(color[0], color[1], color[2]);
		}
		
		return textWriter;
	}
	
	/**
	 * Destroy the current text writter, then force the creation of a new one
	 */
	public void destroyTextWriter() {
		if (textWriter != null) {
			// free resources used by the current one
			textWriter.flush();
			textWriter.dispose();
		}
		textWriter = null;
	}
	
}
