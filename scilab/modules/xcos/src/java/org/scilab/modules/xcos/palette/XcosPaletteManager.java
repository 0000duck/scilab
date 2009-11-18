/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.palette;

import java.awt.LayoutManager;
import java.util.HashMap;
import java.util.Map;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeSelectionModel;

import org.scilab.modules.gui.bridge.tab.SwingScilabTab;
import org.scilab.modules.gui.menu.Menu;
import org.scilab.modules.gui.menu.ScilabMenu;
import org.scilab.modules.gui.menubar.MenuBar;
import org.scilab.modules.gui.menubar.ScilabMenuBar;
import org.scilab.modules.gui.tab.ScilabTab;
import org.scilab.modules.gui.tab.Tab;
import org.scilab.modules.gui.textbox.ScilabTextBox;
import org.scilab.modules.gui.toolbar.ScilabToolBar;
import org.scilab.modules.gui.toolbar.ToolBar;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.window.ScilabWindow;
import org.scilab.modules.gui.window.Window;
import org.scilab.modules.xcos.actions.ClosePalettesAction;
import org.scilab.modules.xcos.actions.NewDiagramAction;
import org.scilab.modules.xcos.actions.OpenAction;
import org.scilab.modules.xcos.block.BasicBlock;
import org.scilab.modules.xcos.block.TextBlock;
import org.scilab.modules.xcos.io.BlockReader;
import org.scilab.modules.xcos.utils.XcosMessages;

/**
 * Manage all the Block Palettes.
 */
public final class XcosPaletteManager {

    private static Thread paletteThread;
    private static boolean paletteLoadStarted;
    private static Tab palettes;
    private static HashMap<String, BasicBlock> allBlocks = new HashMap<String, BasicBlock>();

