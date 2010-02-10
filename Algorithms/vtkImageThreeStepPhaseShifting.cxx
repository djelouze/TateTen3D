#include "vtkImageThreeStepPhaseShifting.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkMath.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <math.h>

vtkCxxRevisionMacro(vtkImageThreeStepPhaseShifting, "$Revision: 1.56 $");
vtkStandardNewMacro(vtkImageThreeStepPhaseShifting);

//----------------------------------------------------------------------------
vtkImageThreeStepPhaseShifting::vtkImageThreeStepPhaseShifting()
{
  this->SetNumberOfInputPorts(3);
}

//----------------------------------------------------------------------------
// The output extent is the intersection.
int vtkImageThreeStepPhaseShifting::RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  // get the info objects
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *inInfo2 = inputVector[1]->GetInformationObject(0);
  vtkInformation *inInfo3 = inputVector[2]->GetInformationObject(0);

  int ext[6], ext2[6], ext3[6], idx;

  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),ext);
  inInfo2->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),ext2);
  inInfo3->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),ext3);
  
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),ext,6);
  vtkDataObject::SetPointDataActiveScalarInfo(outInfo,
                                              VTK_DOUBLE,
                                              2);

  return 1;
}


//----------------------------------------------------------------------------
// This templated function executes the filter for any type of data.
// Handles the two input operations
template <class T>
void vtkImageThreeStepPhaseShiftingExecute2(vtkImageThreeStepPhaseShifting *self,
                                 vtkImageData *in1Data, T *in1Ptr,
                                 vtkImageData *in2Data, T *in2Ptr,
                                 vtkImageData *in3Data, T *in3Ptr,
                                 vtkImageData *outData, double *outPtr,
                                 int outExt[6], int id)
{
  int idxR, idxY, idxZ;
  int maxY, maxZ;
  vtkIdType inIncX, inIncY, inIncZ;
  vtkIdType in2IncX, in2IncY, in2IncZ;
  vtkIdType in3IncX, in3IncY, in3IncZ;
  vtkIdType outIncX, outIncY, outIncZ;
  int rowLength;
  unsigned long count = 0;
  unsigned long target;

  // find the region to loop over
  rowLength =
    (outExt[1] - outExt[0]+1)*in1Data->GetNumberOfScalarComponents();

  maxY = outExt[3] - outExt[2];
  maxZ = outExt[5] - outExt[4];
  target = static_cast<unsigned long>((maxZ+1)*(maxY+1)/50.0);
  target++;

  // Get increments to march through data
  in1Data->GetContinuousIncrements(outExt, inIncX, inIncY, inIncZ);
  in2Data->GetContinuousIncrements(outExt, in2IncX, in2IncY, in2IncZ);
  in3Data->GetContinuousIncrements(outExt, in3IncX, in3IncY, in3IncZ);
  outData->GetContinuousIncrements(outExt, outIncX, outIncY, outIncZ);

  // Loop through ouput pixels
  for (idxZ = 0; idxZ <= maxZ; idxZ++)
    {
    for (idxY = 0; !self->AbortExecute && idxY <= maxY; idxY++)
      {
      if (!id)
        {
        if (!(count%target))
          {
          self->UpdateProgress(count/(50.0*target));
          }
        count++;
        }
      for (idxR = 0; idxR < rowLength; idxR++)
        {
        T I1 = *in1Ptr;
        T I2 = *in2Ptr;
        T I3 = *in3Ptr;
        // Compute the phase
        double phase;
        if( I1 == I3 && I2 == I3 )
           phase = vtkMath::DoublePi();
        else
           phase = atan( (sqrt(3.)*(I1 - I3))/(2.*I2 - I1 -I3 ) );
        *outPtr = phase;
        outPtr++;
        // Compute the texture
        double texture = (I1+I2+I3 + sqrt(3.*pow(I1-I3,2)+pow(2.*I2-I1-I3,2)))/3.;
        *outPtr = texture;
        outPtr++;
        if( 0 )
           {
           cout << idxY << ";"
             << idxR << ";"
             << static_cast<double>(I1) << ";"
             << static_cast<double>(I2) << ";"
             << static_cast<double>(I3) << ";"
             << phase << ";"
             << texture << endl;
           }
        in1Ptr++;
        in2Ptr++;
        in3Ptr++;
        }
      outPtr += outIncY;
      in1Ptr += inIncY;
      in2Ptr += in2IncY;
      in3Ptr += in3IncY;
      }
    outPtr += outIncZ;
    in1Ptr += inIncZ;
    in2Ptr += in2IncZ;
    in3Ptr += in3IncZ;
    }
}


//----------------------------------------------------------------------------
// This method is passed a input and output datas, and executes the filter
// algorithm to fill the output from the inputs.
// It just executes a switch statement to call the correct function for
// the datas data types.
void vtkImageThreeStepPhaseShifting::ThreadedRequestData(
  vtkInformation * vtkNotUsed( request ),
  vtkInformationVector ** vtkNotUsed( inputVector ),
  vtkInformationVector * vtkNotUsed( outputVector ),
  vtkImageData ***inData,
  vtkImageData **outData,
  int outExt[6], int id)
{
  void *inPtr1;
  void *inPtr2;
  void *inPtr3;
  void *outPtr;


  inPtr1 = inData[0][0]->GetScalarPointerForExtent(outExt);
  inPtr2 = inData[1][0]->GetScalarPointerForExtent(outExt);
  inPtr3 = inData[2][0]->GetScalarPointerForExtent(outExt);

  outPtr = outData[0]->GetScalarPointerForExtent(outExt);

  switch (inData[0][0]->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImageThreeStepPhaseShiftingExecute2(this,inData[0][0],
                                  static_cast<VTK_TT *>(inPtr1),
                                  inData[1][0],
                                  static_cast<VTK_TT *>(inPtr2),
                                  inData[2][0],
                                  static_cast<VTK_TT *>(inPtr3),
                                  outData[0],
                                  static_cast<double*>(outPtr), outExt,
                                  id));
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }

}

//----------------------------------------------------------------------------
int vtkImageThreeStepPhaseShifting::FillInputPortInformation(
  int port, vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkImageData");
  return 1;
}

//----------------------------------------------------------------------------
void vtkImageThreeStepPhaseShifting::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

}

