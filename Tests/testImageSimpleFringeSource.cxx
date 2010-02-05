#include <vtkImageSimpleFringeSource.h>

#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkBMPWriter.h>

#include <cstdlib>
using namespace std;

int main(int argc, char* argv[] )
{
   
   int xRes = 256;
   int yRes = 256;
   double phase = 0;
   int dir = 0; // vertical

   if( argc < 2 )
      exit( 0 );

   if( argc == 3)
   {
      xRes = atoi( argv[2] );
      yRes = atoi( argv[2] );
   }
   else if( argc > 3 )
   {
      xRes = atoi( argv[2] );
      yRes = atoi( argv[3] );
     
      if( argc > 4 )
      {
         phase = atof( argv[4] );
      }
      if( argc > 5 )
      {
         dir = atoi( argv[5] );
      }
   }         

   cout << "Using parameters: " <<endl;
   cout << "\t Output file name: " << argv[1] << endl;
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
   source->SetAmplitude( 127 );
   source->Update( );

   vtkSmartPointer<vtkImageShiftScale> shift = vtkSmartPointer<vtkImageShiftScale>::New( );
   shift->SetInputConnection( source->GetOutputPort( ) );
   shift->SetShift( 127 );
   shift->SetOutputScalarTypeToUnsignedChar( );
   
   vtkSmartPointer<vtkBMPWriter> writer = vtkSmartPointer<vtkBMPWriter>::New( );
   writer->SetInputConnection( shift->GetOutputPort( ) );
   writer->SetFileName( argv[1] );
   writer->Write( );
}
