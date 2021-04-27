function t = makeStarFromCircle(na,nb,nr,L)
  ncenter = [cos(na) * sin(nb), sin(na) * sin(nb), cos(nb)];  
  rcenter = round(L * ncenter);
  rr = round(L * sin(nr));
  t = [rcenter,rr];
end

