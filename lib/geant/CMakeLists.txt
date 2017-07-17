#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_NAME GeantSim)

SET (LIBRARY_HDRS
    MGeantFibersRaw.h
    MGeantTrack.h
)

SET(LIBRARY_SRCS
    MGeantFibersRaw.cc
    MGeantTrack.cc
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ROOT_GENERATE_DICTIONARY(G__${LIBRARY_NAME}
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

# ROOT_GENERATE_ROOTMAP(${LIBRARY_NAME} LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/Linkdef.h)

add_library(GeantSim SHARED
    ${LIBRARY_SRCS}
    G__${LIBRARY_NAME}.cxx
)

target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
# install(FILES Event.h Track.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${LIBRARY_HDRS} DESTINATION include)
