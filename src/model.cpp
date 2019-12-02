
#include "model.h"
#include <vector>
#include <cstring>
Model::Model() { //Model class constructor
	//LoadModel(FileName);
}
Model::~Model() {
	//Clears all the vector lists from memory
	Vertices.clear();
	Triangles.clear();
}

void Model::LoadModel(string FileName) { //Loads the model
	bool LineInit = true;
	int id ,V1 ,V2 ,V3 ,LinesToInterate, NumCols, NumProperties = 0;
	float X,Y,Z;
	string parameters;

	ifstream file(FileName, ios::in);

	if (!file){
		cerr<<"File could not be opend"<<endl;
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
	
	
}

int Model::CircumcirclesCheck(double px,double py){
	int NumCircumcirclesContained = 0;
	bool inCircumcircle = false;
	int TriangleID = isPointContained(px,py);
	if (TriangleID == -1){
		cout << "Point: " << px << "," << py << " not within any triangle\n" << endl;
	}
	else{
		cout << "Point: " << px << "," << py << " within triangle: " << TriangleID << "\n" << endl;
		//START triangle ID used to search adjacent triangles HERE
		for (int i(0);i<Triangles.size();i++){ //Loops through all triangles 
											   //IF algorithm to find adjacent triangles was implemented we would
											   //Loop through only those here instead of all 

			CalcCircumcircle(i); //Calculates the triangles circumcircle
			inCircumcircle = Triangles[i].isPointInCircumcircle(px,py); //Checks if the point is within circumcircle 
			if (inCircumcircle == true){
				cout << "Point: " << px << "," << py << " within the circumcircle of triangle with ID: " << i << endl;
				NumCircumcirclesContained += 1;
			}
		}


	}
	return NumCircumcirclesContained;
}

void Model::DelaunayCheck(){
	for (int i(0); i <= Vertices.size(); i++){
		if (CircumcirclesCheck(Vertices[i].getx(),Vertices[i].gety()) > 1){
			cout << "Point in multiple Circumcircles, NON Delaunay" << endl;
		} 
		else{
			cout << "Delaunay Mesh" << endl;
		}
		//if in circumcircle is the point a member of the triangle 
	}

}

void Model::CalcCircumcircle(int id){

	vector<int> p = Triangles[id].getVertices();
	Triangles[id].Circumcircle(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]]);
}

int Model::isPointContained(double px,double py){
	bool result;
	for (int i(0);i<Triangles.size();i++){
		vector<int> p = Triangles[i].getVertices();
		result = Triangles[i].isPointInside(Vertices[p[0]],Vertices[p[1]],Vertices[p[2]], px,py);
		if (result == true) return i;	
	}
	return -1;
}

double Model::TriangleArea(int id){

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

int Model::NumberVertices(void) {
	return Vertices.size();

}
int Model::NumberCells(void) {

	int output = Triangles.size();
	return output;
}

