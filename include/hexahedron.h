#pragma once

#include "cell.h"

class Hexahedron : public cell {
public:
	double getvolume();
	double getWeight();
	Vector getCentre();
};