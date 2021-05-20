function t = inverseCircleFromCircle(c)
  x = c(1);
  y = c(2);
  r = c(3);
  
  l1 = sqrt(x * x + y * y)+r;
  l2 = sqrt(x * x + y * y)-r;
  
  a = atan2(y, x);
  
  b1 = 2*atan2(l1, 2);
  b2 = 2*atan2(l2, 2);
  
  b = (b1+b2)/2;
  rr = (b1-b2)/2;
  
  if(b < 0)
    a = a + pi;
    b = -b;
  end
  t = [a, b, rr];
end

