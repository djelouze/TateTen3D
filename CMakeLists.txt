PROJECT (TateTen3D)

### The following are needed to avoid warnings. See CMake doc. ######
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
#####################################################################

SET (LIBRARY_OUTPUT_PATH ${TateTen3D_BINARY_DIR}/bin
     CACHE 
     PATH
     "Single output directory for building all libraries.")

SET (EXECUTABLE_OUTPUT_PATH ${TateTen3D_BINARY_DIR}/bin
     CACHE
     PATH
     "Single output directory for building all executables.")
     

INCLUDE_DIRECTORIES (${LIBRARY_OUTPUT_PATH})
INCLUDE_DIRECTORIES (${EXECUTABLE_OUTPUT_PATH})
INCLUDE_DIRECTORIES (${TateTen3D_SOURCE_DIR}/Algorithms) 

MARK_AS_ADVANCED(
   LIBRARY_OUTPUT_PATH
   EXECUTABLE_OUTPUT_PATH
)

### Find VTK
INCLUDE (${CMAKE_ROOT}/Modules/FindVTK.cmake)
IF (USE_VTK_FILE)
  INCLUDE(${USE_VTK_FILE})
ENDIF (USE_VTK_FILE)


SUBDIRS(
   Algorithms
)

OPTION( BUILD_DOCUMENTATION 
        "Build Doxygen documentation"
        OFF )

OPTION( BUILD_TESTS 
        "Build tests"
        OFF )

OPTION( BUILD_TOOLS 
        "Build Tools"
        ON )

IF( BUILD_DOCUMENTATION )
   SUBDIRS(Documentation)
ENDIF( BUILD_DOCUMENTATION )

IF( BUILD_TESTS )
   SUBDIRS(Tests)
ENDIF( BUILD_TESTS )

IF( BUILD_TOOLS )
   SUBDIRS(Tools)
ENDIF( BUILD_TOOLS )

