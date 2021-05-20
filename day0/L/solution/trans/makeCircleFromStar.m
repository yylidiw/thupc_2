function t = makeCircleFromStar(x,y,z,r)
  far = [x y z];
  R = far / norm(far);
  a = atan2(R(2),R(1));
  b = acos(R(3));
  c = asin(r / norm(far));
  t = [a,b,c];
end

