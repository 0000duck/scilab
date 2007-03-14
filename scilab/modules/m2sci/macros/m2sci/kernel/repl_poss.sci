function []=repl_poss(expr,varargin)
// Copyright INRIA
// Scilab Project - V. Couvert
// Display informations for replacement for a statement in converted file

txt=[]
nposs=size(varargin)

if nposs==0 | fix(nposs/3)*3~=nposs then
  error(gettext("errors","m2sci_error_5"))
end

txt=[expression2code(expr)+gettext("messages","m2sci_message_68")]
for k=1:3:nposs
  vars=""
  if typeof(varargin(k+1))<>"list" then
    vars=expression2code(varargin(k+1))
  else
    for l=1:size(varargin(k+1))
      vars=vars+expression2code(varargin(k+1)(l))
      if l<size(varargin(k+1)) then
	vars=vars+" and "
      end
    end
  end
  txt=[
      txt
      "   --> "+expression2code(varargin(k))+" "+gettext("messages","m2sci_message_69")+" "+vars+" "+varargin(k+2)]
end

set_infos(txt,1)

endfunction
