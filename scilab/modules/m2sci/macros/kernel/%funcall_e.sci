function val=%funcall_e(field,m2scitlist)
// Copyright INRIA
// V.C.
val=[]
if field=="infer" then
  val=m2scitlist.lhs(1).infer
elseif field=="dims" then
  val=m2scitlist.lhs(1).infer.dims
elseif field=="type" then
  val=m2scitlist.lhs(1).infer.type
elseif field=="vtype" then
  val=m2scitlist.lhs(1).infer.type.vtype
elseif field=="property" then
  val=m2scitlist.lhs(1).infer.type.property
elseif field=="contents" then
  val=m2scitlist.lhs(1).infer.contents
else
  error(msprintf(gettext("errors","m2sci_error_3"),string(field),typeof(m2scitlist)))
end
endfunction
