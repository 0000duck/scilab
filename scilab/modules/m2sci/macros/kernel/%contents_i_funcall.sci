function funcall=%contents_i_funcall(field,contlist,funcall)
// Copyright INRIA
// V.C.

if field=="contents" then
  funcall.lhs(1).infer.contents=contlist
else
  error(gettext("errors","m2sci_error_2"))
end
endfunction
