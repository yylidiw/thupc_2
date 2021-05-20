function result = RIA(N,circles)
 ni = randperm(N);
 circles(1:N,:) = circles(ni,:);
  result = circles(1,:);
  for i = 2:N
    if(dist(result,circles(i,:)) > result(3) - circles(i,3))
      result = circles(i,:);
      for j = 1:i-1
        if(dist(result,circles(j,:)) > result(3) - circles(j,3))
          result = calcCircleOnUnitSphere2(circles(i,:),circles(j,:));
          for k = 1:j-1
            if(dist(result,circles(k,:)) > result(3) - circles(k,3))
              result = calcCircleOnUnitSphere3(circles(i,:),circles(j,:),circles(k,:));
            end
          end
        end
      end
    end
  end
end