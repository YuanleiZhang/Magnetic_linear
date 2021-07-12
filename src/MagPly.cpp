#include<iostream>
#include"Point.h"
#include"Dyadic.h"
#include<vector>
#include <algorithm>
#include"Modeling.h"
#include<ctime>
#include"timer.h"
#include<string>
using namespace std;

int main(int argc, char* argv[]) {
	// clock_t t_start = clock();
	Timer t;
	t.start();
	if (argc < 5) {
		printf("Usage: %s input_paramters_filename\n", argv[0]);
		return 1;
	}
	const char *model_file = argv[1];
	const char *coor_file = argv[2];
	const char *out_file = argv[3];
	string specifier = argv[4];

	Modeling m;
	
	m.read_model(model_file);
	m.read_site(coor_file);
	string field;
	string author;
	if (specifier=="m_b")
	{
		field="magnetic potential and  magnetic field";
		author = "Ren's";
		cout << "Computing " << author << " "<< field<<" ...\n";
		m.analytic_U();
		m.analytic_B();
		m.out_magnetic_B(out_file);
	}
	else if (specifier=="m_t")
	{
		field="magnetic gradient tensor";
		author = "Ren's";
		cout << "Computing " << author << " "<< field<<" ...\n";
		m.analytic_magnetic_T();
		m.out_magnetic_T(out_file);
	}
	else{
			cout << "Input Error! Please Input Again!" << endl;
		}
	t.stop();

	// clock_t t_end = clock();
	double time=t.getElapsedTimeInMilliSec();
	cout << "Total running time: "<<time<< "ms\n\n";

	return 0;
}


