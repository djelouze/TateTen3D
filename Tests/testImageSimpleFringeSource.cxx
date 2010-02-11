#include <vtkImageSimpleFringeSource.h>

#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageAppendComponents.h>
#include <vtkPNGWriter.h>

#include <cstdlib>
using namespace std;

int main(int argc, char* argv[] )
{
   

   vtkSmartPointer<vtkImageSimpleFringeSource> source;
   source = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );

   source->SetResolution( 256, 256 );
   source->SetVertical( );
   source->SetPhase( 0 );
   source->SetAmplitude( 127 );
   source->SetPeriod( 32 );

   // output range is [-127/2,127/2], but It has to be unsigned.
   //! \todo Add a 'SetMean' in vtkImageSimpleFringeSource
   vtkSmartPointer<vtkImageShiftScale> shift;
   shift = vtkSmartPointer<vtkImageShiftScale>::New( );
   shift->SetInputConnection( source->GetOutputPort( ) );
   shift->SetShift( 127 );
   shift->SetOutputScalarTypeToUnsignedChar( );
   
   vtkSmartPointer<vtkPNGWriter> writer;
   writer = vtkSmartPointer<vtkPNGWriter>::New( );
   writer->SetInputConnection( shift->GetOutputPort( ) );
   writer->SetFileName( "testImageSimpleFringeSource-output.png" );
   writer->Write( );
}
