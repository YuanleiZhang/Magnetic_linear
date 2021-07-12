clear;clc;close all;


%% Load in the result of Magnetic 
fid = fopen('B.dat','r');
    nextline2 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f ';
    size = [7,Inf];
    Data_Analytic = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Analytic = Data_Analytic';
x = Data_Analytic(:,1);
y = Data_Analytic(:,2);
z = Data_Analytic(:,3);
U_Analytic = Data_Analytic(:,4);
Bx_Analytic = Data_Analytic(:,5);
By_Analytic = Data_Analytic(:,6);
Bz_Analytic = Data_Analytic(:,7);

%% plot
Linewidth = 2;
fontsize = 15;
markersize = 5;
m=50;
n=50;
% Comparsion of magnetic potential
figure('Position',[100,300,1300,250])
subplot(1,3,1)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,Bx_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands imagesc to plot profile map
xlabel('x(m)')
ylabel('y(m)')
title('B_x(nT)')
set(gca,'fontsize',fontsize)

subplot(1,3,2)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,By_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands imagesc to plot profile map
xlabel('x(m)')
ylabel('y(m)')
title('B_y(nT)')
set(gca,'fontsize',fontsize)

subplot(1,3,3)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,Bz_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands imagesc to plot profile map
xlabel('x(m)')
ylabel('y(m)')
title('B_z(nT)')
set(gca,'fontsize',fontsize)

