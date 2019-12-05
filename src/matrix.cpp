/* matrix.cpp
Matrix class used for the calculation of the circumcenter where
vectors are required.
Ability to Inverse/Multiply 3x3 by 1x3/ rotate Matrix and determinant of the matrix

Created by Edward Percy 12/2019.
*/

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "../include/matrix.h"
using namespace std;

/*-- -------------------------------------------------------*/
Matrix::Matrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33) { //Constructor if values entered
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

Matrix::Matrix(const Matrix &m2) { //Copy - constructor for the matrix class
		m11 = m2.m11;
		m12 = m2.m12;
		m13 = m2.m13;
		m21 = m2.m21;
		m22 = m2.m22;
		m23 = m2.m23;
		m31 = m2.m31;
		m32 = m2.m32;
		m33 = m2.m33;
} 


void Matrix::inverse() { // computes the inverse of a matrix M 3x3
	double det = m11 * (m22 * m33 - m32 * m23) -
				m12 * (m21 * m33 - m23 * m31) +
				m13 * (m21 * m32 - m22 * m31); //Calculates the determinant for 3x3

	double invdet = 1 / det; //Finds the inverse of the det

	SetMatrix((m22 * m33 - m32 * m23) * invdet, //Calculates the final inversed matrix 
	(m13 * m32 - m12 * m33) * invdet,
	(m12 * m23 - m13 * m22) * invdet,
	(m23 * m31 - m21 * m33) * invdet,
	(m11 * m33 - m13 * m31) * invdet,
	(m21 * m13 - m11 * m23) * invdet,
	(m21 * m32 - m31 * m22) * invdet,
	(m31 * m12 - m11 * m32) * invdet,
	(m11 * m22 - m21 * m12) * invdet);
} 

vector<double> Matrix::Multiply1X3(vector<double> &Vec) { //Used in the computation of the circumcenter to multiply a 3x3 matrix by a 1x3 vector
	vector<double> res;
	res.push_back((Vec[0] * m11) + (Vec[1] * m21) + (Vec[2] * m31)); //adds the result to the vector 1x3
	res.push_back((Vec[0] * m12) + (Vec[1] * m22) + (Vec[2] * m32));
	res.push_back((Vec[0] * m13) + (Vec[1] * m23) + (Vec[2] * m33));

	return res; //returns a 1x3 vector
}

//Used to setup the matrix with a 3x3 data
void Matrix::SetMatrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33) { 
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

Matrix::Matrix() { //default constructor just in case no values are entered
	this->m11 = 0;
	this->m12 = 0;
	this->m13 = 0;
	this->m21 = 0;
	this->m22 = 0;
	this->m23 = 0;
	this->m31 = 0;
	this->m32 = 0;
	this->m33 = 0;
}
/*---------------------------------------------------------*/
//identity matrix for a 3x3 matrix
void Matrix::identity(Matrix m) { //diagonals are 1
	this->m11 = 1;
	this->m12 = 0;
	this->m13 = 0;
	this->m21 = 0;
	this->m22 = 1;
	this->m23 = 0;
	this->m31 = 0;
	this->m32 = 0;
	this->m33 = 1;
}

double Matrix::getMatrix(int m) { //Returns the specified matrix value
	if (m==11) return m11;
	else if (m==21) return m21;
	else if (m==31) return m31;
	else if (m==21) return m21;
	else if (m==22) return m22;
	else if (m==23) return m23;
	else if (m==31) return m31;
	else if (m==32) return m32;
	else if (m==33) return m33;
	else {
		throw("ERROR: Invalid matrix parameter entered");
		return 0; //returns 0 if the input is invalid and throws an error
	}
}

//rotation 
// A function to rotate a N x N matrix by 90 degrees in anti-clockwise direction 
void Matrix::rotateMatrix(int mat[][N])
{
	// Consider all squares one by one 
	for (int x = 0; x < N / 2; x++)
	{
		// Consider elements in group of 3 in  
		// current square 
		for (int y = x; y < N - x - 1; y++)
		{
			// store current cell in temp variable 
			int temp = mat[x][y];

			// move values from right to top 
			mat[x][y] = mat[y][N - 1 - x];

			// move values from bottom to right 
			mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

			// move values from left to bottom 
			mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

			// assign temp to left 
			mat[N - 1 - y][x] = temp;
		}
	}
}

//determinant calculation (done using the maths formula)
float Matrix::det(float m) {
	m = ((m11*((m22*m33) - (m23*m32))) - (m12* ((m21*m33) - (m23*m31))) + (m13* ((m21*m32) - (m22*m31))) );
	return m;
}



	

