function addmenu(varargin)
// Add menus in Scilab Windows
// See comments in the code for different implementations

// Copyright INRIA

// Allan CORNET 2005
// Vincent COUVERT 2007: Java version

rhs=argn(2);

select rhs
case 1
  if type(varargin(1))==10
    // addmenu(menu_label)
    // Create a menu in Scilab main Window
    // The callback is the variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single string expected."),"addmenu"));
    end

    addSingleMenu(0, varargin(1));

  else
    error(msprintf(_("%s: Wrong type for first input argument: String expected."),"addmenu"));
  end
case 2
  if type(varargin(1))==10 & type(varargin(2))==10
    // addmenu(menu_label, submenus_labels)
    // Create a menu in Scilab main Window with submenus
    // The callbacks are the items of variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single string expected."),"addmenu"));
    end

    // No verification for submenus labels

    addMenuSubMenus(0, varargin(1), varargin(2));

  elseif type(varargin(1))==10 & type(varargin(2))==15
    // addmenu(menu_label, action_in_a_list)
    // Create a menu in Scilab main Window with submenus
    // The callbacks are the items of variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single string expected."),"addmenu"));
    end

    if size(varargin(2)) <> 2
      error(msprintf(_("%s: Wrong type for second input argument: Two-item list expected."),"addmenu"));
    end

    addSingleMenuCallback(0, varargin(1), varargin(2));

  elseif type(varargin(1))==1 & type(varargin(2))==10
    // addmenu(graphic_window_id,menu_label)
    // Create a menu in Scilab main Window
    // The callback is the variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single value expected."),"addmenu"));
    end

    if size(varargin(2),"*") <> 1
      error(msprintf(_("%s: Wrong type for second input argument: Single string expected."),"addmenu"));
    end

    addSingleMenu(scf(varargin(1)), varargin(2))

  else
    error(msprintf(_("%s: Wrong type for two input arguments"),"addmenu"));
  end
case 3
  if type(varargin(1))==10 & type(varargin(2))==10 & type(varargin(3))==15
    // addmenu(menu_label, submenus_labels, actions_in_a_list)
    // Create a menu in Scilab main Window with submenus
    // The callbacks are given in the third input argument

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single value expected."),"addmenu"));
    end

    // No verification for submenus labels size

    if size(varargin(3)) <> 2
      error(msprintf(_("%s: Wrong type for third input argument: Two-item list expected."),"addmenu"));
    end

    addMenuSubMenusCallback(0, varargin(1), varargin(2), varargin(3));

  elseif type(varargin(1))==1 & type(varargin(2))==10 & type(varargin(3))==10
    // addmenu(graphic_window_id, menu_label, submenus_labels)
    // Create a menu in Scilab main Window with submenus
    // The callbacks are the items of variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single value expected."),"addmenu"));
    end

    if size(varargin(2),"*") <> 1
      error(msprintf(_("%s: Wrong type for second input argument: Single string expected."),"addmenu"));
    end

    // No verification for submenus labels

    addMenuSubMenus(scf(varargin(1)), varargin(2), varargin(3));

  elseif type(varargin(1))==1 & type(varargin(2))==10 & type(varargin(3))==15
    // addmenu(graphic_window_id, menu_label, action_in_a_list)
    // Create a menu in Scilab main Window with submenus
    // The callbacks are the items of variable named menu_label

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single value expected."),"addmenu"));
    end

    if size(varargin(2),"*") <> 1
      error(msprintf(_("%s: Wrong type for second input argument: Single string expected."),"addmenu"));
    end

    if size(varargin(3)) <> 2
      error(msprintf(_("%s: Wrong type for third input argument: Two-item list expected."),"addmenu"));
    end

    addSingleMenuCallback(scf(varargin(1)), varargin(2), varargin(3));

  else
    error(msprintf(_("%s: Wrong type for three input arguments"),"addmenu"));
  end
