
%clear all;
%close all;
figure;
[fx,fy,fz] = sphere(20);
surf(fx(11:21,:), fy(11:21,:), fz(11:21,:),'LineStyle','none','Facealpha',0.35);
axis equal;
hold on

circles = zeros(size(data,1),3);
for i=1:size(data,1)
  circles(i,:) = makeCircleFromStar(data(i,1),data(i,2),data(i,3),data(i,4));
end


result = RIA(size(circles,1),circles);
(result(3)*2/pi*100000)
plotCircle(result);
for i = 1:length(circles)
    if mod(i,1672)==0
        plotCircle(circles(i,:));
    end
end