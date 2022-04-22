clear;clc;close all;

%% load in result of Analytical solution
fid = fopen('MGT.dat','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f %f %f %f %f %f';
    dataSize = [12,Inf];
    Data_Analytic = fscanf(fid,formatSpec,dataSize);
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

%% load Magnet_SFe and Magnet_MFe
fid = fopen('Magnet_MFeborder.bna','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f';
    dataSize = [2,Inf];
    Magnet_MFe = fscanf(fid,formatSpec,dataSize);
fclose(fid);
% Magnet_MFe = Magnet_MFe';
% Magnet_MFe_x = Magnet_MFe(:,1);
% Magnet_MFe_y = Magnet_MFe(:,2);

fid = fopen('Magnet_SFeborder.bna','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f';
    dataSize = [2,Inf];
    Magnet_SFe = fscanf(fid,formatSpec,dataSize);
fclose(fid);

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
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('T_{xx}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(3,3,2)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tyx_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
title('T_{xy}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(3,3,3)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzx_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
title('T_{xz}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(3,3,5)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tyy_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('T_{yy}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(3,3,6)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzy_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize; 
title('T_{yz}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(3,3,9)
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Tzz_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
c = colorbar;
c.Label.String = 'nT/m';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('T_{zz}(nT/m)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

figure('Position',[100,100,800,800])
XI=linspace(min(x),max(x),m);
YI=linspace(min(y),max(y),n); 
ZI=griddata(x,y,Txx_Analytic+Tyy_Analytic+Tzz_Analytic,XI,YI.'); 
contourf(XI,YI,ZI);colorbar;
xlabel('x(m)')
ylabel('y(m)')
title('T_{xx}+T_{yy}+T_{zz}(nT/m)')
set(gca,'fontsize',fontsize)