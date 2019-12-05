/* triangle.cpp
Main shape TRIANGLE class to do functions related to circumcircle and point checks specific to the triangle 
not other cells

Available functions:
Circumcircle (using MATRIX or other METHOD)
get radius
ispointintriangle check

Constructors/Copy constructors in PARENT class cell
Created by Edward Percy 12/2019.
*/


#include "../include/triangle.h"

//calculate the volume of this cell
//execute one time of vector calculation

double Triangle :: getarea() { //Returns the area from the parameter list loaded (Backup in mesh.cpp if parameter not loaded or found)
	string RootArea = getParam(10);
	if (RootArea == "e"){ //Returns an error if the area parameter is not found
		throw("Parameter area not found");
		return -1;
	}

	double RArea = StringToNumber<double>(RootArea);//Converts the parameter to a double value from a string as loaded and stoired
	area = RArea*RArea; //Aread is root so neeed squaring 
	return area;
}

//Circumcircle check using matrices (OTHER method below)
void Triangle::Circumcircle(Vector &A, Vector &B, Vector &C){ //Takes three vectors as input
	//Define Right hand side of m,atrix (Formula in appendix 2 of given sheet)
	Matrix RhsM( A.getx(), B.getx(), C.getx(),  A.gety(), B.gety(), C.gety(), 1,1,1);

	//calculates inverse of matrix
	RhsM.inverse();

	//Defines the left hand side of the matrix
	vector<double> LhsM,res;
	LhsM.push_back((A.getx()*A.getx()) + (A.gety()*A.gety()));
	LhsM.push_back((B.getx()*B.getx()) + (B.gety()*B.gety()));
	LhsM.push_back((C.getx()*C.getx()) + (C.gety()*C.gety()));
	
	//Multiplies 3x3 inverse by 1x3 
	res = RhsM.Multiply1X3(LhsM);

	//calculates ciurcumcentre valies Ox Oy 
	double Ox = res[0] * 0.5;
	double Oy = res[1] * 0.5;
	
	//Save in memory for use later (less runtime processing )
	circumcentre.SetVector(id,Ox,Oy,A.gety());
	
	//calculates the radius using the formulA IN appendix 2
	radius = sqrt(res[2] + Ox*Ox + Oy*Oy);
	//cout << radius << " " << Ox << " " << Oy << endl;

}

//Does the same circumcircle check as above but is slightly slower (however worked better on jenna) Above uses matrix method below does not
 void Triangle::Circumcircle_OLDCHECK(Vector &A, Vector &B, Vector &C){
	Vector AB,BC;
	AB.midpoint(A,B); //Midpoint AB
	BC.midpoint(B,C); //Midpoint AB
	double slopeAB = -1/AB.slope(A,B); //negative reciprocol of slope AB
	double slopeBC = -1/BC.slope(B,C); //negative reciprocol of slope BC
	
	// y = mx + b
	// solve for b
	double bAB = AB.gety() - slopeAB * AB.getx();
	double bBC = BC.gety() - slopeBC * BC.getx();
	
	
	// solve for x & y
	// x = (b1 - b2) / (m2 - m1)
	double x = (bAB - bBC) / (slopeBC - slopeAB);

	
	circumcentre.SetVector(id,x,(slopeAB * x) + bAB,A.gety());
	//cout << circumcentre.length(A) << " " << circumcentre.length(B)  << " " << circumcentre.length(C) << endl;
	//cout << A.getx() << " " << A.gety() << " "<< A.getz()<< " " << B.getx() << " " << B.gety() << " " <<B.getz() << " " << C.getx() << " " << C.gety() << " "<< C.getz() <<endl;


	radius = circumcentre.length(B); //Length OB
}

Vector Triangle::getCircumcentre() const{ //Retuns th vector circumcentre
	  return this->circumcentre;
}

//checks if the point is within the circumcircle of the triangle
bool Triangle::isPointInCircumcircle(double px, double py){
	//calculates distance between circumcentre and poitn and then compares to the radius to do the check
    double distance = sqrt(pow(circumcentre.getx() - px, 2) +  pow(circumcentre.gety() - py , 2)*1);
	if(distance < radius) return true;
	else return false;

}

float Triangle::getRadius() { //get radius and return
	  return this->radius;
}


//check to see if the poitn is within the triangle
bool Triangle::isPointInside(Vector &p0, Vector &p1, Vector &p2, double px, double py){
	double Area = getarea();//get triangles area from parameter list

	//define parameters
	double p0x = p0.getx();
	double p0y = p0.gety();
	double p1x = p1.getx();
	double p1y = p1.gety();
	double p2x = p2.getx();
	double p2y = p2.gety();

	//calculate s and t parameters
	double s = 1/(2*Area)*(p0y*p2x - p0x*p2y + (p2y - p0y)*px + (p0x - p2x)*py);
	double t = 1/(2*Area)*(p0x*p1y - p0y*p1x + (p0y - p1y)*px + (p1x - p0x)*py);
	//std::cout << s << "  " << t << std::endl;

	//comparison from formula on google to determine if point is inside triangle
	if (s>0 && t>0 && 1-s-t>0) {
		return true;
	}
	else return false;
}
