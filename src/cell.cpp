/* Cell.cpp
Cell class which is used as the parent class for the triangle class
and can be used for expansion/scalability in the future to base cells with
the number of vertices != 3 (Other shapes, tetrahedron, hexahedron etc..)

Created by Edward Percy 12/2019.
*/

#include "../include/cell.h"
using namespace std;

cell::cell(){ //Default Constructor 
	id = 0;
}

cell::cell(const cell &c2) { //Copy-Constructor 
	id = c2.id;
	type = c2.type;
	p = c2.p;
	params = c2.params;
} 

//store cellID, matID and cell type
void cell :: setCell(int ID, string p){ //Sets the parameters for the cell
    this->id = ID;
	istringstream iss(p); //string stream to read characters in string
	vector<std::string> results((std::istream_iterator<std::string>(iss)), //Splits the cell argument string into a vector with space deliminator
		istream_iterator<std::string>());
	params = results; //Saves the parameters in string format as a vector<string> for later use/conversion
						//Saved as string as the inputted data could have any format and allows nfor scalability 
						//as many arguments as required without writing lots of float/int/string etc
}

void cell :: setCell(int ID){ //Allows the Cell parameters to be set without the additional arguments (When arguments = 0)
    this->id = ID;
}

void cell::setVertices(int v){ //Sets the vertices by pushing incoming data into the vector<int> list
      this->p.push_back(v); //Add incoming PointIDs to the vector list for later referencing
}

vector<int> cell::getVertices(){ //Returns the list of PointIDS for the particular shape (eg, triangle would return 3)
      return p;
}

int cell::getCellID() { //Returns the ID for the cell
	  return this->id;
}

string cell::getParam(int i) { //Returns the specific parameter the user needs
	if (params.size() < i){
		throw("ERROR: Parameter requested not available");
		return "e"; //Returns an error if the parameter required is not available 
	}
	else{
		return this->params[i]; //Returns the rquested parameter params[0] would be the first loaded when .tri was initially read
	}
}

int cell::getVerticesID(int n) { //Returns the ID of the specific vertexID requested 
	if (p.size() < n){
			throw("ERROR: Vertex requested not available"); //Returns an error if the parameter required is not available
			return p[0];  
		}
    return this->p[n];
}


