clear;clc;close all;

%% Load in the result of Guass_Integral
fid = fopen('Numeric_prism_order_m_b512out.txt','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f ';
    size = [7,Inf];
    Data_Guass = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Guass = Data_Guass';
x = Data_Guass(:,1);
y = Data_Guass(:,2);
z = Data_Guass(:,3);
U_Guass = Data_Guass(:,4);
Bx_Guass = Data_Guass(:,5);
By_Guass = Data_Guass(:,6);
Bz_Guass = Data_Guass(:,7);

%% Load in the result of Magnetic analytic solution
fid = fopen('magnetic_linear_fields_out_prism_site','r');
    nextline2 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f ';
    size = [7,Inf];
    Data_Analytic = fscanf(fid,formatSpec,size);
fclose(fid);
Data_Analytic = Data_Analytic';
% x = Data_Analytic(:,1);
% y = Data_Analytic(:,2);
% z = Data_Analytic(:,3);
U_Analytic = Data_Analytic(:,4);
Bx_Analytic = Data_Analytic(:,5);
By_Analytic = Data_Analytic(:,6);
Bz_Analytic = Data_Analytic(:,7);

%% plot
Linewidth = 2;
fontsize = 13;
markersize = 5;
% Comparsion of magnetic potential
figure('Position',[100,600,800,400])
subplot(1,2,1)
plot(x,U_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,U_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Maghetic Potential')
axis([-5 25 -5e-5 15e-5]); % ������������ָ��������
% legendon = legend('Guass integral','Analytic solution');
% set(legendon,'box','off')
set(gca,'fontsize',fontsize)
subplot(1,2,2)
plot(x,100*(U_Guass-U_Analytic)./U_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Relative error of U(%)')
% axis([-5 25 -1e-10 1e-10]); % ������������ָ��������
set(gca,'fontsize',fontsize)

% Comparsion of magnetic fields components
figure1 = figure('Position',[300,100,800,800])
subplot(3,2,1)
plot(x,Bx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Bx_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('B_x of Maghetic field(nT)')
% axis([-5 25 -1e4 1e4]); 
legendon = legend('Guass integral','Analytic solution');
set(legendon,'box','off')
set(gca,'fontsize',fontsize)
subplot(3,2,2)
plot(x,100*(Bx_Guass-Bx_Analytic)./Bx_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Relative error of B_x(%)')
axis([-5 25 -4e-11 4e-11]); 
set(gca,'fontsize',fontsize)

%figure('Position',[100,100,800,400])
subplot(3,2,3)
plot(x,By_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,By_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('B_y of Maghetic field(nT)')
% axis([-5 25 -15e3 10e3]); 
% legendon = legend('Guass integral','Analytic solution');
set(gca,'fontsize',fontsize)
% set(legendon,'box','off')
subplot(3,2,4)
plot(x,100*(By_Guass-By_Analytic)./By_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Relative error of B_y(%)')
axis([-5 25 -6e-11 4e-11]); 
set(gca,'fontsize',fontsize)

%figure('Position',[300,100,800,400])
subplot5 = subplot(3,2,5)
plot(x,Bz_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
hold on
plot(x,Bz_Analytic,'k-.','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('B_z of Maghetic field(nT)')
% axis([-5 25 -1.0e4 2.0e4]); 
set(gca,'fontsize',fontsize)
% set(legendon,'box','off')
subplot(3,2,6)
plot(x,100*(Bz_Guass-Bz_Analytic)./Bz_Guass,'ko','Markersize',markersize,'Linewidth',Linewidth)
xlabel('x(m)')
ylabel('Relative error of B_z(%)')
% axis([-5 25 -8e-11 2e-11]); 
set(gca,'fontsize',fontsize)