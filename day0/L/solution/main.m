
%clear all;
%close all;
figure;
[fx,fy,fz] = sphere(20);
surf(fx(11:21,:), fy(11:21,:), fz(11:21,:),'LineStyle','none','Facealpha',0.35);
axis equal;
hold on

dataFile = fopen('../bqsg/data.tmp','r');
dataL = fscanf(dataFile, '%d');  
data = reshape(dataL(2:end),4,[])';

modN = floor((length(dataL)-1)/4/100);

circles = zeros(size(data,1),3);
circlesP = zeros(size(data,1),3);
for i=1:size(data,1)
  circles(i,:) = makeCircleFromStar(data(i,1),data(i,2),data(i,3),data(i,4));
  circlesP(i,:) = makeCircleFromCircle(circles(i,:));
end


result = RIA(size(circles,1),circles);
planer = makeCircleFromCircle(result);
(result(3)*2/pi*100000)
plotCirclePlane(planer);
plotCircle(result);
for i = 1:length(circles)
  if(mod(i,modN)==0)
  plotCircle(circles(i,:));
  plotCirclePlane(circlesP(i,:));
end
end