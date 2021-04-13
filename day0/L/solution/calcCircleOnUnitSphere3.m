% circle = [alpha(lon) beta(la) radius(arc)]
%function c = calcCircleOnUnitSphere(c1,c2,c3)

%c1 = [0,0,0];
%c2 = [0,pi/2,0];
%c3 = [pi/2,pi/2,0];

function c = calcCircleOnUnitSphere3(c1,c2,c3)
  a1 = c1(1);b1 = c1(2);r1 = c1(3);
  a2 = c2(1);b2 = c2(2);r2 = c2(3);
  a3 = c3(1);b3 = c3(2);r3 = c3(3);
  
  x1 = cos(a1)*sin(b1);y1=sin(a1)*sin(b1);z1=cos(b1);
  x2 = cos(a2)*sin(b2);y2=sin(a2)*sin(b2);z2=cos(b2);
  x3 = cos(a3)*sin(b3);y3=sin(a3)*sin(b3);z3=cos(b3);
  
  M = [x1 y1 z1;x2 y2 z2;x3 y3 z3];
  N = [cos(r1) sin(r1);cos(r2) sin(r2);cos(r3) sin(r3);];
  
  A = M\N;
  T = A'*A;
  u = T(1,1);
  v = T(1,2);
  w = T(2,2);
  
  tg = (-v - sqrt(v*v - (u-1)*(w-1)))/(w-1); 
  if(tg < 0)
    tg = (-v + sqrt(v*v - (u-1)*(w-1)))/(w-1);
  end
  r = atan(tg);
  
  R = A*[cos(r);sin(r)];
  a = atan2(R(2),R(1));
  b = acos(R(3));
  c=[a b r];
end
  
 %end