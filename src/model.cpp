
#include "model.h"
#include <vector>
#include <cstring>
Model::Model() { //Model class constructor
	//LoadModel(FileName);
}
Model::~Model() {
	//Clears all the vector lists from memory
	Vertices.clear();
	Cells.clear();
	Triangles.clear();
}

void Model::LoadModel(string FileName) { //Loads the model
	string line, data;
	int LinesToInterate, NumCols, NumProperties= 0;
	bool LineInit = true;
	int LinePointer = 0; //Initialise variables
	int InputType = 0; //Initialise variables
	ifstream file;

	
	file.open(FileName); //Loads the model file 
	if (file.is_open()) { //Checks the file is open 
		while (getline(file, data)) { //Read each line and send data to classes

			if (data.empty() || line == "#") continue; //Checks if the data is empty or a comment (Ignore)

			if (LineInit == true){
				if (isdigit(data[0])==false) continue;
				//~~Reads thespecific data from the string using index~~
				istringstream iss(data);
				vector<std::string> results((std::istream_iterator<std::string>(iss)),istream_iterator<std::string>());

				LinesToInterate = stoi(results[0]);
				NumCols= stoi(results[1]);
				NumProperties = stoi(results[2]);
				InputType += 1; //Move to the next type of data (Vertices -> cells(Triangles))
				LineInit = false;
				std::cout << LinesToInterate << "  " << NumCols << "  " << NumProperties << std::endl;
				LinePointer = 0;
			}
			else if (LinePointer == LinesToInterate) {
				LineInit = true;
			}

			else{
				if (InputType == 0) SetVertices(data);
				else if (InputType == 1) SetCell(data,NumCols);
			}

			LinePointer++; //Increment current line
		}
		file.close(); // Close the file when finished
	}
	else {
		throw "Error opening file, use a compatible model file";
		exit(EXIT_FAILURE);

	}
		

}
void Model::SetCell(string data, int NumCols) {
	istringstream iss(data); //string stream to read characters in string
	vector<std::string> results((std::istream_iterator<std::string>(iss)), //Splits into characters
		istream_iterator<std::string>());

	int ID = stoi(results[0]); //Gather the ID from second value in results string


	
	if (NumCols == 3) {
		Triangle *T = new Triangle;
		T->setCell(ID, "Triangle");
		
		for (int i = 0; i < 3; i++) {		
			T->setVertices(stoi(results[i + 1]));
		}	
		Triangles.push_back(*T);
	}

	//Depending on the number of columns different shapes can be defined, eg - 4 could be square

}
void Model::SetVertices(string data) { //creates new vector objects then sends the data to the new vector class created above 
	istringstream iss(data);
	vector<std::string> results((std::istream_iterator<std::string>(iss)),istream_iterator<std::string>());

	float ID = stoi(results[0]);
	float X = stof(results[1]);
	float Y = stof(results[2]);
	float Z = stof(results[3]);	

	Vector *V = new Vector; //Creates a new vector object
	V->SetVector(ID,X,Y,Z); //Sends the data to the class function
	Vertices.push_back(*V); //Adds it to the vector list 
}
int Model::NumberVertices(void) {
	return Vertices.size();

}
int Model::NumberCells(void) {

	int output = Triangles.size();
	return output;
}

