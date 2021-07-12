/*
 *Magnetic.h is used to caculate the linear magnetic contrast  polyhedral's magnetic_potential(U) ,
    magnetic field component(Bx,By,Bz) and magnetic gradient tensor(Txx - Tzz(6 components))
 * Copyright  2020
 * Yuanlei Zhang
 * Central South University
 ******************************************************************/

#include"Integral.h"
#include"Polyhedral.h"
#include"Dyadic.h"

class Magnetic
{
	public:
		Magnetic();
		~Magnetic();
		double U_const(const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M);
		Point B_const(const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M);
		Dyadic T_const(const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M);

		double U_linear(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M);
		Point B_linear(const Polyhedral& pol,const Point& ob, const double& a, const double& b, const double& c, const Point& M);
		Dyadic T_linear(const Polyhedral& pol,const Point& ob, const double& a, const double& b, const double& c, const Point& M);

		//******Caculate of Magnetic Linear Polyhedal***************//
		double U_1st(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M);
		Point B_1st(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M);
		Dyadic T_1st(const Polyhedral& pol,const Point& ob, const double& a, const double& b, const double& c, const Point& M);
	private:
		Point ex;
		Point ey;
		Point ez;
};

