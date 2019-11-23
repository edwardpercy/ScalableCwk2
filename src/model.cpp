/** @file
* This file is the main model loader and has functionality to save
*/
/** Brief description
* Passes all of the model data to each of the respected classes 
*/
#include "model.h"
#include <vector>
#include <cstring>
Model::Model() { //Model class constructor
	//LoadModel(FileName);
}
Model::~Model() {
	//Clears all the vector lists from memory
	Vertices.clear();
	Materials.clear();
	Cells.clear();
	Pyramids.clear();
	Tetrahedrons.clear();
	Hexahedrons.clear();
}

void Model::SaveModel(string FileName,string Hexstring) {
        cout << "Saving to "<< FileName << endl;
        std::ofstream outfile(FileName);
        if (Hexstring == ""){
	//Write materials
	for (int m = 0; m < Materials.size(); m++) {
		outfile << "m " << Materials[m].getMatID() << " " << Materials[m].getDensity() << " " << Materials[m].getColour() << " " << Materials[m].getName() << endl;
	}
        }
        else{

            for (int m = 0; m < Materials.size(); m++) {
                    outfile << "m " << Materials[m].getMatID() << " " << Materials[m].getDensity() << " " << Hexstring << " " << Materials[m].getName() << endl;
            }
        }

	//Write Vectors
	for (int v = 0; v < Vertices.size(); v++) {
		outfile << "v " << Vertices[v].getID() << " " << Vertices[v].getx() << " " << Vertices[v].gety() << " " << Vertices[v].getz() << endl;
	}

	//Write Cells
	int size = Pyramids.size() + Tetrahedrons.size() + Hexahedrons.size();
	for (int c = 0; c < size; c++) {
		for (int p = 0; p < Pyramids.size(); p++) {
			if (Pyramids[p].getCellID() == c)
				outfile << "c " << Pyramids[p].getCellID() << " p " << Pyramids[p].getMaterialID() << " " << Pyramids[p].getVerticesID(0) << " " << Pyramids[p].getVerticesID(1) << " " << Pyramids[p].getVerticesID(2) << " " << Pyramids[p].getVerticesID(3) << " " << Pyramids[p].getVerticesID(4) << endl;
		}
		for (int h = 0; h < Hexahedrons.size(); h++) {
			if (Hexahedrons[h].getCellID() == c)
				outfile << "c " << Hexahedrons[h].getCellID() << " h " << Hexahedrons[h].getMaterialID() << " " << Hexahedrons[h].getVerticesID(0) << " " << Hexahedrons[h].getVerticesID(1) << " " << Hexahedrons[h].getVerticesID(2) << " " << Hexahedrons[h].getVerticesID(3) << " " << Hexahedrons[h].getVerticesID(4) << " " << Hexahedrons[h].getVerticesID(5) << " " << Hexahedrons[h].getVerticesID(6) << " " << Hexahedrons[h].getVerticesID(7) << endl;
		}
		for (int t = 0; t < Tetrahedrons.size(); t++) {
			if (Tetrahedrons[t].getCellID() == c)
				outfile << "c " << Tetrahedrons[t].getCellID() << " t " << Tetrahedrons[t].getMaterialID() << " " << Tetrahedrons[t].getVerticesID(0) << " " << Tetrahedrons[t].getVerticesID(1) << " " << Tetrahedrons[t].getVerticesID(2) << " " << Tetrahedrons[t].getVerticesID(3) << endl;
		}
	}
	
	cout << "Finished Saving to Model.mod" << endl;


}
void Model::LoadModel(string FileName) { //Loads the model
	string line, data;
	int LineNum = 0; //Initialise variables
	ifstream file;

	file.open(FileName); //Loads the model file 
	if (file.is_open()) { //Checks the file is open 
		while (getline(file, data)) { //Read each line and send data to classes
			LineNum++; //Increment current line
			line = data[0]; //First char for each line
	
			if (data.empty() || line == "#") continue; //Checks if the data is empty or a comment (Ignore)
			
			//If statement to check which type of data is being read
			if (line == "v")
				SetVertices(data); //Sends data to vector class
			else if (line == "m")
				SetMaterial(data); //Sends data to material class
			else if (line == "c")
				SetCell(data); //Sends data to cell class
			else
				throw "Unknown type: " + line + ". Fix model file"; //Unknown letter found
		}
		file.close(); // Close the file when finished
	}
	else {
		throw "Error opening file, use a compatible model file";
		exit(EXIT_FAILURE);

	}
		

}
void Model::SetCell(string data) {
	istringstream iss(data); //string stream to read characters in string
	vector<std::string> results((std::istream_iterator<std::string>(iss)), //Splits into characters
		istream_iterator<std::string>());

	int ID = stoi(results[1]); //Gather the ID from second value in results string
	string Type = results[2]; //Reads the corresponding char type from the string 
	int MaterialID = stoi(results[3]);

	//Checks to see which type of shape it is Hexahedron/Pyramid/Tetrahedron
	if (Type == "h") {
		Hexahedron *H = new Hexahedron; //Creates a new hexahedron object 
		H->setCell(ID, MaterialID, Type); //Sets the data for the new cell
		
		//Iterates through all vertices for the cell and sends them to the class
		for (int i = 0; i < 8; i++) {
			H->setVertices(stoi(results[i + 4])); //Set the vertex from the resulsts data stream 
		}
		Hexahedrons.push_back(*H); //Add this object to the vector array so it can be used in the future.
	} 
	else if (Type == "p") { //Shape type pyramid 
		Pyramid *P = new Pyramid;
		P->setCell(ID, MaterialID, Type); // Set the cell data 
		
		for (int i = 0; i < 5; i++) {	
			P->setVertices(stoi(results[i + 4]));
		}
		Pyramids.push_back(*P);//Stored the data into the vector array so it can be reference in the future
	}
	else if (Type == "t") { //Same as the if statemnets above but for the shape tetrahedron.
		Tetrahedron *T = new Tetrahedron;
		T->setCell(ID, MaterialID, Type);
		
		for (int i = 0; i < 4; i++) {		
			T->setVertices(stoi(results[i + 4]));
		}	
		Tetrahedrons.push_back(*T);
	}

}
void Model::SetVertices(string data) { //creates new vector objects then sends the data to the new vector class created above 

	//~~Reads thespecific data from the string using index~~
	istringstream iss(data);
	vector<std::string> results((std::istream_iterator<std::string>(iss)),
		istream_iterator<std::string>());
	int ID = stoi(results[1]);
	float X = stof(results[2]);
	float Y = stof(results[3]);
	float Z = stof(results[4]);

	Vector *V = new Vector; //Creates a new vector object
	V->SetVector(ID, X, Y, Z); //Sends the data to the class function
	Vertices.push_back(*V); //Adds it to the vector list 
}
void Model::SetMaterial(string data) {
	//Sends the data to a string stream so that it can be used to find the  data items for the class
	istringstream iss(data);
	vector<string> results((istream_iterator<string>(iss)),
		istream_iterator<string>());

	int ID = stoi(results[1]); //Uses index to find data such as ID within the line of data
	int Density = stoi(results[2]);
	string Name = results[4];
	string Colour = results[3];

	Material *M = new Material; //Creates the object and initialises it with the data 
	M->setMaterial(ID, Density, Colour, Name);
	Materials.push_back(*M);
}
int Model::GetCell(int ID, string Type) { //Used to get a specific cell
        if (Type == "p") { //Checks which type of shape it is
		if (ID <= Pyramids.size())
                        return Pyramids[ID].getCellID();
	}
	else if (Type == "t") {
		if (ID <= Tetrahedrons.size())
			return Tetrahedrons[ID].getCellID();

	}
	else if (Type == "h") {
                if (ID <= Hexahedrons.size())
                        return Hexahedrons[ID].getCellID();

	}
	else
		cout << "Type not Found" << endl;
		
}
vector<int>  Model::GetCellVertices(int ID, string Type) { //Used to get a specific cell
        if (Type == "p") { //Checks which type of shape it is
                if (ID <= Pyramids.size())
                        return Pyramids[ID].getVertices();
        }
        else if (Type == "t") {
                if (ID <= Tetrahedrons.size())
                        return Tetrahedrons[ID].getVertices();

        }
        else if (Type == "h") {
                if (ID <= Hexahedrons.size())
                        return Hexahedrons[ID].getVertices();

        }
        else
                cout << "Type not Found" << endl;

}
vector<float> Model::GetVertices(int ID) {
        V.clear();
        float x = Vertices[ID].getx(); //Gets the x,y and z for a vertex with an id of ID
        float y = Vertices[ID].gety();
        float z = Vertices[ID].getz();

	this->x = x; //Sets the variables to be used
	this->y = y;
	this->z = z;
        this->V.push_back(x);
        this->V.push_back(y);
        this->V.push_back(z);


        return V;

}
int Model::GetCellMaterial(int ID, string Type){
    if (Type == "p") { //Checks which type of shape it is
            return Pyramids[ID].getMaterialID();
    }
    else if (Type == "t") {
            return Tetrahedrons[ID].getMaterialID();

    }
    else if (Type == "h") {

        return Hexahedrons[ID].getMaterialID();
    }

}
vector<float> Model::GetMaterialColour(int ID) { //Gets the material data from the material class with id ID
        RGB.clear();
        string hex = Materials[ID].getColour();
        char *cstr = new char[hex.length() + 1];
        std::strcpy(cstr, hex.c_str());

        int r, g, b;
        sscanf(cstr, "%02x%02x%02x", &r, &g, &b);
        delete [] cstr;
        RGB.push_back(r);
        RGB.push_back(g);
        RGB.push_back(b);

        return RGB;
}
vector<float> Model::FindCentre(void) { //Finds the centre of the model 
	Vector sum;
	sum.SetVector(0,0.0, 0.0, 0.0);
	for (int Vertex = 0; Vertex < Vertices.size(); Vertex++) {
		sum = sum.operator+(Vertices[Vertex]); //Adds all the vectors together
	}
	
	sum = sum.divide((float)Vertices.size()); //Divides by the number of vectors
	vector<float> output = { sum.getx(),sum.gety(),sum.getz() };
	return output;


}
int Model::NumberVertices(void) {
	return Vertices.size();

}
vector<int> Model::NumberCells(void) {
	int NumP = Pyramids.size();
	int NumT = Tetrahedrons.size();
	int NumH = Hexahedrons.size();

	
	vector<int> output = { NumP,NumT,NumH };
	return output;
}
double Model::GetCellVolume(int ID) { //Get the volume of the cell
	Hexahedrons[ID].setV(Vertices); //Send the required vertices
	return Hexahedrons[ID].getvolume(); //Get volume
}
