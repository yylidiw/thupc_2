Tx=[0.282544, 0.0927109, 0.954764, 0.429516;
0.613102, 0.0704097, 0.78686, 0.135169;
0.359034, 0.397544, 0.844425, 0.573461;];

for i=1:3
  Tx(i,1:3) = Tx(i,1:3) /norm(Tx(i,1:3) ); 
  Tx(i,:) =[atan2(Tx(i,2),Tx(i,1)),acos(Tx(i,3)),Tx(i,4) 0];
end
Tx(:,4) = [];