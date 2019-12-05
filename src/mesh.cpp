
#include "../include/mesh.h"
#include <vector>
#include <cstring>

Mesh::Mesh() { //Model class constructor
	//LoadMesh(FileName);
}
Mesh::Mesh(string FileName) { //Model class constructor
	LoadMesh(FileName);
}
Mesh::~Mesh() {
	//Clears all the vector lists from memory
	Vertices.clear();
	Triangles.clear();
}

Mesh::Mesh(const Mesh &m2) {
		Vertices = m2.Vertices;
		Cells = m2.Cells;
		Triangles = m2.Triangles;
		x = m2.x;
		y = m2.y;
		z = m2.z;
		V = m2.V;
	} 

void Mesh::SaveMesh(string FileName) { //Loads the model
	std::ofstream file(FileName.c_str());

	if (!file){
		throw("ERROR: Error saving to file");
	}

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
	int temp,id ,LinesToInterate, NumCols, NumProperties = 0;
	int iterator = 0;
    double X,Y,Z;
	vector<int> C_Vertices;
	string attributes;

	ifstream file(FileName.c_str(), ios::in);

	if (!file){
		throw("ERROR: File could not be opened");
	}
	

	while(file>>LinesToInterate>>NumCols>>NumProperties) { 
	
		if (iterator==0){
			for (int i(0);i<LinesToInterate;i++){
				if (NumCols == 2) (file>>id>>X>>Y) && getline(file, attributes);
				else if (NumCols == 3) (file>>id>>X>>Y>>Z) && getline(file, attributes);
				else throw "ERROR: Invalid dimensions entered";
				SetVertices(id,X,Y,Z,NumCols ,attributes);
				
			}
		}
		else{
			for (int i(0);i<LinesToInterate;i++){
				file>>id;
				for (int v_per_cell(0);v_per_cell < NumCols ;v_per_cell++){
					file>>temp;
					C_Vertices.push_back(temp);
				}
				getline(file, attributes);	
			
				if (NumCols == 3) SetTriangle(id,C_Vertices[0],C_Vertices[1],C_Vertices[2],attributes); //3 vertices is triangle 
				else throw("ERROR: 3 vertices shapes only supported currently");
				C_Vertices.clear();
				
			  //else if WRITE OTHER SHAPES HERE 
			  //else if (NumCols == 4) SetTetrahedron; (EXAMPLE)
			  //else if (NumCols == 8) SetHexahedron; (EXAMPLE for future code)
				
			}
		}
		iterator +=1;
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
			
			
			cout << "Point(" << point.getx() << "," << point.gety() << ") in circumcircle triangleID(" << i << ")    ";
			NumCircumcirclesContained += 1;
		}
	}
	return NumCircumcirclesContained;
}

bool Mesh::DelaunayCheck(){
	bool isDelaunay = true;
	for (int i(0); i < Vertices.size(); i++){
		if (CircumcirclesCheck(Vertices[i]) > 0){
			cout << "PointID: "<< i << endl;
			isDelaunay = false;
		}
	}
	cout << "\n";
	if(isDelaunay == true) return true;
	else return false;
	

}
void Mesh::SetVertices(int id,double X,double Y,double Z,int dimensions, string attributes){
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

void Mesh::SetTriangle(int id,double V1,double V2,double V3,string attributes){
	Triangle *T = new Triangle;
					
	T->setCell(id, attributes);
	T->setVertices(V1);
	T->setVertices(V2);
	T->setVertices(V3);

	Triangles.push_back(*T);
}

vector<Vector> Mesh::GetVertices(){
	return Vertices;
}

vector<cell> Mesh::GetCells(){
	return Cells;
}

vector<Triangle> Mesh::GetTriangles(){
	return Triangles;
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
int Mesh::NumberTriangles(void) {

	return Triangles.size();
	
}

int Mesh::NumberCells(void) {

	return Cells.size();
	
}

