#include "catch.hpp"
#include "../include/triangle.h"



TEST_CASE( "Create Triangle", "[Triangle]" ) {

    Triangle *T = new Triangle;		
	T->setCell(0);
	T->setVertices(10);
	T->setVertices(6);
	T->setVertices(3);

    REQUIRE( T->getCellID() == 0 );
    REQUIRE( T->getVerticesID(0) == 10 );
    REQUIRE( T->getVerticesID(1) == 6 );
    REQUIRE( T->getVerticesID(2) == 3 );
}


TEST_CASE( "Parameter test", "[TriangleParameter]" ) {

    Triangle *T = new Triangle;		
	T->setCell(0,"0 0 0 1212 1.23232323 test");
	T->setVertices(10);
	T->setVertices(6);
	T->setVertices(3);

    REQUIRE( T->getParam(3) == "1212" );
    REQUIRE( T->getParam(0) == "0" );

}


TEST_CASE( "Circumcircle", "[CircumcircleTest]" ) {

    Triangle *T = new Triangle;		
	T->setCell(0);
	T->setVertices(10);
	T->setVertices(6);
	T->setVertices(3);

    Vector A = Vector(0.232,3,2.32);
    Vector B = Vector(3.2,8.321,5);
    Vector C = Vector(0.1,3,9);

    Vector out;

    T->Circumcircle(A, B, C);
    out  = T->getCircumcentre();
    REQUIRE( T->getRadius() == Approx(3.52569) );
    REQUIRE( out.getx() == Approx(0.1660000089 ) );
    REQUIRE( out.gety() == Approx(6.5250749728 ) );
    REQUIRE( out.getz() == Approx(3.0  ) );

}


