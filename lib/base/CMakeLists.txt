#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_NAME MAPT)

SET (LIBRARY_HDRS
    MCategory.h
    MDataManager.cc
)

SET(LIBRARY_SRCS
    MCategory.cc
    MDataManager.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR})

ROOT_GENERATE_DICTIONARY(G__${LIBRARY_NAME}
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

# ROOT_GENERATE_ROOTMAP(${LIBRARY_NAME} LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/Linkdef.h)

add_library(${LIBRARY_NAME} SHARED
    ${LIBRARY_SRCS}
    G__${LIBRARY_NAME}.cxx
)

target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
install(FILES ${LIBRARY_HDRS} DESTINATION include)
