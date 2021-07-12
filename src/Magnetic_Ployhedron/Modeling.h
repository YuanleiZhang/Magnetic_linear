#pragma once
/*****************************************************************
 * Modeling class is to read geometrical information of a collection of
 * polyhedrons from ASCII files, to read observation sites from files
 * and calculate gravity fields and GGTs of all polyhedrons at all
 * observation sites.
 *
 * Copyright 2017
 * Zhong, Yiyuan 
 * Central South University
 ******************************************************************/
#include <vector>
#include "Point.h"
#include "Magnetic.h"
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iomanip>

class Modeling
{
  public:
	Modeling();
	~Modeling();
	void read_model(const char *name);
	void read_site(const char *name);
	/*Analysics solution of linear magnetic*/
	void analytic_U();
	void analytic_B();
	void analytic_magnetic_T();
	void out_magnetic_B(const char *name);
	void out_magnetic_T(const char *name);


  private:
	vector<Point> coor;	//array of coordinates for observation sites
	vector<Polyhedral> po; // array of polyhedrons
	unsigned num_site;	 //number of observation sites
	unsigned num_po;	   //number of polyhedrons
	
	/*Analysics solution of linear magnetic*/
	vector<double>U_m;
	vector<Point> B;
	vector<Dyadic> Magnetic_T;

	//delete spaces at the begining and the end, and delete comments
	void line_process(string &line, const string comment_str = "#")
	{
		// if(line.size()==1&&(line[0]=='\n'||line[0]=='\r')){
		// 	cout<<"23333"<<endl;
		// }
		for (char &c : line)
			if (c == '\t' || c == ',' || c == ';'||c=='\r'||c=='\n')
				c = ' ';
		line.erase(0, line.find_first_not_of(" "));
		line.erase(line.find_last_not_of(" ") + 1);
		int n_comment_start = line.find_first_of(comment_str);
		if (n_comment_start != string::npos)
			line.erase(n_comment_start);
	}
};
