#include<iostream>

#include<vector>
#include <algorithm>

#include<ctime>
#include<string>
#include"Point.h"
#include"Dyadic.h"
#include"Tetrahedron.h"
#include"tet_model.h"

using namespace std;

int main(int argc, char* argv[]) {
	clock_t t_start = clock();
	if (argc <2) {
		printf("Usage: %s input_paramters_filename\n", argv[0]);
		return 1;
	}
	/**************************command parameters*******************************************/
	//the first input parameter specify the model file
	const char *config = argv[1];
	tet_model model;
	const string out_B_file("B.dat");
	const string out_MGT_file("MGT.dat");

	model.read_config(config);
	model.compute_U();
	model.compute_B();
	model.out_magnetic_B(out_B_file.c_str());
	cout << "Calculated magnetic data has been written into \"" << out_B_file <<"\""<< endl;

	

	model.compute_magnetic_T();
	model.out_magnetic_T(out_MGT_file.c_str());
	cout << "Calculated MGT data has been written into \"" << out_MGT_file << "\"" << endl;
	return 0;
}


