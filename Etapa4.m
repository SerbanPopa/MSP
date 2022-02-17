clc;
lamA=0.2261;
lamB=0.2379;
miuA=4.1400;
miuB=3.0507;
for alfa = 0 : 0.5 : 1
a=[
-2*(lamA+(1+alfa)*lamB),miuA,miuB,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
2*lamA,-(lamA+miuA+(1+alfa)*lamB),0, miuA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
2*(1+alfa)*lamB, 0, -(2*lamA+(2+alfa)*lamB + miuB), 0, miuA, miuB, miuA, miuB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
0, lamA, 0, -miuA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0;
0, (1+alfa)*lamB, lamA,0, -(lamA+lamB+miuA), 0, 0, 0, 0, 0, 0, 0, miuA, miuB, 0, 0, 0, 0;
0, 0, (1+alfa)*lamB, 0, 0, -(2*lamB+2*lamA+miuB), 0, 0, 0, 0, miuA,miuB, 0, 0, 0, 0, 0, 0;
0, 0, lamA, 0, 0, 0, -(miuA+lamA+(1+alfa)*lamB), 0, miuA, 0,0,0,0,0,0,0,0,0;
0, 0, lamB, 0, 0, 0, 0, -(miuB+lamA+(1+alfa)*lamB), 0, miuA, 0, 0, 0, 0, 0,0,0,0;
0,0,0,0, lamA, 0,0,0,-miuA,0,0,0,0,0,0,0,0,0;
0,0,0,0, lamB,0,0,0,0, -miuA,0,0,0,0,0,0,0,0;
0,0,0,0,0,2*lamA,(1+alfa)*lamB,0,0,0,-(lamA+lamB+miuA),0,0,0,miuA,0,miuB,0;
0,0,0,0,0,2*lamB,0,(1+alfa)*lamB,0,0,0,-(lamA+lamB+miuB),0,0,0,miuA,0,miuB;
0,0,0,0,0,0,lamA,0,0,0,0,0,-miuA,0,0,0,0,0;
0,0,0,0,0,0,0,lamA,0,0,0,0,0,-miuB,0,0,0,0;
0,0,0,0,0,0,0,0,0,0,lamA,0,0,0,-miuA,0,0,0;
0,0,0,0,0,0,0,0,0,0,lamB,0,0,0,0,-miuA,0,0;
0,0,0,0,0,0,0,0,0,0,0,lamA,0,0,0,0,-miuB,0;
%0,0,0,0,0,0,0,0,0,0,0,-lamB,0,0,0,0,0,-miuB;
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;];    
b = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]';
p=a\b;
s = sum(p);
D = (p(1) + p(3) + p(6) + (p(2) + p(5) + p(7) + p(8) + p(11) + p(12))/2)*100;
O = (1 - p(1))*100;
fprintf('alfa = %f\n', alfa);
fprintf('sum(p) = %f \t D = %f \t O = %f\n', s, D, O);
end
