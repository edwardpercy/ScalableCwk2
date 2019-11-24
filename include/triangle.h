#pragma once

#include "cell.h"

class Triangle : public cell {
public:
	double getvolume();
	Vector getCentre();
};