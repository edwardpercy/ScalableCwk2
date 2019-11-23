/** @file
* This file stores the tetrahedron data. Child class of the cell
*/
/** Brief description
* Allows the volume, weight and centre to be calculated
*/
#include "tetrahedron.h"

//calculate the volume of this cell
//execute one time of vector calculation
double Tetrahedron :: getvolume() {
	std::vector<Vector> v = getV();
	double volume = 0;
	Vector A = v[0] - v[1];
	Vector B = v[0] - v[2];
	Vector C = v[0] - v[3];
	volume = std::abs((A.vectorproduct(B)).scalarproduct(C)) * (1.0 / 6.0);
	this->volume = volume;
	return volume;
}

double Tetrahedron::getWeight() {
	double weight;
	Material m = getM();
	weight = this->volume * m.getDensity();
	return weight;
}

//get the centre of the cell
//divide the sum of all vertices coordinate by 4
Vector Tetrahedron::getCentre() {
	std::vector<Vector> v = getV();
	Vector centre;
	Vector total = v[0] + v[1] + v[2] + v[3];
	centre = total.divide(4);
	return centre;
}