#include <iostream>
#include <fstream>
#include <string>
#include <vector>   //for std::vector
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "cell.h"
#include "vector.h"
#include "tetrahedron.h"

using namespace std;

class Model
{
private:
	vector<Vector> Vertices;
	vector<cell> Cells;
	vector<Tetrahedron> Tetrahedrons;
	float x, y, z;
    vector<float> V;


public:
	Model();
	~Model();
    void SaveModel(string FileName,string Hexstring);
	void LoadModel(string FileName);
	void SetCell(string data);
	void SetVertices(string data); 
	int GetCell(int ID, string Type);
    vector<int> GetCellVertices(int ID, string Type);
    vector<float> GetVertices(int ID);
	vector<int> NumberCells(void);
	int NumberVertices(void);
};

