#include "tet_model.h"

tet_model::tet_model()
{
}

tet_model::~tet_model()
{
}
void tet_model::compute_U()
{
	vector<Magnetic> Mag;
	unsigned int num_site = observation.get_n_obs();
	unsigned int num_tet = mesh.get_n_tets();
	const vector<Tetrahedron *> &tetrahedrons = mesh.get_tets();
	Mag.resize(num_site);
	U.resize(num_site);
	//cout << (*tetrahedrons[1]).lin[0] << (*tetrahedrons[1]).lin[1] << (*tetrahedrons[1]).lin[2] << endl;
	if (Magnetization_order == 0)
	{
		cout << "\nThe magnetization contrast is constant.\n";
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			U[i] = 0;
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				U[i] += Mag[i].U_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
			}
		}
	}
	else if (Magnetization_order == 1)
	{
		cout << "\nThe magnetization contrast is linear.\n";
		cout << "Computing magnetic potential ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			U[i] = 0;
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				U[i]+= Mag[i].U_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
				U[i]+= Mag[i].U_1st(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).lin[0],
									 (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2], (*tetrahedrons[j]).Me);
			}
		}
	}
}

void tet_model::compute_B()
{
	vector<Magnetic> Mag;
	unsigned int num_site = observation.get_n_obs();
	unsigned int num_tet = mesh.get_n_tets();
	const vector<Tetrahedron *> &tetrahedrons = mesh.get_tets();
	Mag.resize(num_site);
	B.resize(num_site);

	Timer ti;
	ti.start();
	//cout << (*tetrahedrons[1]).lin[0] << (*tetrahedrons[1]).lin[1] << (*tetrahedrons[1]).lin[2] << endl;
	if (Magnetization_order == 0)
	{
		cout << "\nThe magnetization contrast is constant.\n";
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			B[i].setPoint(0., 0., 0.);
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				B[i] += Mag[i].B_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
			}
		}
	}
	else if (Magnetization_order == 1)
	{
		cout << "\nThe magnetization contrast is linear.\n";
		cout << "Computing  magnetic field ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			B[i].setPoint(0., 0., 0.);
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				B[i]+= Mag[i].B_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
				B[i]+= Mag[i].B_1st(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).lin[0],
									 (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2], (*tetrahedrons[j]).Me);
			}
		}
	}
	/*
	else if (Magnetization_order == 2)
	{
		cout << "\nThe magnetization contrast is quadratic.\n";
		cout << "Computing magnetic ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			g[i].setPoint(0., 0., 0.);
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				B[i]+= Mag[i].g_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization);

				B[i]+= Mag[i].g_1st(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).lin[0],
									 (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2]);

				B[i]+= Mag[i].g_2nd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).qua[0],
									 (*tetrahedrons[j]).qua[1], (*tetrahedrons[j]).qua[2], (*tetrahedrons[j]).qua[3],
									 (*tetrahedrons[j]).qua[4], (*tetrahedrons[j]).qua[5]);
			}
		}
	}
	else if (Magnetization_order == 3)
	{
		cout << "\nThe Magnetization contrast is cubic.\n";
		cout << "Computing Magvity ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			g[i].setPoint(0., 0., 0.);
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				B[i]+= Mag[i].g_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization);

				B[i]+= Mag[i].g_1st(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).lin[0],
									 (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2]);

				B[i]+= Mag[i].g_2nd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).qua[0],
									 (*tetrahedrons[j]).qua[1], (*tetrahedrons[j]).qua[2], (*tetrahedrons[j]).qua[3],
									 (*tetrahedrons[j]).qua[4], (*tetrahedrons[j]).qua[5]);

				B[i]+= Mag[i].g_3rd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).cub);
			}
		}
	}
	*/
	ti.stop();
	cout << "Computing magnetic field vector done! ";
	cout << "Computation time for magnetic field vector is " << ti.getElapsedTimeInSec() << " second(s).\n\n";
}

