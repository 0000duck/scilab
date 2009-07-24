//  Scicos
//
//  Copyright (C) INRIA - METALAU Project <scicos@inria.fr>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// See the file ../license.txt
//
function  ok=xml2modelica(xmlfile,Flati)
//Scilab interface  with external tool modelicac.exe
  tmpdir=pathconvert(TMPDIR,%t,%t);  //for error log and  shell scripts
  xmlfile=pathconvert(xmlfile,%f,%t);  
  Flati=pathconvert(Flati,%f,%t);  
  
  exe='""'+pathconvert(SCI+'/bin/xml2modelica.exe',%f,%t)+'""'
  
  in='""'+xmlfile+'""'
  out='-o ""'+Flati+'""'
  Errfile= '>""'+tmpdir+'ixml2modelica.err""'
  instr=strcat([exe in out Errfile],' ')
 "'    
  if MSDOS then, 
    mputl(instr,tmpdir+'igenx.bat');
    instr=tmpdir+'igenx.bat';
  end
  
  if execstr('unix_s(instr)','errcatch')==0 then
    mprintf('%s\n',' xml->Modelica : '+Flati);
  else 
    messagebox([_('-------XML to Modelica error:-------');
		mgetl(Errfile);],'error','modal');	    
    ok=%f,
    TCL_EvalStr("Compile_finished nok "+ %_winId); 
    return
  end
endfunction

