#include <iostream>
#include <fstream>
#include <string>
#include <vector>   //for std::vector
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "cell.h"
#include "vector.h"
#include "Triangle.h"

using namespace std;

class Mesh
{
private:
	vector<Vector> Vertices;
	vector<Triangle> Cells;
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
};

