
/* vector.h
vector header for storing XYZ and XY vectors from node and .tri files
Created by Edward Percy 12/2019.
*/

#ifndef vector_h
#define vector_h


#include <iostream>
 
#include <math.h>
using namespace std;

class Vector{
public:

// Overload + and - operator to add two 2 vectors
	Vector operator+(Vector v);
	Vector operator-(Vector v);

	Vector();
	Vector( double x, double y, double z ); //initialise
    Vector( double x, double y);
    Vector(const Vector &v2);
    
	void SetVector(int ID,double x, double y, double z);
	void print();

	//add, subtract,divide, scalar and vector product with no operator overloading
    void add( Vector v );
    bool equal( Vector v );
    void subtract( Vector v);
    float scalarproduct (Vector v);
    Vector vectorproduct (Vector v);
    void midpoint( Vector a, Vector b);
    double slope( Vector from, Vector to);
	Vector divide(int n);
    double length(Vector B);

    double getx(); //{ return x; }
    double gety(); //{ return y; }
    double getz(); //{ return z; }
	int getID(); //{ return z; }


private:
    int ID;
    double x;
    double y;
    double z;

};


#endif /* vector_h */
