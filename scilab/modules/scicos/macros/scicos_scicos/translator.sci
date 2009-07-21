function [ok]=translator(filemo,Mblocks,modelica_libs,Flat)
//Generate the flat model of the Modelica model given in the filemo file
//and the Modelica libraries. Interface to the external tool
//translator.exe
// if <name> is the basename of filemo this function produces
// - the flat Modelica model file in outpath+name+'f.mo'
// - the flat xml representation file in  outpath+name+'f_init.xml'
// - the flat xml  file in  outpath+name+'f_relations.xml'
   
  mlibs=pathconvert(modelica_libs,%f,%t)
  filemo=pathconvert(filemo,%f,%t) 
  Flat=pathconvert(Flat,%f,%t) 
  
  name=basename(filemo)
  namef=name+'f';

 
  molibs=[]
  mlibsM=pathconvert(TMPDIR+'/Modelica/',%f,%t)      
  for k=1:size(Mblocks,'r')
    funam=stripblanks(Mblocks(k))
    [dirF,nameF,extF]=fileparts(funam);
    if (extF=='.mo') then
      molibs=[molibs;""""+funam+""""];
    else
      molibs=[molibs;""""+mlibsM+funam+'.mo'+""""]
    end
  end

  for k=1:size(mlibs,'*')
    modelica_file=listfiles(mlibs(k)+'/*.mo'); 
    if modelica_file<> [] then 
      molibs=[molibs;""""+modelica_file+""""];
    end
  end
  translator_libs=strcat(' -lib '+ molibs);
  // build the sequence of -lib arguments for translator
  if MSDOS then, Limit=1000;else, Limit=3500;end
  if (length(translator_libs)>Limit) then 
    // OS limitation may restrict the length of shell command line
    // arguments. If there are to many .mo file we catenate them into a
    // single MYMOPACKAGE.mo file
    messagebox(msprintf(_('There are too many Modelica files.\n'+..
			  'it would be better to define several \n'+..
			  'Modelica programs in a single file.')),'warning','modal')
    mymopac= pathconvert(outpath+'MYMOPACKAGE.mo',%f,%t)
    txt=[];
    for k=1:size(molibs,'*')
      [pathx,fnamex,extensionx]=fileparts(molibs(k));
      if (fnamex<>'MYMOPACKAGE') then 
	txt=[txt;mgetl(evstr(molibs(k)))];
      end
    end
    mputl(txt,mymopac);     
    translator_libs= ' -lib ""'+mymopac+'""';
  end 
  translator_libs=translator_libs+'  -lib ""'+filemo+'""'

  //Build the shell instruction for callin the translator
  exe='""'+pathconvert(SCI+'/bin/translator.exe',%f,%t)+'"" '
  out=' -o ""'+Flat+'""' //flat modelica
  Errfile=outpath+'S_translator.err""';
    
  instr=exe+translator_libs+out+' -command ""'+name+' '+namef+';"" >""'+Errfile
  if MSDOS then,   mputl(instr,tmpdir+'gent.bat'), instr=tmpdir+'gent.bat';end
  if execstr('unix_s(instr)','errcatch')<>0 then
    messagebox([_('-------Modelica translator error message:-----');
		mgetl(outpath+'S_translator.err')],'error','modal');
    ok=%f,
  else
    ok=%t
  end
endfunction
