function res=m2sci_gui()
// Copyright INRIA
// Scilab Project - V. Couvert
// Call m2sci.tcl to get file or path to convert using M2SCI and user defined options

if ~with_tk() then
  error(gettext("errors","m2sci_error_1"));
end

// Default Options and Values
TCL_SetVar("ePathToConvert",getcwd());
TCL_SetVar("eFileToConvert",gettext("menus","m2sci_menu_1"));
TCL_SetVar("eResDirName",getcwd());
TCL_SetVar("rRecMode",gettext("messages","m2sci_message_1"));
TCL_SetVar("rOnlyDouble",gettext("messages","m2sci_message_1"));
TCL_SetVar("rVerbMode","3");
TCL_SetVar("rPrettyPrint",gettext("messages","m2sci_message_1"));
TCL_SetVar("rFlagWhatToConvert","0");
TCL_SetVar("rToDo","0");
TCL_SetVar("rWindowKilled","0");

TCL_EvalFile(SCI+"/modules/m2sci/tcl/m2sci.tcl");

rWindowKilled=TCL_GetVar("rWindowKilled");
rToDo=TCL_GetVar("rToDo");
while rToDo=="0" & rWindowKilled=="0"
  rWindowKilled=TCL_GetVar("rWindowKilled");
  rToDo=TCL_GetVar("rToDo");
  sleep(1);
end

if rToDo=="1" then
  DirName=TCL_GetVar("ePathToConvert");
  FileName=TCL_GetVar("eFileToConvert");
  ResDirName=TCL_GetVar("eResDirName");
  RecMode=TCL_GetVar("rRecMode");
  OnlyDouble=TCL_GetVar("rOnlyDouble");
  VerbMode=TCL_GetVar("rVerbMode");
  PrettyPrint=TCL_GetVar("rPrettyPrint");
  FlagWhatToConvert=TCL_GetVar("rFlagWhatToConvert");
  
  // Modify Tcl/Tk values
  if RecMode==gettext("messages","m2sci_message_2") then
    RecMode=%T
  else  
    RecMode=%F
  end    
  if OnlyDouble==gettext("messages","m2sci_message_2") then
    OnlyDouble=%T
  else
    OnlyDouble=%F
  end    
  if PrettyPrint==gettext("messages","m2sci_message_2") then
    PrettyPrint=%T
  else
    PrettyPrint=%F
  end    
  VerbMode=evstr(VerbMode);
  
  if FlagWhatToConvert=="0" then // Convert a whole directory
    translatepaths(DirName,ResDirName);
    res=0
  else
    res=mfile2sci(FileName,ResDirName,RecMode,OnlyDouble,VerbMode,PrettyPrint);
  end
elseif rToDo=="-1" then
  // Cancel button
  res=0
else
  // Window killed
  res=0
end
endfunction
