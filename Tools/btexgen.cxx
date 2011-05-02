#include <vtkImageSimpleFringeSource.h>

#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageAppendComponents.h>
#include <vtkPNGWriter.h>

#include <cstdlib>
using namespace std;

int main(int argc, char* argv[] )
{
   
   int xRes = 256;
   int yRes = 256;
   double phase = 0;
   int dir = 0; // vertical
   int period = 16; // period of sinusoid in pixel
   if( argc < 2 )
   {
      cout << "usage: " << argv[0] 
                        << " output_file_name.jpg"
                        << " [ x_resolution{def-256}"
                        << " y_resolution{def-256}"
                        << " phase{0-cosine, pi/2-sine, def-0}"
                        << " direction{0-vertical, 1-horizontal, def-0}"
                        << " period{in pixel, def-16} ]"
                        << endl;
                        
      exit( 0 );
    }

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
       if( argc > 6 )
      {
         period = atoi( argv[6] );
      }
   }         

   cout << "Using parameters: " <<endl;
   cout << "\t Output file name: " << argv[1] << endl;
   cout << "\t xRes: " << xRes << endl;
   cout << "\t yRes: " << yRes << endl;
   cout << "\t phase: " << phase << endl;
   cout << "\t direction: " << (dir==0?"Vertical":"Horizontal") << endl;
   cout << "\t period: " << period << endl;

   vtkSmartPointer<vtkImageSimpleFringeSource> source = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );

   source->SetResolution( xRes, yRes );
   if( !dir )
      source->SetVertical( );
   else
      source->SetHorizontal( );
   source->SetPhase( phase );
   source->SetAmplitude( 127 );
   source->SetPeriod( period );
   source->Update( );

   vtkSmartPointer<vtkImageShiftScale> shift = vtkSmartPointer<vtkImageShiftScale>::New( );
   shift->SetInputConnection( source->GetOutputPort( ) );
   shift->SetShift( 127 );
   shift->SetOutputScalarTypeToUnsignedChar( );
   
   vtkSmartPointer<vtkImageAppendComponents> append = vtkSmartPointer<vtkImageAppendComponents>::New( );
   append->AddInputConnection( 0, shift->GetOutputPort( )); // R
   append->AddInputConnection( 0, shift->GetOutputPort( )); // G
   append->AddInputConnection( 0, shift->GetOutputPort( )); // B
   append->AddInputConnection( 0, shift->GetOutputPort( )); // A

   vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New( );
   writer->SetInputConnection( append->GetOutputPort( ) );
   writer->SetFileName( argv[1] );
   writer->Write( );
}
