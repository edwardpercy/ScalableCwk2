#pragma once

#include "cell.h"

class Tetrahedron : public cell {
public:
	double getvolume();
	double getWeight();
	Vector getCentre();
};