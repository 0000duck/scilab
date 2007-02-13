function ok = add_help_chapter(helptitle,path)
	
	// =========================================================================================
	// Modified by Pierre MARECHAL
	// Scilab team
	// Copyright INRIA
	// Date : August 1st 2006
	//
	// add_help_chapter(title,path)
	//
	// Parameters
	//
	// 	title : a character string, the help chapter title 
	// 	path : a character string, the path of the directory containing the help files.
	//
	// Description
	//
	// 	This function adds a new entry in the helps list. The help chapter files are to
	// 	be located in a single directory. If the given  title  already exists in the helps
	// 	list associated with the same path nothing is done. The function checks if the
	// 	directory exist.
	// =========================================================================================
	
	global %helps;
	ok = %F;
	
	// V�rification des param�tres
	// -----------------------------------------------------------------------------------------
	[lhs,rhs]=argn(0);
	if rhs <> 2 then error(39); end
	if type(helptitle) <> 10 then error(55,1); end
	if type(path) <> 10 then error(55,2); end
	
	// Sauvegarde du chemin dans lequel l'on se trouve
	// -----------------------------------------------------------------------------------------
	current_directory = pwd();
	
	// Conversion du chemin dans le format du syst�me d'exploitation utilis�
	// -----------------------------------------------------------------------------------------
	path=pathconvert(path,%f,%t);
	
	// V�rification que la cha�ne de caract�re pass� en deuxi�me param�tre est bien un chemin
	// -----------------------------------------------------------------------------------------
	if ~isdir(path) then 
		error('second argument should give the path to a directory');
	
	// Transformation du chemin pass� en deuxi�me param�tre
	// -----------------------------------------------------------------------------------------
	else
		chdir(path);
		if MSDOS then
			path = getlongpathname(pwd());
		else
			path = pwd();
		end
		chdir(current_directory);
	end
	
	// V�rification que le titre n'est pas d�ja pr�sent dans %helps
	// -----------------------------------------------------------------------------------------
	
	k1 = find( %helps(:,2) == helptitle);
	
	if k1 == [] then
		
		// Cas o� le titre du chapitre n'est pas pr�sent
		%helps=[%helps;path,helptitle];
		ok = %T;
		return;
	
	else
		k2 = find( %helps(k1,1) == path );
		
		if k2 <> [] then 
			// Cas o� le path est �galement le m�me
			return;
		else
			
			for i=1:100
				k3 = find( %helps(:,2) == helptitle+' ('+string(i)+')' );
				if k3 == [] then
					// On a pas trouv� de "title (i)"
					k4 = find( %helps(k3,1) == path );
					if k4 == [] then
						%helps=[%helps;path,helptitle+' ('+string(i)+')'];
						ok = %T;
						return;
					else
						return;
					end
					
				else
					// On a trouv� "title (i)"
					if find( %helps(k3,1) == path ) <> [] then
						return;
					end
				end
			end
		end
	end
	
endfunction
