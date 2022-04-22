#import numpy as np
from vedo import TetMesh, show, screenshot, settings, Picture, buildLUT, Box, Plotter, Axes

# Do some settings
settings.useDepthPeeling = True  # Useful to show the axes grid
settings.defaultFont = 'Kanopus'

tet = TetMesh('without_receivers.vtk')
conductor = tet.clone().threshold(name='material', above=5.5, below=7.5)

box = Box(size=(39530000, 39533800, 3434000,3438000,-1600,10.1))
tet.cutWithMesh(box, wholeCells=True)
# msh = tet.tomesh().lineWidth(1).lineColor('b')

# build a look up table for our color bar
lut_table = [
    # Value, color, alpha, category
    (2.2, 'silver', 1, 'USF'),
    (3.2, 'teal', 1, 'LSF'),
    (4.2, 'lime', 1, 'BBF'),
    (5.2, 'dodgerblue', 1, 'DP'),
    (6.2, 'yellow', 1, 'MG'),
    (7.2, 'red', 1, 'PR'),
]
lut = buildLUT(lut_table)

msh = tet.tomesh(shrink=0.95).cmap(lut, 'material', on='cells')
msh.addScalarBar3D(
    categories=lut_table,
    pos=(39534800, 3436000, -1600),
    title='Lithology',
    titleSize=1.8,
    labelSize=1.5,
    sx=150,
    sy=3000,
    titleXOffset=-1.8,    
)

# put scalarbar vertical, tell camera to keep bounds into account
#msh.scalarbar.rotateX(90, locally=True).rotateY(55, locally=True).useBounds()

# Create cmap for conductor
cond = conductor.tomesh().cmap(lut, 'material', on='cells')

zlabels = [(-500,'-500'), (-1000, '-1000')]
axes = Axes(msh + cond,
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
            yrange=(msh + cond).ybounds(),
 #           yShiftAlongX=1,
            yzShift=1,
            #xyShift=0.2
            #tipSize=0,
            yzGrid=True,
            xyGrid=True,
            gridLineWidth=5,
)
for a in axes.unpack():
    # print(a.name)
    if ("zAxis" in a.name or "zM" in a.name or "zN" in a.name
        or "yzGrid" in a.name):
        xb = msh.xbounds()
        a.shift(-(xb[1]-xb[0]), 0, 0)

size = [1600, 900]
show(msh, cond, axes,__doc__, size=size, interactive=
         True, roll=-78, azimuth=55).close()
