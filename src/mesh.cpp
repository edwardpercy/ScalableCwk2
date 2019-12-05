/* mesh.cpp
Main Mesh class used for handling the main functions and also handling the classes for object creation
of Triangles and Vertices plus the ability to expand to other shapes with the cell class

Available functions:
~ SaveMech, LoadMesh, CircumcirclesCheck, DelaunayCheck, Calccircumcenter, Set vertices, Set triangles, Triangle Area
~ isPointContained? - Checks to see if the point is within a triangle
~ Get, Set functions for vetices,cells and triangles
~ GenerateDelaunayTriangle NOT FINISHED 

Constructors/Copy constructors and destructors available also
Created by Edward Percy 12/2019.
*/

#include "../include/mesh.h"
#include <vector>
#include <cstring>

Mesh::Mesh() { //Mesh class default constructor
}
Mesh::Mesh(string FileName) { //Mesh class constructor with compact filename to automatically load .tri file
	LoadMesh(FileName);
}
Mesh::~Mesh() { //Destrucotor to clear memory lists 
	//Clears all the vector lists from memory
	Vertices.clear();
	Triangles.clear();
}

Mesh::Mesh(const Mesh &m2) { //Copy-constructor 
	//Copies all required variables and parameters to new object
		Vertices = m2.Vertices;
		Cells = m2.Cells;
		Triangles = m2.Triangles;
		x = m2.x;
		y = m2.y;
		z = m2.z;
		V = m2.V;
	} 

void Mesh::SaveMesh(string FileName) { //Saves the mesh into the specified file name
	std::ofstream file(FileName.c_str()); //Starts the OUT stream for the file with filname specified

	if (!file){ //Throws an error if the file creation was unsucessful 
		throw("ERROR: Error saving to file");
	}

	file << Vertices.size() << " " << dimensions << " " << 0; //Writes the initialising line to define the arguments for the vertices#
	//Checks the dimensions - Currently only 2 and 3 supported XYZ or XY
	if (dimensions == 3){ //XYZ Tri file
		for (int i = 0;i < Vertices.size();i++){ //Loops through all vertices and saves them line by line
			file << "\n" << i << " " << Vertices[i].getx() << " " << Vertices[i].gety() << " " << Vertices[i].getz();
		}
	}
	else if (dimensions == 2){ //XY -Node file
		for (int i = 0;i < Vertices.size();i++){ //Loops through all vertices and saves them line by line
			file << "\n" << i << " " << Vertices[i].getx() << " " << Vertices[i].gety();
		}
	}

	//Checks to see if triangles have been loadedc into the mesh and if so it will write the initing line for the cells and write below
	if (Triangles.size() > 0) file << "\n" << Triangles.size() << " " << 3 << " " << 17; 

	//Writes line by line the triangles/Cells plus the parameters
	for (int i = 0;i < Triangles.size();i++){
		vector<int> p = Triangles[i].getVertices(); //Gets the vertices IDs from the triangles
		file << "\n" << i << " " << p[0] << " " << p[1] << " " << p[2] << " "; //Writes the POINT IDs 
		for (int j(0);j<NoArguments;j++){ //Loops through all available parameters
			file << Triangles[i].getParam(j) << " "; //Writes the arguments for the cell at the end the same as the .tri file
		}
			
	}
	file.close(); //Closes the file when finished writing data
}

