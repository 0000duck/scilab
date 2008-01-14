// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// ====================================================================

mode(-1);
lines(0);

try   
 version_scilab = getversion('scilab');
catch  
 warning('Scilab 5.0 or more is required.');  
 return;
end;  

if ~haveacompiler() then
  warning('This toolbox requires a compiler to build.');
  return;
end


current_dir = pwd();
main_dir_tlbx_sklt = get_absolute_file_path('builder.sce');


disp('Build macros');
chdir(main_dir_tlbx_sklt);
// build macros
if ( isdir('macros') ) then
  chdir('macros');
  exec('buildmacros.sce');
else
end

disp('Build src C & fortran');
chdir(main_dir_tlbx_sklt);
if ( isdir('src') ) then 
 chdir('src');
 exec('builder_src.sce',-1);
else
end

disp('Build gateway C & fortran');
chdir(main_dir_tlbx_sklt);
if ( isdir('sci_gateway') ) then 
 chdir('sci_gateway');
 exec('builder_gateway.sce',-1);
else
end

disp('Build help');
chdir(main_dir_tlbx_sklt);
if ( isdir('help') ) then 
 chdir('help');
 exec('builder_help.sce',-1);
else
end

chdir(main_dir_tlbx_sklt);
clear main_dir_tlbx_sklt;

chdir(current_dir);
clear current_dir;
// ====================================================================
