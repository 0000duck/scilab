//------------------------------------------------------------------------------
// Allan CORNET
// INRIA 2005-2007
//------------------------------------------------------------------------------
function [HomeDirectory,ScilabHomeDirectory]=sethomedirectory(varargin)
  nv=size(varargin);
	ScilabHomeDirectory=SCIHOME;
	HomeDirectory=getenv('HOME',SCI);

  if nv==1 then // to set Scilab home with a path
    warning(' Obsolete: Define SCIHOME & HOME before to launch Scilab.');
  end
endfunction
//------------------------------------------------------------------------------
