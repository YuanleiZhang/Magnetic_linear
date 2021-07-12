#Complier  g++
CXX     	:=  g++

#Standrad C++11 ; Optimization  03 ; Use 'openmp';
CXXFLAGS    	:=  -std=c++11 -O3 -fopenmp -Wfatal-errors

#paths of source files
DIR_PLY 	:= ./src/Magnetic_Ployhedron
DIR_TET  	:= ./src/Magnetic_Tetrahedron
DIR_COM 	:= ./src/Common
DIR     	:= ./src

#include
INCLUDE_PLY	:=-I$(DIR_PLY)
INCLUDE_TET	:=-I$(DIR_TET)
INCLUDE_COM	:=-I$(DIR_COM)
INCLUDE_OTHERS	:=-I$(DIR)

#source files
SRCS		:=$(wildcard $(DIR_PLY)/*.cpp) $(wildcard $(DIR_COM)/*.cpp) $(wildcard $(DIR_TET)/*.cpp)
OBJS         	:= $(patsubst %.cpp, %.o, $(SRCS))

#---------------------------------------------------------------------------------------
all: MagPly MagTet
.PHONY: all

#link object files to executable files
MagPly: $(OBJS) ./src/MagPly.o
	$(CXX) $(CXXFLAGS) ./src/MagPly.o $(OBJS) -o MagPly 
MagTet: $(OBJS) ./src/MagTet.o
	$(CXX) $(CXXFLAGS) ./src/MagTet.o $(OBJS) -o MagTet

#compile c++ files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCLUDE_COM) $(INCLUDE_OTHERS) $(INCLUDE_PLY) $(INCLUDE_TET) -c $< -o $@
./src/MagPly.o: ./src/MagPly.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_COM) $(INCLUDE_OTHERS) $(INCLUDE_PLY) ./src/MagPly.cpp -c -o ./src/MagPly.o
./src/MagTet.o: ./src/MagTet.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_COM) $(INCLUDE_OTHERS) $(INCLUDE_PLY) $(INCLUDE_TET) ./src/MagTet.cpp -c -o ./src/MagTet.o

echo:	
	@echo -e "Source Files:\t$(SRCS)"
	@echo -e "Object Files:\t$(OBJS)"
	@echo -e "C++ Compiler:\t$(CXX)"
	@echo -e "CXXFLAGS:    \t$(CXXFLAGS)"	

.PHONY: clean
clean:
	@rm -rf *.o *~  $(OBJS) ./src/MagPly.o ./src/MagTet.o  MagPly MagTet
