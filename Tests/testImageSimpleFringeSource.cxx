#include <vtkImageSimpleFringeSource.h>

#include <vtkSmartPointer.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>

#include <cstdlib>
using namespace std;

int main(int argc, char* argv[] )
{

   int xRes = 256;
   int yRes = 256;
   double phase = 0;
   int dir = 0; // vertical

   if( argc == 2)
   {
      xRes = atoi( argv[1] );
      yRes = atoi( argv[1] );
   }
   else if( argc > 2 )
   {
      xRes = atoi( argv[1] );
      yRes = atoi( argv[2] );
     
      if( argc > 3 )
      {
         phase = atof( argv[3] );
      }
      if( argc > 4 )
      {
         dir = atoi( argv[4] );
      }
   }         

   cout << "Using parameters: " <<endl;
   cout << "\t xRes: " << xRes << endl;
   cout << "\t yRes: " << yRes << endl;
   cout << "\t phase: " << phase << endl;
   cout << "\t direction: " << (dir==0?"Vertical":"Horizontal") << endl;

   vtkSmartPointer<vtkImageSimpleFringeSource> source = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );

   source->SetResolution( xRes, yRes );
   if( !dir )
      source->SetVertical( );
   else
      source->SetHorizontal( );
   source->SetPhase( phase );
   source->Update( );

   vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New( );
   viewer->SetInputConnection( source->GetOutputPort( ) );

   vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New( );
   viewer->SetupInteractor( iren );
   iren->Start( );
}
