# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Python CXX)

OPTION(WITH_PYTHON "Build Python Bindings" ON)
if (WITH_PYTHON)
    find_package(PythonLibs REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

link_directories(${PROJECT_SOURCE_DIR}/../lib)
include_directories(${PROJECT_SOURCE_DIR}/../lib/base)
include_directories(${PROJECT_SOURCE_DIR}/../lib/geant)

# add_library(mapt_python MAPT.cpp)
# target_link_libraries(mapt_analysis ${ROOT_LIBRARIES})
# 
# target_link_libraries(mapt_analysis MAPT GeantSim Fibers)

if (PYTHONLIBS_FOUND)
    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(DEPS        ${CMAKE_CURRENT_SOURCE_DIR}/mapt_python.pyx
                    ${CMAKE_CURRENT_SOURCE_DIR}/mgeanttrack.pyx
                    ${CMAKE_CURRENT_SOURCE_DIR}/mgeantfibersraw.pyx
                    ${CMAKE_CURRENT_SOURCE_DIR}/mfiberscal.pyx
                    ${CMAKE_CURRENT_SOURCE_DIR}/MAPT.cpp
                    )
    set(OUT         "${CMAKE_CURRENT_SOURCE_DIR}/mapt_python.cpp")

    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    add_custom_command(
        OUTPUT ${OUT}
        COMMAND python ${SETUP_PY} build_ext
        DEPENDS ${DEPS} ${SETUP_PY_IN}
    )

    add_custom_target(target ALL DEPENDS ${OUT})
    install(CODE "execute_process(COMMAND python ${SETUP_PY} install --prefix=\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX})")
endif()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
# install(TARGETS mapt_analysis DESTINATION bin)
