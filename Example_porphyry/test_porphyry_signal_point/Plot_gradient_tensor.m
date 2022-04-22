clear;clc;close all;

%% load in result of Analytical solution
fid = fopen('MGT.dat','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f %f %f %f %f %f';
    size = [12,Inf];
    Data_Analytic = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Analytic = Data_Analytic';
x = Data_Analytic(:,1);
y = Data_Analytic(:,2);
z = Data_Analytic(:,3);
Txx_Analytic = Data_Analytic(:,4);
Tyx_Analytic = Data_Analytic(:,5);
Tzx_Analytic = Data_Analytic(:,6);
Tyy_Analytic = Data_Analytic(:,8);
Tzy_Analytic = Data_Analytic(:,9);
Tzz_Analytic = Data_Analytic(:,12);
%% plot
Linewidth = 1.5;
fontsize = 15;
markersize = 5;
m = 100;
n = 100;
figure('Position',[100,100,1300,800])
subplot(3,3,1)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,Txx_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands contourf to plot profile map
xlabel('x(m)')
ylabel('y(m)')
title('T_{xx}(nT/m)')
set(gca,'fontsize',fontsize)
subplot(3,3,2)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tyx_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar; 

title('T_{xy}(nT/m)')
set(gca,'fontsize',fontsize)
subplot(3,3,3)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzx_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar; 

title('T_{xz}(nT/m)')
set(gca,'fontsize',fontsize)
subplot(3,3,5)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tyy_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar; 
xlabel('x(m)')
ylabel('y(m)')
title('T_{yy}(nT/m)')
set(gca,'fontsize',fontsize)
subplot(3,3,6)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzy_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar; 

title('T_{yz}(nT/m)')
set(gca,'fontsize',fontsize)
subplot(3,3,9)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzz_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar; 
xlabel('x(m)')
ylabel('y(m)')
title('T_{zz}(nT/m)')
set(gca,'fontsize',fontsize)

figure('Position',[100,100,800,800])
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Txx_Analytic+Tyy_Analytic+Tzz_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
xlabel('x(m)')
ylabel('y(m)')
title('T_{xx}+T_{yy}+T_{zz}(nT/m)')
set(gca,'fontsize',fontsize)