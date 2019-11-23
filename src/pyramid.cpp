/** @file
* This file stores the pyramid data. Child class of the cell
*/
/** Brief description
* Allows the volume, weight and centre to be calculated
*/
#include "pyramid.h"

//calculate the volume of this cell
//a pyramid can be spilted into two tetrahedrons
//execute two times of vector calculation
double Pyramid::getvolume() {
	std::vector<Vector> v = getV();
	double volume, volume1, volume2 = 0;
	Vector A = v[0] - v[1];
	Vector B = v[0] - v[3];
	Vector C = v[0] - v[4];
	volume1 = std::abs((A.vectorproduct(B)).scalarproduct(C)) * (1.0 / 6.0);
	Vector D = v[2] - v[1];
	Vector E = v[2] - v[3];
	Vector F = v[2] - v[4];
	volume2 = std::abs((D.vectorproduct(E)).scalarproduct(F)) * (1.0 / 6.0);
	volume = volume1 + volume2;
	this->volume = volume;
	return volume;
}

double Pyramid::getWeight() {
	double weight;
	Material m = getM();
	weight = this->volume * m.getDensity();
	return weight;
}

//get the centre of the cell
//divide the sum of all vertices coordinate by 5
Vector Pyramid::getCentre() {
	std::vector<Vector> v = getV();
	Vector centre;
	Vector total = v[0] + v[1] + v[2] + v[3] + v[4];
	centre = total.divide(5);
	return centre;
}