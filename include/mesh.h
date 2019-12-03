#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>   //for std::vector
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "cell.h"
#include "vector.h"
#include "Triangle.h"
#include <math.h> 
#include "matrix.h"

using namespace std;

class Mesh
{
private:
	vector<Vector> Vertices;
	vector<cell> Cells;
	vector<Triangle> Triangles;
	float x, y, z;
    vector<float> V;


public:
	Mesh();
	~Mesh();
	void LoadMesh(string FileName);
	void SaveMesh(string FileName);
	double TriangleArea(int id);
	int NumberCells(void);
	int NumberVertices(void);
	int isPointContained(double px,double py);
	int CircumcirclesCheck(Vector p);
	void GenerateDelaunayTriangle(Vector point);
	void CalcCircumcircle(int id);
	bool DelaunayCheck();

	template <typename T>
    double integrate(T func, int ApproxType) {
		double res = 0;

        for (int i = 0; i < Triangles.size(); i++) {
			if (ApproxType == 0) res +=  abs(ConstantApprox(func, Triangles[i]));
			else if (ApproxType == 1) res += abs(LinearApprox(func, Triangles[i]));
		}
		return res;
    }

	
	template<typename T>
    double ConstantApprox(T func, Triangle &triangle) {
		Vector O = triangle.getCircumcentre();
        return (triangle.getarea() *  func(O.getx(),O.gety()));
    }

	template<typename T>
    double LinearApprox(T func, Triangle &triangle) {

		vector<int> p = triangle.getVertices();
		double res = ((
												(triangle.getarea() / 3) * func(Vertices[p[0]].getx(),Vertices[p[0]].gety()) +
												(triangle.getarea() / 3) * func(Vertices[p[1]].getx(),Vertices[p[1]].gety()) + 
												(triangle.getarea() / 3) * func(Vertices[p[2]].getx(),Vertices[p[2]].gety())
												)
		);
	
		return res;
		
    }


	


	
};

