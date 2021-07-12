#pragma once

#include"Node.h"
#include"Magnetic.h"
#include"Tetrahedron.h"
#include<fstream>
class tet_mesh
{
public:
	tet_mesh();
	~tet_mesh();

	void clear();
	void read_mesh(string grid_name);

	void set_tet_Magnetization_0(int index, const double& rho_const) {
		(*tets[index]).const_Magnetization = rho_const;
	}
	void set_tet_Magnetization_1(int index, const vector<double>& rho_lin) {
		assert(rho_lin.size() == 3);
		for (int i = 0; i < 3; i++) {
			(*tets[index]).lin[i] = rho_lin[i];
		}
	}
	void set_tet_Magnetization_2(int index, const vector<double>& rho_qua) {
		assert(rho_qua.size() == 6);
		for (int i = 0; i < 6; i++) {
			(*tets[index]).qua[i] = rho_qua[i];
		}
	}
	void set_tet_Magnetization_3(int index, const vector<double>& rho_cub) {
		assert(rho_cub.size() == 10);
		for (int i = 0; i < 10; i++) {
			(*tets[index]).cub[i] = rho_cub[i];
		}
	}
	void set_tet_Magnetization_direction(int index, const Point& M_direction) {
		(*tets[index]).Me = M_direction;
	}

	const unsigned int& get_n_nodes() { return n_nodes; }
	const unsigned int& get_n_tets() { return n_tets; }

	const vector<Node*>& get_mesh_nodes() { return mesh_nodes; }
	const vector<Tetrahedron*>& get_tets() { return tets; }
private:
	unsigned int n_nodes;
	unsigned int n_tets;
	vector<Node*> mesh_nodes;
	vector<Tetrahedron*> tets;

	void nodes_in(std::istream& node_stream);
	void tets_in(std::istream& ele_stream);
};