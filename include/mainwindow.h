
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

	/** @file
	* This file is the mainwindoiw for Qt and contains most of the main functions   
	*/
	/** Brief description
	* Allows slots and other functions 
	*/

//Include Utility parameters
#include <array>
#include <vector>
#include <QTimer>

//Include Qt Header files
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QString>
#include <iostream>


//Include Vtk Header files
#include <vtkActor.h>

#include <vtkAxisActor.h>


#include <vtkAssembly.h>

#include <vtkSTLReader.h>


#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
//#include <QFileInfo.h>
#include <vtkPoints.h>


#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkGlyph3DMapper.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkGenericClip.h>
#include <vtkPropAssembly.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkRenderer.h>

//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>

#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkStringArray.h>
#include <vtkUnstructuredGrid.h>

//Type of the object
#include <vtkTetra.h>
#include <vtkPyramid.h>
#include <vtkHexahedron.h>

#include <vtkCubeSource.h>
#include <vtkSphereSource.h>


//Feature
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>
//#include <vtkContourFilter.h>

//Convert Point to Scalar
#include <vtkDoubleArray.h>
#include <vtkPointData.h>

//Other Header files
#include "model.h"//ModelLoader
#include "ui_mainwindow.h"

//Second Window header files
//#include "clipdialog.h"

#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Create global variables

    vector<int> NumCells;

    vtkSmartPointer<vtkRenderer> renderer;
    vector<vtkSmartPointer<vtkActor>> actors;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkHexahedron> hex ;
    vtkSmartPointer<vtkActor> actor;

    //Shrink
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter;
    vector<vtkSmartPointer<vtkShrinkFilter>> Shrinks;

    vtkSmartPointer<vtkUnstructuredGrid> uGrid;
    vector<vtkSmartPointer<vtkUnstructuredGrid>> uGrids;

    //Clip
    vtkSmartPointer<vtkPlane> planeLeft;
    vtkSmartPointer<vtkClipDataSet> clipFilter;
    vector<vtkSmartPointer<vtkClipDataSet>> ClipFilters;
    double ClipFactor;


    //Contour
//    vector<vtkSmartPointer<vtkContourFilter>> Contours;
//    int NumberofPieces;
//    double ContourLength;
//    vtkSmartPointer<vtkContourFilter> contourFilter;
//    vtkSmartPointer<vtkPlane> planeContour;


    //Light
    vtkSmartPointer<vtkLight> light;

     //Hana: clip filter
     vtkSmartPointer<vtkCubeSource> cubeSource;

    //Create Indicator
    int Indicator;
    int Cell_Iterations = 0;
    vector<float> Last_Colour = {0,0,0};

private slots:

    void on_actionModel_triggered(); //Colour model function
    void on_actionBackground_triggered(); //Colour of background function

    //-----------------Shrink Filter----------------------------
    void on_ShrinkFilter_sliderMoved();
    void on_Shrink_toggled(bool checked);
    //----------------------------------------------------------

    void on_ListView_activated(const QString &View); //Camera combo box
    void Load_STL_File(QString File);
    void Load_Mod_File(std::string FileName);

    //-------------------Clip Filter------------------------------
    void on_ClipFilterSlider_sliderMoved();
    void on_Clip_toggled(bool checked);
    void on_ReverseClip_clicked();
    void on_ClipSpinBox_valueChanged(double arg1);
    void on_ClipPosition_currentIndexChanged(const QString &arg1);
    //------------------------------------------------------------

    //-----------------Light-------------------------
    void on_Light_sliderMoved(int position);
    void on_LightradioButton_toggled(bool checked);
    //-----------------------------------------------

    void on_actionOpen_triggered();//Loading of model
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();

    //Contour
//    void on_Contour_toggled(bool checked);
//    void on_ContourLength_valueChanged(double arg1);
//    void on_ContourSpinBox_valueChanged(int arg1);
//    void on_ContourPosition_currentTextChanged(const QString &arg1);

    //----------------------Display------------------
    void on_Default_toggled(bool checked);
    void on_wireframe_toggled(bool checked);
    void on_vertices_toggled(bool checked);
    void on_OpacitySlider_sliderMoved(int position);
    //-----------------------------------------------



private:
    Ui::MainWindow *ui;
    vector<float> CellVertex;
    vector<int> CellVertices;
    vector<float> MatColour;
    vector<array<double, 3>> pointCoordinates;
    vector<array<double, 3>> CellColours;
    array<double, 3> SaveColour;
    Model M;
    string Opened_FileName;
    std::string Hexstring = "";

    //Clip Filter
    void ClipOperation();
    void ClipFunction();


    //Shrink Filter
    void ShrinkOperation();

    //Contour Filter
//    void ContourOperation();
//    void ContourFunction();

    //Display
    void WhatToDisplay();
};

#endif // MAINWINDOW_H
