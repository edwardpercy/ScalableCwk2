
#include "mesh.h"
#include <vector>
#include <cstring>
Mesh::Mesh() { //Model class constructor
	//LoadModel(FileName);
}
Mesh::~Mesh() {
	//Clears all the vector lists from memory
	Vertices.clear();
	Triangles.clear();
}

void Mesh::SaveMesh(string FileName) { //Loads the model
	std::ofstream file(FileName);
	file << Vertices.size() << " " << 3 << " " << 0;
	for (int i = 0;i < Vertices.size();i++){
		file << "\n" << i << " " << Vertices[i].getx() << " " << Vertices[i].gety() << " " << Vertices[i].getz();
	}
	file << "\n" << Triangles.size() << " " << 3 << " " << 17;

	for (int i = 0;i < Triangles.size();i++){
		vector<int> p = Triangles[i].getVertices();
		file << "\n" << i << " " << p[0] << " " << p[1] << " " << p[2] << " ";
		for (int j(0);j<17;j++){
			file << Triangles[i].getParam(j) << " ";
		}
			
	}
	file.close();
}


void Mesh::LoadMesh(string FileName) { //Loads the model
	bool LineInit = true;
	int id ,V1 ,V2 ,V3 ,LinesToInterate, NumCols, NumProperties = 0;
	double X,Y,Z;
	string parameters;

	ifstream file(FileName, ios::in);

	if (!file){
		cerr<<"File could not be opened"<<endl;
		exit(EXIT_FAILURE);
	}

	while(file>>LinesToInterate>>NumCols>>NumProperties) { 
		if (NumProperties==0){
			for (int i(0);i<LinesToInterate;i++){
				(file>>id>>X>>Y>>Z);
				Vector *V = new Vector; //Creates a new vector object
				V->SetVector(id,X,Y,Z); //Sends the data to the class function
				Vertices.push_back(*V); //Adds it to the vector list 
			}
		}
		else{
			for (int i(0);i<LinesToInterate;i++){
				(file>>id>>V1>>V2>>V3) && getline(file, parameters);	
				Triangle *T = new Triangle;
				
				T->setCell(id, parameters);
				T->setVertices(V1);
				T->setVertices(V2);
				T->setVertices(V3);
				
				Triangles.push_back(*T);
			}
		}
	}
	cout << "Number of triangles loaded: " << Triangles.size() << endl;
	cout << "Number of vertices loaded: " << Vertices.size() <<"\n" << endl;
	
	file.close();
}

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

int Mesh::CircumcirclesCheck(Vector point){
	int NumCircumcirclesContained = 0;
	bool inCircumcircle = false;


	for (int i(0);i<Triangles.size();i++){ 
		CalcCircumcircle(i); //Calculates the triangles circumcircle
		inCircumcircle = Triangles[i].isPointInCircumcircle(point.getx(),point.gety()); //Checks if the point is within circumcircle 
		vector<int> p = Triangles[i].getVertices();

		if (inCircumcircle == true && !Vertices[p[0]].equal(point) && !Vertices[p[1]].equal(point)  && !Vertices[p[2]].equal(point)){
			
			
			cout << "Point: " << point.getx() << "," << point.gety() << " within the circumcircle of triangle with ID: " << i << endl;
			NumCircumcirclesContained += 1;
		}
	}
	return NumCircumcirclesContained;
}

bool Mesh::DelaunayCheck(){
	bool isDelaunay = true;
	for (int i(0); i < Vertices.size(); i++){
		if (CircumcirclesCheck(Vertices[i]) > 0){
			cout << "Point ID "<< i << endl;
			isDelaunay = false;
		} 
	}
	if(isDelaunay == true) return true;
	else return false;
	

}

void Mesh::CalcCircumcircle(int id){

	vector<int> p = Triangles[id].getVertices();
	Triangles[id].Circumcircle(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]]);
}

int Mesh::isPointContained(double px,double py){
	bool result;
	for (int i(0);i<Triangles.size();i++){
		vector<int> p = Triangles[i].getVertices();
		result = Triangles[i].isPointInside(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]], px,py);
		if (result == true) return i;	
	}
	return -1;
}

double Mesh::TriangleArea(int id){

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

int Mesh::NumberVertices(void) {
	return Vertices.size();
}
int Mesh::NumberCells(void) {

	int output = Triangles.size();
	return output;
}