    /**
     * Instantiate all the known names (default configuration)
     */
    private static final PaletteStringDescriptor[] allPalettesStringDescriptor =
    {
    	/** SOURCES palette */
    	new PaletteStringDescriptor(
    			XcosMessages.SOURCES_PAL,
    			new String[] {
    					"CLKINV_f", 
	    				"CLOCK_c", 
	    				"CONST_m",
	    				"CURV_f", 
	    				"Counter", 
	    				"FROMWSB",
	    				"GENSIN_f", 
	    				"GENSQR_f", 
	    				"INIMPL_f",
	    				"IN_f", 
	    				"Modulo_Count", 
	    				"RAMP", 
	    				"RAND_m", 
	    				"READAU_f", 
	    				"READC_f", 
	    				"RFILE_f", 
	    				"SAWTOOTH_f", 
	    				"STEP_FUNCTION", 
	    				"SampleCLK", 
	    				"Sigbuilder", 
	    				"TIME_f", 
	    				"TKSCALE"
    			}
    	),
    	
    	/** CONTINUOUS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.CONTINUOUS_PAL,
    			new String[] {
						"CLINDUMMY_f",
						"CLR", 
						"CLSS", 
						"DERIV", 
						"INTEGRAL_f",
						"INTEGRAL_m", 
						"PID", 
						"TCLSS", 
						"TIME_DELAY", 
						"VARIABLE_DELAY"	
    			}
    	),
    	
    	/** DISCONTINUOUS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.DISCONTINUOUS_PAL,
    			new String[] {
    					"BACKLASH", 
    					"DEADBAND", 
    					"DELAYV_f",
    					"HYSTHERESIS", 
    					"RATELIMITER", 
    					"QUANT_f", 
    					"SATURATION"
    			}
		),
		
		/** LOOKUP TABLES palette */
		new PaletteStringDescriptor(
				XcosMessages.LOOKUPTABLES_PAL,
				new String[] {
						"INTRP2BLK_f", 
						"INTRPLBLK_f",
						"LOOKUP_f"
				}
		),
		
		/** SIGNAL PROCESSING palette */
		new PaletteStringDescriptor(
				XcosMessages.SIGNALPROCESSING_PAL,
				new String[] {
						"QUANT_f", 
						"SAMPHOLD_m"
				}
		),
    	
		/** THRESHOLD palette */
		new PaletteStringDescriptor(
				XcosMessages.THRESHOLD_PAL,
				new String[] {
						"GENERAL_f",
						"NEGTOPOS_f", 
						"POSTONEG_f", 
						"ZCROSS_f"
				}
		),
		
		/** MATH OPERATIONS palette */
		new PaletteStringDescriptor(
				XcosMessages.MATHSOPS_PAL,
				new String[] {
						"ABS_VALUE", 
						"BIGSOM_f", 
						"COSBLK_f", 
						"EXPBLK_m", 
						"GAINBLK_f", 
						"INVBLK", 
						"LOGBLK_f",
						"MATMAGPHI", 
						"MATZREIM", 
						"MAXMIN", 
						"MAX_f",
						"MIN_f", 
						"POWBLK_f",
						"PRODUCT", 
						"PROD_f", 
						"SIGNUM", 
						"SINBLK_f", 
						"SQRT", 
						"SUMMATION", 
						"SUM_f", 
						"TANBLK_f",
						"TrigFun"
				}
		),
		
		/** INTEGER palette */
		new PaletteStringDescriptor(
				XcosMessages.INTEGER_PAL,
				new String[] {
						"BITCLEAR", 
						"BITSET", 
						"CONVERT", 
						"DFLIPFLOP", 
						"DLATCH", 
						"EXTRACTBITS", 
						"INTMUL", 
						"JKFLIPFLOP", 
						"LOGIC",
						"SHIFT", 
						"SRFLIPFLOP"
				}
		),
		
		/** MATRIX palette */
		new PaletteStringDescriptor(
				XcosMessages.MATRIX_PAL,
				new String[] {
						"CUMSUM", 
						"EXTRACT", 
						"EXTTRI", 
						"MATBKSL", 
						"MATCATH", 
						"MATCATV", 
						"MATDET", 
						"MATDIAG", 
						"MATDIV", 
						"MATEIG",
						"MATEXPM", 
						"MATINV", 
						"MATLU", 
						"MATMAGPHI", 
						"MATMUL", 
						"MATPINV", 
						"MATRESH", 
						"MATSING", 
						"MATSUM", 
						"MATTRAN", 
						"MATZCONJ", 
						"MATZREIM", 
						"RICC", 
						"ROOTCOEF", 
						"SQRT", 
						"SUBMAT"
				}
		),
		
		/** SINKS palette */
		new PaletteStringDescriptor(
				XcosMessages.SINKS_PAL,
				new String[] {
						"AFFICH_m", 
						"CANIMXY", 
						"CANIMXY3D",
						"CFSCOPE", 
						"CMAT3D", 
						"CMATVIEW", 
						"CMSCOPE", 
						"CSCOPE", 
						"CSCOPXY", 
						"CSCOPXY3D", 
						"HALT_f", 
						"TOWS_c", 
						"TRASH_f",
						"WFILE_f",
						"WRITEAU_f", 
						"WRITEC_f"
				}
		),
		
		/** PORT ACTION palette */
		new PaletteStringDescriptor(
				XcosMessages.PORTACTION_PAL,
				new String[] {
						"CLKINV_f",
						"CLKOUTV_f",
						"IN_f",
						"INIMPL_f",
						"OUTIMPL_f",
						"OUT_f",
						"SUPER_f"
				}
    	),
    	
    	/** DISCRETE palette */
    	new PaletteStringDescriptor(
    			XcosMessages.DISCRETE_PAL,
    			new String[] {
    					"DELAYV_f",
    					"DELAY_f", 
    					"DLR", 
    					"DLRADAPT_f", 
    					"DLSS", 
    					"DOLLAR_f",
    					"SAMPHOLD_m",
    					"TCLSS"
    			}
    	),
    	
    	/** EVENTS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.EVENTS_PAL,
    			new String[] {
    					"ANDBLK", 
    					"ANDLOG_f",
    					"CEVENTSCOPE",
    					"CLKFROM", 
    					"CLKGOTO", 
    					"CLKGotoTagVisibility", 
    					"CLKOUTV_f", 
    					"CLKSOMV_f", 
    					"CLOCK_c", 
    					"EDGE_TRIGGER",
    					"ESELECT_f",
    					"EVTDLY_c", 
    					"EVTGEN_f", 
    					"EVTVARDLY", 
    					"Extract_Activation", 
    					"HALT_f", 
    					"IFTHEL_f", 
    					"M_freq",
    					"MCLOCK_f", 
    					"MFCLCK_f", 
    					"REGISTER",
    					"SampleCLK", 
    					"freq_div"
    			}
    	),
    	
    	/** Signal Routing palette */
    	new PaletteStringDescriptor(
    			XcosMessages.SIGNALROUTING_PAL,
    			new String[] {
    					"DEMUX",
    					"EXTRACTOR", 
    					"FROM", 
    					"FROMMO", 
    					"GOTO", 
    					"GOTOMO", 
    					"GotoTagVisibility", 
    					"GotoTagVisibilityMO", 
    					"ISELECT_m", 
    					"MUX", 
    					"M_SWITCH", 
    					"NRMSOM_f", 
    					"RELAY_f", 
    					"SELECT_m", 
    					"SWITCH2_m", 
    					"SWITCH_f"
    			}
    	),
    	
    	/** COMMONLY USED BLOCKS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.COMMONUSED_PAL,
    			new String[] {
    					"ANDBLK", 
    					"BIGSOM_f",
    					"CMSCOPE", 
    					"CONST_m", 
    					"CONVERT", 
    					"CSCOPXY", 
    					"DEMUX", 
    					"DOLLAR_f", 
    					"INTEGRAL_f", 
    					"IN_f", 
    					"LOGICAL_OP", 
    					"MUX", 
    					"NRMSOM_f", 
    					"OUT_f", 
    					"PRODUCT", 
    					"RELATIONALOP", 
    					"SATURATION", 
    					"SWITCH2_m",
    					"TEXT_f"
    			}
    	),
    	
    	/** USER-DEFINED FUNCTIONS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.USERDEFINEDFUNCTIONS_PAL,
    			new String[] {
    					"CBLOCK",
    					"EXPRESSION", 
    					"MBLOCK", 
    					"PDE", 
    					"SUPER_f",
    					"c_block", 
    					"fortran_block", 
    					"generic_block3", 
    					"scifunc_block_m"
    			}
    	),
    	
    	/** ELECTRICAL palette */
    	new PaletteStringDescriptor(
    			XcosMessages.ELECTRICAL_PAL,
    			new String[] {
    					"CCS", 
    					"CVS",
    					"Capacitor", 
    					"ConstantVoltage", 
    					"CurrentSensor", 
    					"Diode",
    					"Ground", 
    					"Gyrator",
    					"IdealTransformer", 
    					"Inductor",
    					"NMOS", 
    					"NPN", 
    					"OpAmp", 
    					"PMOS", 
    					"PNP", 
    					"PotentialSensor", 
    					"Resistor", 
    					"SineVoltage", 
    					"Switch", 
    					"VVsourceAC", 
    					"VariableResistor", 
    					"VoltageSensor", 
    					"VsourceAC"
    			}
    	),
    	
    	/** THERMO-HYDRAULICS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.THERMOHYDRAULICS_PAL,
    			new String[] {
    					"Bache", 
    					"PerteDP", 
    					"PuitsP", 
    					"SourceP",
    					"VanneReglante"
    			}
    	),
    	
    	/** IMPLICIT palette */
    	new PaletteStringDescriptor(
    			XcosMessages.IMPLICIT_PAL,
    			new String[] {
    					"CONSTRAINT_f"
    			}
    	),
    	
    	/** ANNOTATIONS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.ANNOTATIONS_PAL,
    			new String[] {
    					"TEXT_f"
    			}
    	),
    	
    	/** DEMO-BLOCKS palette */
    	new PaletteStringDescriptor(
    			XcosMessages.DEMOBLOCKS_PAL,
    			new String[] {
    					"AUTOMAT", 
    					"BOUNCE", 
    					"BOUNCEXY", 
    					"BPLATFORM", 
    					"PDE"
    			}
    	)
    };

