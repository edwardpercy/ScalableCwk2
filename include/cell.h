#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "vector.h"
#include "matrix.h"
#include <cmath>
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator

using namespace std;

/*Class cell*/
class cell {
protected:
	  friend class Triangle;
      int id;
      string type;
      vector<int> p;                            //vector storing verticesID
	  vector<string> params;                            //vector storing verticesID
	  double volume;
public:	 
      void setCell(int ID, string parameters); //store cellID, matID and cell type
      void setVertices(int v);                  //store verticesID
      vector<int> getVertices();
	  int getCellID();
	  string getParam(int i);
	  int getVerticesID(int n);
	  std::vector<Vector> getV();               //return vertices stored in this cell
};
