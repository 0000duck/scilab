/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Jean-Baptiste Silvy
 * desc : Singleton class used to set font of text objects   
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */


package org.scilab.modules.renderer.utils;

import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.util.ArrayList;

/**
 * Singleton class used to set font of text objects.
 * @author Jean-Baptiste Silvy
 */
public class FontManager {

	private static final float[] SCI_SIZE_2_AWT_SIZE_POLYNOM = {0.4f, 1.2f, 8.0f};
	
	// logical awt fonts
	private static final String DIALOG = "Dialog";
	private static final String DIALOG_INPUT = "DialogInput";
	private static final String MONOSPACED = "Monospaced";
	private static final String SERIF = "Serif";
	private static final String SANS_SERIF = "SansSerif";
	
	private static final Font DEFAULT_FONT = new Font("Default", Font.PLAIN, 1);
	
	/** Singleton instance */
	private static FontManager sciFontManager;
	
	/**
	 * A list of fonts.
	 */
	private class FontList extends ArrayList<Font> {
		
		private static final long serialVersionUID = 1L;

		/**
		 * Default constructor.
		 */
		public FontList() {
			super();
		}
		
	}
	
	private FontList sciFonts;

	/**
	 * Default constructor.
	 * Should not be called.
	 */
	protected FontManager() {
		sciFonts = new FontList();
		// set default font
		sciFonts.add(createFont(DIALOG));
		sciFonts.add(createFont(DIALOG_INPUT));
		sciFonts.add(createFont(MONOSPACED));
		sciFonts.add(createFont(SERIF));
		sciFonts.add(createFont(SERIF, true, false));
		sciFonts.add(createFont(SERIF, false, true));
		sciFonts.add(createFont(SANS_SERIF));
		sciFonts.add(createFont(SANS_SERIF, true, false));
		sciFonts.add(createFont(SANS_SERIF, false, true));
		sciFonts.add(createFont(SANS_SERIF, true, true));
		sciFonts.add(createFont(MONOSPACED, true, false));
	}
	
	/**
	 * Get the font manager instance
	 * @return the only instance of fontmanager.
	 */
	public static FontManager getSciFontManager() {
		if (sciFontManager == null) {
			sciFontManager = new FontManager();
		}
		return sciFontManager;
	}
	
	/**
	 * Convert sciab font size to awt font size.
	 * We use a degree 2 polygon to compute this.
	 * Tthe equivalence list is (0 => 8, 1 => 10, 2 => 12, 3 => 14, 4 => 18, 5 => 24).
	 * @param sciSize scilab size
	 * @return awt size
	 */
	public static float scilabSizeToAwtSize(double sciSize) {
		float sciSizef = (float) sciSize;
		return  SCI_SIZE_2_AWT_SIZE_POLYNOM[0] * sciSizef * sciSizef
		      + SCI_SIZE_2_AWT_SIZE_POLYNOM[1] * sciSizef
		      + SCI_SIZE_2_AWT_SIZE_POLYNOM[2];
	}
	
	/**
	 * Get a font from its index in Scilab.
	 * @param fontIndex scilab index of the font.
	 * @return font corresponding to the index with size 1.
	 */
	public Font getFontFromIndex(int fontIndex) {
		if (fontIndex >= 0 && fontIndex < sciFonts.size()) {
			return sciFonts.get(fontIndex);
		} else if (fontIndex < 0) {
			return sciFonts.get(0);
		} else {
			return sciFonts.get(sciFonts.size() - 1);
		}
	}
	
	/**
	 * Get a font from its index in Scilab.
	 * @param fontIndex scilab index of the font.
	 * @param fontSize size of the font (scilab size).
	 * @return font corresponding to the index.
	 */
	public Font getFontFromIndex(int fontIndex, double fontSize) {
		Font res = getFontFromIndex(fontIndex);
		return res.deriveFont(scilabSizeToAwtSize(fontSize));
	}
	/**
	 * Add a new font in the font list.
	 * @param newFont font to add to the list
	 * @return index of added font.
	 */
	public int addFont(Font newFont) {
		sciFonts.add(newFont);
		return sciFonts.size();
	}
	
	/**
	 * Replace a font in the font list by a new one.
	 * @param index index of the font to replace
	 * @param newFont font to add in the font list.
	 * @return index of the added fonr or -1 if an error occured.
	 */
	public int changeFont(int index, Font newFont) {
		int nbFonts = sciFonts.size();
		if (index > nbFonts) {
			// we need to add fonts untils index
			for (int i = nbFonts; i < index; i++) {
				addFont(DEFAULT_FONT);
			}
			return addFont(newFont);
		} else if (index == nbFonts) {
			// add a new Font
			return addFont(newFont);
		} else {
			sciFonts.set(index, newFont);
			return index;
		}
		
	}
	
	/**
	 * Create a new font knowing its name and size.
	 * @param fontName Name of the font.
	 * @return new font.
	 */
	protected Font createFont(String fontName) {
		// size must be applied after.
		// by default, we use PLAIN font.
		return new Font(fontName, Font.PLAIN, 1); 
	}
	
	/**
	 * Create a new font knowing its name and size.
	 * @param fontName Name of the font.
	 * @param isBold wether the font is bold or not.
	 * @param isItalic wether the font is in italic or not.
	 * @return new font.
	 */
	protected static Font createFont(String fontName, boolean isBold, boolean isItalic) {
		int style;
		if (isBold && isItalic) {
			style = Font.BOLD | Font.ITALIC;
		} else if (isBold) {
			style = Font.BOLD;
		} else if (isItalic) {
			style = Font.ITALIC;
		} else {
			style = Font.PLAIN;
		}
		return new Font(fontName, style, 1);
	}
	
	/**
	 * Add a new font from its font name.
	 * @param fontName name of the font to add.
	 * @return index of the added font.
	 */
	public int addFont(String fontName) {
		return addFont(createFont(fontName));
	}
	
	/**
	 * Add a new font from its font name.
	 * @param fontName name of the font to add.
	 * @param isBold wether the font is bold or not.
	 * @param isItalic wether the font is in italic or not.
	 * @return index of the added font.
	 */
	public int addFont(String fontName, boolean isBold, boolean isItalic) {
		return addFont(createFont(fontName, isBold, isItalic));
	}
	
	/**
	 * Get the list of all fonts available.
	 * @return Names of the available fonts.
	 */
	public String[] getAllFontsName() {
		return GraphicsEnvironment.getLocalGraphicsEnvironment().getAvailableFontFamilyNames();
	}
	
}
