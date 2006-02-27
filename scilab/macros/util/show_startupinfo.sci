function show_startupinfo()
  //used to inform users on first start after installation
  
  // If in No Window mode then returns...
  if ~isempty(grep(sciargs(),["-nw","-nwni"])) then
    return
  end
  
  settings_file=pathconvert(SCIHOME+'/.scilab_settings',%f,%t)
  w=fileinfo(settings_file);
  global LANGUAGE
  if  LANGUAGE=='fr' then
    DialogNewGraphic=["Attention:"
		      " "
		      "Les versions Scilab 4.x seront les derni�res � fonctionner"
		      "avec l''ancien mode graphique."
		      " "
		      "Veuillez lire le fichier RELEASE_NOTES pour plus de d�tails."]
    Buttons=['Rappel','Ok']
  else
    DialogNewGraphic=["Warning:"
 		      " "
		      "Scilab 4.x versions family will be the last versions working"
		      "with the old graphics mode."
		      " "
		      "Please read the RELEASE_NOTES file for more details."]
    Buttons=['Remind Me','Ok']
  end
  if ~MSDOS  then
    show=%t
    if w <> [] then
      show=grep(mgetl(SCIHOME+'/.scilab_settings'),'displayDialogNewGraphic=no')==[]
    end
    if show
      if x_message(DialogNewGraphic, Buttons) == 2 then
	mputl('displayDialogNewGraphic=no',SCIHOME+'/.scilab_settings')
      end
    end
  end
endfunction