void tet_model::compute_magnetic_T()
{
	vector<Magnetic> Mag;
	unsigned int num_site = observation.get_n_obs();
	unsigned int num_tet = mesh.get_n_tets();
	const vector<Tetrahedron *> &tetrahedrons = mesh.get_tets();
	Mag.resize(num_site);

	Timer ti;
	ti.start();
	if (Magnetization_order == 0)
	{
		cout << "\nThe Magnetization contrast is constant.\n";
		cout << "Computing Magnetic gradient tensor ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			T[i].set();
			for (unsigned j = 0; j < num_tet; j++)
			{
				T[i] = T[i] + Mag[i].T_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
			}
		}
	}
	else if (Magnetization_order == 1)
	{
		cout << "\nThe Magnetization contrast is linear.\n";
		cout << "Computing Magnetic gradient tensor ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			T[i].set();
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				T[i] = T[i] + Mag[i].T_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization, (*tetrahedrons[j]).Me);
				T[i] = T[i] + Mag[i].T_1st(*tetrahedrons[j], observation(i),
												(*tetrahedrons[j]).lin[0], (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2], (*tetrahedrons[j]).Me);
			}
		}
	}
	/*
	else if (Magnetization_order == 2)
	{
		cout << "\nThe Magnetization contrast is quadratic.\n";
		cout << "Computing Magnetic gradien tensor ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			T[i].set();
			for (unsigned j = 0; j < num_tet; j++)
			{
				//clock_t t_start = clock();
				T[i] = T[i] + Mag[i].tensor_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization);
				T[i] = T[i] + Mag[i].tensor_1st(*tetrahedrons[j], observation(i),
												(*tetrahedrons[j]).lin[0], (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2]);
				T[i] += Mag[i].tensor_2nd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).qua[0],
										  (*tetrahedrons[j]).qua[1], (*tetrahedrons[j]).qua[2], (*tetrahedrons[j]).qua[3],
										  (*tetrahedrons[j]).qua[4], (*tetrahedrons[j]).qua[5]);
			}
		}
	}
	else if (Magnetization_order == 3)
	{
		cout << "\nThe Magnetization contrast is cubic.\n";
		cout << "Computing Magnetic gradient tensor ..." << endl;
#pragma omp parallel for
		for (int i = 0; i < num_site; i++)
		{
			T[i].set();
			for (unsigned j = 0; j < num_tet; j++)
			{
				T[i] = T[i] + Mag[i].tensor_const(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).const_Magnetization);
				T[i] = T[i] + Mag[i].tensor_1st(*tetrahedrons[j], observation(i),
												(*tetrahedrons[j]).lin[0], (*tetrahedrons[j]).lin[1], (*tetrahedrons[j]).lin[2]);
				T[i] += Mag[i].tensor_2nd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).qua[0],
										  (*tetrahedrons[j]).qua[1], (*tetrahedrons[j]).qua[2], (*tetrahedrons[j]).qua[3],
										  (*tetrahedrons[j]).qua[4], (*tetrahedrons[j]).qua[5]);
				T[i] += Mag[i].tensor_3rd(*tetrahedrons[j], observation(i), (*tetrahedrons[j]).cub);
			}
		}
	}
	*/
	ti.stop();
	cout << "Computing Magnetic gradient tensors done!\n";
	cout << " Computaion time for Magnetic gradient tensors is " << ti.getElapsedTimeInSec() << " second(s)\n\n";
}

