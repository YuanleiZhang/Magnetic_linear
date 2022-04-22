#!/usr/bin/env python3

import numpy as np
from vedo import TetMesh, show, screenshot, settings, Picture, buildLUT, Box, \
    Plotter, Axes

import time as tm

# Do some settings
settings.useDepthPeeling=True  # Useful to show the axes grid
font_name = 'Theemim'
settings.defaultFont = font_name
settings.multiSamples=8

tet = TetMesh('without_receivers.vtk')

cond = tet.clone().threshold(name='material', above=5.5, below=7.5)

box_cond = Box(size=(39530000, 39533800, 3434000,3438000,-1200,10.1))
cond.cutWithMesh(box_cond, wholeCells=True)
cond_msh = cond.tomesh().lineWidth(1).lineColor('w')
# print(cond.bounds())

lut_table = [
    # Value, color, alpha, category
    (2.2, 'white', 1, 'USF'),
    (3.2, 'dodgerblue', 1, 'LSF'),
    (4.2, 'skyblue', 1, 'BBF'),
    (5.2, 'green', 1, 'DP'),
    (6.2, 'gold', 1, 'MG'),
    (7.2, 'red', 1, 'PR'),
]
lut = buildLUT(lut_table)
#msh.cmap(lut, 'material', on='cells')
cond_msh.cmap(lut, 'material', on='cells')
#cond_msh.addScalarBar3D(
#    categories=lut_table,
#    pos=(39534600, 3436000, -1600),
#    title='Lithology',
#    titleSize=1.5,
#    sx=100,
#    sy=3000,
#    titleXOffset=-2.5,
#)

zlabels = [(-700, '-700'), (-1000, '-1000')]
axes = Axes(cond_msh,
            xtitle='Easting (m)',
            ytitle='Northing (m)',
            ztitle='Elevation (m)',
            xLabelSize=0.022,
            xTitleOffset=0.03,
            xTitlePosition=0.65,
            yTitlePosition=0.6,
            yTitleOffset=-1.14,
            yLabelRotation=90,
            yLabelOffset=-1.5,
            yLabelSize=0.022,
            zTitlePosition=0.85,
            zLabelSize=0.022,
            zTitleOffset=0.02,
            zLabelRotation=90,
#            zValuesAndLabels=zlabels,
            axesLineWidth=3,
            yrange=cond_msh.ybounds(),
 #           yShiftAlongX=1,
            yzShift=1,
            tipSize=0.,
            yzGrid=True,
            xyGrid=True,
            gridLineWidth=5,
            )

for a in axes.unpack():
    # print(a.name)
    if ("zAxis" in a.name or "zM" in a.name or "zN" in a.name
        or "yzGrid" in a.name):
        xb = cond_msh.xbounds()
        a.shift(-(xb[1]-xb[0]), 0, 0)
# plt = Plotter()
# plt.camera.SetPosition( [39534900, 3434100,500] )
# plt.camera.SetFocalPoint( [39533300, 3435600, -800.467] )
# plt.camera.SetViewUp( [-0.1, 0.1, 1.0] )

#plt.camera.SetDistance( 14415.028 )
#plt.camera.SetClippingRange( [7367.387, 23203.319] )

show(cond_msh, axes, __doc__, size=(1600, 900),
          roll=-80, azimuth=50, elevation=-10, zoom=1.25).close()
# size = [1600, 900]
# plt.show(cond_msh,axes,size=size, interactive=
#          False, resetcam=0,zoom=1.0)
screenshot('nihe_conductivity_vedo.png')

from wand import image

with image.Image(filename='nihe_conductivity_vedo.png') as imag:
    imag.trim(color=None, fuzz=0)
    imag.save(filename='nihe_conductivity_vedo.eps')
