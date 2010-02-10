#include <vtkImageThreeStepPhaseShifting.h>
#include <vtkImageSimpleFringeSource.h>

#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageMagnitude.h>
#include <vtkMetaImageWriter.h>
#include <vtkPNGWriter.h>
#include <vtkPNGReader.h>

#include <cstdlib>
using namespace std;

int main(int argc, char* argv[] )
{

   if( argc < 2 )
      {
      cout << "usage: testImageThreeStepPhaseShifting out.png [png1 png2 png3]" << endl;
      return( 0 );
      }


   vtkSmartPointer<vtkImageThreeStepPhaseShifting> tspsFilter = vtkSmartPointer<vtkImageThreeStepPhaseShifting>::New( );
   
   if( argc == 2 ) // Test with auto generated fringe image
      {
      double Pi = 3.141592654;

      vtkSmartPointer<vtkImageSimpleFringeSource> source1 = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );
      vtkSmartPointer<vtkImageSimpleFringeSource> source2 = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );
      vtkSmartPointer<vtkImageSimpleFringeSource> source3 = vtkSmartPointer<vtkImageSimpleFringeSource>::New( );

      source1->SetPhase( -2 * Pi / 3. );
      source1->SetAmplitude( 127 );
      source1->Update( );

      source2->SetPhase( 0 );
      source2->SetAmplitude( 127 );
      source2->Update( );

      source3->SetPhase( 2 * Pi / 3. );
      source3->SetAmplitude( 127 );
      source3->Update( );

      tspsFilter->SetInputConnection( 0, source1->GetOutputPort( ) );
      tspsFilter->SetInputConnection( 1, source2->GetOutputPort( ) );
      tspsFilter->SetInputConnection( 2, source3->GetOutputPort( ) );
      }

   else if( argc != 5 )
      {
      cout << "missing fringe image" << endl;
      return( 0 );
      }
   else
      {
      vtkSmartPointer<vtkPNGReader> source1 = vtkSmartPointer<vtkPNGReader>::New( );
      vtkSmartPointer<vtkPNGReader> source2 = vtkSmartPointer<vtkPNGReader>::New( );
      vtkSmartPointer<vtkPNGReader> source3 = vtkSmartPointer<vtkPNGReader>::New( );

      source1->SetFileName( argv[2] );
      source2->SetFileName( argv[3] );
      source3->SetFileName( argv[4] );

      vtkSmartPointer<vtkImageMagnitude> mag1 = vtkSmartPointer<vtkImageMagnitude>::New( );
      vtkSmartPointer<vtkImageMagnitude> mag2 = vtkSmartPointer<vtkImageMagnitude>::New( );
      vtkSmartPointer<vtkImageMagnitude> mag3 = vtkSmartPointer<vtkImageMagnitude>::New( );
      
      mag1->SetInputConnection( source1->GetOutputPort( ) );
      mag2->SetInputConnection( source2->GetOutputPort( ) );
      mag3->SetInputConnection( source3->GetOutputPort( ) );
      
      tspsFilter->SetInputConnection(0, mag1->GetOutputPort( ) );
      tspsFilter->SetInputConnection(1, mag2->GetOutputPort( ) );
      tspsFilter->SetInputConnection(2, mag3->GetOutputPort( ) );
      }


   vtkSmartPointer<vtkImageExtractComponents> extractPhase = vtkSmartPointer<vtkImageExtractComponents>::New( );
   extractPhase->SetInputConnection( tspsFilter->GetOutputPort( ) );
   extractPhase->SetComponents( 0 );
   extractPhase->Update( );

   vtkSmartPointer<vtkMetaImageWriter> writer = vtkSmartPointer<vtkMetaImageWriter>::New( );
//   vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New( );
   writer->SetInputConnection( extractPhase->GetOutputPort( ) );
   writer->SetFileName( argv[1] );
   writer->Write( );
}