    /**
     * Represent a palette configuration values
     */
    private static class PaletteStringDescriptor {
		public String Name;
		public String[] Components;

		public PaletteStringDescriptor(String name, String[] components) {
			Name = name;
			Components = components;
		}
	}

    /**
     * Represent the instanciation of the configurations values
     */
	private static class PaletteDescriptor {
		public String Name;
		public PaletteBlockData[] Components;

		public PaletteDescriptor(String name, PaletteBlockData[] components) {
			Name = name;
			Components = components;
		}
		
		@Override
		public String toString() {
			return Name;
		}
	}

	/**
	 * Represent any block data
	 */
	private static class PaletteBlockData {
		public String Name;
		public ImageIcon Icon;
		public BasicBlock Block;

		/**
		 * Any PaletteBlock data (arguments of the
		 * org.scilab.modules.xcos.palette.XcosPalette#addTemplate)
		 * 
		 * @param name The name of the block
		 * @param icon The icon of the block
		 * @param block Extracted from PATH/BlockName.hf5
		 */
		public PaletteBlockData(String name, ImageIcon icon, BasicBlock block) {
			Name = name;
			Icon = icon;
			Block = block;
		}
	}
	
    /** Palette creation */
    static {
	paletteThread = new Thread() {
	    public void run() {

				final JSplitPane allpalettes = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
				final XcosPalette rootPalette = new XcosPalette(XcosMessages.PALETTES);
				DefaultMutableTreeNode rootNode = new DefaultMutableTreeNode(rootPalette);
				TreeModel paletteTreeModel = new DefaultTreeModel(rootNode);
				final JTree paletteTree = new JTree(paletteTreeModel);
				
				allpalettes.setRightComponent(rootPalette);
				allpalettes.setLeftComponent(new JScrollPane(paletteTree));
				
				paletteTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
				paletteTree
						.addTreeSelectionListener(new TreeSelectionListener() {

							@Override
							public void valueChanged(TreeSelectionEvent tree) {
								DefaultMutableTreeNode node = (DefaultMutableTreeNode) paletteTree.getLastSelectedPathComponent();

								if (node == null)
									// Nothing is selected.
									return;

								XcosPalette nodeInfo = (XcosPalette) node.getUserObject();
								allpalettes.setRightComponent(nodeInfo);
							}

						});			
				// Add a default Java bloc in HashMap
				 allBlocks.put("TEXT_f", new TextBlock("TEXT_f"));
				((SwingScilabTab) palettes.getAsSimpleTab()).setContentPane(allpalettes);

				palettes.setVisible(true);
				
				for (PaletteStringDescriptor paletteStringDescriptor : allPalettesStringDescriptor) {
					/* Doesn't perform UI update */
					PaletteDescriptor currentDescriptor = new PaletteDescriptor(
							paletteStringDescriptor.Name,
							createPaletteData(paletteStringDescriptor.Components));
					
					/* Perform UI update */
					XcosPalette xcosPalette = new XcosPalette(paletteStringDescriptor.Name);
					for (PaletteBlockData iter : currentDescriptor.Components) {
						xcosPalette.addTemplate(iter.Name, iter.Icon, iter.Block);
					}
					rootNode.add(new DefaultMutableTreeNode(xcosPalette));
				}

				synchronized (this) {
					this.notifyAll();
				}

				paletteLoadStarted = true;
				palettes.getAsSimpleTab().getInfoBar().setText(XcosMessages.EMPTY_INFO);
				
				/* UI Layout specific operations */
				paletteTree.expandRow(0);
				paletteTree.setSelectionRow(1);
				paletteTree.setRootVisible(false);
				allpalettes.getLeftComponent().setMinimumSize(paletteTree.getPreferredSize());
				
			}
		};
    }

