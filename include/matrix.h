
#pragma once

#include <vector> 
/* matrix.h
matrix header for matrix sums used in circumcircle calculations 
Created by Edward Percy 12/2019.
*/

using namespace std;

class Matrix {
public:
#define N 3

	float m;
	Matrix();
	Matrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33); //initialise
	Matrix(const Matrix &m2);
	void SetMatrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33);
	//initialise 3x3 matrix array
	int mat[N][N];
	void identity(Matrix m); //identity matrix
	void inverse();
	vector<double> Multiply1X3(vector<double> &Vec);
	//void inverse(int mat[N][N]); //inverse matrix function
	double getMatrix(int m);
	void rotateMatrix(int mat[][N]); //rotate matrix 90 degrees anti clockwise function
	float det(float m); //determinant function

private: //different numbers in the matrix are identified in the same way as in the group task presentation pdf
	double m11;
	double m12;
	double m13;
	double m21;
	double m22;
	double m23;
	double m31;
	double m32;
	double m33;
};
