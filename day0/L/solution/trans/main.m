
%clear all;
close all;
figure;
[fx,fy,fz] = sphere(20);
surf(fx(11:21,:), fy(11:21,:), fz(11:21,:),'LineStyle','none','Facealpha',0.35);
axis equal;
hold on
dataFile = fopen('../../bqsg/data.tmp','r');
dataL = fscanf(dataFile, '%d');  
data = reshape(dataL(2:end),4,[])';

modN = floor((length(dataL)-1)/4/100);

circlesR = zeros(size(data,1),3);
circles = zeros(size(data,1),3);
for i=1:size(data,1)
  circlesR(i,:) = makeCircleFromStar(data(i,1),data(i,2),data(i,3),data(i,4));
  circles(i,:) = makeCircleFromCircle(circlesR(i,:));
end


planer = RIA(size(circles,1),circles);
result = inverseCircleFromCircle(planer);
(result(3)*2/pi*100000)


plotCirclePlane(planer);
plotCircle(result);
for i = 1:length(circles)
  if(mod(i,modN)==0)
    plotCirclePlane(circles(i,:));
    plotCircle(circlesR(i,:));
  end
end