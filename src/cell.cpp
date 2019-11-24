#include "cell.h"
/** @file
* This file stores the data for each cell of the model
*/
/** Brief description
* It stores the ID, material and type of cell (Hexahedron, tetrahedron, pyramid)
*/
using namespace std;

//store cellID, matID and cell type
void cell :: setCell(int ID, string type){
      this->CellID = ID;

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

//return vertices stored in this cell
std::vector<Vector> cell :: getV() {
	return v;

}
