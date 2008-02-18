function close(h)
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Vincent COUVERT
// 
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at    
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

// Close a graphic figure or delete an uimenu or an uicontrol
// This function has been written for compatibility with old TK uicontrols/uimenus

// handle has been given ?
rhs=argn(2);

if rhs < 1 then
  // No handle given so destroy current figure
  delete(gcf());
else 
  if type(h) == 9 then // Graphics handle
    delete(h);
  else
    // Do not know what to do
    error(msprintf(gettext("Do not know how to delete an object of type: %d.\n"), type(h)));
  end
end
endfunction

