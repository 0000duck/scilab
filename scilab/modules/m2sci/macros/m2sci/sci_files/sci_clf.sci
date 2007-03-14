function [tree]=sci_clf(tree)
// Copyright INRIA
// M2SCI function
// Conversion function for Matlab clf()
// Input: tree = Matlab funcall tree
// Ouput: tree = Scilab equivalent for tree
// V.C.

if rhs<1 then
  set_infos(gettext("messages","m2sci_message_82"),2);
end
if rhs==1 then
  set_infos(gettext("messages","m2sci_message_83"),2);
end

// f=gcf() inserted if output value stored in a variable
if tree.lhs(1).name<>"ans" then
  f=tree.lhs(1)
  insert(Equal(list(f),Funcall("gcf",1,list(),list())),1)
end
tree.lhs(1).name="ans"
endfunction
