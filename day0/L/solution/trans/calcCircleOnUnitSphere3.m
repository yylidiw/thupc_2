% circle = [alpha(lon) beta(la) radius(arc)]
%function c = calcCircleOnUnitSphere(c1,c2,c3)

function co = calcCircleOnUnitSphere3(c1,c2,c3)
  x1 = c1(1);
  y1 = c1(2);
  r1 = c1(3);
  x2 = c2(1);
  y2 = c2(2);
  r2 = c2(3);
  x3 = c3(1);
  y3 = c3(2);
  r3 = c3(3);
  
  v11 = 2 * x2 - 2 * x1;
  v12 = 2*y2 - 2*y1;
  v13 = x1*x1 - x2*x2 + y1*y1 - y2*y2 - r1*r1 + r2*r2;
  v14 = 2*r2 - 2*r1;

  v21 = 2*x3 - 2*x2;
  v22 = 2*y3 - 2*y2;
  v23 = x2*x2 - x3*x3 + y2*y2 - y3*y3 - r2*r2 + r3*r3;
  v24 = 2*r3 - 2*r2;

  w12 = v12/v11;
  w13 = v13/v11;
  w14 = v14/v11;

  w22 = v22/v21-w12;
  w23 = v23/v21-w13;
  w24 = v24/v21-w14;

  P = -w23/w22;
  Q = w24/w22;
  M = -w12*P-w13;
  N = w14 - w12*Q;

  a = N*N + Q*Q - 1;
  b = M*N - N*x1 + P*Q - Q*y1 + r1;
  c = x1*x1 + M*M - 2*M*x1 + P*P + y1*y1 - 2*P*y1 - r1*r1;
  r = (- b - sqrt(b*b - a * c)) / (a);
  
  
  x = M+N*r;
  y = P+Q*r;
  
  co = [x,y,r];
  
end
  
 %end