cmake_minimum_required(VERSION 3.3 FATAL_ERROR) #Check for version 3.3 or above for cmake otherwise return an error
project( Mesh_Loader ) # Name of the project


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
add_library( mesh STATIC src/mesh.cpp )
add_library( triangle STATIC src/triangle.cpp )
add_library( matrix STATIC src/matrix.cpp )


#Link all the src files to the executable
add_executable(Mesh_Loader MACOSX_BUNDLE
  include/main.h
  include/cell.h
  include/mesh.h
  include/vector.h
  include/triangle.h
  include/matrix.h
  src/main.cpp
  ${UI_Srcs}
)

target_link_libraries( Mesh_Loader
								mesh
								vector
								cell
								triangle
								matrix
								)


