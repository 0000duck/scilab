function z=bitor(x,y)
// Copyright INRIA
// BITOR function
// Given x,y two positives integers this function returns the decimal number whose the binary form is the OR of the binary representations of x and y

// -Inputs : 
//  x, y :  scalars/vectors/matices/hypermatices of positives integers, x and y must have the same size
// -Output :
//  z : scalar/vector/matrix/hypermatice
//
// F.Belahcene

if size(x)<>size(y)
	error(msprintf(gettext("%s: Wrong size for inputs arguments: Same sizes expected.\n"),"bitor"));
elseif isempty(x) & isempty(x)
	z=[]
	return
end

if (type(x)==1 & (x-floor(x)<>0 | x<0)) | (type(x)==8 & x<0) | (type(x)==17 & (type(x.entries<>1) | type(x.entries<>8)) & find(x.entries>0)<>[])  | (type(x)<>1 & type(x)<>8 & type(x)<>17)
	error(msprintf(gettext("%s: Wrong first input argument: Scalar/vector/matrix of positive integers expected.\n"),"bitor"));
end

if (type(y)==1 & (y-floor(y)<>0 | y<0)) | (type(y)==8 & y<0) | (type(y)==17 & (type(y.entries<>1) | type(y.entries<>8)) & find(y.entries>0)<>[]) | (type(y)<>1 & type(y)<>8 & type(y)<>17)
	error(msprintf(gettext("%s: Wrong second input argument: Scalar/vector/matrix of positive integers expected.\n"),"bitor"));
end

for i=1:prod(size(x))
	zbin=dec2bin([x(i);y(i)])
	zand=strcat((string(sum(asciimat(zbin)-48,1))))
	zand=strsubst(zand,'2','1')
	z(i)=bin2dec(zand)
end
z=matrix(z,size(x))
endfunction
