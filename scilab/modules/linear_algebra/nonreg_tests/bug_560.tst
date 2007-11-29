// <-- Non-regression test for bug 560 -->
//
// <-- Bugzilla URL -->
// http://www.scilab.org/cgi-bin/bugzilla_bug_II/show_bug.cgi?id=560
//
// <-- Short Description -->

// Non-regression test file for bug 560
// Author : Pierre MARECHAL
// Copyright INRIA
// Scilab Project
// Date : 29 novembre 2007

format(15);
m=100;
n=15;

t=(0:m-1)'/(m-1); A=[];

for i=1:n
	A = [A t.^(i-1)];
end

b = exp(sin(4*t));
b = b/2006.7874531048527;

x1        = A\b;
[Q,R]     = qr(A);
x2        = R(1:n,1:n)\(Q(:, 1:n)'*b);
[U, S, V] = svd(A);
x3        = V*(diag(1 ./ diag(S))*U(:,1:n)'*b)

if or(round(1000000*x1)<>round(1000000*x2)) <>  then pause,end
if or(round(1000000*x1)<>round(1000000*x3)) <>  then pause,end
if or(round(1000000*x2)<>round(1000000*x3)) <>  then pause,end