case 4
    // addmenu(graphic_window_id, menu_label, submenus_labels, action_in_a_list)
    // Create a menu in a Scilab graphic Window with submenus
    // The callbacks are given in a list

    if size(varargin(1),"*") <> 1
      error(msprintf(_("%s: Wrong type for first input argument: Single value expected."),"addmenu"));
    end

    if size(varargin(2),"*") <> 1
      error(msprintf(_("%s: Wrong type for second input argument: Single string expected."),"addmenu"));
    end

    // No verification for submenus labels

    if size(varargin(4)) <> 2
      error(msprintf(_("%s: Wrong type for second input argument: Two-item list expected."),"addmenu"));
    end

    addMenuSubMenusCallback(scf(varargin(1)), varargin(2), varargin(3), varargin(4));

else
  error(msprintf(_("%s: Wrong number of input argument(s)")),"addmenu");
end
endfunction
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Add a menu with no callback given by the user
//------------------------------------------------------------------------------
function addSingleMenu(fig, menulabel)
h = UImenu("parent", fig, "label", menulabel);
if fig==0
  set(h, "callback", list(0, "execstr("""+menulabel+"(1)"")"));
else
  set(h, "callback", list(0, "execstr("""+menulabel+"_"+string(get(fig,"figure_id"))+"(1)"")"));
end
endfunction
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Add a menu with callback given by the user
//------------------------------------------------------------------------------
function addSingleMenuCallback(fig, menulabel, callback)

[callbackStr, callbackType] = getCallbackProperties(callback);

h = UImenu("parent", fig, "label", menulabel);
if callbackType <> 2
  set(h, "callback", list(0, "execstr("""+callbackStr+""")"));
else
  if fig==0
    set(h, "callback", list(0, "execstr("""+callbackStr+"(1)"")"));
  else
    set(h, "callback", list(0, "execstr("""+callbackStr+"(1,"+string(get(fig,"figure_id"))+")"")"));
  end
end

endfunction
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Add a menu and its submenus with no callback given by the user
//------------------------------------------------------------------------------
function addMenuSubMenus(fig, menulabel, submenuslabels)

h0 = UImenu("parent", fig, "label", menulabel);

for K=1:size(submenuslabels,"*")
  if (type(fig)==1)
    UImenu("parent", h0, "label", submenuslabels(K), "callback", "execstr("+menulabel+"("+string(K)+"))");
  else
    UImenu("parent", h0, "label", submenuslabels(K), "callback", "execstr("+menulabel+"_"+string(get(fig,"figure_id"))+"("+string(K)+"))");
  end
end

endfunction
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Add a menu and its submenus with callback given by the user
//------------------------------------------------------------------------------
function addMenuSubMenusCallback(fig, menulabel, submenuslabels, callback)

[callbackStr, callbackType] = getCallbackProperties(callback);

h0 = UImenu("parent",fig,"label",menulabel);

for K=1:size(submenuslabels,"*")
  h = UImenu("parent", h0, "label", submenuslabels(K));
  if callbackType <> 2
    set(h, "callback", list(0, "execstr("""+callbackStr+""")"));
  else
    if fig == 0
      set(h, "callback", list(0, "execstr("""+callbackStr+"(1)"")"));
    else
      set(h, "callback", list(0, "execstr("""+callbackStr+"("+string(K)+","+string(get(fig,"figure_id"))+")"")"));
    end
  end
end
endfunction
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Manages callback given as list and check parameters
//------------------------------------------------------------------------------
function [callbackStr, callbackType] = getCallbackProperties(callback)
callbackType = callback(1);
if type(callbackType)<>1 | size(callbackType,"*")<>1
  error(_("Callback type must be a 0, 1 or 2"));
end

callbackStr = callback(2);
if size(callbackStr,"*")<>1
  error(_("Callback must be a single string."));
end
endfunction
//------------------------------------------------------------------------------
