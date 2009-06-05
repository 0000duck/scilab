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
function   [ok]=  compile_init_modelica(xmlmodel,paremb,jaco)  
  lines(0)
 %_winId=TCL_GetVar("IHMLoc");
  global icpr;

  tmpdir=TMPDIR+'\'; tmpdir=pathconvert(tmpdir,%f,%t)    
  ext='\*.mo';       ext=pathconvert(ext,%f,%t)  
  [ok,modelicac,translator,xml2modelica]=Modelica_execs();
  
  if (~ok) then, 
    TCL_EvalStr("Compile_finished nok "+ %_winId); 
    return; 
  end

  xmlfile=tmpdir+xmlmodel+'_init.xml'; if MSDOS then,xmlfile=strsubst(xmlfile,'\','\\') ;end
  namei=xmlmodel+'i';
  Flati=tmpdir+xmlmodel+'i.mo';
  FlatCi=tmpdir+xmlmodel+'i.c';
  incidencei=tmpdir+xmlmodel+'i_incidence_matrix.xml';
  Flat_functions=tmpdir+xmlmodel+'_functions'+'.mo';
  //--------------------------------------------------------------------
  instr='""'+xml2modelica+'"" ""'+xmlfile+'"" -o ""'+Flati+'""  > ""'+tmpdir+'ixml2modelica.err""'    
  if MSDOS then, mputl(instr,tmpdir+'igenx.bat');instr=tmpdir+'igenx.bat';end
  
  if execstr('unix_s(instr)','errcatch')==0 then
    mprintf('%s',' xml->Modelica : '+Flati); mprintf('\n\r');
  else 
    MSG3= mgetl(tmpdir+'ixml2modelica.err');
    x_message(['------- XML to Modelica error message:-------';MSG3]);
    ok=%f
    TCL_EvalStr("Compile_finished nok "+ %_winId); 
    return	         
  end

  //--------------------------------------------------------------------
  if fileinfo(Flat_functions)==[] then,
    Flat_functions=" ";
  else
    Flat_functions='""'+Flat_functions+'""';
  end

  if jaco=='0' then   
    JAC='';
  else
    JAC=' -jac ';
  end
  
  instr='""'+modelicac+'"" ""'+Flati+'"" '+Flat_functions+' '+JAC+' -with-init-in ""'+xmlfile+'"" -with-init-out ""'+xmlfile+'"" -o ""'+FlatCi+'"" > ""'+tmpdir+'imodelicac.err""'

  if MSDOS then, mputl(instr,tmpdir+'igenm.bat'); instr=tmpdir+'igenm.bat'; end
  if execstr('unix_s(instr)','errcatch')==0 then
    mprintf('%s',' Init C code   : '+FlatCi); mprintf('\n\r');
    ok=Link_modelica_C(FlatCi)
    [nipar,nrpar,nopar,nz,nx,nx_der,nx_ns,nin,nout,nm,ng,dep_u]=reading_incidence(incidencei)
    if (~ok) then, 
      TCL_EvalStr("Compile_finished nok "+ %_winId); 
      return; 
    end
  else
    MSG3= mgetl(tmpdir+'imodelicac.err');
    x_message(['-------Modelica compiler error flat2C:-------';MSG3;'Please read the error message in the Scilab window']);
    ok=%f,
    TCL_EvalStr("Compile_finished nok "+ %_winId); 
    return	         
  end
  
  //build model data structure of the block equivalent to the implicit
  bllst=bllst;nblock=length(bllst);
  mdl=bllst(nblock)
  mdl.sim=list(namei,10004);
  mdl.state=zeros(nx*2,1);
  mdl.dstate=zeros(nz,1);
  mdl.nzcross=ng;
  mdl.nmode=nm;
  mdl.in=ones(nin,1);
  mdl.out=ones(nout,1);
  mdl.dep_ut=[dep_u, %t];
  bllst(nblock)=mdl; 
  if size(connectmat,2)==6 then connectmat=connectmat(:,[1 2 4 5]),end
  scs_m=null()
  
  icpr=list();
  %scicos_solver=100
  icpr=c_pass2(bllst,connectmat,clkconnect,cor,corinv);

  if icpr==list() then 
    TCL_EvalStr("Compile_finished nok "+ %_winId); 
    return,
  end   

  // suppressing display blocks
  Ignore=['bouncexy','cscope','cmscope','canimxy','canimxy3d','cevscpe','cfscope','cscopexy',...
           'cscopexy3d','cscopxy','cscopxy3d','cmatview', 'cmat3d','affich', 'affich2','BPLATFORM']
  
  for i=1:length(icpr.sim.funs)
    if type(icpr.sim.funs(i))<>13 then
      if find(icpr.sim.funs(i)(1)==Ignore)<>[] then
	icpr.sim.funs(i)(1)='trash';
      end
    end
  end
  TCL_EvalStr("Compile_finished ok "+ %_winId); 
endfunction
//-----------------------------------------------------------------------------
