/** @file
* Stores the material data for the cell
*/
/** Brief description
* stores the ID, density, name and hex colour for the material
*/
#include "material.h"

//Create Material with Default Value
Material::Material()
{
  this->MatID = 0;
  this->Density = 0;
}

//Create Material by Overload Constructor
Material::Material(int RCMat, int RCDen, string RCCol, string RCNam){
	this->MatID = RCMat;
	this->Density = RCDen;
	this->MatName = RCNam;
	this->Colour = RCCol;
}

//Destructor
Material::~Material()
{
}

//Create Material by Setup Function
void Material::setMaterial(int RCMat, int RCDen, string RCCol, string RCNam){
	this->MatID = RCMat;
	this->Density = RCDen;
	this->MatName = RCNam;
	this->Colour = RCCol;
}

//Accessor Functions
int Material::getMatID(){
	return this->MatID;
}
string Material::getColour(){
	return this->Colour;
}
int Material::getDensity(){
	return this->Density;
}
string Material::getName(){
	return this->MatName;
}
