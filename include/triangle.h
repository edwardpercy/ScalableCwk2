#pragma once
#include <iostream>
#include "cell.h"
#include <string>

class Triangle : public cell {
	
public:
	Vector circumcentre;
	float radius;
	Vector getCircumcentre();
	float getRadius();
	double getarea();
	bool isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py);
	void Circumcircle(Vector &A, Vector &B, Vector &C);
	bool isPointInCircumcircle(float px, float py);
};