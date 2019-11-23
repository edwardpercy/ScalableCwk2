/** @file
* This file contains the QT slots and functions
*/
/** Brief description
* Allows the user to interact with the screen
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );
    this->setWindowTitle("ModelLoader");

    QTimer::singleShot(200, this, SLOT(showMaximized()));

    //Indicator Value at the beginning
    Indicator = 0;
    ClipFactor = 10.0;

    //Create the render window
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow; //New render window

    //Set Ui Connection

    ui->qtvtkWidget->SetRenderWindow( renderWindow );	 //Assign window to Qtwidget in mainwindow.ui
    renderer = vtkSmartPointer<vtkRenderer>::New(); //Create a smartpointer pointing to the window renderer
    ui->qtvtkWidget->GetRenderWindow()->AddRenderer( renderer );
    renderer->SetBackground(2.55,2.55,2.55);

    //**Hana: defining cube source for clip filter
    cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    //Create light on the screen
    light = vtkSmartPointer<vtkLight>::New();
    light->SetLightTypeToHeadlight();
    light->SetIntensity(1);

    planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(ClipFactor, 0.0, 0.0);
    planeLeft->SetNormal(-ClipFactor, 0.0, 0.0);

    clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    clipFilter->SetInputConnection(0, cubeSource->GetOutputPort() ) ;
    clipFilter->SetClipFunction( planeLeft.Get() );
    ClipFilters.push_back(clipFilter);

    shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkFilter->SetShrinkFactor(1);
    shrinkFilter->SetInputConnection(0, clipFilter->GetOutputPort(0));
    Shrinks.push_back(shrinkFilter);

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering

    //vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New(); //mapper is defined in the header file in private member variables
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( 0, shrinkFilter->GetOutputPort(0) );

    // Create an actor that is used to set the cube's properties for rendering and place it in the window
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );
    actors.push_back(actor);

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->AddLight(light);
    renderer->ResetCamera(); //Set the camera back to origin
    renderer->ResetCameraClippingRange();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//----------Clip Filter----------
//Slider
void MainWindow::on_ClipFilterSlider_sliderMoved(){
    ClipFunction();
}
//Reverse Button
void MainWindow::on_ReverseClip_clicked(){
    ClipFunction();
}
//Clip Range Spinbox
void MainWindow::on_ClipSpinBox_valueChanged(double arg1){
    ClipFunction();
}
//Perspective List
void MainWindow::on_ClipPosition_currentIndexChanged(const QString &arg1){
    ClipFunction();
}
//Apply Button
void MainWindow::on_Clip_toggled(bool checked){
    ClipFunction();
}

//Clip Functions
void MainWindow::ClipFunction(){
         for(int x = 0;x < ClipFilters.size();x++){
             ClipOperation();
             ClipFilters[x]->Update();
         }
    ui->qtvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::ClipOperation(){
    ClipFactor = ui->ClipSpinBox->value();
    if (ui->Clip->isChecked()) {
        if (ui->ReverseClip->isChecked()){
            if (ui->ClipPosition->currentText() == "X-Axis"){
                planeLeft->SetNormal(ClipFactor,0,0);
                planeLeft->SetOrigin(-(ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100),0,0);
            }
            else if (ui->ClipPosition->currentText() == "Y-Axis"){
                planeLeft->SetNormal(0,ClipFactor,0);
                planeLeft->SetOrigin(0,-(ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100),0);
            }
            else{
                planeLeft->SetNormal(0,0,ClipFactor);
                planeLeft->SetOrigin(0,0,-(ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100));
            }
        }
        else {
            if (ui->ClipPosition->currentText() == "X-Axis"){
                planeLeft->SetNormal(-ClipFactor,0,0);
                planeLeft->SetOrigin((ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100),0,0);
            }
            else if (ui->ClipPosition->currentText() == "Y-Axis"){
                planeLeft->SetNormal(0,-ClipFactor,0);
                planeLeft->SetOrigin(0,(ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100),0);
            }
            else{
                planeLeft->SetNormal(0,0,-ClipFactor);
                planeLeft->SetOrigin(0,0,(ClipFactor-2*ClipFactor*ui->ClipFilterSlider->value()/100));
            }
        }
     }
    else{
        if (Indicator == 1){
            planeLeft->SetOrigin(0,0,0);
            planeLeft->SetNormal(0,0,0);
        }
        else {
            if (ui->ClipPosition->currentText() == "X-Axis"){
                   planeLeft->SetOrigin(100,0,0);
                   planeLeft->SetNormal(-100,0,0);
            }
            else if (ui->ClipPosition->currentText() == "Y-Axis"){
                   planeLeft->SetOrigin(0,100,0);
                   planeLeft->SetNormal(0,-100,0);
            }
            else if (ui->ClipPosition->currentText() == "Z-Axis"){
                   planeLeft->SetOrigin(0,0,100);
                   planeLeft->SetNormal(0,0,-100);
            }

        }

    }
}
//------------------------------



//----------Shrink Filter----------
//Slider
void MainWindow::on_ShrinkFilter_sliderMoved()
{
    ShrinkOperation();
}
//Apply Button
void MainWindow::on_Shrink_toggled(bool checked){
    ShrinkOperation();
}

//Shrink Function
void MainWindow::ShrinkOperation(){
    if (ui->Shrink->isChecked()){
       for(int x = 0;x < Shrinks.size();x++){
             Shrinks[x]->SetShrinkFactor( (double) (100 - ui->ShrinkFilter->value())/ 100);
             Shrinks[x]->Update();
           }
     }
    else {

          for(int x = 0;x < Shrinks.size();x++){
                Shrinks[x]->SetShrinkFactor(1);
                Shrinks[x]->Update();
              }
        }
  ui->qtvtkWidget->GetRenderWindow()->Render();
}
//------------------------------



//----------Color Change----------
//Model
void MainWindow::on_actionModel_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if ( color.isValid() )
    {

        QString Hex = color.name();
        Hexstring = Hex.toUtf8().constData();
        Hexstring.substr(1);
        Hexstring.replace(0,1,"");


        for (int x=0; x < actors.size(); x++){
            actors[x]->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());
        }

        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
}

//Background
void MainWindow::on_actionBackground_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if ( color.isValid() )
    {
        renderer->SetBackground(color.redF(), color.greenF(), color.blueF());
    }
    ui->qtvtkWidget->GetRenderWindow()->Render();
}
//------------------------------



//----------Load Model----------
//Open
void MainWindow::on_actionOpen_triggered(){
    //Load the model
    QString File = QFileDialog::getOpenFileName(this, tr("Open MOD File"), "./../../Resource", tr("MODEL Files(*.mod *.stl)"));
    std::string FileName = File.toUtf8().constData();
    if (FileName != ""){
        QStringList partsList = File.split('.');
        QString suffix = partsList.at(1);
        std::string s = suffix.toUtf8().constData();

        actors.clear();
        ClipFilters.clear();
        Shrinks.clear();
        renderer->RemoveAllViewProps();
        if (s == "mod")
            Load_Mod_File(FileName); //Load the .mod file
        else
            Load_STL_File(File); //Load the .stl file
    }
    ui->qtvtkWidget->GetRenderWindow()->Render();
}

//Load STL Function
void MainWindow::Load_STL_File(QString File){
    if (ui->ClipPosition->currentText() == "X-Axis"){
           planeLeft->SetOrigin(100,0,0);
           planeLeft->SetNormal(-100,0,0);
    }
    else if (ui->ClipPosition->currentText() == "Y-Axis"){
           planeLeft->SetOrigin(0,100,0);
           planeLeft->SetNormal(0,-100,0);
    }
    else if (ui->ClipPosition->currentText() == "Z-Axis"){
           planeLeft->SetOrigin(0,0,100);
           planeLeft->SetNormal(0,0,-100);
    }

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(File.toLatin1().data());
    reader->Update();

    // Visualize
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    //Link the shrink filter into the grid
    shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkFilter->SetShrinkFactor(1);
    shrinkFilter->SetInputConnection(0, reader->GetOutputPort(0));
    Shrinks.push_back(shrinkFilter);

    clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    clipFilter->SetInputConnection( 0,shrinkFilter->GetOutputPort() ) ;
    clipFilter->SetClipFunction( planeLeft.Get() );
    ClipFilters.push_back(clipFilter);





    //Contour Filter
//    vtkSmartPointer<vtkDataSetMapper> Contourmapper = vtkSmartPointer<vtkDataSetMapper>::New();
//    ContourOperation();
//    contourFilter = vtkSmartPointer<vtkContourFilter>::New();
//    //contourFilter->ComputeScalarsOn();
//    contourFilter->GenerateValues(NumberofPieces*2,
//            .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[0],
//            .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[1]);
//    contourFilter->SetInputConnection(0,reader->GetOutputPort());
//    Contours.push_back(contourFilter);
//    Contourmapper->SetInputConnection(contourFilter->GetOutputPort(0));





    mapper->SetInputConnection( clipFilter->GetOutputPort() );

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    //Add contour actor
//    vtkSmartPointer<vtkActor> Contouractor = vtkSmartPointer<vtkActor>::New();
//    Contouractor->SetMapper(Contourmapper);//Link the contour actor to mapper
//    renderer->AddActor(Contouractor);//Add the Contour actor to window

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( 1.30,0.97,1.64 );
    renderer->AddActor(actor);
    actors.push_back(actor);

    renderer->ResetCamera(); //Set the camera back to origin
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    WhatToDisplay();
//    ui->qtvtkWidget->GetRenderWindow()->Render();
}

//Load Mod Function
void MainWindow::Load_Mod_File(std::string FileName){

    //INITIALISATIONS
    Hexstring = "";
    CellColours.clear();
    Indicator = 1; //Indicator for ModelLoader scenario
    renderer->RemoveAllViewProps();
    Cell_Iterations = 0;
    //Model M(FileName);
    M = Model();
    M.LoadModel(FileName);
    Opened_FileName = FileName;
    NumCells = M.NumberCells(); //Retrieves the number of cells for each shape


    //-------------LOAD HEXAHEDRONS--------------
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkUnstructuredGrid> uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    for (int H = 0; H < NumCells[2]; H++ ){ //Loops through each Cell
        CellVertices = M.GetCellVertices(H,"h"); //Gets the vertices and material colour for each cell
        MatColour = M.GetMaterialColour(M.GetCellMaterial(H, "h")); //Retrieve the colour data for the cell

        //Creates a new actor for each colour by checking if the colour for the cells has changed since the previous cell.
        if ((Last_Colour[0] != MatColour[0] || Last_Colour[1] != MatColour[1] || Last_Colour[2] != MatColour[2]) && H != 0){
            Cell_Iterations = H; //If a new colour has started the SetID for the hexagon must be offset back to zero so a reference point is used
            CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Store the colours for each actor for later use
            uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
            uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
            points = vtkSmartPointer<vtkPoints>::New(); //Creates a new smart pointer of points for storing the new cells
            uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New(); //Creates a new unstructured grid for the next actor
        }

        for (int V = 0; V < 8; V++){ //Push the Vector data for each cell. (Loops through each vector for that cell)
            CellVertex = M.GetVertices(CellVertices[V]); //Retrieve the cells vector
            points->InsertNextPoint(CellVertex[0], CellVertex[1], CellVertex[2]); //Store the vector as a point
        }

        vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();
        for (auto i = 0; i < 8; ++i) //Inserts the points into the smartpointers
            hex->GetPointIds()->SetId(i, ((8*(H-Cell_Iterations))+i));        // Create a hexahedron from the points.

        uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds()); //Insert the created cell into the grid
        Last_Colour = MatColour; //Set the last_colour reference to the current colour so it can be checked on the next loop
    }
        if (NumCells[2] > 0){
    //Send the final group of cells into an unstructured grid
    CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Send the colour of the actor to a vector for later use
    uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
    uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
    Cell_Iterations = 0;
        }
    //-------------------------------------------


    //-------------LOAD PYRAMIDS-----------------
    points = vtkSmartPointer<vtkPoints>::New();
    uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    for (int P = 0; P < NumCells[0]; P++ ){ //Loops through each Cell
        CellVertices = M.GetCellVertices(P,"p");
        MatColour = M.GetMaterialColour(M.GetCellMaterial(P, "p"));

        //Creates a new actor for each colour by checking if the colour for the cells has changed since the previous cell.
        if ((Last_Colour[0] != MatColour[0] || Last_Colour[1] != MatColour[1] || Last_Colour[2] != MatColour[2]) && P != 0){
            Cell_Iterations = P; //If a new colour has started the SetID for the hexagon must be offset back to zero so a reference point is used
            CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Store the colours for each actor for later use
            uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
            uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
            points = vtkSmartPointer<vtkPoints>::New(); //Creates a new smart pointer of points for storing the new cells
            uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New(); //Creates a new unstructured grid for the next actor
        }

        for (int V = 0; V < 5; V++){ //Push the Vector data for each cell. (Loops through each vector for that cell)
            CellVertex = M.GetVertices(CellVertices[V]); //Retrieve the cells vector
            points->InsertNextPoint(CellVertex[0], CellVertex[1], CellVertex[2]); //Store the vector as a point
        }

        vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
        for (auto i = 0; i < 5; ++i) //Inserts the points into the smartpointers
            pyramid->GetPointIds()->SetId(i, ((5*(P-Cell_Iterations))+i));        // Create a hexahedron from the points.

        vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
        cells->InsertNextCell (pyramid);

        uGrid->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds()); //Insert the created cell into the grid
        Last_Colour = MatColour; //Set the last_colour reference to the current colour so it can be checked on the next loop
    }
        if (NumCells[0] > 0){
    //Send the final group of cells into an unstructured grid
    CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Send the colour of the actor to a vector for later use
    uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
    uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
    Cell_Iterations = 0;
        }
    //-------------------------------------------


    //-------------LOAD TETRAHEDRONS-----------------
    points = vtkSmartPointer<vtkPoints>::New();
    uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    for (int T = 0; T < NumCells[1]; T++ ){
        CellVertices = M.GetCellVertices(T,"t");
        MatColour = M.GetMaterialColour(M.GetCellMaterial(T, "t"));

        //Creates a new actor for each colour by checking if the colour for the cells has changed since the previous cell.
        if ((Last_Colour[0] != MatColour[0] || Last_Colour[1] != MatColour[1] || Last_Colour[2] != MatColour[2]) && T != 0){
            Cell_Iterations = T; //If a new colour has started the SetID for the hexagon must be offset back to zero so a reference point is used
            CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Store the colours for each actor for later use
            uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
            uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
            points = vtkSmartPointer<vtkPoints>::New(); //Creates a new smart pointer of points for storing the new cells
            uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New(); //Creates a new unstructured grid for the next actor
        }

        for (int V = 0; V < 4; V++){ //Push the Vector data for each cell. (Loops through each vector for that cell)
            CellVertex = M.GetVertices(CellVertices[V]); //Retrieve the cells vector
            points->InsertNextPoint(CellVertex[0], CellVertex[1], CellVertex[2]); //Store the vector as a point
        }

        vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();
        for (auto i = 0; i < 4; ++i) //Inserts the points into the smartpointers
            tetra->GetPointIds()->SetId(i, ((4*(T-Cell_Iterations))+i));        // Create a hexahedron from the points.

        vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
        cells->InsertNextCell (tetra);

        uGrid->InsertNextCell(tetra->GetCellType(),tetra->GetPointIds()); //Insert the created cell into the grid
        Last_Colour = MatColour; //Set the last_colour reference to the current colour so it can be checked on the next loop
    }
        if (NumCells[1] > 0){
    //Send the final group of cells into an unstructured grid
    CellColours.push_back({Last_Colour[0],Last_Colour[1],Last_Colour[2]}); //Send the colour of the actor to a vector for later use
    uGrid->SetPoints(points); //Sets the points for the grouop of cells into an unstructured grid
    uGrids.push_back(uGrid); //Adds the unstructuredgrid to vector of grids for later rendering
    Cell_Iterations = 0;
        }
    //-------------------------------------------


    //-------------MAPPER -> FILTERS -> RENDER-----------------
    //Loop through the vector of unstructured grids to render them and link a mapper plus add filters

    for (int G=0;G<uGrids.size();G++){
        vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputData(uGrids[G]); //Create a mapper and send the grid as the inputted data

        //Link the shrink filter into the grid
        shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
        shrinkFilter->SetInputDataObject(0,uGrids[G]);
        shrinkFilter->SetShrinkFactor(1);
        //shrinkFilter->AddInputDataObject(0,uGrids[G]);
        Shrinks.push_back(shrinkFilter);

        clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
        clipFilter->SetInputConnection( 0,shrinkFilter->GetOutputPort(0) ) ;
        clipFilter->SetClipFunction( planeLeft.Get() );
        ClipFilters.push_back(clipFilter);




        //Contour Filter
//        vtkSmartPointer<vtkDataSetMapper> Contourmapper = vtkSmartPointer<vtkDataSetMapper>::New();
//        ContourOperation();
//        contourFilter = vtkSmartPointer<vtkContourFilter>::New();
//        //contourFilter->ComputeScalarsOn();
//        contourFilter->GenerateValues(NumberofPieces*2,
//                .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[0],
//                .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[1]);
//        contourFilter->SetInputDataObject(0,uGrids[G]);
//        Contours.push_back(contourFilter);
//        Contourmapper->SetInputConnection(contourFilter->GetOutputPort(0));





        mapper->SetInputConnection(clipFilter->GetOutputPort(0));

        //Add as an actor
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->GetProperty()->SetColor( CellColours[G][0]/100,CellColours[G][1]/100,CellColours[G][2]/100 ); //Set the colour of the actor
        actor->SetMapper(mapper); //Link the actor to a mapper
        renderer->AddActor(actor); //Add the actor to the render window
        actors.push_back(actor); //Put the actors into a vector of actors so they can be accessed later

        //Add an contour actor
//        vtkSmartPointer<vtkActor> Contouractor = vtkSmartPointer<vtkActor>::New();
//        Contouractor->SetMapper(Contourmapper);//Link the contour actor to mapper
//        renderer->AddActor(Contouractor);//Add the Contour actor to window

    }


    //Reset the render window
    renderer->ResetCamera(); //Set the camera back to origin
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    WhatToDisplay();
//    ui->qtvtkWidget->GetRenderWindow()->Render();


    ui->listWidget->clear();
    QString end = QString::number(M.NumberVertices());
    QString start = "Number of vertices: ";
    QString result = start + end;
    ui->listWidget->addItem(result);

    vector<int> NCells = M.NumberCells();
    for (int x = 0; x <3; x++){
    QString end = QString::number(NCells[x]);
    if (x == 0)
        start = "Number of Pyramids: ";
    else if (x == 1)
        start = "Number of Tetrahedrons: ";
    else
        start = "Number of Hexahedrons: ";
    QString result = start + end;
    ui->listWidget->addItem(result);
    }

    vector<float> Mcentre = M.FindCentre();
    start = "Centre of model: ";
    end = "X: " + QString::number(Mcentre[0]) + " Y: "+ QString::number(Mcentre[1]) +" Z: "+ QString::number(Mcentre[2]);
    result = start + end;
    ui->listWidget->addItem(result);


    CellVertex.clear();
    CellVertices.clear();
    MatColour.clear();
    pointCoordinates.clear();
    uGrids.clear();
}
//------------------------------



//----------Save Model----------
//Save
void MainWindow::on_actionSave_triggered(){

    if( Indicator == 1){
        M.SaveModel(Opened_FileName,Hexstring);
        cout << "saving" << endl;
    }

}
//Save As
void MainWindow::on_actionSave_as_triggered(){

    QString File = QFileDialog::getSaveFileName(this,tr("Save Model"), "",tr("Mod Files (*.mod);;All Files (*)"));

    std::string FileName = File.toUtf8().constData();
    if (FileName != ""){

        if( Indicator == 1){
            Opened_FileName = FileName;
            M.SaveModel(Opened_FileName,Hexstring);
            cout << "saving" << endl;
        }
    }

}
//------------------------------



//----------View Functions----------
//Perspective
void MainWindow::on_ListView_activated(const QString &View)
{
    if (View == "Left"){
        renderer->GetActiveCamera ()->SetPosition(1.0,0.0,0.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
    else if (View == "Right"){
        renderer->GetActiveCamera ()->SetPosition(-1.0,0.0,0.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
    else if (View == "Top") {
        renderer->GetActiveCamera ()->SetPosition(0.0,1.0,0.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
    else if (View == "Bottom") {
        renderer->GetActiveCamera ()->SetPosition(0.0,-1.0,0.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
    else if (View == "Front") {
        renderer->GetActiveCamera ()->SetPosition(0.0,0.0,-1.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
    else if (View == "Back") {
        renderer->GetActiveCamera ()->SetPosition(0.0,0.0,1.0);
        renderer->ResetCamera();
        ui->qtvtkWidget->GetRenderWindow()->Render();
    }
}

//Light
void MainWindow::on_Light_sliderMoved(int position){

    if (ui->LightradioButton->isChecked()){
      light->SetIntensity(1-(double) (position)/100);}

    else{
            light->SetIntensity( 1 );
    }
      ui->qtvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_LightradioButton_toggled(bool checked)
{
    if (checked){
        light->SetIntensity( 1- (double) (ui->Light->value())/100);}
    else{
            light->SetIntensity( 1 );
    }
    ui->qtvtkWidget->GetRenderWindow()->Render();
}
//------------------------------



//----------Contour Filter----------
//Apply Button
//void MainWindow::ContourOperation(){
//    ContourLength = ui->ContourLength->value();
//    NumberofPieces = ui->ContourSpinBox->value();
//    vtkSmartPointer<vtkPlane> planeContour = vtkSmartPointer<vtkPlane>::New();
//    if (ui->Contour->isChecked()){
//        if (ui->ContourPosition->currentText() == "X-Axis"){
//            planeContour->SetOrigin(ContourLength,0.0,0.0);
//            planeContour->SetNormal(-ContourLength,0.0,0.0);
//        }
//        else if (ui->ContourPosition->currentText() == "Y-Axis"){
//            planeContour->SetOrigin(0.0,ContourLength,0.0);
//            planeContour->SetNormal(0.0,-ContourLength,0.0);
//        }
//        else {
//            planeContour->SetOrigin(0.0,0.0,ContourLength);
//            planeContour->SetNormal(0.0,0.0,-ContourLength);
//        }
//    }
//    else {
//        planeContour->SetOrigin(0.0,0.0,0.0);
//        planeContour->SetNormal(0.0,0.0,0.0);
//    }

//    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
//    int numberOfPoints = shrinkFilter->GetUnstructuredGridInput(0)->GetNumberOfPoints();
//    scalars->SetNumberOfTuples(numberOfPoints);
//    vtkPoints *pts = shrinkFilter->GetUnstructuredGridInput(0)->GetPoints();
//    for (int i = 0; i < numberOfPoints; ++i)
//      {
//        double point[3];
//        pts->GetPoint(i, point);
//        scalars->SetTuple1(i, planeContour->EvaluateFunction(point));
//    }
//      shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->SetScalars(scalars);
//      shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange();
//}

//void MainWindow::ContourFunction(){
//    ContourOperation();
//    contourFilter->GenerateValues(NumberofPieces*2,
//            .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[0],
//            .99 * shrinkFilter->GetUnstructuredGridInput(0)->GetPointData()->GetScalars()->GetRange()[1]);
//    contourFilter->Update();
//    ui->qtvtkWidget->GetRenderWindow()->Render();
//}
//------------------------------


//----------Display Object-------------------------------------------
void MainWindow::on_Default_toggled(bool checked){
    WhatToDisplay();
}

void MainWindow::on_wireframe_toggled(bool checked){
    WhatToDisplay();
}

void MainWindow::on_vertices_toggled(bool checked){
    WhatToDisplay();
}

void MainWindow::WhatToDisplay(){
        if (ui->Default->isChecked()){
            for (int x=0; x < actors.size(); x++){
                actors[x]->GetProperty()->SetRepresentationToSurface();
                if (ui->OpacitySlider->value() <= 1){
                    actors[x]->GetProperty()->SetOpacity(1.0);
                }
                else {
                    actors[x]->GetProperty()->SetOpacity(1-(double)ui->OpacitySlider->value()/100);
                }
            }
        }
        else if (ui->wireframe->isChecked()){
            for (int x=0; x < actors.size(); x++){
                actors[x]->GetProperty()->SetRepresentationToWireframe();
            }
        }
        else if (ui->vertices->isChecked()){
            for (int x=0; x < actors.size(); x++){
                actors[x]->GetProperty()->SetRepresentationToPoints();
                actors[x]->GetProperty()->SetPointSize(5);
            }
        }
    ui->qtvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_OpacitySlider_sliderMoved(int position){
    WhatToDisplay();
}
//--------------------------------------------------------------------
