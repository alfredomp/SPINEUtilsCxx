


#include <iostream>


#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkCollectionIterator.h>

#include <SPINEContoursReader.h>
#include <spinecontoursinterpolation.h>

using namespace std;

int main(int argv, char** argc){

    vtkSmartPointer<SPINEContoursReader> sourcereader = vtkSmartPointer<SPINEContoursReader>::New();
    sourcereader->SetFileName(argc[1]);

    sourcereader->Update();

    vtkPolyDataCollection* contours = sourcereader->GetOutput();
    vtkCollectionSimpleIterator it;
    contours->InitTraversal(it);

    cout<<argc[1]<<"; ";

    for(unsigned i = 0; i < contours->GetNumberOfItems(); i++){

        if(i > 0){
            cout<<"; ";
        }

        vtkPolyData* nextpoly = contours->GetNextPolyData(it);

        vtkSmartPointer<SPINEContoursInterpolation> contourinterpolation = vtkSmartPointer<SPINEContoursInterpolation>::New();
        contourinterpolation->SetInputData(nextpoly);
        contourinterpolation->Update();
        cout<<contourinterpolation->GetArea();

    }
    cout<<endl;


    return EXIT_SUCCESS;

}

