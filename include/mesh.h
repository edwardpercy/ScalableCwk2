#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>   //for std::vector
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "cell.h"
#include "vector.h"
#include "triangle.h"
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
	Mesh(string FileName);
	~Mesh();
	Mesh(const Mesh &m2);
	void LoadMesh(string FileName);
	void SaveMesh(string FileName);
	double TriangleArea(int id);
	vector<Vector> GetVertices();
	vector<cell> GetCells();
	vector<Triangle> GetTriangles();
	void SetVertices(int id,double X,double Y,double Z,int dimensions,string attributes);
	void SetTriangle(int id,double V1,double V2,double V3,string attributes);
	int NumberCells(void);
	int NumberVertices(void);
	int NumberTriangles(void);
	int isPointContained(double px,double py);
	int CircumcirclesCheck(Vector p);
	void GenerateDelaunayTriangle(Vector point);
	void CalcCircumcircle(int id);
	bool DelaunayCheck();

	template <typename T>
    double integrate(T func, int ApproxType) {
		double res,temp = 0;

        for (int i = 0; i < Triangles.size(); i++) {
			if (ApproxType == 0) {
				temp =  abs(ConstantApprox(func, Triangles[i]));
				if(isnan(temp)==false) res += temp;
			}
			else if (ApproxType == 1){
				temp = abs(LinearApprox(func, Triangles[i]));
				if(isnan(temp)==false) res += temp;
			}
			
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

