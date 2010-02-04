
### Listing of the files used in VesselExtraction
FILE(GLOB SRC_TATETEN3D_ALGO *.cxx *.h)

### Defines VesselExtractionVTK lib an links
IF( WIN32 )
   ADD_LIBRARY( TateTen3DAlgo STATIC ${SRC_TATETEN3D_ALGO} )
ELSE( WIN32 )
   ADD_LIBRARY( TateTen3DAlgo SHARED ${SRC_TATETEN3D_ALGO} )
ENDIF( WIN32)

TARGET_LINK_LIBRARIES( TateTen3DAlgo vtkCommon vtkFiltering vtkImaging )

