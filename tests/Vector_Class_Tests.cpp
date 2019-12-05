#include "catch.hpp"
#include "../include/vector.h"



TEST_CASE( "Create Vector", "[Vector]" ) {
    Vector V = Vector(321,33.22,2);
    REQUIRE(V.getx() == 321);
    REQUIRE(V.gety() == 33.22);
    REQUIRE(V.getz() == 2);
}

TEST_CASE( "Equality Vector Test", "[VectorEquality]" ) {
    Vector V = Vector(321,33.22,2);
    Vector V2 = Vector(321,33.22,2);
    Vector V3 = Vector(1,2,2);
    REQUIRE(V.equal(V2) == true);
    REQUIRE(V.equal(V3) == false);
}

TEST_CASE( "Subtract Vector Test", "[VectorSubtract]" ) {
    Vector V = Vector(9,8,7);
    Vector V2 = Vector(1,1,1);
    V.subtract(V2);
    REQUIRE(V.getx()== 8);
    REQUIRE(V.gety()== 7);
    REQUIRE(V.getz()== 6);

    
}

