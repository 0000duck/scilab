//==========================================
// Allan CORNET
// INRIA 2008
// Detect LCC-Win32 compiler
//==========================================
function res = findlcccompiler()
  res = %F;
  if MSDOS then
    try
      lccincludepath = winqueryreg('HKEY_CURRENT_USER', ..
                                   'Software\lcc\compiler', ..
                                   'includepath');
                        
    catch
      return;
    end
  
    try
      winqueryreg('HKEY_CURRENT_USER', ..
                  'Software\lcc\lcclnk', ..
                  'libpath');
      index = strindex(lccincludepath,filesep());
      szindex = size(index);
      lccbasepath = part(lccincludepath,[1:index(szindex(2))]);
      lccbinpath = lccbasepath + 'bin';
      lccexe = lccbinpath + filesep() + 'lcc.exe';
      if ( fileinfo(lccexe) <> [] ) then
        res = %T;
      end
    catch
      return; 
    end
  end
endfunction
//==========================================

