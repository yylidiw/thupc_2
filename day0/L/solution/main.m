
%clear all;
%close all;
figure;
[fx,fy,fz] = sphere(20);
surf(fx(11:21,:), fy(11:21,:), fz(11:21,:),'LineStyle','none','Facealpha',0.35);
axis equal;
hold on
circles = [
  makeCircleFromStar(30,10,10,9);
  makeCircleFromStar(100,-10,100,50);
  makeCircleFromStar(-30,100,50,30);
  makeCircleFromStar(12,42,64,20);
  makeCircleFromStar(287,123,46,31);
];


result = RIA(5,circles);
(result(3)*2/pi*100000)
plotCircle(result);
plotCircle(circles(1,:));
plotCircle(circles(2,:));
plotCircle(circles(3,:));
plotCircle(circles(4,:));
plotCircle(circles(5,:));