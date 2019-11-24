#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "vector.h"

#include <cmath>


using namespace std;

/*Class cell*/
class cell {
protected:
	  friend class Tetrahedron;
      int CellID, material;
      string type;
      vector<int> p;                            //vector storing verticesID
	  vector<Vector> v;                         //vector storing vertices used in this cell
	  double volume;
public:	 
      void setCell(int ID, string type); //store cellID, matID and cell type
      void setVertices(int v);                  //store verticesID
      vector<int> getVertices();
	  string getType();                         //return cell type, cellID, materialID and verticesID
	  int getCellID();
	  int getVerticesID(int n);
	  void setV(vector<Vector>& CellVertices);  //store vertices used in this cell
	  std::vector<Vector> getV();               //return vertices stored in this cell
};
