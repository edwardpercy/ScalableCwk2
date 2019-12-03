/** @file
* This file handles matrices for model loader 
*/
/** Brief description
* It can currently calculate the determinant of a 3x3 matrix as well as rotate it 90 degrees anti clockwise.
*/
//Matrix source file by Hana Makhlouf as part of H62PEP
//The matrix class is a work in progress. It can currently calculate the determinant
//of a 3x3 matrix as well as rotate it 90 degrees anti clockwise

//The code to find the inverse is not working right now. The class is not linked to the rest of the classes yet


#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "matrix.h"
using namespace std;

/*-- -------------------------------------------------------*/
Matrix::Matrix( double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33) { //constructor
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

vector<double> Matrix::getMatrix() { //diagonals are 1
	vector<double> res;
	res.push_back(m11);
	res.push_back(m21);
	res.push_back(m31);
	res.push_back(m12);
	res.push_back(m22);
	res.push_back(m32);
	res.push_back(m13);
	res.push_back(m23);
	res.push_back(m33);

	return res;
}
	/*---------------------------------------------------------*/
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


	/*---------------------------------------------------------*/
//determinant calculation (done using the maths formula)
	float Matrix::det(float m) {
		m = ((m11*((m22*m33) - (m23*m32))) - (m12* ((m21*m33) - (m23*m31))) + (m13* ((m21*m32) - (m22*m31))) );
		return m;
	}


	/*---------------------------------------------------------*/
//calculating the inverse - currently outputting incorrect values
	
	void Matrix::inverse() {
		// computes the inverse of a matrix m
		double det = m11 * (m22 * m33 - m32 * m23) -
					m12 * (m21 * m33 - m23 * m31) +
					m13 * (m21 * m32 - m22 * m31);

		double invdet = 1 / det;

		SetMatrix((m22 * m33 - m32 * m23) * invdet,
		(m13 * m32 - m12 * m33) * invdet,
		(m12 * m23 - m13 * m22) * invdet,
		(m23 * m31 - m21 * m33) * invdet,
		(m11 * m33 - m13 * m31) * invdet,
		(m21 * m13 - m11 * m23) * invdet,
		(m21 * m32 - m31 * m22) * invdet,
		(m31 * m12 - m11 * m32) * invdet,
		(m11 * m22 - m21 * m12) * invdet);
	} 

	vector<double> Matrix::Multiply1X3(vector<double> &Vec) {
		vector<double> res;
		res.push_back((Vec[0] * m11) + (Vec[1] * m21) + (Vec[2] * m31));
		res.push_back((Vec[0] * m12) + (Vec[1] * m22) + (Vec[2] * m32));
		res.push_back((Vec[0] * m13) + (Vec[1] * m23) + (Vec[2] * m33));

		return res;
	}
