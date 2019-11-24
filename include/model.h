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
	vector<cell> Cells;
	vector<Triangle> Triangles;
	float x, y, z;
    vector<float> V;


public:
	Model();
	~Model();
	void LoadModel(string FileName);
	void SetCell(string data, int NumCols);
	void SetVertices(string data); 
	int NumberCells(void);
	int NumberVertices(void);
};

