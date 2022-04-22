#!/usr/bin/env python3

import numpy as np
from vedo import TetMesh, show, screenshot, settings, Picture, buildLUT, Box, Plotter, Axes, Latex, Mesh
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
# import time as tm

# Do some settings
settings.useDepthPeeling=False  # Useful to show the axes grid
font_name = 'Kanopus'
settings.defaultFont = font_name
settings.multiSamples=8

tet = TetMesh('without_receivers.vtk')

cond = tet.clone().threshold(name='material', above=5.5, below=7.5)
bm1=tet.clone().threshold('material',above=1.5,below=5.5)
bm2=tet.clone().threshold('material',above=3.5,below=5.5)

box_cond = Box(size=(39530000, 39535000, 3434000,3438000,-1600,10.1))
cond.cutWithMesh(box_cond, wholeCells=True)
cond_msh = cond.tomesh().lineWidth(1).lineColor('w')
#print(cond.bounds())

box_bm1=Box(size=(39530000, 39532500, 3434000,3438000,-1600,10.1))
bm1.cutWithMesh(box_bm1, wholeCells=True)
bm1_msh = bm1.tomesh().lineWidth(1).lineColor('w')
# And we need to convert it to a mesh object for later plotting

box_bm2=Box(size=(39530000, 39532500, 3434000,3438000,-1600,10.1))
bm2.cutWithMesh(box_bm2, wholeCells=True)
bm2_msh = bm2.tomesh().lineWidth(1).lineColor('w')

lut_table = [
    # Value, color, alpha, category
    (2.2, 'gainsboro', 1, r'K_1 s_1'),
    (3.2, 'lightcoral', 1, r'K_1 s_2'),
    (4.2, 'green', 1, r'K_1 z'),
    (5.2, 'deepskyblue', 1, '\mu\sigma'),
    (6.2, 'orangered', 1, 'Fe_3 O_4'),
    (7.2, 'gold', 1, 'Fe_1-z S'),
]
lut = buildLUT(lut_table)
group=cond_msh+bm1_msh+bm2_msh
#msh.cmap(lut, 'material', on='cells')
cond_msh.cmap(lut, 'material', on='cells')
bm1_msh.cmap(lut, 'material', on='cells')
bm2_msh.cmap(lut, 'material', on='cells')
cond_msh.addScalarBar3D(
    categories=lut_table,
    pos=(39534300, 3438000, -600),
    title='Lithology',
    titleSize=2,
    labelSize=1.8,
    sx=120,
    sy=2800,
    titleXOffset=-1.8,
)
cond_msh.scalarbar.rotateX(112, locally=True).rotateY(35, locally=True).useBounds()

vector1 = [(39531000, 3434800, 100), (39534000, 3434800, 100), (39534000, 3438000, 100), (39531000, 3438000, 100)]
faces  = [(0,1,2,3)]
m1 = Mesh([vector1, faces])
m1.color('blueviolet', 0.3).lineColor('royalblue').lineWidth(2)

zlabels = [(-500,'-500'), (-1000, '-1000')]
axes = Axes(group,
            xtitle='Easting (m)',
            ytitle='Northing (m)',
            ztitle='Elevation (m)',
            xLabelSize=0.022,
            xTitlePosition=0.65,
            xTitleOffset=0.03,
            yTitlePosition=0.6,
            yTitleOffset=-1.15,
            yLabelRotation=90,
            yLabelOffset=-1.6,
            yLabelSize=0.022,
            zLabelSize=0.022,
            zTitlePosition=0.85,
#            zTitleOffset=0.04,
            zLabelRotation=90,
            zValuesAndLabels=zlabels,
            axesLineWidth=3,
            yrange=group.ybounds(),
 #           yShiftAlongX=1,
            yzShift=1,
            tipSize=0.,
            yzGrid=True,
            xyGrid=True,
            gridLineWidth=5,
            )
#start_point = (39351000, 3434800, 100)
#Rect = Rectangle(start_point, 4000, 3200, linewidth = 2, linestyle = '-', zorder = 2, edgecolor = 'red', facecolor = 'red')
#cond_msh.add_patch(Rect)
vig1 = m1.vignette('Observation profile', point=(39531300, 3437700, 100), s=107, offset=(500,700))
for a in axes.unpack():
    # print(a.name)
    if ("zAxis" in a.name or "zM" in a.name or "zN" in a.name
        or "yzGrid" in a.name):
        xb = group.xbounds()
        a.shift(-(xb[1]-xb[0]), 0, 0)
plt = Plotter()
plt.camera.SetPosition( [39538100, 3430600,3000.973] )
plt.camera.SetFocalPoint( [39533000, 3435000, -800.467] )
plt.camera.SetViewUp( [-0.1, 0.0001, 1.0] )
#plt.camera.SetDistance( 14415.028 )
#plt.camera.SetClippingRange( [7367.387, 23203.319] )

size = [1600, 900]
plt.show(m1, vig1, bm1_msh, cond_msh, axes, size=size, interactive=
         False, resetcam=0,zoom=1.0)
screenshot('nihe_model_vedo.png')

from wand import image

with image.Image(filename='nihe_model_vedo.png') as imag:
    imag.trim(color=None, fuzz=0)
    imag.save(filename='nihe_model_vedo.eps')
