#include <string>//For string type variables

using namespace std;//For std::

#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
private:
	//Variables
	int MatID;//Unique ID
	int Density;
	string MatName;//Name
	string Colour;

public:
	//Default Constructor
	Material();

	/*Overload Constructor
	@param RCMat = Unique ID
		   RCDen = Density
		   RCCol = Colour
		   RCNam =  Name*/
	Material(int RCMat, int RCDen, string RCCol,string RCNam);

	//Destructor
	~Material();

	/*Setup Function (Just in case)
	@param RCMat = Unique ID
		   RCDen = Density
		   RCCol = Colour
		   RCNam =  Name*/
	void setMaterial(int RCMat, int RCDen, string RCCol,string RCNam);

	//Accessor Functions
	int getMatID();
			//return Unique ID

	int getDensity();
			//return Density

	string getName();
			//return Name

	string getColour();
			//return Colour in <string "HEX Color Code">
};

#endif //End of material.h
