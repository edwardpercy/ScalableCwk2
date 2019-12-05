#include "catch.hpp"
#include "../include/mesh.h"


TEST_CASE( "Mesh created", "[Mesh]" ) {
    Mesh M = Mesh();
    REQUIRE( M.NumberVertices() == 0 );
    REQUIRE( M.NumberCells() == 0 );
    REQUIRE( M.NumberTriangles() == 0 );
}


TEST_CASE( ".Tri File loaded", "[LoadMesh]" ) {
    Mesh M = Mesh();
    M.LoadMesh("../resources/triangulation_files/triangulation#1.tri");
    
    REQUIRE( M.NumberVertices() == 1467);
    REQUIRE( M.NumberTriangles() == 2620);
}

TEST_CASE( ".node File loaded", "[LoadNodes]" ) {
    Mesh M = Mesh();
    M.LoadMesh("../resources/vertex_files/vertices#1.node");
    
    REQUIRE( M.NumberVertices() == 22);
 
}

TEST_CASE( ".Tri File Saved", "[SaveMesh]" ) {
    Mesh M = Mesh("../resources/triangulation_files/triangulation#1.tri");
    M.SaveMesh("triangulation#1_copy.node");

    Mesh MCopy = Mesh("triangulation#1_copy.node");
    REQUIRE( MCopy.NumberVertices() == 1467);
    REQUIRE( MCopy.NumberTriangles() == 2620);

}

TEST_CASE( ".node File Saved", "[SaveNodes]" ) {
    Mesh M = Mesh("../resources/vertex_files/vertices#1.node");
    M.SaveMesh("vertices#1_copy.node");

    Mesh MCopy = Mesh("vertices#1_copy.node");
    REQUIRE( MCopy.NumberVertices() == 22);
}

TEST_CASE( "CircumcirclesCheck", "[CircumcirclesCheck]" ) {
    Mesh M = Mesh("../resources/triangulation_files/triangulation#2.tri");
    Vector p = Vector(65.674, 1.48582, 994);
    REQUIRE(M.CircumcirclesCheck(p) == 4);

}

TEST_CASE( "Delaunay Check", "[DelaunayCheck]" ) {
    Mesh M1 = Mesh("../resources/triangulation_files/triangulation#1.tri");
    Mesh M2 = Mesh("../resources/triangulation_files/triangulation#2.tri");
    Mesh M3 = Mesh("../resources/triangulation_files/triangulation#3.tri");
    Mesh M4 = Mesh("../resources/triangulation_files/triangulation#4.tri");

    REQUIRE(M1.DelaunayCheck() == false);
    REQUIRE(M2.DelaunayCheck() == false);
    REQUIRE(M3.DelaunayCheck() == true);
    REQUIRE(M4.DelaunayCheck() == false);
}

TEST_CASE( "Invalid dimension", "[InvalidDimensions]" ) {
    Mesh M = Mesh();
    REQUIRE_THROWS_WITH(M.LoadMesh("../resources/triangulation#5.tri"),"ERROR: Invalid dimensions entered");

}

TEST_CASE( "Invalid file", "[InvalidFile]" ) {
    Mesh M = Mesh();
    REQUIRE_THROWS_WITH(M.LoadMesh("triangulation#6.tri"),"ERROR: File could not be opened");

}


TEST_CASE( "Invalid Number of Vertices per cell", "[InvalidVpC]" ) {
    Mesh M = Mesh();
    REQUIRE_THROWS_WITH(M.LoadMesh("../resources/triangulation#7.tri"),"ERROR: 3 vertices shapes only supported currently");

}


double function (double x, double y){
        return x*3 + y*3;
}



TEST_CASE( "Integrate Function over mesh (Constant)", "[ConstantIntegration]" ) {
    Mesh M = Mesh("../resources/triangulation_files/triangulation#1.tri");
    
    for (int i(0);i < M.NumberTriangles();i++){
        M.CalcCircumcircle(i);

    }

    double I = M.integrate(function, 0);
    cout << "Constant Approx: " << I << endl;
    REQUIRE(I == Approx(2920231.515));
    

}

TEST_CASE( "Integrate Function over mesh (Linear)", "[LinearIntegration]" ) {
    Mesh M = Mesh("../resources/triangulation_files/triangulation#1.tri");
    double I = M.integrate(function, 1);
    cout << "Linear Approx: " << I << endl;
    REQUIRE(I == Approx(2920218.269));

}