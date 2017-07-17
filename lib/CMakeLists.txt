#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_HDRS
    AnalysisData.h
    ParticlePF.hh
    Track.h
)

SET(LIBRARY_SRCS
    AnalysisData.cc
    ParticlePF.cc
    Track.cc
)

set(MODULES base geant)
include_directories(
    ${MODULES}
)

link_directories(
    ${MODULES}
)

ROOT_GENERATE_DICTIONARY(G__Event
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

add_library(Event SHARED
    ${LIBRARY_SRCS}
    G__Event.cxx
)

target_link_libraries(Event ${ROOT_LIBRARIES})

# install(TARGETS Event DESTINATION lib)
# install(FILES Event.h Track.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(FILES Category.hh GeantSim.h DESTINATION include)



add_subdirectory(base)
add_subdirectory(geant)
add_subdirectory(fibers)
