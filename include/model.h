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

class Model
{
private:
	vector<Vector> Vertices;
	vector<Triangle> Triangles;
	float x, y, z;
    vector<float> V;


public:
	Model();
	~Model();
	void LoadModel(string FileName);
	double TriangleArea(int id);
	int NumberCells(void);
	int NumberVertices(void);
	int isPointContained(double px,double py);
	int CircumcirclesCheck(double px,double py);
	void CalcCircumcircle(int id);
	void DelaunayCheck();
};

