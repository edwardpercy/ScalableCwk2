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
}
// /main.cpp------------------------------------------------------------------