void tet_model::read_config(string config_file)
{
	ifstream in_stream(config_file.c_str());
	string model_mesh;

	std::string line;
	while (std::getline(in_stream, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> model_mesh;
		break;
	}
	std::cout << model_mesh << "\n";

	string station_file;
	while (std::getline(in_stream, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> station_file;
		break;
	}
	std::cout << station_file << "\n";

	while (std::getline(in_stream, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> Magnetization_order;
		break;
	}
	std::cout << Magnetization_order << "\n";

	unsigned int n_regions;
	while (std::getline(in_stream, line))
	{
		line_process(line, "#");
		if (line.empty())
			continue;
		std::istringstream iss(line);
		iss >> n_regions;
		break;
	}

	std::cout << n_regions << "\n";
	for (unsigned i = 0; i < n_regions; i++)
	{
		std::vector<double> temp;
		Point M_direction;
		int marker;
		while (std::getline(in_stream, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			iss >> marker;
			break;
		}
		std::cout << marker << "\n";

		double mag_const;
		while (std::getline(in_stream, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			iss >> mag_const;
			break;
		}
		std::cout << "\t" << mag_const << "\n";
		region_table_0[marker] = mag_const;

		temp.resize(3);
		cout << "\t";
		while (std::getline(in_stream, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 3; j++)
			{
				iss >> temp[j];
				std::cout << temp[j] << "\t";
			}
			break;
		}
		std::cout << "\n";
		region_table_1[marker] = temp;

		temp.resize(6);
		cout << "\t";
		while (std::getline(in_stream, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 6; j++)
			{
				iss >> temp[j];
				std::cout << temp[j] << "\t";
			}
			break;
		}
		std::cout << "\n";
		region_table_2[marker] = temp;

		temp.resize(10);
		cout << "\t";
		while (std::getline(in_stream, line))
		{
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			for (int j = 0; j < 10; j++)
			{
				iss >> temp[j];
				std::cout << temp[j] << "\t";
			}
			break;
		}
		std::cout << "\n";
		region_table_3[marker] = temp;

		M_direction.zero();
		cout << "\t";
		while (std::getline(in_stream, line)){
			line_process(line, "#");
			if (line.empty())
				continue;
			std::istringstream iss(line);
			double x, y, z;
			iss >>x >>y >> z;
			M_direction.setPoint(x, y, z);
			M_direction.display();
			break;
		}	
		std::cout << "\n";
		region_table_Me[marker] = M_direction;

	}
	
	mesh.read_mesh(model_mesh);
	this->set_Magnetization();
	observation.read_site(station_file);
	int n_data = observation.get_n_obs();
	this->B.resize(n_data);
	this->T.resize(n_data);
}

void tet_model::set_Magnetization()
{
	typedef std::map<int, double>::iterator IT0;
	typedef std::map<int, std::vector<double>>::iterator IT;
	typedef std::map<int, Point > ::iterator ITm;
	const vector<Tetrahedron *> &tetrahedrons = mesh.get_tets();
	for (int i = 0; i < mesh.get_n_tets(); i++)
	{
		int marker;
		marker = (*tetrahedrons[i]).get_marker();
		IT0 it0 = region_table_0.find(marker);
		IT it1 = region_table_1.find(marker);
		IT it2 = region_table_2.find(marker);
		IT it3 = region_table_3.find(marker);
		ITm it4 =region_table_Me.find(marker);
		mesh.set_tet_Magnetization_0(i, (*it0).second);
		mesh.set_tet_Magnetization_1(i, (*it1).second);
		mesh.set_tet_Magnetization_2(i, (*it2).second);
		mesh.set_tet_Magnetization_3(i, (*it3).second);
		mesh.set_tet_Magnetization_direction(i, (*it4).second);
	}
}

void tet_model::out_magnetic_B(const char *name)
{
	unsigned num_site = observation.get_n_obs();
	ofstream os;
	os.open(name);
	assert(os.good());

	os << setw(25) << left << "x(m)"
	   << setw(25) << left << "y(m)"
	   << setw(25) << left << "z(m)"
	   << setw(25) << left << "Magnetic_Potential"
	   << setw(25) << left << "Magnetic_x(nT)"
	   << setw(25) << left << "Magnetic_y(nT)"
	   << setw(25) << left << "Magnetic_z(nT)";
	os << '\n';
	for (unsigned i = 0; i < num_site; i++)
	{
		assert(os.good());
		os << setprecision(7);
		os << fixed;
		os << setw(25) << left << observation(i).x
		   << setw(25) << left << observation(i).y
		   << setw(25) << left << observation(i).z;
		os << setprecision(14);
		os << scientific;
		os << setw(25) << left << U[i];
		os << setw(25) << left << B[i].x;
		os << setw(25) << left << B[i].y;
		os << setw(25) << left << B[i].z << '\n';
	}
}

void tet_model::out_magnetic_T(const char *name)
{

	unsigned num_site = observation.get_n_obs();
	ofstream os;
	os.open(name);
	assert(os.good());

	os << setw(25) << left << "x(m)"
	   << setw(25) << left << "y(m)"
	   << setw(25) << left << "z(m)"
	   << setw(25) << left << "Txx(nT/m)"
	   << setw(25) << left << "Tyx(nT/m)"
	   << setw(25) << left << "Tzx(nT/m)"
	   << setw(25) << left << "Txy(nT/m)"
	   << setw(25) << left << "Tyy(nT/m)"
	   << setw(25) << left << "Tzy(nT/m)"
	   << setw(25) << left << "Txz(nT/m)"
	   << setw(25) << left << "Tyz(nT/m)"
	   << setw(25) << left << "Tzz(nT/m)";
	os << '\n';
	for (unsigned i = 0; i < num_site; i++)
	{
		assert(os.good());
		os << setprecision(7);
		os << fixed;
		os << setw(25) << left << observation(i).x
		   << setw(25) << left << observation(i).y
		   << setw(25) << left << observation(i).z;
		os << setprecision(14);
		os << scientific;
		os << setw(25) << left << T[i].xx;
		os << setw(25) << left << T[i].yx;
		os << setw(25) << left << T[i].zx;
		os << setw(25) << left << T[i].xy;
		os << setw(25) << left << T[i].yy;
		os << setw(25) << left << T[i].zy;
		os << setw(25) << left << T[i].xz;
		os << setw(25) << left << T[i].yz;
		os << setw(25) << left << T[i].zz << '\n';
	}
}