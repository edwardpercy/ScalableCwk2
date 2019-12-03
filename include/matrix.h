
//Matrix header file by Hana Makhlouf as part of H62PEP

//The matrix class is a work in progress. It can currently calculate the determinant

//of a 3x3 matrix as well as rotate it 90 degrees anti clockwise



//The code to find the inverse is not working right now. The class is not linked to the rest of the classes yet
#pragma once

#include <vector> 
using namespace std;

class Matrix {
public:
#define N 3



	float m;

	Matrix();

	Matrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33); //initialise

	void SetMatrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33);



	//initialise 3x3 matrix array

	int mat[N][N];

	//int i,j; //uncomment this for inverse function



	//Functions

	void identity(Matrix m); //identity matrix

	void inverse();

	vector<double> Multiply1X3(vector<double> &Vec);
	//void inverse(int mat[N][N]); //inverse matrix function
	vector<double> getMatrix();

	void rotateMatrix(int mat[][N]); //rotate matrix 90 degrees anti clockwise function

	float det(float m); //determinant function



private: //different numbers in the matrix are identified in the same way as in the group task presentation pdf

	float m11;

	float m12;

	float m13;

	float m21;

	float m22;

	float m23;

	float m31;

	float m32;

	float m33;



};
