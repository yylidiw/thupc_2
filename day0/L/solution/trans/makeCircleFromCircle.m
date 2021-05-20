function t = makeCircleFromCircle(c)
  a = c(1);
  b = c(2);
  c = c(3);
  
  
  rb1 = (b-c)/2;
  rb2 = (b+c)/2;
  
  l1 = 2*tan(rb1);
  l2 = 2*tan(rb2);
   
  pt1 = [l1 * cos(a),l1 * sin(a)];
  pt2 = [l2 * cos(a),l2 * sin(a)];
  r = norm(pt2-pt1)/2;
  pc = (pt1+pt2)/2;
  t = [pc(1),pc(2), r];
end

