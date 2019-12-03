// main.cpp-------------------------------------------------------------------
/** @file
* This file starts the program
*/
/** Brief description
* Initiates QT and opens the main windows
*/
#include "main.h"

double function (double x, double y){
        return x*2 + y/5;
}


int main( int argc, char** argv )
{
   
	M = Mesh();
    M.LoadMesh("triangulation#1.tri");
   

    //AREA
    cout << "Area of triangle ID:10 " <<  M.TriangleArea(10) << "\n" << endl;

    //WHICH POINT IS THE TRIANGLE IN
    int TriangleID = M.isPointContained(70,-2);

    cout << "The point is within triangle with ID: " << TriangleID << "\n" << endl;

    M.CalcCircumcircle(0); //Calculates the triangles circumcircle

    if(M.DelaunayCheck()==true) cout << "Mesh is Delaunay" << endl;
    else cout << "Mesh is NOT Delaunay" << endl;

    M.SaveMesh("test.tri");

    cout << "Constrant Approx: " << M.integrate(function, 0) << endl;
    cout << "Linear Approx: " << M.integrate(function, 1) << endl;

}
// /main.cpp------------------------------------------------------------------