    private XcosPaletteManager() {
	}

    public static Tab loadPalette() {
		if (paletteLoadStarted == false) {
			createPaletteWindow();
			palettes.getAsSimpleTab().getInfoBar().setText(XcosMessages.LOADING_PALETTES);
			paletteThread.start();
		}
		return palettes;
	}

    private static PaletteBlockData[] createPaletteData(String[] blocksNames) {

		PaletteBlockData[] xcosPalette = new PaletteBlockData[blocksNames.length];

		final String blocksPath = System.getenv("SCI") + "/modules/scicos_blocks/blocks/";
		final String palImagesPath = System.getenv("SCI") + "/modules/xcos/images/palettes/";

		BasicBlock theBloc = null;

		for (int kBlock = 0; kBlock < blocksNames.length; kBlock++) {
			// Search the bloc in global hashmap
			theBloc = allBlocks.get(blocksNames[kBlock]);

			// If not found then create it
			if (theBloc == null) {
				theBloc = BlockReader.readBlockFromFile(blocksPath
						+ blocksNames[kBlock] + ".h5");
				allBlocks.put(blocksNames[kBlock], theBloc);
			}

			if (theBloc.getStyle().compareTo("") == 0) {
				theBloc.setStyle(theBloc.getInterfaceFunctionName());
				theBloc.setValue(theBloc.getInterfaceFunctionName());
			}

			xcosPalette[kBlock] = new PaletteBlockData(
					blocksNames[kBlock],
					new ImageIcon(palImagesPath + blocksNames[kBlock] + ".jpg"),
					theBloc);

		}

		return xcosPalette;
	}

    public static Tab getPalettes() {
        return palettes;
    }
    
    private static void createPaletteWindow() {
		paletteLoadStarted = false;
		// Add a default Java bloc in HashMap
		// Xcos.getAllBlocks().put("TEXT_f", new TextBlock("TEXT_f"));

		Window palWin = ScilabWindow.createWindow();
		palWin.setDims(new Size(700, 600));
		palWin.setVisible(true);
		palettes = ScilabTab.createTab(XcosMessages.PALETTE_BROWSER);

		palettes.setCallback(new ClosePalettesAction(null));

		/** Create the menubar */
		MenuBar palMenuBar = ScilabMenuBar.createMenuBar();
		palettes.addMenuBar(palMenuBar);

		Menu palMenu = ScilabMenu.createMenu();
		palMenu.setText(XcosMessages.PALETTES);
		palMenu.setMnemonic('P');
		palMenuBar.add(palMenu);

		palMenu.add(ClosePalettesAction.createMenu(null));

		/** Create the toolbar */
		ToolBar palToolbar = ScilabToolBar.createToolBar();
		palettes.addToolBar(palToolbar);
		palToolbar.add(NewDiagramAction.createButton(null));
		palToolbar.add(OpenAction.createButton(null));

		/** Create the infobar */
		palettes.getAsSimpleTab().setInfoBar(ScilabTextBox.createTextBox());

		palWin.addTab(palettes);
	}
    
    public static boolean isVisible() {
		if (palettes != null && palettes.isVisible() == true) {
			return true;
		}
		return false;
	}
}
