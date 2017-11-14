#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_NAME MAPT)

SET (LIBRARY_HDRS
    MMAPTManager.h
    MCategory.h
    MCategoryIndex.h
    MCategoryHeader.h
    MLocator.h
    MTaskManager.h
    MTask.h
    MDetectorManager.h
    MDetector.h
    MParManager.h
    MParContainer.h
    MPar.h
)

SET(LIBRARY_SRCS
    MMAPTManager.cc
    MCategory.cc
    MCategoryIndex.cc
    MCategoryHeader.cc
    MLocator.cc
    MTaskManager.cc
    MTask.cc
    MDetectorManager.cc
    MDetector.cc
    MParManager.cc
    MParContainer.cc
    MPar.cc
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

install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${LIBRARY_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the export set for use with the install-tree
install(TARGETS ${LIBRARY_NAME}
	EXPORT ${CMAKE_PROJECT_NAME}Targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT shlib COMPONENT dev)
