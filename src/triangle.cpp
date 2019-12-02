
#include "triangle.h"

//calculate the volume of this cell
//execute one time of vector calculation

double Triangle :: getarea() {
	string RootArea = getParam(10);
	if (RootArea == "e") return -1;
	double RArea = stof(RootArea);
	return RArea*RArea;
}




 void Triangle::Circumcircle(Vector &A, Vector &B, Vector &C){
	Vector AB,BC;
	AB.midpoint(A,B); //Midpoint AB
	BC.midpoint(B,C); //Midpoint AB
	float slopeAB = -1/AB.slope(A,B); //negative reciprocol of slope AB
	float slopeBC = -1/BC.slope(B,C); //negative reciprocol of slope BC

	// y = mx + b
	// solve for b
	float bAB = AB.gety() - slopeAB * AB.getx();
	float bBC = BC.gety() - slopeBC * BC.getx();

	// solve for x & y
	// x = (b1 - b2) / (m2 - m1)
	float x = (bAB - bBC) / (slopeBC - slopeAB);

	circumcentre.SetVector(id,x,(slopeAB * x) + bAB,A.gety());
	radius = circumcentre.length(B); //Length OB
	delete &AB,&BC;
}

Vector Triangle::getCircumcentre() {
	  return this->circumcentre;
}

bool Triangle::isPointInCircumcircle(float px, float py){

	double distance = sqrt( (double)(circumcentre.getx()-px)*(circumcentre.getx()-px) + (circumcentre.gety()-py)*(circumcentre.gety()-py));
    if(distance <= radius) return true;
	else return false;

}

float Triangle::getRadius() {
	  return this->radius;
}


bool Triangle::isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py){
	double Area = getarea();
	float p0x = p0.getx();
	float p0y = p0.gety();
	float p1x = p1.getx();
	float p1y = p1.gety();
	float p2x = p2.getx();
	float p2y = p2.gety();

	double s = 1/(2*Area)*(p0y*p2x - p0x*p2y + (p2y - p0y)*px + (p0x - p2x)*py);
	double t = 1/(2*Area)*(p0x*p1y - p0y*p1x + (p0y - p1y)*px + (p1x - p0x)*py);
	//std::cout << s << "  " << t << std::endl;
	if (s>0 && t>0 && 1-s-t>0) {
		return true;
	}
	else return false;
}
