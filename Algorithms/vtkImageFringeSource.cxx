#include <vtkImageFringeSource.h>

#include <vtkObjectFactory.h>

vtkCxxRevisionMacro(vtkImageFringeSource, "$Revision: 1.43 $");
vtkStandardNewMacro(vtkImageFringeSource);

//----------------------------------------------------------------------------
vtkImageFringeSource::vtkImageFringeSource()
{
}


void vtkImageFringeSource::SetResolution( int xRes, int yRes)
{
   this->SetWholeExtent( 0, xRes-1,
                         0, yRes-1,
                         0, 0 );
}

void vtkImageFringeSource::SetHorizontal( )
{
   this->SetDirection( 0, 1, 0);
}

void vtkImageFringeSource::SetVertical( )
{
   this->SetDirection( 1, 0, 0);
}

void vtkImageFringeSource::SetPixelSize( double pixSize )
{
   // Not implemented
   //! \todo check how to access output spacing here.
}
