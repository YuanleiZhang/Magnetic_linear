#include "Magnetic.h"

Magnetic::Magnetic()
{
	ex.setPoint(1., 0., 0.);
	ey.setPoint(0., 1., 0.);
	ez.setPoint(0., 0., 1.);
}

Magnetic::~Magnetic(){}

/*************************************************Magnetic_Const******************************************************/
double Magnetic::U_const (const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M)
{
	double result = 0.0;
	double R_1 = 0.;
	Point M_e = M.getUnit();
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i]; 
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		R_1 = Integral::Surface_R_1(ob, face_node, pol.face_node_number[i]);
		result += M_e*unit_normal * R_1;
	}
	result *= C*const_magnetic;
	return result;
}
Point Magnetic::B_const(const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M)
{
	Point result (0., 0., 0.);
	double R_1 = 0.;
	double R_3 = 0.;
	double h_i = 0.0;
	Point M_e = M.getUnit();
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i]; 
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		h_i = (pol.face_normal_vector[i] * (ob - *face_node[0]));
		int n = pol.faces[i].size();
		R_3 = Integral::Surface_R_3(ob, face_node, pol.face_node_number[i]);
		//cout << "result_S_R_3" << R_3 << endl;
		Point temp(0., 0., 0.);
		for (int j = 0;j < n; j++)
		{
			int j_next = (j + 1) % n;
			Point m_ij = unitCross(unit_normal, *face_node[j] - *face_node[j_next]);
			R_1 = Integral::Line_R_1(ob, *face_node[j], *face_node[j_next]);
			temp +=  m_ij*R_1;
		}
		result += unit_normal*M_e*(temp + h_i *unit_normal *R_3);
	}
	result *= C*const_magnetic*1e09;  //unit :nT
	//result.display();
	return result;
}

Dyadic Magnetic::T_const(const Polyhedral& pol, const Point& ob, const double& const_magnetic, const Point& M)
{
	Dyadic result;
	//double h_i = 0.;
	Point M_e = M.getUnit();
 	Dyadic temp;
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i]; 
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		//h_i = (pol.face_normal_vector[i] * (ob - *face_node[0]));
		//cout << "23333333333333333333333333333::" <<endl;
		result.xx = 3.*Integral::Surface_x2R_5(ob, face_node, pol.face_node_number[i]) - Integral::Surface_R_3(ob, face_node, pol.face_node_number[i]);
		result.xy = 3.*Integral::Surface_xyR_5(ob, face_node, pol.face_node_number[i]);
		result.yx = result.xy;
		result.xz = 3.*Integral::Surface_xzR_5(ob, face_node, pol.face_node_number[i]);	
		result.zx = result.xz;
		result.yy = 3.*Integral::Surface_y2R_5(ob, face_node, pol.face_node_number[i]) - Integral::Surface_R_3(ob, face_node, pol.face_node_number[i]);
		result.yz = 3.*Integral::Surface_yzR_5(ob, face_node, pol.face_node_number[i]);
		result.zy = result.yz;
		result.zz = 3.*Integral::Surface_z2R_5(ob, face_node, pol.face_node_number[i]) - Integral::Surface_R_3(ob, face_node, pol.face_node_number[i]);

		temp = temp +  (unit_normal*M_e)*result ;
	}
	temp = temp*const_magnetic*(-1.)*C*1e09;
	return temp;
}
/**********************************************************Magnetic_linear*************************************************************/
double Magnetic::U_linear(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	 Point L_T(a, b, c);
	Point M_e = M.getUnit();
	double result = 0.0;
	double h_i = 0.0;
	Point rR_1(0., 0., 0.);
	double R_1 = 0.;
	double temp1 = 0., temp2 = 0.;
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i];  
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		h_i = (unit_normal * (ob - *face_node[0]));	
		rR_1 = Integral::Surface_rR_1(ob, face_node, pol.face_node_number[i]);
		R_1 = Integral::Surface_R_1(ob, face_node, pol.face_node_number[i]);
		temp1 += unit_normal*(rR_1* L_T)*M_e;
		temp2 += h_i*R_1*(L_T*M_e);
	}
	result  = temp1 + 0.5*temp2;  //+ 
	result *= C;
	return result;
}

Point Magnetic::B_linear(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	Point L_T;
	L_T.setPoint(a,b,c);
	Point M_e = M.getUnit();
	Point result (0.0,0.0,0.0);	
	double h_i = 0.0;
	Point rR_1;
	Point rR_3;
	double R_1;
	Point temp1(0., 0., 0.);
	Point temp2(0., 0., 0.);
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i];  
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		h_i = pol.face_normal_vector[i] * (ob - *face_node[0]);
		int n = pol.faces[i].size();
		rR_3 = Integral::Surface_rR_3(ob,face_node,pol.face_node_number[i]);
		R_1 = Integral::Surface_R_1(ob,face_node,pol.face_node_number[i]);
		Point temp_result(0.0, 0.0, 0.0);
		for (int j = 0;j < n; j++)
		{
			int j_next = (j + 1) % n;
			Point m_ij = unitCross(unit_normal, *face_node[j] - *face_node[j_next]);
			rR_1 = Integral::Line_rR_1(ob, *face_node[j], *face_node[j_next]);
			temp_result = temp_result + m_ij*(L_T*rR_1);
		}
		temp1 += unit_normal*M_e*(temp_result + unit_normal*(h_i*(L_T*rR_3)) + ((unit_normal*L_T)*unit_normal - L_T)*R_1);   // +
		temp2 +=  unit_normal*(L_T*M_e)*R_1;
	}
	result += temp1 - temp2;
	result *= C*1e09;   //Unit :nT
	return result;
}

