function  y=complex(varargin)
// Copyright INRIA
// COMPLEX function
// Given the real part and the imaginary part this function constructs the complex form : y=complex(a,b) returns y=a+b*i
// Inputs : 
//  a, b : real scalars/vectors/matrices
// output :
// y : complex form
// F.Belahcene

rhs = argn(2);
if rhs == 1 then
  a = varargin(1);
  if isreal(a) then
    y = a+imult(zeros(a)); 
  else
    error(msprintf(gettext("%s: Wrong type for input argument: Real expected.\n"),"complex"));
  end
elseif rhs == 2 then
  a = varargin(1);
  b = varargin(2);
  if isreal(a) & isreal(b) then
    y = a+imult(b);
  else
    error(msprintf(gettext("%s: Wrong type for input arguments: Reals expected.\n"),"complex"));
  end
else 
  error(58);
end
endfunction
