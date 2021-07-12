# M3D_Linear
It's a C++ program for computing magnetic potential, magnetic fields and magnetic gradient tensors caused by polyhedrons with linear magnetization contrasts and homogeneous magnetization. 

## 1.Magply

The command to use  '**MagPly**' is 
```
MagPly model_file observation_file output_file field_flag
```
The 'field_flag' can be 'm_b' or 'm_t'. The 'm_b' is used to calculate the magnetic potential and magnetic field, and the 'm_t' is used to calculate the magnetic gradient tensor.

**Model_file**
The 'model_file' is a file containing descriptions about polyhedrons. The format for the model file is 
```
*********************************************************************************
First line: <Number of polyhedrons n> 
Following lines: <Description of polyhedron 0>
                 <Description of polyhedron 1>
                 ...
                 <Description of polyhedron n-1>
*********************************************************************************
```
where the format for <descriptoin of polyhedron i\> is
```
One line: <index of this polyhedron> <number of nodes> <number of facets>
Following lines list nodes:
  <index of this node> <x> <y> <z>
  ...
Following lines list facets:
  <index of this facet> <number of corners> <corner 1> <corner 2> ...
Folowing lines list polynomial coefficients of polynomial magnetization contrast. This program only supports the calculation of linear and constant functions now. The calculation of higher-order needs to be improved, it can be temporarily set to '0' :
  a000
  a100  a010  a001
Folowing lines list the dircetion of magnetized, an unit vector isn't necessary:
  Mx    My    Mz
```
Given the polynomial coefficients in the model file, the polynomial magnetization contrast is
```
a000
+ a100*x   + a010*y     + a001*z
```

In the model file, all polyhedrons, facets of a single polyhedron,and corners of a single facet are numbered from zero. The units for x, y, z are meter, and the unit for magnetization is A/m.

**Observation_file**
The format for files containing observation points is given as
```
*********************************************************************************
First line: <Number of points>
Following lines list coordinates of points:
            <index of this point> <x> <y> <z>
            ...
*********************************************************************************
```
The obervation points can be numbered from zero or one.  Comments in the files are prefixed by charactor '#'.

**Output_file**
The 'Output_file' is a file containing the result of calculation, readers can name it according to their preferances.

An example is given in the folder '/Example_polyhedron/Prism_linearDM_test_xy/'.

## 2.MagTet
This is a program for forward modelling of magnetic fields and magnetic gradient tensor using tetrahedral unstructured grids.

The command for '**MagTet**' is
```
MagTet configuration_file
```
The configuration file contains information about mesh files and density contrasts of different regions. The format is
```
*********************************************************************************
<input file name>
<observation point file name>
<order of polynomial density contrast> #0, 1
<number of regions> # agree with the number of regions specified in *.poly file
<marker> #region marker
<polynomial coefficients of magnetization contrast>
<magnetized direction of each region>
...      # next region
*********************************************************************************

The polynomial coefficients given in the file as
```
a000
a100  a010  a001
Mx	My	Mz
Attention:This program only supports the calculation of linear and constant functions now. The calculation of higher-order needs to be improved, it can be temporarily set to '0'.
```
will define the following density contrast:
```
a000
+ a100*x   + a010*y     + a001*z
```

An example is given in the folder '/Example_porphyry/test_porphyry/' .

## 3.Citation
Use the following citations to reference our codes:

## 4.Notice
This version of the code is limited to calculate the analytical solution of polyhedral bodies with linear and constant-order magnetization contrsat. Higher-order implementations are theoretically feasible, which are introduced in our paper. Welcome to optimize our algorithm!

## 5.Author
- Yuanlei Zhang
Central south university, changsha, China
yuanleizhang@csu.edu.cn
2021-07-12
- Yiyuan Zhong
Central south university, changsha, China
zhongyiyuan@csu.edu.cn
2021-07-12
- Zhengyong Ren
Central south university, changsha, China
renzhengyong@csu.edu.cn
2021-07-12
