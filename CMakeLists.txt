cmake_minimum_required(VERSION 3.3 FATAL_ERROR) #Check for version 3.3 or above for cmake otherwise return an error
project( Model_Loader ) # Name of the project


foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

set( CMAKE_INCLUDE_CURRENT_DIR ON ) # Force CMake to use files in the current directory

include_directories( include ) # include all files from the /include directory


# output library name and File input for library
add_library( vector STATIC src/vector.cpp)
add_library( cell STATIC src/cell.cpp )
add_library( model STATIC src/model.cpp )
add_library( triangle STATIC src/triangle.cpp )


#Link all the src files to the executable
add_executable(Model_Loader MACOSX_BUNDLE
  include/main.h
  include/cell.h
  include/model.h
  include/vector.h
  include/triangle.h
  src/main.cpp
  ${UI_Srcs}
)

target_link_libraries( Model_Loader
								model
								vector
								cell
								triangle
								)