//Loads the mesh into the datastructure from either a .tri or .node file
void Mesh::LoadMesh(string FileName) { 

	//Temporary variables used for loading the file / reading it
	int temp,id ,LinesToInterate, NumCols, NumProperties = 0; 
	int iterator = 0;
    double X,Y,Z;
	vector<int> C_Vertices;
	string attributes;

	ifstream file(FileName.c_str(), ios::in); //Starts the file IN stream with specified filename ~ C_str used as C++11 required for it without

	if (!file){ //Throws an error if the file name couild not be opened
		throw("ERROR: File could not be opened");
	}
	
	//Loops through all the INITING lines. Eg: vertices, cells
	//Alllows for scalability if more types of cells want to be added to the same file or more lines of INITING are needed
	//Maybe dimension 2 or 3 in same file so three INITING lines 
	while(file>>LinesToInterate>>NumCols>>NumProperties) { 
	
		if (iterator==0){ //IF first line (READING VECTORS)
			dimensions = NumCols; //Saves the dimesntion for later saving if required
			for (int i(0);i<LinesToInterate;i++){ //Iterates through all the lines (no_points)

				//Checks the dimensions
				if (NumCols == 2) (file>>id>>X>>Y) && getline(file, attributes);
				else if (NumCols == 3) (file>>id>>X>>Y>>Z) && getline(file, attributes);
				else throw "ERROR: Invalid dimensions entered";
				//Sets the vertices with any attributes
				SetVertices(id,X,Y,Z,NumCols ,attributes);
				
			}
		}
		else{ //IF second line or further for scalabiluty? (READING TRIANGLES / OTHER SHAPES)
			NoArguments = NumCols; //Sets the number of arguments/parameters for saving the file later
			for (int i(0);i<LinesToInterate;i++){ //Loops through all cells/triangles in memory
				file>>id; //Gets the ID (First column)
				for (int v_per_cell(0);v_per_cell < NumCols ;v_per_cell++){ //Loops through the number of vertices per cell (allows for scalability as not constrained to 3 - triangle)
																			//Means that other shapes with more vetrices per cell can be used
					file>>temp; 
					C_Vertices.push_back(temp); //Stores the vectors temporarily before stored in the cell/triangles class
				}
				getline(file, attributes);	//Get the rest of the line (parameters) future versions could loop through and save as loaded but this code is currently in the cell class 
			
				//checks the type of shape 
				if (NumCols == 3) SetTriangle(id,C_Vertices[0],C_Vertices[1],C_Vertices[2],attributes); //3 vertices is triangle 
				else throw("ERROR: 3 vertices shapes only supported currently");
				C_Vertices.clear();
				
				//else if **** WRITE OTHER SHAPES HERE ****
				//else if (NumCols == 4) SetTetrahedron; (EXAMPLE)
				//else if (NumCols == 8) SetHexahedron; (EXAMPLE for future code)
				
			}
		}
		iterator +=1;
	}

	//Prints the number if triangles/vertices loaded for debugging/.testing 
	cout << "Number of triangles loaded: " << Triangles.size() << endl;
	cout << "Number of vertices loaded: " << Vertices.size() <<"\n" << endl;
	
	file.close();//Closes the file when finished
}

//Checks to see if the point is within a circucircle and if so returns the number of circumcircles whioch contain it
int Mesh::CircumcirclesCheck(Vector point){ //input a vector point (good for checking entire vector <Vector> which is in this format)
	int NumCircumcirclesContained = 0;
	bool inCircumcircle = false;

	for (int i(0);i<Triangles.size();i++){  //Loops thropugh all triangles and checks if the point is within the circumcircle
		CalcCircumcircle(i); //Calculates the triangles circumcircle and stores it in tirangles memory
		inCircumcircle = Triangles[i].isPointInCircumcircle(point.getx(),point.gety()); //Checks if the point is within circumcircle 
		vector<int> p = Triangles[i].getVertices(); //Gets the triangles verticesIDs 

		//Uses the tirangle verticesIDs to check if the point is owned by the triangle as this would not count as in circumcircle
		if (inCircumcircle == true && !Vertices[p[0]].equal(point) && !Vertices[p[1]].equal(point)  && !Vertices[p[2]].equal(point)){
			cout << "Point(" << point.getx() << "," << point.gety() << ") in circumcircle triangleID(" << i << ")    "; //Printed for debugging 
			NumCircumcirclesContained += 1; //Increments variable for output to check if true
		}
	}
	return NumCircumcirclesContained;
}

//A delaunay check to see if the current loaded mesh has all triangles with delaunay
bool Mesh::DelaunayCheck(){ 
	bool isDelaunay = true;
	for (int i(0); i < Vertices.size(); i++){ //Loops through all vertices 
		if (CircumcirclesCheck(Vertices[i]) > 0){ //Checks if the number of inCircumcircles(check) returns more than 0 (means the point is not delaunay compatible)
			cout << "PointID: "<< i << endl; //Debugging
			isDelaunay = false;
		}
	}
	cout << "\n";
	if(isDelaunay == true) return true; //Returns true or false depending on outcome
	else return false;
	

}

