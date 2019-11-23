#include <iostream>
#include <fstream>
#include <string>
#include <vector>   //for std::vector
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "cell.h"
#include "vector.h"
#include "material.h"
#include "pyramid.h"
#include "hexahedron.h"
#include "tetrahedron.h"

using namespace std;

class Model
{
private:
	vector<Vector> Vertices;
	vector<Material> Materials;
	vector<cell> Cells;
	vector<Pyramid> Pyramids;
	vector<Hexahedron> Hexahedrons;
	vector<Tetrahedron> Tetrahedrons;
	float x, y, z;
        vector<float> V;
        vector<float> RGB;

public:
	Model();
	~Model();
        void SaveModel(string FileName,string Hexstring);
	void LoadModel(string FileName);
	void SetCell(string data);
	void SetVertices(string data); 
	void SetMaterial(string data);
        int GetCellMaterial(int ID, string Type);
	int GetCell(int ID, string Type);
        vector<int> GetCellVertices(int ID, string Type);
        vector<float> GetVertices(int ID);
        vector<float> GetMaterialColour(int ID);
	double GetCellVolume(int ID);
	vector<float> FindCentre(void);
	vector<int> NumberCells(void);
	int NumberVertices(void);
};

