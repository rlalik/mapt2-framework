#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_HDRS
    AnalysisData.h
    B1DetectorResponse.hh
    B1Particle.hh
    Category.hh
    DataManager.hh
    GeantSim.h
    Hits30x30.h
    ParticlePF.hh
    Track.h
)

SET(LIBRARY_SRCS
    AnalysisData.cc
    B1DetectorResponse.cc
    B1Particle.cc
    Category.cc
    DataManager.cc
    GeantSim.cc
    Hits30x30.cc
    ParticlePF.cc
    Track.cc
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(G__Event
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

add_library(Event SHARED
    ${LIBRARY_SRCS}
    G__Event.cxx
)

target_link_libraries(Event ${ROOT_LIBRARIES})

install(TARGETS Event DESTINATION lib)
# install(FILES Event.h Track.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES Category.hh GeantSim.h DESTINATION include)