//Used for generating a Delaunay triangle by removing nearby triangles and connecting nodes
//NOT FULLY IMPLEMENTED as was NOT REQUIRED by spec!
//WILL be added in future versions
void Mesh::GenerateDelaunayTriangle(Vector point){ 
	int NumCircumcirclesContained = 0;
	bool inCircumcircle = false;
	int TriangleID = isPointContained(point.getx(),point.gety());
	if (TriangleID == -1){
		cout << "Point: " << point.getx() << "," << point.gety() << " not within any triangle\n" << endl;
	}
	else{
		//cout << "Point: " << point.getx() << "," << point.gety() << " within triangle: " << TriangleID << "\n" << endl;
		//START triangle ID used to search adjacent triangles HERE
		//Loops through all triangles 
		//IF algorithm to find adjacent triangles was implemented we would
		//Loop through only those here instead of all 
	}
}

//Sets the vertices from files or new inputted ones
void Mesh::SetVertices(int id,double X,double Y,double Z,int dimensions, string attributes){
	//checks dimensiosd for type of XY or XYZ
	if (dimensions == 3){
		Vector *V = new Vector; //Creates a new vector object
		V->SetVector(id,X,Y,Z); //Sends the data to the class function
		Vertices.push_back(*V); //Adds it to the vector list 
	}
	else if (dimensions == 2){
		Vector *V = new Vector(id,X,Y); //Creates a new vector object
		Vertices.push_back(*V); //Adds it to the vector list 
	}
	
}

//Sets the cell type triangle
void Mesh::SetTriangle(int id,double V1,double V2,double V3,string attributes){
	Triangle *T = new Triangle;
					
	T->setCell(id, attributes);

	//push vertices ID
	T->setVertices(V1);
	T->setVertices(V2);
	T->setVertices(V3);

	Triangles.push_back(*T);
}

vector<Vector> Mesh::GetVertices(){ //Returns Vertices list
	return Vertices;
}

vector<cell> Mesh::GetCells(){ //Returns Cell list
	return Cells;
}

vector<Triangle> Mesh::GetTriangles(){ //Returns triangles list
	return Triangles;
}

void Mesh::CalcCircumcircle(int id){//Calculates the circumcircle for the Triangle with ID id

	vector<int> p = Triangles[id].getVertices();//GEt vertices IDs for triangle specified
	Triangles[id].Circumcircle(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]]); //Pass vertices to triangle check
}

//checks if the point XY is within a triangle and returns the ID of the triangle
int Mesh::isPointContained(double px,double py){
	bool result;
	for (int i(0);i<Triangles.size();i++){
		vector<int> p = Triangles[i].getVertices();
		result = Triangles[i].isPointInside(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]], px,py);
		if (result == true) return i;	//Returns the ID of the triangle its contained in
	}
	return -1;//Returns -1 if not contained in any triangle
}

double Mesh::TriangleArea(int id){ //USed for getting the triangles area

	//Gather area from loaded parameters 
	double RootArea = Triangles[id].getarea();
	if (RootArea != -1){
		return RootArea;
	}
	//Backup incase area parameter has not been imported successfully
	else{
		vector<int> p = Triangles[id].getVertices();
		p.clear();
		return(0.5 *(-Vertices[p[1]].gety()*Vertices[p[2]].getx() + Vertices[p[0]].gety()*(-Vertices[p[1]].getx() + Vertices[p[2]].getx()) + Vertices[p[0]].getx()*(Vertices[p[1]].gety() - Vertices[p[2]].gety()) + Vertices[p[1]].getx()*Vertices[p[2]].gety()));
	}
}

int Mesh::NumberVertices(void) { //Return amount of vertices loaded
	return Vertices.size();
}
int Mesh::NumberTriangles(void) {//triangles loaded returns

	return Triangles.size();
	
}

int Mesh::NumberCells(void) {//returns amount of cells loaded

	return Cells.size();
	
}

