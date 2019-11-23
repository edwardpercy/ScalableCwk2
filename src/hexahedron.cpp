/** @file
* This file is a child class of cell
*/
/** Brief description
* It can calculate the volume, weight and centre
*/

#include "hexahedron.h"

//calculate the volume of this cell
//a pyramid can be spilted into six tetrahedrons
//execute six times of vector calculation
double Hexahedron :: getvolume() {
	std::vector<Vector> v = getV();
	double volume, volume1, volume2, volume3, volume4, volume5, volume6 = 0;
	Vector A = v[0] - v[1];
	Vector B = v[0] - v[2];
	Vector C = v[0] - v[4];
	volume1 = std::abs((A.vectorproduct(B)).scalarproduct(C)) * (1.0 / 6.0);
	Vector D = v[5] - v[1];
	Vector E = v[5] - v[2];
	Vector F = v[5] - v[4];
	volume2 = std::abs((D.vectorproduct(E)).scalarproduct(F)) * (1.0 / 6.0);
	Vector G = v[6] - v[2];
	Vector H = v[6] - v[4];
	Vector I = v[6] - v[5];
	volume3 = std::abs((G.vectorproduct(H)).scalarproduct(I)) * (1.0 / 6.0);
	Vector J = v[3] - v[1];
	Vector K = v[3] - v[2];
	Vector L = v[3] - v[7];
	volume4 = std::abs((J.vectorproduct(K)).scalarproduct(L)) * (1.0 / 6.0);
	Vector M = v[5] - v[1];
	Vector N = v[5] - v[2];
	Vector O = v[5] - v[7];
	volume5 = std::abs((M.vectorproduct(N)).scalarproduct(O)) * (1.0 / 6.0);
	Vector P = v[6] - v[2];
	Vector Q = v[6] - v[5];
	Vector R = v[6] - v[7];
	volume6 = std::abs((P.vectorproduct(Q)).scalarproduct(R)) * (1.0 / 6.0);
	volume = volume1 + volume2 + volume3 + volume4 + volume5 + volume6;
	this->volume = volume;
	return volume;
}

double Hexahedron::getWeight() {
	double weight;
	Material m = getM();
	weight = this->volume * m.getDensity();
	return weight;
}

//get the centre of the cell
//divide the sum of all vertices coordinate by 6
Vector Hexahedron::getCentre() {
	std::vector<Vector> v = getV();
	Vector centre;
	Vector total = v[0] + v[1] + v[2] + v[3] + v[4] + v[5] + v[6] + v[7];
	centre = total.divide(8);
	return centre;
}