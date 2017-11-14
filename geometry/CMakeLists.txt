# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(MAPT-Framework-Geometry)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" OFF)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

add_definitions("-g")

# CADMesh
find_package(cadmesh)
include_directories(${CADMESH_INCLUDE_DIRS})


# Root
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
set(LIBS ${LIBS} ${ROOT_LIBRARIES})


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



#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the libraries
#
add_library(Geometry SHARED ${sources})
target_link_libraries(Geometry ${Geant4_LIBRARIES})
target_link_libraries(Geometry ${cadmesh_LIBRARIES})
target_link_libraries(Geometry ${ROOT_LIBRARIES})
target_link_libraries(Geometry ${CGAL_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS Geometry DESTINATION ${CMAKE_INSTALL_LIBDIR})
