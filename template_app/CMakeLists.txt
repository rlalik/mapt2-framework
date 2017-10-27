#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Template CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

add_definitions("-std=c++11")

find_package(ROOT REQUIRED COMPONENTS Core)
include_directories(${ROOT_INCLUDE_DIR})

find_package(MAPT QUIET COMPONENTS MAPT Fibers GeantSim)
if (MAPT_FOUND)
    include_directories(${MAPT_INCLUDE_DIR})
    link_directories(${MAPT_LIBRARY_DIR})
endif()

add_executable(template_app template_app.cpp)
target_link_libraries(template_app ${ROOT_LIBRARIES})

target_link_libraries(template_app MAPT GeantSim Fibers)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS template_app DESTINATION bin)
