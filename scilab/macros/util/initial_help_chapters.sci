//================================
//
// Copyright INRIA 2005
// Scilab team
// Date : December 8th 2005
// 
//================================

function %helps=initial_help_chapters(language)
	
	[lhs,rhs]=argn(0)
	
	if rhs==0 then
		language="eng"
	else
		if rhs<>1 then error(39), end
	end
	
	dirs=["programming";"graphics";"elementary";"fileio";"functions";"strings";
		"gui";"utilities";"linear";"polynomials";"control";"robust";
		"nonlinear";"signal";"arma";"metanet";"scicos";"sound";"translation";
		"tdcs";"statistics";"dcd";"identification";"mtlb";
		"sparse"];
	
	sep="/";
	if MSDOS then sep="\",end
	
	%helps=sep+"man"+sep+language+sep+dirs; 
	
	select language
	
	case "eng"
		%helps=[%helps,..
			["Programming";"Graphics Library";"Elementary Functions";
			"Input/Output Functions";"Handling of functions and libraries";
			"Character string manipulations";"GUI and Dialogs";"Utilities";
			"Linear Algebra";"Polynomial calculations";
			"General System and Control";"Robust control toolbox";
			"Optimization and simulation";
			"Signal Processing toolbox";
			"Arma modelisation and simulation toolbox";
			"Metanet: graph and network toolbox";
			"Scicos: Bloc diagram editor and simulator";"Sound file handling";
			"Language or data translations";"TdCs";
			"Statistic basics";
			"Cumulative Distribution Functions; Inverses, grand";
			"Identification";
			"Matlab to Scilab conversion tips";
			"Sparse solvers"]];
			
		if with_tk() then
			tk_dir = sep+"man"+sep+language+sep+"tksci";
			tk_message = "TCL/Tk interface";
			%helps = cat(1,%helps,[tk_dir,tk_message]);
		end
		
		if with_pvm() then
			pvm_dir = sep+"man"+sep+language+sep+"pvm";
			pvm_message = "PVM parallel toolbox";
			%helps = cat(1,%helps,[pvm_dir,pvm_message]);
		end
	
	case "fr"
		%helps=[%helps,..
			["Programmation";"Librairie graphique";"Fonctions �l�mentaires";
			"Entr�es-sorties";"Manipulation des fonctions et des librairies";
			"Manipulations de cha�nes de caract�res";"IHM et Dialogues";"Utilitaires";
			"Alg�bre lin�aire";"Calculs sur les polyn�mes";
			"Contr�le et th�orie des syst�mes";"Contr�le robuste";
			"Optimisation et simulation";
			"Traitement du signal";"Mod�lisation et simulation ARMA";
			"Metanet : graphes et r�seaux";
			"Scicos : �diteur et simulateur de blocs diagrammes";
			"Manipulation de fichiers sons";
			"G�n�ration de code, traduction de donn�es";
			"TdCs";
			"Statistiques";
			"Fonctions de distributions statistiques";
			"Identification";
			"Aide � la conversion Matlab vers Scilab";
			"Solveurs creux"]];
		
		if with_tk() then
			tk_dir = sep+"man"+sep+language+sep+"tksci";
			tk_message = "Interface TCL/Tk";
			%helps = cat(1,%helps,[tk_dir,tk_message]);
		end
		
		if with_pvm() then
			pvm_dir = sep+"man"+sep+language+sep+"pvm";
			pvm_message = "Calcul parall�le avec PVM";
			%helps = cat(1,%helps,[pvm_dir,pvm_message]);
		end
	
	end
	
	%helps=[SCI+%helps(:,1),%helps(:,2)];
	
endfunction
