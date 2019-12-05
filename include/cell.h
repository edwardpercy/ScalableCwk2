/* cell.h
cell header parent of triangle class pluss other shapes in future
Created by Edward Percy 12/2019.
*/

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
public:	 
	  cell();
	  cell(const cell &c2);
	  void setCell(int ID);
      void setCell(int ID, string parameters); //store cellID, matID and cell type
      void setVertices(int v);                  //store verticesID
      vector<int> getVertices();
	  int getCellID();
	  string getParam(int i);
	  int getVerticesID(int n);
	  std::vector<Vector> getV();               //return vertices stored in this cell
};
