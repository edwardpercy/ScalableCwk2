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
   
	M = Mesh();
    M.LoadMesh("triangulation#4.tri");
   

    //AREA
    cout << "Area of triangle ID:10 " <<  M.TriangleArea(10) << "\n" << endl;

    //WHICH POINT IS THE TRIANGLE IN
    int TriangleID = M.isPointContained(70,-2);

    cout << "The point is within triangle with ID: " << TriangleID << "\n" << endl;

    M.CalcCircumcircle(0); //Calculates the triangles circumcircle

    if(M.DelaunayCheck()==true) cout << "Mesh is Delaunay" << endl;
    else cout << "Mesh is Delaunay" << endl;
    M.SaveMesh("test.tri");
    
}
// /main.cpp------------------------------------------------------------------
