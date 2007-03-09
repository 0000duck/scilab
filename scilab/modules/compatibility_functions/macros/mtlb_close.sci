function [status]=mtlb_close(h)
// Copyright INRIA
// Emulation function for Matlab close()
// V.C.

rhs=argn(2)

warning(gettext("messages","compatibility_functions_message_5"));
status=1

// close
if rhs<=0 then
  if type(gcf())==9 then
    delete(gcf())
  else
    close()
  end
// close(h) - close('all') - close(name)
elseif rhs==1 then
  if type(h)==9 then 
    delete(h)
  elseif type(h)==1 then 
    close(h)
  elseif type(h)==10 then
    if h=="all" then
      xdel(winsid())
    else // close(name)
      cf_save=gcf()
      
      allwin=winsid()
      for k=1:size(allwin,"*")
	if get(scf(allwin(k)),"figure_name")==h then
	  delete(gcf())
	  break
	end
      end

      scf(cf_save)
    end
  else // Unknown type for h
    error(gettext("errors","compatibility_functions_error_5"))
  end
else // close('all','hidden')
  warning(gettext("messages","compatibility_functions_message_6"));
  xdel(winsid())
end
endfunction


