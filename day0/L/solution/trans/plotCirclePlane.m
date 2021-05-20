
function plotCirclePlane(c)
  x = c(1);y=c(2);r=c(3);
  
  theta=(0:2*pi/100:2*pi)'; %theta角从0到2*pi
  
  xd=x + r*cos(theta);%圆上各点的x坐标
  yd=y + r*sin(theta);%圆上各点的y坐标

  plot3(xd,yd,ones(size(yd)));
end
