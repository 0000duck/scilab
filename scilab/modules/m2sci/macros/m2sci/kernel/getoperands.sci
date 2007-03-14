function [varargout] = getoperands(op_tree)
// Copyright INRIA

varargout=list()

if typeof(op_tree)<>"operation" then
  error(gettext("errors","m2sci_error_30"))
end

opnb=size(op_tree.operands)

for k=1:opnb
  varargout(k)=op_tree.operands(k)
end

endfunction
