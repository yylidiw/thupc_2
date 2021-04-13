function l = dist(c1,c2)
  a1 = c1(1);b1 = c1(2);
  a2 = c2(1);b2 = c2(2);
  x1 = cos(a1)*sin(b1);y1=sin(a1)*sin(b1);z1=cos(b1);
  x2 = cos(a2)*sin(b2);y2=sin(a2)*sin(b2);z2=cos(b2);
  u = [x1,y1,z1];
  v = [x2,y2,z2];
  l = acos(u*v');
end