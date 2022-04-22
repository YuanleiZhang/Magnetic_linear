#include "Modeling.h"
#include <ctime>

Modeling::Modeling()
{
}

Modeling::~Modeling()
{
	assert(num_po == po.size());
	for (int i = 0; i < num_po; i++)
	{
		assert(po[i].node_number == po[i].node.size());
		for (int k = 0; k < po[i].node_number; k++)
		{
			delete po[i].node[k];
		}
	}
}

void Modeling::read_model(const char *name)
{
	ifstream is;
	is.open(name);
	unsigned lab;
	assert(is.good());
	std::string line;
	cout << "Reading model file: \"" << string(name) <<"\""<< endl;
	while (std::getline(is, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> num_po;
		break;
	}
	po.resize(num_po);
	cout << "\nNumber of polyhedrons: " << num_po << "\n\n";

	for (unsigned i = 0; i < num_po; i++)
	{
		cout << "Polyhedral " << i << endl;
		// assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			iss >> lab;
			cout<<"lab="<<lab<<",i="<<i<<endl;
			assert(lab == i);
			iss >> po[i].node_number; //total number of vertices in the polyhedral
			po[i].node.resize(po[i].node_number);
			// cout << po[i].node.size() << endl;
			for (int kk = 0; kk < po[i].node_number; kk++)
			{
				po[i].node[kk] = NULL;
			}

			iss >> po[i].face_number;
			cout << "     Number of nodes : " << po[i].node_number << "\n"
				 << "     Number of facets: " << po[i].face_number << "\n\n";
			po[i].face_node_number.resize(po[i].face_number);
			po[i].face_node.resize(po[i].face_number);
			po[i].face_normal_vector.resize(po[i].face_number);
			break;
		}

		unsigned temp;

		for (int j = 0; j < po[i].node_number; j++)
		{
			assert(is.good());
			while (std::getline(is, line))
			{
				line_process(line, "#");
				if (line.empty())
					continue;

				std::istringstream iss(line);
				iss >> temp;
				//coordinate of each node
				double x, y, z;
				iss >> x >> y >> z;
				po[i].node[j] = new Node(x, y, z);
				break;
			}
		}
		// for (int j = 0; j < po[i].node_number; j++) {
		// 	cout << "node " << j << ": (x, y, z)=" << (*po[i].node[j]).x <<
		// 		", " << (*po[i].node[j]).y << ", " << (*po[i].node[j]).z << endl;
		// 	// (*po[i].node[j]).display();
		// }

		for (int j = 0; j < po[i].face_number; j++)
		{
			assert(is.good());
			while (std::getline(is, line))
			{
				line_process(line, "#");
				if (line.empty())
					continue;
				std::istringstream iss(line);
				iss >> temp;
				iss >> po[i].face_node_number[j];
				po[i].face_node[j].resize(po[i].face_node_number[j]);
				// cout << "Face " << j << ": " << "(";
				for (int k = 0; k < po[i].face_node_number[j]; k++)
				{
					iss >> po[i].face_node[j][k];
					// cout << po[i].face_node[j][k] << ", ";
				}

				// cout << ")\n";
				// for (int k = 0; k < po[i].face_node_number[j]; k++) {
				// 	cout << po[i].face_node[j][k] << ",";
				// 	(*po[i].node[po[i].face_node[j][k]]).display();
				// }
				break;
			}
		}

		assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			iss >> po[i].const_Magnetization;
			 po[i].const_Magnetization =  po[i].const_Magnetization;
			break;
		}

		//cout << po[i].const_Magnetization<<endl;

		assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 3; j++)
			{
				iss >> po[i].lin[j];
				//cout << po[i].lin[j]<<"\t";
			}
			break;
		}

		//cout << endl;
		assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 6; j++)
			{
				iss >> po[i].qua[j];
				//cout << po[i].qua[j] << "\t";
			}
			break;
		}
		//cout << endl;

		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 10; j++)
			{
				iss >> po[i].cub[j];
				//cout << po[i].cub[j]<<"\t";
			}
			break;
		}

		assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			double x, y, z;
			iss >>x >>y >> z;
			po[i].Me.setPoint(x, y, z);
			break;
		}

		cout << "Me = "<< endl;
		po[i].Me.display();

		po[i].init();
		//po[i].sort_and_compute_normal_vector();//sort the order of face nodes

		// to check whether all vertice on a face are coplanar, if not, exit
		for (int j = 0; j < po[i].face_number; j++)
		{
			if (po[i].face_node_number[j] > 3)
			{
				for (int k = 3; k < po[i].face_node_number[j]; k++)
				{
					double flag = po[i].face_normal_vector[j] * (*po[i].node[po[i].face_node[j][k]] - *po[i].node[po[i].face_node[j][0]]);
					if (abs(flag) > TOLERANCE)
					{
						cerr << "The " << k << "-th vertex on the " << j << "-th facet of the " << i << "-th polyhedron is not coplanar with the first three point on face" << j << endl;
						exit(1);
					}
				}
			}
		}
	}
}

