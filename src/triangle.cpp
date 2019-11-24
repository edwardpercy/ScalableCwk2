
#include "triangle.h"

//calculate the volume of this cell
//execute one time of vector calculation
double Triangle :: getvolume() {
	std::vector<Vector> v = getV();
	double volume = 0;
	Vector A = v[0] - v[1];
	Vector B = v[0] - v[2];
	Vector C = v[0] - v[3];
	volume = std::abs((A.vectorproduct(B)).scalarproduct(C)) * (1.0 / 6.0);
	this->volume = volume;
	return volume;
}


//get the centre of the cell
//divide the sum of all vertices coordinate by 4
Vector Triangle::getCentre() {
	std::vector<Vector> v = getV();
	Vector centre;
	Vector total = v[0] + v[1] + v[2] + v[3];
	centre = total.divide(4);
	return centre;
}