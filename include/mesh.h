/* mesh.h
mesh header for handling main objects/classes (Triangle and Vertices) and supplying functions for key operations
Created by Edward Percy 12/2019.
*/

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
	int dimensions,NoArguments;


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



	//INTEGRATION TEMPLATES

	template <typename T>
    double integrate(T func, int ApproxType) { //Allows input of functions

		//I wanted to pass the Approx type as a templated function reeference but was not able to pass
		//a templated function to a template and I ran out of time so had to use int

		double res,temp = 0;
		//loops through all triangles to get integration over entire domain of the mesh
        for (int i = 0; i < Triangles.size(); i++) {

			//checks the type of approximation the user wants
			if (ApproxType == 0) {
				temp =  abs(ConstantApprox(func, Triangles[i])); //Constant approximation
				if(isnan(temp)==false) res += temp;
			}
			else if (ApproxType == 1){
				temp = abs(LinearApprox(func, Triangles[i])); //linear approximation
				if(isnan(temp)==false) res += temp; //Check for infinite values /0 etc
			}
			
		}
	
		return res;
    }

	//constant approximation check
	template<typename T>
    double ConstantApprox(T func, Triangle &triangle) {
		//formula in appendix of sheet given by client 

		//A * F(Ox,Oy) for all triangles
		Vector O = triangle.getCircumcentre();
        return (triangle.getarea() *  func(O.getx(),O.gety()));
    }


	//Lionear approximation check
	template<typename T>
    double LinearApprox(T func, Triangle &triangle) {
		vector<int> p = triangle.getVertices();

		//Formula given in appendix by client 
		//A/3 (F0(x,y) + F1(x,y) + F2(x,y))
		double res = ((
					(triangle.getarea() / 3) * func(Vertices[p[0]].getx(),Vertices[p[0]].gety()) +
					(triangle.getarea() / 3) * func(Vertices[p[1]].getx(),Vertices[p[1]].gety()) + 
					(triangle.getarea() / 3) * func(Vertices[p[2]].getx(),Vertices[p[2]].gety())
					)
		);
		return res;
    }


	


	
};

