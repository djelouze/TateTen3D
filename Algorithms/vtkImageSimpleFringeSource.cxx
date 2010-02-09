#include <vtkImageSimpleFringeSource.h>

#include <vtkObjectFactory.h>

vtkCxxRevisionMacro(vtkImageSimpleFringeSource, "$Revision: 1.43 $");
vtkStandardNewMacro(vtkImageSimpleFringeSource);

//----------------------------------------------------------------------------
vtkImageSimpleFringeSource::vtkImageSimpleFringeSource()
{
   this->SetResolution( 256, 256 );
   this->SetVertical( );
   this->SetPeriod( 256 );

}


void vtkImageSimpleFringeSource::SetResolution( int xRes, int yRes)
{
   this->SetWholeExtent( 0, xRes-1,
                         0, yRes-1,
                         0, 0 );
}

void vtkImageSimpleFringeSource::SetHorizontal( )
{
   this->SetDirection( 0, 1, 0);
}

void vtkImageSimpleFringeSource::SetVertical( )
{
   this->SetDirection( 1, 0, 0);
}

void vtkImageSimpleFringeSource::SetPixelSize( double pixSize )
{
   // Not implemented
   //! \todo check how to access output spacing here.
}
