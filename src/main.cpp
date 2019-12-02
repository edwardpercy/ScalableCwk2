// main.cpp-------------------------------------------------------------------
/** @file
* This file starts the program
*/
/** Brief description
* Initiates QT and opens the main windows
*/
#include "main.h"

int main( int argc, char** argv )
{
    string FileName = "triangulation#1.tri";
	M = Model();
    M.LoadModel(FileName);

    //AREA
    cout << "Area of triangle ID:10 " <<  M.TriangleArea(10) << "\n" << endl;

    //WHICH POINT IS THE TRIANGLE IN
    int TriangleID = M.isPointContained(70,-2);

    cout << "The point is within triangle with ID: " << TriangleID << "\n" << endl;

    M.CalcCircumcircle(0); //Calculates the triangles circumcircle

    M.CircumcirclesCheck(70,-2); //Checks all triangles to see which circumcircl(s) the point lies within
}
// /main.cpp------------------------------------------------------------------
