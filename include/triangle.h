#pragma once
#include <iostream>
#include "cell.h"
#include <string>

class Triangle : public cell {

private:
	Vector circumcentre;
	double radius, area;	

public:
	
	Vector getCircumcentre() const;
	float getRadius();
	double getarea();
	bool isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py);
	void Circumcircle(Vector &A, Vector &B, Vector &C);
	bool isPointInCircumcircle(double px, double py);
};