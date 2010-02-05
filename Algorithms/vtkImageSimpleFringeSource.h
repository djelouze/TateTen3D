
#ifndef __VTKIMAGEFRINGESOURCE_H__
#define __VTKIMAGEFRINGESOURCE_H__

#include <vtkImageSinusoidSource.h>

class VTK_IMAGING_EXPORT vtkImageSimpleFringeSource : public vtkImageSinusoidSource
{
public:
  static vtkImageSimpleFringeSource *New();
  vtkTypeRevisionMacro(vtkImageSimpleFringeSource,vtkImageSinusoidSource);

  void SetResolution(int xRes, int yRes );
  void SetHorizontal( );
  void SetVertical( );
  void SetPixelSize( double pixSize );

protected:
  vtkImageSimpleFringeSource();
  ~vtkImageSimpleFringeSource() {};

};


#endif



