#include "cell.h"
/** @file
* This file stores the data for each cell of the model
*/
/** Brief description

*/




using namespace std;



//store cellID, matID and cell type
void cell :: setCell(int ID, string p){
    this->id = ID;
	
	istringstream iss(p); //string stream to read characters in string
	vector<std::string> results((std::istream_iterator<std::string>(iss)), //Splits into characters
		istream_iterator<std::string>());
	
	for (int i(0);i <results.size(); i++){
		params.push_back(results[i]);

	}
}

//store verticesID
void cell :: setVertices(int v){
      this->p.push_back(v);  
}

vector<int> cell :: getVertices(){
      return p;
}

int cell :: getCellID() {
	  return this->id;
}

string cell :: getParam(int i) {
	if (params.size() < i) return "e";

	else{
		return this->params[i];
	}
}

int cell :: getVerticesID(int n) {
        return this->p[n];
}


