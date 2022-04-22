import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as mcolors
plt. close()
#clrmap = mcolors.LinearSegmentedColormap.from_list("mycmap", ["magenta","blueviolet","royalblue","aqua","springgreen","lawngreen","yellow","orangered","red","white"])
clrmap = "jet"

## load in data
# load in data from file dobs_g_z
x,y,z,U,Bx,By,Bz = np.loadtxt('B.dat', unpack = True)
X_B = np.reshape(x,(21, 21), order = 'C')
Y_B = np.reshape(y,(21, 21), order = 'C')
B_x = np.reshape(Bx,(21, 21), order = 'C')
B_y = np.reshape(By,(21, 21), order = 'C')
B_z = np.reshape(Bz,(21, 21), order = 'C')

# load in data from file dpredicted_g_z
x,y,z,Txx,Tyx,Tzx,Txy,Tyy,Tzy,Txz,Tyz,Tzz = np.loadtxt('MGT.dat', unpack = True)
X_T = np.reshape(x,(21, 21), order = 'C')
Y_T = np.reshape(y,(21, 21), order = 'C')
T_xx = np.reshape(Txx,(21, 21), order = 'C')
T_xy = np.reshape(Txy,(21, 21), order = 'C')
T_xz = np.reshape(Txz,(21, 21), order = 'C')
T_yy = np.reshape(Tyy,(21, 21), order = 'C')
T_yz = np.reshape(Tyz,(21, 21), order = 'C')
T_zz = np.reshape(Tzz,(21, 21), order = 'C')
## plot setting
Fontsize = 8
Fontsize_Axis = 12
Linewidth = 0.5

fig1 = plt.figure(num = 1, figsize = (20, 15), dpi = 80)
ax1 = fig1.add_subplot(4,3,1)
cset = plt.contourf(X_B, Y_B, B_x, 10, cmap = clrmap)
contour = plt.contour(X_B, Y_B, B_x, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis) # 色标刻度字体大小
#cb.set_label('$Unit : nT$', fontsize = Fontsize_Axis) #设置colorbar的标签字体及其大小
cb.ax.set_title(r'$(nT)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax1.spines['top'].set_linewidth(1.5)
ax1.spines['right'].set_linewidth(1.5)
ax1.spines['bottom'].set_linewidth(1.5)
ax1.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('$B_x$', fontsize = Fontsize_Axis, pad = 8)

ax2 = fig1.add_subplot(4,3,2)
cset = plt.contourf(X_B, Y_B, B_y, 10, cmap = clrmap)
contour = plt.contour(X_B, Y_B, B_y, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
# plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${B_y}$', fontsize = Fontsize_Axis, pad = 8)

ax3 = fig1.add_subplot(4,3,3)
cset = plt.contourf(X_B, Y_B, B_z, 10, cmap = clrmap)
contour = plt.contour(X_B, Y_B, B_z, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT)$',fontsize = Fontsize_Axis, loc = "left", pad = 25) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
# plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${B_z}$', fontsize = Fontsize_Axis, pad = 8)

ax4 = fig1.add_subplot(4,3,4)
cset = plt.contourf(X_T, Y_T, T_xx, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_xx, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_xx}$', fontsize = Fontsize_Axis, pad = 15)

ax5 = fig1.add_subplot(4,3,5)
cset = plt.contourf(X_T, Y_T, T_xy, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_xy, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
# plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_xy}$', fontsize = Fontsize_Axis, pad = 15)

ax6 = fig1.add_subplot(4,3,6)
cset = plt.contourf(X_T, Y_T, T_xz, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_xz, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
# plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_xz}$', fontsize = Fontsize_Axis, pad = 8)

ax7 = fig1.add_subplot(4,3,8)
cset = plt.contourf(X_T, Y_T, T_yy, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_yy, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_yy}$', fontsize = Fontsize_Axis, pad = 15)

ax8 = fig1.add_subplot(4,3,9)
cset = plt.contourf(X_T, Y_T, T_yz, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_yz, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
# plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
# plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_yz}$', fontsize = Fontsize_Axis, pad = 15)

ax9 = fig1.add_subplot(4,3,12)
cset = plt.contourf(X_T, Y_T, T_zz, 10, cmap = clrmap)
contour = plt.contour(X_T, Y_T, T_zz, colors = 'k', linestyles = '--')
plt.clabel(contour, fontsize = Fontsize, colors = 'r', fmt = '%.1f') # 调整等值线的字号、颜色、小数
cb = plt.colorbar(cset, orientation='vertical')#方向
cb.ax.tick_params(labelsize = Fontsize_Axis - 5) # 色标刻度字体大小
cb.ax.set_title(r'$(nT/m)$',fontsize = Fontsize_Axis, loc = "left", pad = 8) 
cb.formatter.set_scientific(True) # 科学计数法
cb.formatter.set_powerlimits((0,0))
cb.ax.yaxis.get_offset_text().set_fontsize(Fontsize_Axis - 5)#改变bar顶部字体大小
cb.update_ticks()
#设置边框粗细 —— set_visible(False)去掉边框
ax2.spines['top'].set_linewidth(1.5)
ax2.spines['right'].set_linewidth(1.5)
ax2.spines['bottom'].set_linewidth(1.5)
ax2.spines['left'].set_linewidth(1.5)
# 坐标轴字体用 Latex
plt.xlabel('$x/(m)$', fontsize = Fontsize_Axis)
plt.ylabel('$y/(m)$', fontsize = Fontsize_Axis)
plt.xticks(fontsize = Fontsize_Axis)
plt.yticks(fontsize = Fontsize_Axis)
plt.title('${T_zz}$', fontsize = Fontsize_Axis, pad = 15)


plt.savefig('plot_sci.png',dpi=300,bbox_inches='tight')

plt.show()
