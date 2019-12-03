
#include "triangle.h"

//calculate the volume of this cell
//execute one time of vector calculation

double Triangle :: getarea() {
	string RootArea = getParam(10);
	if (RootArea == "e") return -1;
	double RArea = stof(RootArea);
	area = RArea*RArea;
	return area;
}



void Triangle::Circumcircle(Vector &A, Vector &B, Vector &C){
	Matrix RhsM( A.getx(), B.getx(), C.getx(),  A.gety(), B.gety(), C.gety(), 1,1,1);
	RhsM.inverse();

	vector<double> LhsM,res;
	LhsM.push_back((A.getx()*A.getx()) + (A.gety()*A.gety()));
	LhsM.push_back((B.getx()*B.getx()) + (B.gety()*B.gety()));
	LhsM.push_back((C.getx()*C.getx()) + (C.gety()*C.gety()));
	
	res = RhsM.Multiply1X3(LhsM);
	
	double Ox = res[0] * 0.5;
	double Oy = res[1] * 0.5;
	
	circumcentre.SetVector(id,Ox,Oy,A.gety());

	radius = sqrt(res[2] + Ox*Ox + Oy*Oy);
	//cout << radius << " " << Ox << " " << Oy << endl;
	
	delete &RhsM,&LhsM,&res;
}


//  void Triangle::Circumcircle(Vector &A, Vector &B, Vector &C){
// 	Vector AB,BC;
// 	AB.midpoint(A,B); //Midpoint AB
// 	BC.midpoint(B,C); //Midpoint AB
// 	double slopeAB = -1/AB.slope(A,B); //negative reciprocol of slope AB
// 	double slopeBC = -1/BC.slope(B,C); //negative reciprocol of slope BC
	
// 	// y = mx + b
// 	// solve for b
// 	double bAB = AB.gety() - slopeAB * AB.getx();
// 	double bBC = BC.gety() - slopeBC * BC.getx();
	
	
// 	// solve for x & y
// 	// x = (b1 - b2) / (m2 - m1)
// 	double x = (bAB - bBC) / (slopeBC - slopeAB);

	
// 	circumcentre.SetVector(id,x,(slopeAB * x) + bAB,A.gety());
// 	//cout << circumcentre.length(A) << " " << circumcentre.length(B)  << " " << circumcentre.length(C) << endl;
// 	//cout << A.getx() << " " << A.gety() << " "<< A.getz()<< " " << B.getx() << " " << B.gety() << " " <<B.getz() << " " << C.getx() << " " << C.gety() << " "<< C.getz() <<endl;


// 	radius = circumcentre.length(B); //Length OB

	
// 	delete &AB,&BC;
// }

Vector Triangle::getCircumcentre() const{
	  return this->circumcentre;
}

bool Triangle::isPointInCircumcircle(double px, double py){


    double distance = sqrt(pow(circumcentre.getx() - px, 2) +  pow(circumcentre.gety() - py , 2)*1);
	if(distance < radius) return true;
	else return false;

}

float Triangle::getRadius() {
	  return this->radius;
}


bool Triangle::isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py){
	double Area = getarea();
	double p0x = p0.getx();
	double p0y = p0.gety();
	double p1x = p1.getx();
	double p1y = p1.gety();
	double p2x = p2.getx();
	double p2y = p2.gety();

	double s = 1/(2*Area)*(p0y*p2x - p0x*p2y + (p2y - p0y)*px + (p0x - p2x)*py);
	double t = 1/(2*Area)*(p0x*p1y - p0y*p1x + (p0y - p1y)*px + (p1x - p0x)*py);
	//std::cout << s << "  " << t << std::endl;
	if (s>0 && t>0 && 1-s-t>0) {
		return true;
	}
	else return false;
}
