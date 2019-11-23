#pragma once

#include "cell.h"

class Pyramid : public cell {
public:
	double getvolume();
	double getWeight();
	Vector getCentre();
};