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


#include <iostream>
#include "../include/vector.h"
#include <vector> 
using namespace std;

/*-- -------------------------------------------------------*/
Vector::Vector( double x, double y, double z ) { //constructor
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector( double x, double y) { //constructor
    this->x = x;
    this->y = y;
    this->y = 0;
}

void Vector::SetVector(int ID, double x, double y, double z) { //setting vector values using this
	this->ID = ID;
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector() { //default constructor just in case no values are entered
    this->x = 0.;
    this->y = 0.;
    this->z = 0.;
}

Vector::Vector(const Vector &v2) {
		ID = v2.ID;
        x = v2.x;
        y = v2.y;
        z = v2.z;

	} 

/*---------------------------------------------------------*/
//add function
void Vector::add( Vector v ) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}
bool Vector::equal( Vector v ) {
	if (this->x == v.x && this->y ==v.y && this->z == v.z) return true;
	else return false;
#
}

void Vector::midpoint( Vector a, Vector b) {

    this->x = (a.x + b.x) / 2;
	this->y = (a.y + b.y) / 2;

}

double Vector::length(Vector B) {

    return sqrt(((this->x - B.x) * (this->x - B.x))+((this->y - B.y) * (this->y - B.y)));
	

}

double Vector::slope( Vector from, Vector to) {

    return (to.y - from.y) / (to.x - from.x);

}

Vector Vector::divide(int n) { //divide function
	Vector vector1;
	vector1.x = this->x / n;
	vector1.y = this->y / n;
	vector1.z = this->z / n;
	
	return vector1;
}

//add function using operator overloading
Vector Vector::operator+(Vector v) { //this allows us to use + to add 2 vectors instead of using the add function above
	Vector vector1;
	vector1.x = this->x + v.x;
	vector1.y = this->y + v.y;
	vector1.z = this->z + v.z;
	return vector1;
}

/*---------------------------------------------------------*/

//subtract function
void Vector::subtract( Vector v ){
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}

//subtract function using operator overloading 
Vector Vector::operator-(Vector v) {
	Vector vector1;
	vector1.x = this->x - v.x;
	vector1.y = this->y - v.y;
	vector1.z = this->z - v.z;
	return vector1;
}

/*---------------------------------------------------------*/
//scalar product function
float Vector::scalarproduct( Vector v ){ //dot product
    float scalarresult = this->x*v.x + this->y*v.y + this->z*v.z;
    return scalarresult;
}

//vector product function
Vector  Vector:: vectorproduct( Vector v){ //cross product
    float vectorresult1 = this->y*v.z - this->z*v.y;
    float vectorresult2 = this->z*v.x - this->x*v.z;
    float vectorresult3 = this->x*v.y - this->y*v.x;
    
    Vector final(vectorresult1,vectorresult2,vectorresult3);
    
    return final;
}
/*---------------------------------------------------------*/
//print function - prints vectors
void Vector::print() {

	cout << this-> x << "," << this-> y << "," << this-> z << endl;

}

double Vector::getx(){ return x; }
double Vector::gety(){ return y; }
double Vector::getz(){ return z; }
int Vector::getID() { return ID; }

/*---------------------------------------------------------*/
