clear;clc;close all;


%% Load in the result of Magnetic 
fid = fopen('B.dat','r');
    nextline2 = fgetl(fid);
    formatSpec = '%f %f %f %f %f %f %f ';
    dataSize = [7,Inf];
    Data_Analytic = fscanf(fid,formatSpec,dataSize);
fclose(fid);
Data_Analytic = Data_Analytic';
x = Data_Analytic(:,1);
y = Data_Analytic(:,2);
z = Data_Analytic(:,3);
U_Analytic = Data_Analytic(:,4);
Bx_Analytic = Data_Analytic(:,5);
By_Analytic = Data_Analytic(:,6);
Bz_Analytic = Data_Analytic(:,7);

%% load Magnet_SFe and Magnet_MFe
fid = fopen('Magnet_MFeborder.bna','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f';
    dataSize = [2,Inf];
    Magnet_MFe = fscanf(fid,formatSpec,dataSize);
fclose(fid);

fid = fopen('Magnet_SFeborder.bna','r');
    nextline1 = fgetl(fid);
    formatSpec = '%f %f';
    dataSize = [2,Inf];
    Magnet_SFe = fscanf(fid,formatSpec,dataSize);
fclose(fid);

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
c = colorbar;
c.Label.String = 'nT';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('B_x(nT)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(1,3,2)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,By_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands imagesc to plot profile map
c = colorbar;
c.Label.String = 'nT';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('B_y(nT)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end

subplot(1,3,3)
XI=linspace(min(x),max(x),m); %divide X axis into m parts
YI=linspace(min(y),max(y),n); %divide Y axis into n parts
ZI=griddata(x,y,Bz_Analytic,XI,YI.'); %obtain the Z matrix
contourf(XI,YI,ZI);colorbar; %use commands imagesc to plot profile map
c = colorbar;
c.Label.String = 'nT';
c.Label.HorizontalAlignment = 'right';
c.FontSize = fontsize;
c.Label.FontSize = fontsize;
xlabel('x(m)')
ylabel('y(m)')
title('B_z(nT)')
set(gca,'fontsize',fontsize)
for i = 1 : size(Magnet_MFe, 2) - 1
    line([Magnet_MFe(1, i),Magnet_MFe(1,i + 1)],[Magnet_MFe(2, i),Magnet_MFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'y');  %连接节点line([x1,x2],[y1,y2])
    hold on
end
for i = 1 : size(Magnet_SFe, 2) - 1
    line([Magnet_SFe(1, i),Magnet_SFe(1,i + 1)],[Magnet_SFe(2, i),Magnet_SFe(2,i + 1)], 'linestyle', '-', 'LineWidth', 2,'color', 'r');  %连接节点line([x1,x2],[y1,y2])
    hold on
end