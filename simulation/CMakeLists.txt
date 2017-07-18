#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Simulation CXX)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# CADMesh
find_package(cadmesh)
include_directories(${CADMESH_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


# Link directories for libEvent.so
link_directories(${PROJECT_SOURCE_DIR}/../lib)
include_directories(${PROJECT_SOURCE_DIR}/../lib/base)
include_directories(${PROJECT_SOURCE_DIR}/../lib/geant)

# Link directories for libgeometry.so
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../geometry/build)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../geometry/include)


#----------------------------------------------------------------------------
# Add the executable, and link it to the libraries
#
add_executable(mapt_simulation exampleB1.cc ${sources} ${headers})
target_link_libraries(mapt_simulation ${Geant4_LIBRARIES} ${cadmesh_LIBRARIES} ${ROOT_LIBRARIES} MAPT GeantSim Event Geometry)

add_subdirectory(example)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
# set(EXAMPLEB1_SCRIPTS
#   exampleB1.in
#   exampleB1.out
#   init_vis.mac
#   run1.mac
#   run2.mac
#   vis.mac
#   )
# 
# foreach(_script ${EXAMPLEB1_SCRIPTS})
#   configure_file(
#     ${PROJECT_SOURCE_DIR}/${_script}
#     ${PROJECT_BINARY_DIR}/${_script}
#     COPYONLY
#     )
# endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS mapt_simulation DESTINATION bin)
