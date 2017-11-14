# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Analysis CXX)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# CADMesh
find_package(cadmesh)
include_directories(${CADMESH_INCLUDE_DIRS})

# CGAL
find_package(CGAL)
if (CGAL_CONFIG_LOADED)
	if (CGAL_VERSION VERSION_LESS 4.1)
		message(SEND_ERROR "CGAL version 4.1 or newer not found!")
	endif()
	include_directories(${CGAL_INCLUDE_DIRS})
	include(${CGAL_USE_FILE})
	message(STATUS "CGAL version: " ${CGAL_VERSION})
else()
	message(SEND_ERROR "CGAL library not found!")
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

link_directories(${PROJECT_SOURCE_DIR}/../lib)
include_directories(${PROJECT_SOURCE_DIR}/../lib/base)
include_directories(${PROJECT_SOURCE_DIR}/../lib/geant)
include_directories(${PROJECT_SOURCE_DIR}/../lib/fibers_stack)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(particle_filter PFAnalysis.cc ${sources} ${headers})
target_link_libraries(particle_filter ${ROOT_LIBRARIES})

target_link_libraries(particle_filter MAPT GeantSim FibersStack Geometry)
target_link_libraries(particle_filter ${CGAL_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS particle_filter DESTINATION ${CMAKE_INSTALL_BINDIR})
