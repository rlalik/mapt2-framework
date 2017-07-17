#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework CXX)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

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

add_definitions("-std=c++11")

# Root
find_package(ROOT QUIET REQUIRED COMPONENTS Core Cint)
include(RootNewMacros)
include_directories(${ROOT_INCLUDE_DIR})

# set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
# set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

if (DEFINED ROOT_USE_FILE)
include(${ROOT_USE_FILE})
endif()

add_custom_target(rlibmap)

#----------------------------------------------------------------------------
# Setup include directory for this project
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Link directories for libgeometry.so
link_directories(${PROJECT_SOURCE_DIR}/geometry/build)
include_directories(${PROJECT_SOURCE_DIR}/geometry/include)

#----------------------------------------------------------------------------
add_subdirectory(lib)
add_subdirectory(geometry)
add_subdirectory(simulation)
add_subdirectory(event_display)
add_subdirectory(analysis)

message("")
message("Add to your profile")
message("export PATH=${CMAKE_INSTALL_PREFIX}/bin:\$\{PATH\}")
message("export LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib:\$\{LD_LIBRARY_PATH\}")
message("")
