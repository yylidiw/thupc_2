function c = calcCircleOnUnitSphere2(c1,c2)
  
  a1 = c1(1);b1 = c1(2);r1 = c1(3);
  a2 = c2(1);b2 = c2(2);r2 = c2(3);
  
  x1 = cos(a1)*sin(b1);y1=sin(a1)*sin(b1);z1=cos(b1);
  x2 = cos(a2)*sin(b2);y2=sin(a2)*sin(b2);z2=cos(b2);
  
  
  u = [x1,y1,z1];
  v = [x2,y2,z2];
  
  
  r = (acos(u*v')+r1+r2)/2;
  
  n = cross(u,v);
  n = n / norm(n);
  q = cross(n,u);
  q = q / norm(q);
  R = u*cos(r-r1)+q*sin(r-r1);
  a = atan2(R(2),R(1));
  b = acos(R(3));
  c=[a b r];
end
  