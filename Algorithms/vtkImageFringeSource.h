
#ifndef __VTKIMAGEFRINGESOURCE_H__
#define __VTKIMAGEFRINGESOURCE_H__

#include <vtkImageSinusoidSource.h>

class VTK_IMAGING_EXPORT vtkImageFringeSource : public vtkImageSinusoidSource
{
public:
  static vtkImageFringeSource *New();
  vtkTypeRevisionMacro(vtkImageFringeSource,vtkImageSinusoidSource);

  void SetResolution(int xRes, int yRes );
  void SetHorizontal( );
  void SetVertical( );
  void SetPixelSize( double pixSize );

protected:
  vtkImageFringeSource();
  ~vtkImageFringeSource() {};

};


#endif



