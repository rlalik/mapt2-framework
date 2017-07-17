# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Analysis CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

link_directories(${PROJECT_SOURCE_DIR}/../lib)
include_directories(${PROJECT_SOURCE_DIR}/../lib/base)
include_directories(${PROJECT_SOURCE_DIR}/../lib/geant)


add_executable(analysis analysis.cc)
target_link_libraries(analysis ${ROOT_LIBRARIES})

target_link_libraries(analysis Event MAPT GeantSim)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS analysis DESTINATION bin)
