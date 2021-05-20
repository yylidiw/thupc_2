function c = calcCircleOnUnitSphere2(c1,c2)
  r1 = c1(3);r2=c2(3);
  x1=c1(1:2);x2=c2(1:2);
  l = norm(x2 - x1);
  r = (l + r1 + r2) / 2;
  v = r - r2;
  cc = v / l * (x1 - x2) + x2;
  c=[cc(1) cc(2) r];
end
  