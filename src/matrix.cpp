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
Matrix::Matrix( float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33) { //constructor
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

void Matrix::SetMatrix(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33) {
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

	// Function to print the matrix 
	void Matrix::displayMatrix(int mat[N][N])
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				printf("%2d ", mat[i][j]);

			printf("\n");
		}
		printf("\n");
	}


	/*---------------------------------------------------------*/
//determinant calculation (done using the maths formula)
	float Matrix::det(float m) {
		m = ((m11*((m22*m33) - (m23*m32))) - (m12* ((m21*m33) - (m23*m31))) + (m13* ((m21*m32) - (m22*m31))) );
		return m;
	}


	/*---------------------------------------------------------*/
//calculating the inverse - currently outputting incorrect values
	/*
	void Matrix::inverse(int mat[N][N]) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) 
				m = (((mat[(j + 1) % 3][(i + 1) % 3] * mat[(j + 2) % 3][(j + 2) % 3]) - (mat[(j + 1) % 3][(i + 2) % 3] * mat[(j + 2) % 3][(i + 1) % 3])) / m);
					printf("%2d ", mat[i][j]);

			printf("\n");
		}
		printf("\n");
	} */
