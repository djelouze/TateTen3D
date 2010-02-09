

#ifndef __VTKIMAGETHREESTEPPHASESHIFTING_H__
#define __VTKIMAGETHREESTEPPHASESHIFTING_H__

#include "vtkThreadedImageAlgorithm.h"

class VTK_EXPORT vtkImageThreeStepPhaseShifting : public vtkThreadedImageAlgorithm
{
public:
  static vtkImageThreeStepPhaseShifting *New();
  vtkTypeRevisionMacro(vtkImageThreeStepPhaseShifting,vtkThreadedImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the two inputs to this filter
  virtual void SetInput1(vtkDataObject *in) { this->SetInput(0,in); }
  virtual void SetInput2(vtkDataObject *in) { this->SetInput(1,in); }
  virtual void SetInput3(vtkDataObject *in) { this->SetInput(2,in); }

protected:
  vtkImageThreeStepPhaseShifting();
  ~vtkImageThreeStepPhaseShifting() {};

  virtual int RequestInformation (vtkInformation *,
                                  vtkInformationVector **,
                                  vtkInformationVector *);

  virtual void ThreadedRequestData(vtkInformation *request,
                                   vtkInformationVector **inputVector,
                                   vtkInformationVector *outputVector,
                                   vtkImageData ***inData,
                                   vtkImageData **outData,
                                   int extent[6], int threadId);

  virtual int FillInputPortInformation(int port, vtkInformation* info);

private:
  vtkImageThreeStepPhaseShifting(const vtkImageThreeStepPhaseShifting&);  // Not implemented.
  void operator=(const vtkImageThreeStepPhaseShifting&);  // Not implemented.
};

#endif













