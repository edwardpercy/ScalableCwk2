#include "cell.h"
/** @file
* This file stores the data for each cell of the model
*/
/** Brief description
* It stores the ID, material and type of cell (Hexahedron, tetrahedron, pyramid)
*/
using namespace std;

//store cellID, matID and cell type
void cell :: setCell(int ID, int m, string type){
      this->CellID = ID;
      this->material = m;
      this->type = type;	   
}

//store verticesID
void cell :: setVertices(int v){
	
      this->p.push_back(v); 
	  
}

vector<int> cell :: getVertices(){

      return p;

}

//return cell type, cellID, materialID and verticesID
string cell :: getType() {
	  return this->type;
}

int cell :: getCellID() {
	  return this->CellID;
}

int cell :: getMaterialID() {
	  return this->material;
}

int cell :: getVerticesID(int n) {


        return this->p[n];
}

//store vertices used in this cell
//getting values from pointers of Vector class
void cell :: setV(vector<Vector>& CellVertices) {
	Vector *V = new Vector;
	for (int Vertex = 0; Vertex < p.size(); Vertex++) {
		*V = CellVertices[p[Vertex]];
		v.push_back(*V);
	}
}

//store material used in this cell
//getting values from pointers of Material class
void cell::setM(Material& CellMaterial) {
	m = CellMaterial;
}

//return vertices stored in this cell
std::vector<Vector> cell :: getV() {
	return v;

}

//return material stored in this cell
Material cell::getM() {
	return m;
}
