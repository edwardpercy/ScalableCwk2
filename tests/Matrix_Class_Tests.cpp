#include "catch.hpp"
#include "../include/matrix.h"



TEST_CASE( "Inverse Matrix", "[Matrix]" ) {
    Matrix M = Matrix(1.33223443,123.323,323,2.2,3213.32,23,3.32,32.23,33);
    M.inverse();


    REQUIRE(M.getMatrix(11) == Approx(-0.0320817349));
}

vector<double> Multiply1X3(vector<double> &Vec);

TEST_CASE( "Matrix multiplied by 1x3 vector", "[Matrix]" ) {
    Matrix M = Matrix(1,1,1,1,1,1,1,1,1);
    vector<double> in;
    in.push_back(2);
    in.push_back(2);
    in.push_back(2);
    vector<double> out = M.Multiply1X3(in);


    REQUIRE(out[0] == 6);
    REQUIRE(out[1] == 6);
    REQUIRE(out[2] == 6);
}