Dyadic Magnetic::T_linear(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	//cout << "run here!!!" << endl;
	Dyadic result;
	Point M_e = M.getUnit();
	Point L_T;
	L_T.setPoint(a,b,c);
	double h_i = 0.0;
 	Dyadic temp, temp1, temp2;
	 //ob.display();
	for (int i = 0; i < pol.face_number; i++)
	{
		const vector<Node*>& face_node = pol.faces[i]; 
		int num = pol.face_node_number[i];
		Point unit_normal = unitCross(*face_node[1] - *face_node[0], *face_node[2] - *face_node[1]);
		//unit_normal.display();
		h_i = unit_normal * (ob - *face_node[0]);
		double x3R_5 = 0., y3R_5 = 0., z3R_5 = 0., x2yR_5 = 0., x2zR_5= 0., y2xR_5= 0., y2zR_5= 0., z2xR_5 = 0., z2yR_5 = 0., xyzR_5 = 0.;
		Integral::Surface_f3R_5(ob, face_node, num, x3R_5, y3R_5, z3R_5,x2yR_5,x2zR_5,y2xR_5,y2zR_5,z2xR_5,z2yR_5,xyzR_5);
		result.xx = 3.*a*x3R_5 + 3*b*x2yR_5 + 3*c*x2zR_5 - a*Integral::Surface_rR_3(ob, face_node, num).x - b*Integral::Surface_rR_3(ob, face_node, num).y - c*Integral::Surface_rR_3(ob, face_node, num).z;
		result.yy = 3.*a*y2xR_5 + 3*b*y3R_5 + 3*c*y2zR_5 - a*Integral::Surface_rR_3(ob, face_node, num).x - b*Integral::Surface_rR_3(ob, face_node, num).y - c*Integral::Surface_rR_3(ob, face_node, num).z;
		result.zz = 3.*a*z2xR_5 + 3*b*z2yR_5 + 3*c*z3R_5 - a*Integral::Surface_rR_3(ob, face_node, num).x - b*Integral::Surface_rR_3(ob, face_node, num).y - c*Integral::Surface_rR_3(ob, face_node, num).z;
		result.xy = 3.*a*x2yR_5 + 3*b*y2xR_5 + 3*c*xyzR_5;
		result.yx = result.xy;
		result.xz = 3.*a*x2zR_5 + 3*b*xyzR_5 + 3*c*z2xR_5;
		result.zx = result.xz;
		result.yz = 3.*a*xyzR_5 + 3*b*y2zR_5 + 3*c*z2yR_5;
		result.zy = result.yz;
		temp1 = temp1 + (unit_normal*M_e)* result;
		int n = pol.faces[i].size();
		double R_1 =0.;
		Point temp2_result(0., 0., 0.);
		for (int j = 0; j < n; j++)
		{
			int j_next = (j + 1) % n;
			Point m_ij = unitCross( *face_node[j_next] - *face_node[j], unit_normal);
			R_1 = Integral::Line_R_1(ob, *face_node[j], *face_node[j_next]);
			temp2_result += m_ij*R_1;
		}
		temp2_result =temp2_result + unit_normal*h_i*Integral::Surface_R_3(ob, face_node, num);
		temp2 += Dyadic( unit_normal,temp2_result);
	}
	temp = temp1 - (M_e*L_T)*temp2;
	temp = temp*(-1.)*C*1e09;
	return temp;
}
//***********************************************Caculate of Magnetic Linear Polyhedal*************************************************//
double Magnetic::U_1st(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	double  result = 0.;
	result  = U_linear(pol, ob, a, b, c, M);
	result  = result + U_const(pol, ob, a*ob.x + b*ob.y + c*ob.z,M);
	return result;
}

Point Magnetic::B_1st(const Polyhedral& pol, const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	Point  result (0., 0., 0.);
	result  = B_linear(pol, ob, a, b, c, M);
	result  = result + B_const(pol, ob, a*ob.x + b*ob.y + c*ob.z, M);
	return result; 
}

Dyadic Magnetic::T_1st(const Polyhedral& pol,const Point& ob, const double& a, const double& b, const double& c, const Point& M)
{
	Dyadic result;
	result = T_linear(pol, ob, a, b, c, M);
	result = result + T_const(pol, ob, (a*ob.x + b*ob.y + c*ob.z), M);
	return result;
}