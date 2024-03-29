/* triangle.h
triangle header, main shape in the mesh with point inside and circumcircle tests
Created by Edward Percy 12/2019.
*/
#pragma once
#include <iostream>
#include "cell.h"
#include <sstream>
#include <string>

class Triangle : public cell {

private:
	Vector circumcentre;
	double radius, area;	

	
 
   template<typename T>
   T StringToNumber(const std::string& numberAsString)
   {
      T valor;

      std::stringstream stream(numberAsString);
      stream >> valor;
      if (stream.fail()) {
         
         throw("Error");
      }
      return valor;
   }
public:
	Vector getCircumcentre() const;
	float getRadius();
	double getarea();
   void Circumcircle_OLDCHECK(Vector &A, Vector &B, Vector &C);
	bool isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py);
	void Circumcircle(Vector &A, Vector &B, Vector &C);
	bool isPointInCircumcircle(double px, double py);
};