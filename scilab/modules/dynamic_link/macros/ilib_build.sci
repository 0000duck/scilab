//==========================================
// INRIA 2008
//==========================================
function ilib_build(ilib_name,table,files,libs,makename,ldflags,cflags,fflags,ismex)

  if ~haveacompiler() then
  	error(_('A Fortran or C compiler is required.'))  
  	return;
  end
  
  [lhs,rhs]=argn(0);
  
  if rhs <= 4 then makename = 'Makelib';end
  if rhs <= 5 then ldflags = ''; end 
  if rhs <= 6 then cflags  = ''; end 
  if rhs <= 7 then fflags  = ''; end 
  if rhs <= 8 then ismex  = %f; end 
  
  warningmode = warning('query');
  
  // generate the gateway file
  if (warningmode == 'on') then
    write(%io(2),_('   generate a gateway file'));
  end    
  ilib_gen_gateway(ilib_name,table)
  
  // generate a loader file
  if (warningmode == 'on') then
    write(%io(2),_('   generate a loader file'));
  end
  if ~ismex then
    ilib_gen_loader(ilib_name,table,libs);
  else
    ilib_gen_loader(ilib_name,table);
  end
  
  // generate a Makefile
  if (warningmode == 'on') then
    write(%io(2),sprintf(_('   generate a Makefile: %s'),'Makelib'));
  end
  ilib_gen_Make(ilib_name,table,files,libs,makename,%t,ldflags,cflags,fflags);
  
  // we call make
  if (warningmode == 'on') then
    write(%io(2),_('   running the makefile'));
  end
  ilib_compile(ilib_name,makename,files);
  
endfunction
//==========================================
