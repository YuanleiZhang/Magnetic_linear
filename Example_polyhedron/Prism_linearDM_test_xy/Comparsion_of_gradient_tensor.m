clear;clc;close all;

%% Load in the result of Guass_Integral
fid = fopen('Numeric_prism_order_m_t512out.txt','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f %f %f';
    size = [9,Inf];
    Data_Guass = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Guass = Data_Guass';
x = Data_Guass(:,1);
y = Data_Guass(:,2);
z = Data_Guass(:,3);
Txx_Guass = Data_Guass(:,4);
Tyx_Guass = Data_Guass(:,5);
Tzx_Guass = Data_Guass(:,6);
Tyy_Guass = Data_Guass(:,7);
Tzy_Guass = Data_Guass(:,8);
Tzz_Guass = Data_Guass(:,9);
%% load in result of Analytical solution
fid = fopen('magnetic_linear_tensor_out_prism_site','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f %f %f';
    size = [9,Inf];
    Data_Analytic = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Analytic = Data_Analytic';
x = Data_Analytic(:,1);
y = Data_Analytic(:,2);
z = Data_Analytic(:,3);
Txx_Analytic = Data_Analytic(:,4);
Tyx_Analytic = Data_Analytic(:,5);
Tzx_Analytic = Data_Analytic(:,6);
Tyy_Analytic = Data_Analytic(:,7);
Tzy_Analytic = Data_Analytic(:,8);
Tzz_Analytic = Data_Analytic(:,9);
%% plot
Linewidth = 1.5;
fontsize = 12;
markersize = 5;
% Comparsion of magnetic potential
figure('Position',[100,100,1000,600])
subplot(3,3,1)
plot(x,Txx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Txx_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('T_{xx}(nT/m)')
%axis([-5 25 -1e3 2e3]);
legendon = legend('Guass integral','Analytic solution');
set(gca,'fontsize',fontsize)
set(legendon,'box','off')
subplot(3,3,2)
plot(x,Tyx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Tyx_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
ylabel('T_{xy}(nT/m)')
%axis([-5 25 -1e3 1e3]);
set(gca,'fontsize',fontsize)
subplot(3,3,3)
plot(x,Tzx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Tzx_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
ylabel('T_{xz}(nT/m)')
axis([-5 25 -2e3 2e3]);
set(gca,'fontsize',fontsize)
subplot(3,3,5)
plot(x,Tyy_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Tyy_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('T_{yy}(nT/m)')
%axis([-5 25 -2e3 2e3]);
set(gca,'fontsize',fontsize)
subplot(3,3,6)
plot(x,Tzy_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Tzy_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
ylabel('T_{yz}(nT/m)')
% axis([-5 25 -1e3 3e3]);
set(gca,'fontsize',fontsize)
subplot(3,3,9)
plot(x,Tzz_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Tzz_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('T_{zz}(nT/m)')
%axis([-5 25 -4e3 2e3]);
set(gca,'fontsize',fontsize)
%% Laplace validation
figure('Position',[100,100,600,400])
plot(y,Txx_Guass+Tyy_Guass+Tzz_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(y,Txx_Analytic+Tyy_Analytic+Tzz_Analytic,'k+','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('T_{xx}+T_{yy}+T_{zz}(nT/m)')
legendon = legend('Guass integral','Analytic solution');
set(legendon,'box','off')
%axis([-5 25 -1.5e-11 1.5e-11]);
set(gca,'fontsize',fontsize)

%% Realtive error 
figure('Position',[300,100,1000,600])
subplot(3,3,1)
plot(x,100*(Txx_Guass - Txx_Analytic)./Txx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Realtive error(%)')
title('T_{xx}')
axis([-5 25 -5e-11 5e-11]);
set(gca,'fontsize',fontsize)
subplot(3,3,2)
plot(x,100*(Tyx_Guass - Tyx_Analytic)./Tyx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
title('T_{xy}')
axis([-5 25 -1e-11 5e-11]);
set(gca,'fontsize',fontsize)
subplot(3,3,3)
plot(x,100*(Tzx_Guass - Tzx_Analytic)./Tzx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
title('T_{xz}')
axis([-5 25 -1e-11 1e-11]);
set(gca,'fontsize',fontsize)
subplot(3,3,5)
plot(x,100*(Tyy_Guass - Tyy_Analytic)./Txx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Realtive error(%)')
title('T_{yy}')
axis([-5 25 -1e-11 5e-11]);
set(gca,'fontsize',fontsize)
subplot(3,3,6)
plot(x,100*(Tzy_Guass - Tzy_Analytic)./Tzy_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
title('T_{zy}')
axis([-5 25 -1e-11 1e-11]);
set(gca,'fontsize',fontsize)
subplot(3,3,9)
plot(x,100*(Tzz_Guass - Tzz_Analytic)./Tzz_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Realtive error(%)')
title('T_{zz}')
axis([-5 25 -5e-12 1e-12]);
set(gca,'fontsize',fontsize)