void Modeling::read_site(const char *name)
{
	ifstream is;
	is.open(name);
	string line;
	assert(is.good());
	cout << "Reading computation points in file: \"" << string(name) << "\"" << endl;
	while (std::getline(is, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> num_site;
		break;
	}

	cout << "Number of computation points: " << num_site << endl
		 << endl;
	unsigned lab;
	coor.resize(num_site);
	B.resize(num_site);
	Magnetic_T.resize(num_site);
	//gx.resize(num_site);
	//gy.resize(num_site);
	//gz.resize(num_site);
	double x, y, z;
	for (unsigned i = 0; i < num_site; i++)
	{
		assert(is.good());
		while (std::getline(is, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			iss >> lab;
			iss >> x >> y >> z;
			break;
		}
		coor[i].setPoint(x, y, z);
	}
}


void Modeling::analytic_U()
{
	vector<Magnetic> Mag;
	Mag.resize(num_site);
	U_m.resize(num_site);
#pragma omp parallel for
	for (int i = 0; i < num_site; i++)
	{
		U_m.clear();
		for (int j = 0; j < num_po; j++)
		{
			//clock_t t_start = clock();
			U_m[i] += Mag[i].U_const(po[j], coor[i], po[j].const_Magnetization, po[j].Me);
			U_m[i] += Mag[i].U_1st(po[j], coor[i], po[j].lin[0], po[j].lin[1], po[j].lin[2], po[j].Me);
		}
	}
}

void Modeling::analytic_B()
{
	vector<Magnetic> Mag;
	Mag.resize(num_site);
	B.resize(num_site);
#pragma omp parallel for
	for (int i = 0; i < num_site; i++)
	{
		B[i].zero();
		for (int j = 0; j < num_po; j++)
		{
			//clock_t t_start = clock();
			B[i] = B[i] + Mag[i].B_const(po[j], coor[i], po[j].const_Magnetization, po[j].Me);
			B[i] = B[i] + Mag[i].B_1st(po[j], coor[i], po[j].lin[0], po[j].lin[1], po[j].lin[2], po[j].Me);
		}
	}	
}

void Modeling::analytic_magnetic_T()
{
	vector<Magnetic> Mag;
	Mag.resize(num_site);
	Magnetic_T.resize(num_site);
	for (int i = 0; i < num_site; i++)
	{
		Magnetic_T[i].set();
		for (int j = 0; j < num_po; j++)
		{
			//clock_t t_start = clock();
			//coor[i].display();
			Magnetic_T[i] += Mag[i].T_const(po[j], coor[i], po[j].const_Magnetization, po[j].Me);
			Magnetic_T[i]  += Mag[i].T_1st(po[j], coor[i], po[j].lin[0], po[j].lin[1], po[j].lin[2], po[j].Me);
		}
	}
}

void Modeling::out_magnetic_B(const char *name)  // Printf U and Bx,By,Bz
{
	ofstream os;
	os.open(name);
	assert(os.good());
	//os << "elasped time: " << time << " ms\n";
	os << setw(25) << left << "x(m)"
	   << setw(25) << left << "y(m)"
	   << setw(25) << left << "z(m)"
	   << setw(25) << left << "U(unit)"
	   << setw(25) << left << "magnetic_x(nT)"
	   << setw(25) << left << "magnetic_y(nT)"
	   << setw(25) << left << "magnetic_z(nT)";
	os << '\n';
	for (unsigned i = 0; i < num_site; i++)
	{
		assert(os.good());
		os << setprecision(7);
		os << fixed;
		os << setw(25) << left << coor[i].x
		   << setw(25) << left << coor[i].y
		   << setw(25) << left << coor[i].z;
		os << setprecision(14);
		os << scientific;
		os << setw(25) << left <<U_m[i];
		os << setw(25) << left << B[i].x;
		os << setw(25) << left << B[i].y;
		os << setw(25) << left << B[i].z << '\n';
	}
}

void Modeling::out_magnetic_T(const char *name)
{
	ofstream os;
	os.open(name);
	assert(os.good());

	os << setw(18) << left << "x(m)"
	   << setw(18) << left << "y(m)"
	   << setw(18) << left << "z(m)"
	   << setw(25) << left << "Txx"
	   << setw(25) << left << "Tyx"
	   << setw(25) << left << "Tzx"
	   //<< setw(25) << left << "Magnetic_Txy(nT/m)"
	   << setw(25) << left << "Tyy"
	   << setw(25) << left << "Tzy"
	   //<< setw(25) << left << "Magnetic_Txz(nT/m)"
	   //<< setw(25) << left << "Magnetic_Tyz(nT/m)"
	   << setw(25) << left << "Tzz";
	os << '\n';
	for (unsigned i = 0; i < num_site; i++)
	{
		assert(os.good());
		os << setprecision(7);
		os << fixed;
		os << setw(18) << left << coor[i].x
		   << setw(18) << left << coor[i].y
		   << setw(18) << left << coor[i].z;
		os << setprecision(14);
		os << fixed;
		os << scientific;
		os << setw(25) << left << Magnetic_T[i].xx;
		os << setw(25) << left << Magnetic_T[i].yx;
		os << setw(25) << left << Magnetic_T[i].zx;
		//os << setw(25) << left << Magnetic_T[i].xy;
		os << setw(25) << left << Magnetic_T[i].yy;
		os << setw(25) << left << Magnetic_T[i].zy;
		//os << setw(25) << left << Magnetic_T[i].xz;
		//os << setw(25) << left << Magnetic_T[i].yz;
		os << setw(25) << left << Magnetic_T[i].zz;
		os << '\n';
	}
}